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
#include "dogen.logical/types/entities/physical/backend.hpp"
#include "dogen.identification/types/helpers/logical_meta_name_factory.hpp"
#include "dogen.text/types/formatters/assistant.hpp"
#include "dogen.text/types/transforms/cpp/types/backend_class_header_transform_transform.hpp"
#include "dogen.text/types/transforms/cpp/types/backend_class_header_transform_factory.hpp"

namespace dogen::text::transforms::cpp::types {
namespace {

const std::string transform_id("text.transforms.types.backend_class_header_transform_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

const physical::entities::archetype& backend_class_header_transform_transform::static_archetype() {
    static auto r(backend_class_header_transform_factory::make());
    return r;
}

const physical::entities::archetype& backend_class_header_transform_transform::archetype() const {
    return static_archetype();
}

void backend_class_header_transform_transform::
apply(const text::transforms::context& ctx, const text::entities::model& lps,
    const logical::entities::element& e, physical::entities::artefact& a) const {
    tracing::scoped_transform_tracer stp(lg, "backend class header",
        transform_id, e.name().qualified().dot(), *ctx.tracer(), e);
    text::formatters::assistant ast(lps, e, a, true/*requires_header_guard*/);
    const auto& be(ast.as<logical::entities::physical::backend>(e));

    {
        auto sbf(ast.make_scoped_boilerplate_formatter(be));
        {
            const auto ns(ast.make_namespaces(be.name(),
                    false/*detect_model_name*/));
            auto snf(ast.make_scoped_namespace_formatter(ns));
ast.stream() << std::endl;
            ast.comment(be.documentation());
ast.stream() << "class " << be.name().simple() << "_backend_chain final {" << std::endl;
ast.stream() << "public:" << std::endl;
ast.stream() << "    // static const physical::entities::backend& static_backend();" << std::endl;
ast.stream() << "    // const physical::entities::backend& backend() const;" << std::endl;
ast.stream() << std::endl;
ast.stream() << "public:" << std::endl;
ast.stream() << "    // static void initialise(transforms::registrar& r);" << std::endl;
ast.stream() << "};" << std::endl;
        } // snf
ast.stream() << std::endl;
    } // sbf
    ast.update_artefact();
    stp.end_transform(a);
}

}
