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
#include <boost/make_shared.hpp>
#include <boost/algorithm/string/join.hpp>
#include "dogen.utility/types/formatters/sequence_formatter.hpp"
#include "dogen.identification/types/helpers/physical_meta_name_factory.hpp"
#include "dogen.identification/types/helpers/logical_meta_name_factory.hpp"
#include "dogen.logical/types/entities/visual_studio/solution.hpp"
#include "dogen.text/types/formatters/assistant.hpp"
#include "dogen.text/types/transforms/csharp/visual_studio/solution_transform.hpp"
#include "dogen.text/types/transforms/csharp/visual_studio/solution_factory.hpp"

namespace dogen::text::transforms::csharp::visual_studio {
namespace {

const std::string transform_id("text.transforms.visual_studio.solution_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

const physical::entities::archetype& solution_transform::static_archetype() {
    static auto r(solution_factory::make());
    return r;
}

const physical::entities::archetype& solution_transform::archetype() const {
    return static_archetype();
}

void solution_transform::
apply(const text::transforms::context& ctx, const text::entities::model& lps,
    const logical::entities::element& e, physical::entities::artefact& a) const {
    tracing::scoped_transform_tracer stp(lg, "solution",
        transform_id, e.name().qualified().dot(), *ctx.tracer(), e);

    text::formatters::assistant ast(lps, e, a, false/*requires_header_guard*/);
    using logical::entities::visual_studio::solution;
    const auto& sln(ast.as<solution>(e));
ast.stream() << "Microsoft Visual Studio Solution File, Format Version 12.00" << std::endl;
ast.stream() << "# Visual Studio 2012" << std::endl;
    for (const auto& ppb : sln.project_persistence_blocks()) {
ast.stream() << "Project(\"{" << ppb.type_guid() << "}\") = \"" << ppb.name() << "\", \"" << ppb.name() << ".csproj\", \"{" << ppb.guid() << "}\"" << std::endl;
ast.stream() << "EndProject" << std::endl;
    }
ast.stream() << "Global" << std::endl;
ast.stream() << "    GlobalSection(SolutionConfigurationPlatforms) = preSolution" << std::endl;
ast.stream() << "        Debug|Any CPU = Debug|Any CPU" << std::endl;
ast.stream() << "        Release|Any CPU = Release|Any CPU" << std::endl;
ast.stream() << "    EndGlobalSection" << std::endl;
ast.stream() << "    GlobalSection(ProjectConfigurationPlatforms) = postSolution" << std::endl;
    for (const auto& ppb : sln.project_persistence_blocks()) {
ast.stream() << "        {" << ppb.guid() << "}.Debug|Any CPU.ActiveCfg = Debug|Any CPU" << std::endl;
ast.stream() << "        {" << ppb.guid() << "}.Debug|Any CPU.Build.0 = Debug|Any CPU" << std::endl;
ast.stream() << "        {" << ppb.guid() << "}.Release|Any CPU.ActiveCfg = Release|Any CPU" << std::endl;
ast.stream() << "        {" << ppb.guid() << "}.Release|Any CPU.Build.0 = Release|Any CPU" << std::endl;
    }
ast.stream() << "    EndGlobalSection" << std::endl;
ast.stream() << "    GlobalSection(MonoDevelopProperties) = preSolution" << std::endl;
ast.stream() << "        StartupItem = CSharpModel.csproj" << std::endl;
ast.stream() << "    EndGlobalSection" << std::endl;
ast.stream() << "EndGlobal" << std::endl;
    ast.update_artefact();
    stp.end_transform(a);
}
}
