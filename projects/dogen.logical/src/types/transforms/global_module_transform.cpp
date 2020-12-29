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
#include <boost/make_shared.hpp>
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.variability/types/entities/configuration.hpp"
#include "dogen.identification/io/entities/logical_id_io.hpp"
#include "dogen.logical/io/entities/model_io.hpp"
#include "dogen.logical/types/entities/element.hpp"
#include "dogen.logical/types/entities/structural/object.hpp"
#include "dogen.logical/types/entities/structural/builtin.hpp"
#include "dogen.logical/types/entities/structural/visitor.hpp"
#include "dogen.logical/types/entities/structural/exception.hpp"
#include "dogen.logical/types/entities/structural/primitive.hpp"
#include "dogen.logical/types/entities/structural/enumeration.hpp"
#include "dogen.logical/types/entities/structural/object_template.hpp"
#include "dogen.identification/types/helpers/logical_name_builder.hpp"
#include "dogen.logical/types/transforms/transformation_error.hpp"
#include "dogen.logical/types/transforms/global_module_transform.hpp"

namespace {

const std::string transform_id("logical.transforms.global_module_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string global_module_doc("Module that represents the global scope.");
const std::string model_already_has_global_module(
    "Found a global module in model: ");

}

namespace dogen::logical::transforms {

using identification::entities::logical_name;
using identification::entities::model_type;

template<typename AssociativeContainerOfContainable>
inline void
add_containing_module_to_non_contained_entities(
    const logical_name& container_name, AssociativeContainerOfContainable& c) {
    for (auto& pair : c) {
        auto& s(*pair.second);
        if (s.contained_by().value().empty())
            s.contained_by(container_name.id());
    }
}

boost::shared_ptr<entities::structural::module>
global_module_transform::create_global_module(const model_type mt) {
    const std::string gm("global_module");
    const identification::entities::qualified_representations qr(gm, gm, gm);
    auto r(boost::make_shared<entities::structural::module>());
    r->name().qualified(qr);
    r->provenance().model_type(mt);
    r->documentation(global_module_doc);
    r->is_global_module(true);

    using identification::entities::technical_space;
    r->intrinsic_technical_space(technical_space::agnostic);

    using variability::entities::configuration;
    r->configuration(boost::make_shared<configuration>());
    r->configuration()->name().simple(gm);
    r->configuration()->name().qualified(qr.dot());

    return r;
}

logical_name
global_module_transform::inject_global_module(entities::model& m) {
    BOOST_LOG_SEV(lg, debug) << "Injecting global module for: "
                             <<m.name().id();

    const auto gm(create_global_module(m.provenance().model_type()));
    const auto r(gm->name());
    const auto i(m.structural_elements().modules().find(r.id()));
    if (i != m.structural_elements().modules().end()) {
        const auto id(m.name().id());
        BOOST_LOG_SEV(lg, error) << model_already_has_global_module << id;
        BOOST_THROW_EXCEPTION(transformation_error(
                model_already_has_global_module + id.value()));
    }
    m.structural_elements().modules().insert(std::make_pair(r.id(), gm));

    BOOST_LOG_SEV(lg, debug) << "Done injecting global module";
    return r;
}

void global_module_transform::update_element_containment(
    const logical_name& global_module_name, entities::model& m) {
    BOOST_LOG_SEV(lg, debug) << "Updating element containment.";

    const auto& gmn(global_module_name);
    add_containing_module_to_non_contained_entities(gmn,
        m.structural_elements().modules());
    add_containing_module_to_non_contained_entities(gmn,
        m.structural_elements().object_templates());
    add_containing_module_to_non_contained_entities(gmn,
        m.structural_elements().builtins());
    add_containing_module_to_non_contained_entities(gmn,
        m.structural_elements().enumerations());
    add_containing_module_to_non_contained_entities(gmn,
        m.structural_elements().objects());
    add_containing_module_to_non_contained_entities(gmn,
        m.structural_elements().exceptions());
    add_containing_module_to_non_contained_entities(gmn,
        m.structural_elements().visitors());
    add_containing_module_to_non_contained_entities(gmn,
        m.structural_elements().primitives());

    BOOST_LOG_SEV(lg, debug) << "Finished updating element containment.";
}

void global_module_transform::apply(const context& ctx, entities::model& m) {
    tracing::scoped_transform_tracer stp(lg, "containment",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);

    const auto gmn(inject_global_module(m));
    update_element_containment(gmn, m);

    stp.end_transform(m);
}

}
