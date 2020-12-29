/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
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
 *
 */
#ifndef DOGEN_PHYSICAL_TYPES_TRANSFORMS_LEGACY_PATHS_TRANSFORM_HPP
#define DOGEN_PHYSICAL_TYPES_TRANSFORMS_LEGACY_PATHS_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/filesystem/path.hpp>
#include "dogen.variability/types/entities/feature.hpp"
#include "dogen.variability/types/entities/configuration.hpp"
#include "dogen.variability/types/entities/feature_model.hpp"
#include "dogen.identification/types/entities/physical_meta_name_indices.hpp"
#include "dogen.identification/types/entities/logical_name.hpp"
#include "dogen.identification/types/entities/physical_meta_id.hpp"
#include "dogen.identification/types/entities/physical_meta_name.hpp"
#include "dogen.physical/types/entities/artefact.hpp"
#include "dogen.physical/types/entities/model.hpp"
#include "dogen.physical/types/transforms/context.hpp"
#include "dogen.physical/types/entities/legacy_archetype_kind.hpp"

namespace dogen::physical::transforms {

class locator;

/**
 * @brief Populates the include and full paths in artefacts.
 */
class legacy_paths_transform final {
private:
    struct archetype_feature_group {
        variability::entities::feature primary_inclusion_directive;
        variability::entities::feature secondary_inclusion_directive;
    };

    struct feature_group {
        variability::entities::feature inclusion_required;
        std::unordered_map<identification::entities::physical_meta_id,
                           archetype_feature_group>
        archetype_feature_groups;
    };

    static feature_group make_feature_group(
        const variability::entities::feature_model& fm,
        const identification::entities::physical_meta_name_indices& in);

    static bool make_top_level_inclusion_required(const feature_group& fg,
        const variability::entities::configuration& cfg);

    static boost::optional<entities::inclusion_directives>
    read_inclusion_directives(const feature_group& fg,
        const identification::entities::physical_meta_id& archetype,
        const variability::entities::configuration& cfg);

    static bool has_inclusion_directive_overrides(
        const variability::entities::configuration& cfg);

private:
    static std::string to_inclusion_directive(const boost::filesystem::path& p);

private:
    /**
     * @brief Returns the enumeration for the given archetype.
     */
    static entities::legacy_archetype_kind
    get_archetye_kind(const std::string& archetype_name, const bool is_tests);

    /**
     * @brief Returns the full path for a given archetype.
     */
    static boost::filesystem::path get_full_path_for_archetype(
        const identification::entities::logical_name& ln,
        const identification::entities::physical_meta_name& pmn,
        const locator& l);

private:
    static void process_artefact(const feature_group& fg,
        const locator& l, entities::artefact& a);

public:
    static void apply(const context& ctx, entities::model& m);
};

}

#endif
