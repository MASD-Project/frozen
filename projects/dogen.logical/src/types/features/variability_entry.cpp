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
#include "dogen.logical/types/features/variability_entry.hpp"
#include "dogen.variability/types/helpers/feature_selector.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"

namespace dogen::logical::features {
variability_entry::feature_group
variability_entry::make_feature_group(const dogen::variability::entities::feature_model& fm) {
    feature_group r;
    const dogen::variability::helpers::feature_selector s(fm);

    r.binding_point = s.get_by_name("masd.variability.binding_point");
    r.value = s.get_by_name("masd.variability.value");
    r.instantiation_domain_name = s.get_by_name("masd.variability.instantiation_domain_name");

    return r;
}

variability_entry::static_configuration variability_entry::make_static_configuration(
    const feature_group& fg,
    const dogen::variability::entities::configuration& cfg) {

    static_configuration r;
    const dogen::variability::helpers::configuration_selector s(cfg);
    if (s.has_configuration_point(fg.binding_point))
        r.binding_point = s.get_text_content(fg.binding_point);
    if (s.has_configuration_point(fg.value))
        r.value = s.get_text_collection_content(fg.value);
    if (s.has_configuration_point(fg.instantiation_domain_name))
        r.instantiation_domain_name = s.get_text_content(fg.instantiation_domain_name);
    return r;
}
}
