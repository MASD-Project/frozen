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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.text/types/transforms/cpp/odb/odb_factory.hpp"
#include "dogen.text/types/transforms/transformation_error.hpp"
#include "dogen.identification/io/entities/physical_meta_id_io.hpp"
#include "dogen.text/types/transforms/cpp/odb/enum_header_factory.hpp"
#include "dogen.text/types/transforms/cpp/odb/class_header_factory.hpp"
#include "dogen.text/types/transforms/cpp/odb/builtin_header_factory.hpp"
#include "dogen.text/types/transforms/cpp/odb/primitive_header_factory.hpp"
#include "dogen.identification/types/helpers/physical_meta_name_builder.hpp"
#include "dogen.text/types/transforms/cpp/odb/common_odb_options_factory.hpp"
#include "dogen.text/types/transforms/cpp/odb/object_odb_options_factory.hpp"
#include "dogen.text/types/transforms/cpp/odb/primitive_odb_options_factory.hpp"

namespace dogen::text::transforms::cpp::odb {
namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("dogen.text.transforms.cpp.odb"));

}

physical::entities::facet odb_factory::make() {
    identification::helpers::physical_meta_name_builder b;
    b.meta_model("masd");
    b.backend("cpp");
    b.facet("odb");

    physical::entities::facet r;
    r.meta_name(b.build());
    r.directory_name("odb");
    r.postfix("odb");

    const auto lambda([&](auto& container, const auto& element) {
        const auto id(element.meta_name().id());
        const auto pair(std::make_pair(id, element));
        const auto inserted(container.insert(pair).second);
        if (!inserted) {
            using text::transforms::transformation_error;
            const std::string duplicate_archetype("Duplicate id: ");
            BOOST_LOG_SEV(lg, error) << duplicate_archetype << id;
            BOOST_THROW_EXCEPTION(
                transformation_error(duplicate_archetype + id.value()));
        }
    });

    lambda(r.archetypes(), builtin_header_factory::make());
    lambda(r.archetypes(), class_header_factory::make());
    lambda(r.archetypes(), common_odb_options_factory::make());
    lambda(r.archetypes(), enum_header_factory::make());
    lambda(r.archetypes(), object_odb_options_factory::make());
    lambda(r.archetypes(), primitive_header_factory::make());
    lambda(r.archetypes(), primitive_odb_options_factory::make());

    return r;
}

}

