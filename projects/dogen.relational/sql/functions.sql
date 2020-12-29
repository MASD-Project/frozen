/* -*- sql-product: postgres; tab-width: 4; indent-tabs-mode: nil -*-
 *
 * Copyright (C) 2012-2019 Marco Craveiro <marco.craveiro@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

/**
 * Returns all of the runs available.
 * select * from runs();
 */
create or replace function runs()
    returns table("VERSION" text, "TIMESTAMP" timestamp,
        "RUN_ID" text, "ACTIVITY" text, "LOGGING_IMPACT" text, "TRACING_IMPACT"text)
as $$
    select "RUN_EVENT"."VERSION", "RUN_EVENT"."TIMESTAMP", "RUN_EVENT"."RUN_ID",
        "RUN_EVENT"."ACTIVITY", "RUN_EVENT"."LOGGING_IMPACT", "RUN_EVENT"."TRACING_IMPACT"
        from "RUN_EVENT"
        where "EVENT_TYPE" = 1
        order by "TIMESTAMP" desc;
$$ language 'sql';

/**
 * Returns details of the last run.
 */
create or replace function last_run()
    returns table("VERSION" text, "TIMESTAMP" timestamp,
        "RUN_ID" text, "LOGGING_IMPACT" text, "TRACING_IMPACT"text)
as $$
    select "RUN_EVENT"."VERSION", "RUN_EVENT"."TIMESTAMP", "RUN_EVENT"."RUN_ID",
        "RUN_EVENT"."LOGGING_IMPACT", "RUN_EVENT"."TRACING_IMPACT"
        from "RUN_EVENT"
        where "EVENT_TYPE" = 1
        order by "TIMESTAMP" desc limit 1;
$$ language 'sql';

/**
 * Returns the run_id of the last session.
 */
create or replace function last_run_id()
    returns text as $$
    select "RUN_ID" from last_run();
$$ language 'sql';

/**
 * Returns the top few lines of a log for a given run.
 */
create or replace function peek_log(in p_run_id text, in p_how_many int)
    returns setof "LOG_EVENT" as $$
    select *
    from "LOG_EVENT"
    where "RUN_ID" = p_run_id
    order by "TIMESTAMP" asc limit p_how_many;
$$ language 'sql';

/**
 * Returns the target file name used for a given run.
 */
create or replace function target_for_run()
    returns table("TIMESTAMP" timestamp, "RUN_ID" text, "FILE_NAME" text)
as $$
    select "TIMESTAMP", "RUN_ID",
        regexp_replace((substring("MESSAGE", 25)::jsonb->>2), '.+/', '')  "FILE_NAME"
    from "LOG_EVENT"
    where "COMPONENT" = 'main' and "SEVERITY" = 'INFO'
    order by "TIMESTAMP" asc;
$$ language 'sql';


/**
 * Returns the configuration for a given run.
 */
create or replace function configuration_for_run_id(in p_run_id text)
    returns setof TEXT
as $$
    select jsonb_pretty(substring("MESSAGE", 25)::jsonb)
    from "LOG_EVENT"
    where "COMPONENT" = 'main' and "SEVERITY" = 'INFO'
        and "RUN_ID" = p_run_id;
$$ language 'sql';

/**
 * All transforms for a given run.
 */
create or replace function transforms_for_run_id(in p_run_id text)
    returns table("TIMESTAMP" timestamp, "TRANSFORM_ID" text, "TRANSFORM_TYPE" text,
        "EVENT_TYPE" text, "PARENT_TRANSFORM" text, "TRANSFORM_INSTANCE_ID" text, "PAYLOAD" jsonb,
        "PAYLOAD_TYPE" text)
as $$
    select "TIMESTAMP", "TRANSFORM_ID", (CASE WHEN "TRANSFORM_TYPE" = 1 THEN  'CHAIN' ELSE 'LEAF' END) "TRANSFORM_TYPE",
        (CASE WHEN "EVENT_TYPE" = 1 THEN  'START' ELSE 'END' END) "EVENT_TYPE", "PARENT_TRANSFORM",
        "TRANSFORM_INSTANCE_ID", "PAYLOAD", "PAYLOAD"->>'__type__' "PAYLOAD_TYPE"
    from "TRANSFORM_EVENT"
    where "RUN_ID" = p_run_id
    order by "TIMESTAMP" asc;
$$ language 'sql';

/**
 * Deletes all data from all tables.
 */
create or replace function truncate_all_tables()
    returns void
as $$
    truncate "LOG_EVENT";
    truncate "RUN_EVENT";
    truncate "TRANSFORM_EVENT";
$$ language 'sql';

/**
* Get all objects in a dia diagram.
*/
create or replace function dia_objects_in_diagram(in p_transform_instance_id text)
    returns table("OBJECT" jsonb)
as $$
    select jsonb_array_elements(jsonb_array_elements("PAYLOAD"->'layers')->'objects') as object
    from "TRANSFORM_EVENT"
    where "TRANSFORM_INSTANCE_ID" = p_transform_instance_id
    and "EVENT_TYPE" = 1;
$$ language 'sql';

create or replace function dia_objects_with_attributes_in_diagram(in p_transform_instance_id text)
    returns table("ID" text, "TYPE" text, "ATTRIBUTES" jsonb)
as $$
    select
        objects."OBJECT"->>'id' "ID",
        objects."OBJECT"->>'type' "type",
        jsonb_array_elements(objects."OBJECT"->'attributes') "ATTRIBUTES"
    from (
        select * from dia_objects_in_diagram(p_transform_instance_id)
         ) as objects;
$$ language 'sql';

create or replace function classes_in_diagram(in p_transform_instance_id text)
    returns table("ID" text, "NAME" text)
as $$
    select "ID", substring(attrs."ATTRIBUTES"->'values'->0->'data'->>'value', 2,
            length(attrs."ATTRIBUTES"->'values'->0->'data'->>'value') - 2
        ) "NAME"
    from (
        select
            objects."OBJECT"->>'id' "ID",
            objects."OBJECT"->>'type' "TYPE",
            jsonb_array_elements(objects."OBJECT"->'attributes') "ATTRIBUTES"
            from (
                select * from dia_objects_in_diagram(p_transform_instance_id)
            ) as objects
     ) as attrs
     where
         attrs."ATTRIBUTES"->>'name' like 'name' and "TYPE" like 'UML - Class';
$$ language 'sql';

create or replace function dia_objects_names_and_stereotypes(in p_transform_instance_id text)
    returns table("ID" text, "NAME" text, "STEREOTYPES" text)
as $$
    select a."ID", a."NAME", b."STEREOTYPES"
    from (
        select "ID", substring("ATTRIBUTES"->'values'->0->'data'->>'value', 2,
            length("ATTRIBUTES"->'values'->0->'data'->>'value') - 2) "NAME"
        from
            dia_objects_with_attributes_in_diagram(p_transform_instance_id)
        where
            "ATTRIBUTES"->>'name' = 'name' and "TYPE" = 'UML - Class'
    ) a inner join (
        select "ID", substring("ATTRIBUTES"->'values'->0->'data'->>'value', 2,
            length("ATTRIBUTES"->'values'->0->'data'->>'value') - 2) "STEREOTYPES"
        from
            dia_objects_with_attributes_in_diagram(p_transform_instance_id)
        where
            "ATTRIBUTES"->>'name' = 'stereotype' and "TYPE" = 'UML - Class'
    ) b on a."ID" = b."ID";
$$ language 'sql';
