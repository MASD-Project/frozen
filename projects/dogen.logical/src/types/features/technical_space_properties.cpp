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
#include "dogen.variability/types/helpers/value_factory.hpp"
#include "dogen.variability/types/helpers/feature_selector.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"
#include "dogen.logical/types/features/technical_space_properties.hpp"

namespace dogen::logical::features {

namespace {

dogen::variability::entities::feature
make_masd_cpp_aspect_requires_manual_default_constructor() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("requires_manual_default_constructor");
    r.name().qualified("masd.cpp.aspect.requires_manual_default_constructor");
    r.description(R"(If true, the modeling element requires a manual defaul constructor.)");
    const auto vt(value_type::boolean);
    r.value_type(vt);
    r.binding_point(binding_point::element);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "false" }));
    return r;
}

dogen::variability::entities::feature
make_masd_cpp_aspect_requires_manual_move_constructor() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("requires_manual_move_constructor");
    r.name().qualified("masd.cpp.aspect.requires_manual_move_constructor");
    r.description(R"(If true, the modeling element requires a manual move constructor.)");
    const auto vt(value_type::boolean);
    r.value_type(vt);
    r.binding_point(binding_point::element);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "false" }));
    return r;
}

dogen::variability::entities::feature
make_masd_cpp_aspect_requires_stream_manipulators() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("requires_stream_manipulators");
    r.name().qualified("masd.cpp.aspect.requires_stream_manipulators");
    r.description(R"(If true, the modeling element requires stream manipulators.)");
    const auto vt(value_type::boolean);
    r.value_type(vt);
    r.binding_point(binding_point::element);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "false" }));
    return r;
}

}

technical_space_properties::feature_group
technical_space_properties::make_feature_group(const dogen::variability::entities::feature_model& fm) {
    feature_group r;
    const dogen::variability::helpers::feature_selector s(fm);

    r.requires_manual_default_constructor = s.get_by_name("masd.cpp.aspect.requires_manual_default_constructor");
    r.requires_manual_move_constructor = s.get_by_name("masd.cpp.aspect.requires_manual_move_constructor");
    r.requires_stream_manipulators = s.get_by_name("masd.cpp.aspect.requires_stream_manipulators");

    return r;
}

technical_space_properties::static_configuration technical_space_properties::make_static_configuration(
    const feature_group& fg,
    const dogen::variability::entities::configuration& cfg) {

    static_configuration r;
    const dogen::variability::helpers::configuration_selector s(cfg);
    r.requires_manual_default_constructor = s.get_boolean_content_or_default(fg.requires_manual_default_constructor);
    r.requires_manual_move_constructor = s.get_boolean_content_or_default(fg.requires_manual_move_constructor);
    r.requires_stream_manipulators = s.get_boolean_content_or_default(fg.requires_stream_manipulators);
    return r;
}

std::list<dogen::variability::entities::feature>
technical_space_properties::make_features() {
    using namespace dogen::variability::entities;
    std::list<dogen::variability::entities::feature> r;
    r.push_back(make_masd_cpp_aspect_requires_manual_default_constructor());
    r.push_back(make_masd_cpp_aspect_requires_manual_move_constructor());
    r.push_back(make_masd_cpp_aspect_requires_stream_manipulators());
    return r;
}

}
