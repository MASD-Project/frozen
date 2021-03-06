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
#include "dogen.utility/types/io/shared_ptr_io.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.logical/io/entities/element_io.hpp"
#include "dogen.physical/io/entities/artefact_io.hpp"
#include "dogen.identification/types/helpers/physical_meta_name_factory.hpp"
#include "dogen.logical/types/entities/structural/object.hpp"
#include "dogen.identification/types/helpers/logical_meta_name_factory.hpp"
#include "dogen.utility/types/formatters/sequence_formatter.hpp"
#include "dogen.text/types/formatters/assistant.hpp"
#include "dogen.text/types/transforms/csharp/io/class_transform.hpp"
#include "dogen.text/types/transforms/csharp/io/class_factory.hpp"

namespace dogen::text::transforms::csharp::io {
namespace {

const std::string transform_id("text.transforms.io.class_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

const physical::entities::archetype& class_transform::static_archetype() {
    static auto r(class_factory::make());
    return r;
}

const physical::entities::archetype& class_transform::archetype() const {
    return static_archetype();
}

void class_transform::
apply(const text::transforms::context& ctx, const text::entities::model& lps,
    const logical::entities::element& e, physical::entities::artefact& a) const {
    tracing::scoped_transform_tracer stp(lg, "class",
        transform_id, e.name().qualified().dot(), *ctx.tracer(), e);

    text::formatters::assistant ast(lps, e, a, false/*requires_header_guard*/);
    const auto& o(ast.as<logical::entities::structural::object>(e));
    {
        const auto sn(e.name().simple());
        const auto qn(ast.get_qualified_name(e.name()));
        auto sbf(ast.make_scoped_boilerplate_formatter(e));
        {
ast.stream() << "using System;" << std::endl;
ast.stream() << std::endl;
            const auto ns(ast.make_namespaces(e.name()));
            auto snf(ast.make_scoped_namespace_formatter(ns));
            const bool has_attributes(!o.local_attributes().empty());
ast.stream() << "    /// <summary>" << std::endl;
ast.stream() << "    /// Generates sequences of " << sn << "." << std::endl;
ast.stream() << "    /// </summary>" << std::endl;
ast.stream() << "    public static class " << sn << "Dumper" << std::endl;
ast.stream() << "    {" << std::endl;
ast.stream() << "        static internal void Dump(AssistantDumper assistant, " << sn << " value, bool withSeparator = false)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            assistant.IncrementDepth();" << std::endl;
ast.stream() << "            if (assistant.MaximumDepthExceeded())" << std::endl;
ast.stream() << "                return;" << std::endl;
ast.stream() << std::endl;
ast.stream() << "            assistant.AddStartObject();" << std::endl;
ast.stream() << "            assistant.AddType(\"" << qn << "\", true/*withSeparator*/);" << std::endl;
ast.stream() << "            if (value == null)" << std::endl;
ast.stream() << "            {" << std::endl;
ast.stream() << "                assistant.Add(\"data\", \"<null>\");" << std::endl;
ast.stream() << "                assistant.AddEndObject();" << std::endl;
ast.stream() << "                return;" << std::endl;
ast.stream() << "            }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "            assistant.AddKey(\"data\");" << std::endl;
ast.stream() << "            assistant.AddPairSeparator();" << std::endl;
ast.stream() << "            assistant.AddStartObject();" << std::endl;
                if (!o.parents().empty()) {
                    const auto& pn(o.parents().front());
                    const auto pqn(ast.get_qualified_name(pn));
ast.stream() << "            assistant.AddKey(\"__parent_0__\");" << std::endl;
ast.stream() << "            assistant.AddPairSeparator();" << std::endl;
ast.stream() << "            " << pqn << "Dumper.Dump(assistant, value" << (has_attributes ? ", true/*withSeparator*/" : "") << ");" << std::endl;
                }

                utility::formatters::sequence_formatter sf(o.local_attributes().size());
                sf.element_separator("");
                sf.postfix_configuration().not_last(", true/*withSeparator*/");
                sf.postfix_configuration().last("");

                for (const auto& attr : o.local_attributes()) {
                    const auto oap(ast.get_assistant_properties(attr));
                    if (oap && oap->requires_assistance()) {
ast.stream() << "            assistant.Add(\"" << attr.name().simple() << "\", value." << attr.name().simple() << sf.postfix() << ");" << std::endl;
                    } else {
                        const auto attr_qn(ast.get_qualified_name(attr.parsed_type().current()));
ast.stream() << "            assistant.AddKey(\"" << attr.name().simple() << "\");" << std::endl;
ast.stream() << "            assistant.AddPairSeparator();" << std::endl;
ast.stream() << "            " << attr_qn << "Dumper.Dump(assistant, value." << attr.name().simple() << sf.postfix() << ");" << std::endl;
                    }

                    sf.next();
                }
ast.stream() << "            assistant.AddEndObject(); // data" << std::endl;
ast.stream() << "            assistant.AddEndObject(); // main object" << std::endl;
ast.stream() << "            assistant.HandleMemberSeparator(withSeparator);" << std::endl;
ast.stream() << std::endl;
ast.stream() << "            assistant.DecrementDepth();" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        public static string Dump(" << sn << " value)" << std::endl;
ast.stream() << "        {" << std::endl;
                if (o.is_parent()) {
ast.stream() << "            return value.Dump();" << std::endl;
                } else {
ast.stream() << "            var assistant = new AssistantDumper();" << std::endl;
ast.stream() << "            Dump(assistant, value);" << std::endl;
ast.stream() << "            return assistant.ToString();" << std::endl;
                }
ast.stream() << "        }" << std::endl;
ast.stream() << "    }" << std::endl;
        }
    } // sbf

    ast.update_artefact();
    stp.end_transform(a);
}
}
