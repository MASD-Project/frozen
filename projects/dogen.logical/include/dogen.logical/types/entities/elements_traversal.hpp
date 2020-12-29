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
#ifndef DOGEN_LOGICAL_TYPES_ENTITIES_ELEMENTS_TRAVERSAL_HPP
#define DOGEN_LOGICAL_TYPES_ENTITIES_ELEMENTS_TRAVERSAL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen.logical/types/entities/model.hpp"
#include "dogen.logical/types/entities/structural/object.hpp"
#include "dogen.logical/types/entities/structural/enumeration.hpp"
#include "dogen.logical/types/entities/structural/primitive.hpp"
#include "dogen.logical/types/entities/structural/builtin.hpp"
#include "dogen.logical/types/entities/structural/exception.hpp"
#include "dogen.logical/types/entities/structural/visitor.hpp"
#include "dogen.logical/types/entities/structural/module.hpp"
#include "dogen.logical/types/entities/structural/object_template.hpp"
#include "dogen.logical/types/entities/structural/entry_point.hpp"
#include "dogen.logical/types/entities/structural/assistant.hpp"
#include "dogen.logical/types/entities/decoration/licence.hpp"
#include "dogen.logical/types/entities/decoration/modeline.hpp"
#include "dogen.logical/types/entities/decoration/modeline_group.hpp"
#include "dogen.logical/types/entities/decoration/generation_marker.hpp"
#include "dogen.logical/types/entities/variability/profile.hpp"
#include "dogen.logical/types/entities/variability/profile_template.hpp"
#include "dogen.logical/types/entities/variability/feature_template_bundle.hpp"
#include "dogen.logical/types/entities/variability/feature_bundle.hpp"
#include "dogen.logical/types/entities/variability/initializer.hpp"
#include "dogen.logical/types/entities/templating/logic_less_template.hpp"
#include "dogen.logical/types/entities/serialization/type_registrar.hpp"
#include "dogen.logical/types/entities/visual_studio/solution.hpp"
#include "dogen.logical/types/entities/visual_studio/project.hpp"
#include "dogen.logical/types/entities/visual_studio/msbuild_targets.hpp"
#include "dogen.logical/types/entities/orm/common_odb_options.hpp"
#include "dogen.logical/types/entities/build/cmakelists.hpp"
#include "dogen.logical/types/entities/physical/backend.hpp"
#include "dogen.logical/types/entities/physical/facet.hpp"
#include "dogen.logical/types/entities/physical/archetype.hpp"
#include "dogen.logical/types/entities/physical/archetype_kind.hpp"
#include "dogen.logical/types/entities/physical/part.hpp"
#include "dogen.logical/types/entities/physical/helper.hpp"

namespace dogen::logical::entities {

/**
 * @brief Performs a traversal across all elements in an intermediate
 * model.
 */
/**@{*/
template<typename TraversalVisitor>
inline void elements_traversal(const entities::model& m,
    const TraversalVisitor& v) {
    for (const auto& pair : m.structural_elements().modules())
        v(*pair.second);

    for (const auto& pair : m.structural_elements().object_templates())
        v(*pair.second);

    for (const auto& pair : m.structural_elements().builtins())
        v(*pair.second);

    for (const auto& pair : m.structural_elements().enumerations())
        v(*pair.second);

    for (const auto& pair : m.structural_elements().primitives())
        v(*pair.second);

    for (const auto& pair : m.structural_elements().objects())
        v(*pair.second);

    for (const auto& pair : m.structural_elements().exceptions())
        v(*pair.second);

    for (const auto& pair : m.structural_elements().visitors())
        v(*pair.second);

    for (const auto& pair : m.structural_elements().assistants())
        v(*pair.second);

    for (const auto& pair : m.decoration_elements().licences())
        v(*pair.second);

    for (const auto& pair : m.decoration_elements().modelines())
        v(*pair.second);

    for (const auto& pair : m.decoration_elements().modeline_groups())
        v(*pair.second);

    for (const auto& pair : m.decoration_elements().generation_markers())
        v(*pair.second);

    for (const auto& pair : m.variability_elements().profiles())
        v(*pair.second);

    for (const auto& pair : m.variability_elements().profile_templates())
        v(*pair.second);

    for (const auto& pair : m.variability_elements().feature_template_bundles())
        v(*pair.second);

    for (const auto& pair : m.variability_elements().feature_bundles())
        v(*pair.second);

    if (m.variability_elements().initializer())
        v(*m.variability_elements().initializer());

    for (const auto& pair : m.templating_elements().logic_less_templates())
        v(*pair.second);

    for (const auto& pair : m.serialization_elements().type_registrars())
        v(*pair.second);

    for (const auto& pair : m.visual_studio_elements().solutions())
        v(*pair.second);

    for (const auto& pair : m.visual_studio_elements().projects())
        v(*pair.second);

    for (const auto& pair : m.structural_elements().entry_points())
        v(*pair.second);

    for (const auto& pair : m.orm_elements().common_odb_options())
        v(*pair.second);

    for (const auto& pair : m.visual_studio_elements().msbuild_targets())
        v(*pair.second);

    for (const auto& pair : m.build_elements().cmakelists())
        v(*pair.second);

    for (const auto& pair : m.physical_elements().backends())
        v(*pair.second);

    for (const auto& pair : m.physical_elements().facets())
        v(*pair.second);

    for (const auto& pair : m.physical_elements().archetypes())
        v(*pair.second);

    for (const auto& pair : m.physical_elements().archetype_kinds())
        v(*pair.second);

    for (const auto& pair : m.physical_elements().parts())
        v(*pair.second);

    for (const auto& pair : m.physical_elements().helpers())
        v(*pair.second);
}

template<typename TraversalVisitor>
inline void elements_traversal(const entities::model& m,
    TraversalVisitor& v) {
    for (auto& pair : m.structural_elements().modules())
        v(*pair.second);

    for (auto& pair : m.structural_elements().object_templates())
        v(*pair.second);

    for (auto& pair : m.structural_elements().builtins())
        v(*pair.second);

    for (auto& pair : m.structural_elements().enumerations())
        v(*pair.second);

    for (auto& pair : m.structural_elements().primitives())
        v(*pair.second);

    for (auto& pair : m.structural_elements().objects())
        v(*pair.second);

    for (auto& pair : m.structural_elements().exceptions())
        v(*pair.second);

    for (auto& pair : m.structural_elements().visitors())
        v(*pair.second);

    for (auto& pair : m.structural_elements().assistants())
        v(*pair.second);

    for (const auto& pair : m.decoration_elements().licences())
        v(*pair.second);

    for (const auto& pair : m.decoration_elements().modelines())
        v(*pair.second);

    for (const auto& pair : m.decoration_elements().modeline_groups())
        v(*pair.second);

    for (const auto& pair : m.decoration_elements().generation_markers())
        v(*pair.second);

    for (const auto& pair : m.variability_elements().profiles())
        v(*pair.second);

    for (const auto& pair : m.variability_elements().profile_templates())
        v(*pair.second);

    for (const auto& pair : m.variability_elements().feature_template_bundles())
        v(*pair.second);

    for (const auto& pair : m.variability_elements().feature_bundles())
        v(*pair.second);

    if (m.variability_elements().initializer())
        v(*m.variability_elements().initializer());

    for (const auto& pair : m.templating_elements().logic_less_templates())
        v(*pair.second);

    for (const auto& pair : m.serialization_elements().type_registrars())
        v(*pair.second);

    for (const auto& pair : m.visual_studio_elements().solutions())
        v(*pair.second);

    for (const auto& pair : m.visual_studio_elements().projects())
        v(*pair.second);

    for (auto& pair : m.structural_elements().entry_points())
        v(*pair.second);

    for (auto& pair : m.orm_elements().common_odb_options())
        v(*pair.second);

    for (const auto& pair : m.visual_studio_elements().msbuild_targets())
        v(*pair.second);

    for (const auto& pair : m.build_elements().cmakelists())
        v(*pair.second);

    for (const auto& pair : m.physical_elements().backends())
        v(*pair.second);

    for (const auto& pair : m.physical_elements().facets())
        v(*pair.second);

    for (const auto& pair : m.physical_elements().archetypes())
        v(*pair.second);

    for (const auto& pair : m.physical_elements().archetype_kinds())
        v(*pair.second);

    for (const auto& pair : m.physical_elements().parts())
        v(*pair.second);

    for (const auto& pair : m.physical_elements().helpers())
        v(*pair.second);
}

template<typename TraversalVisitor>
inline void elements_traversal(entities::model& m,
    TraversalVisitor& v) {
    for (auto& pair : m.structural_elements().modules())
        v(*pair.second);

    for (auto& pair : m.structural_elements().object_templates())
        v(*pair.second);

    for (auto& pair : m.structural_elements().builtins())
        v(*pair.second);

    for (auto& pair : m.structural_elements().enumerations())
        v(*pair.second);

    for (auto& pair : m.structural_elements().primitives())
        v(*pair.second);

    for (auto& pair : m.structural_elements().objects())
        v(*pair.second);

    for (auto& pair : m.structural_elements().exceptions())
        v(*pair.second);

    for (auto& pair : m.structural_elements().visitors())
        v(*pair.second);

    for (auto& pair : m.structural_elements().assistants())
        v(*pair.second);

    for (const auto& pair : m.decoration_elements().licences())
        v(*pair.second);

    for (const auto& pair : m.decoration_elements().modelines())
        v(*pair.second);

    for (const auto& pair : m.decoration_elements().modeline_groups())
        v(*pair.second);

    for (const auto& pair : m.decoration_elements().generation_markers())
        v(*pair.second);

    for (const auto& pair : m.variability_elements().profiles())
        v(*pair.second);

    for (const auto& pair : m.variability_elements().profile_templates())
        v(*pair.second);

    for (const auto& pair : m.variability_elements().feature_template_bundles())
        v(*pair.second);

    for (const auto& pair : m.variability_elements().feature_bundles())
        v(*pair.second);

    if (m.variability_elements().initializer())
        v(*m.variability_elements().initializer());

    for (const auto& pair : m.templating_elements().logic_less_templates())
        v(*pair.second);

    for (const auto& pair : m.serialization_elements().type_registrars())
        v(*pair.second);

    for (const auto& pair : m.visual_studio_elements().solutions())
        v(*pair.second);

    for (const auto& pair : m.visual_studio_elements().projects())
        v(*pair.second);

    for (auto& pair : m.structural_elements().entry_points())
        v(*pair.second);

    for (auto& pair : m.orm_elements().common_odb_options())
        v(*pair.second);

    for (const auto& pair : m.visual_studio_elements().msbuild_targets())
        v(*pair.second);

    for (const auto& pair : m.build_elements().cmakelists())
        v(*pair.second);

    for (const auto& pair : m.physical_elements().backends())
        v(*pair.second);

    for (const auto& pair : m.physical_elements().facets())
        v(*pair.second);

    for (const auto& pair : m.physical_elements().archetypes())
        v(*pair.second);

    for (const auto& pair : m.physical_elements().archetype_kinds())
        v(*pair.second);

    for (const auto& pair : m.physical_elements().parts())
        v(*pair.second);

    for (const auto& pair : m.physical_elements().helpers())
        v(*pair.second);
}
/**@}*/

/**
 * @brief Performs a traversal across all element pointers in an
 * intermediate model.
 */
/**@{*/
template<typename TraversalVisitor>
inline void shared_elements_traversal(const entities::model& m,
    const TraversalVisitor& v) {
    for (const auto& pair : m.structural_elements().modules())
        v(pair.second);

    for (const auto& pair : m.structural_elements().object_templates())
        v(pair.second);

    for (const auto& pair : m.structural_elements().builtins())
        v(pair.second);

    for (const auto& pair : m.structural_elements().enumerations())
        v(pair.second);

    for (const auto& pair : m.structural_elements().primitives())
        v(pair.second);

    for (const auto& pair : m.structural_elements().objects())
        v(pair.second);

    for (const auto& pair : m.structural_elements().exceptions())
        v(pair.second);

    for (const auto& pair : m.structural_elements().visitors())
        v(pair.second);

    for (const auto& pair : m.structural_elements().assistants())
        v(pair.second);

    for (const auto& pair : m.decoration_elements().licences())
        v(pair.second);

    for (const auto& pair : m.decoration_elements().modelines())
        v(pair.second);

    for (const auto& pair : m.decoration_elements().modeline_groups())
        v(pair.second);

    for (const auto& pair : m.decoration_elements().generation_markers())
        v(pair.second);

    for (const auto& pair : m.variability_elements().profiles())
        v(pair.second);

    for (const auto& pair : m.variability_elements().profile_templates())
        v(pair.second);

    for (const auto& pair : m.variability_elements().feature_template_bundles())
        v(pair.second);

    for (const auto& pair : m.variability_elements().feature_bundles())
        v(pair.second);

    if (m.variability_elements().initializer())
        v(m.variability_elements().initializer());

    for (const auto& pair : m.templating_elements().logic_less_templates())
        v(pair.second);

    for (const auto& pair : m.serialization_elements().type_registrars())
        v(pair.second);

    for (const auto& pair : m.visual_studio_elements().solutions())
        v(pair.second);

    for (const auto& pair : m.visual_studio_elements().projects())
        v(pair.second);

    for (const auto& pair : m.structural_elements().entry_points())
        v(pair.second);

    for (const auto& pair : m.orm_elements().common_odb_options())
        v(pair.second);

    for (const auto& pair : m.visual_studio_elements().msbuild_targets())
        v(pair.second);

    for (const auto& pair : m.build_elements().cmakelists())
        v(pair.second);

    for (const auto& pair : m.physical_elements().backends())
        v(pair.second);

    for (const auto& pair : m.physical_elements().facets())
        v(pair.second);

    for (const auto& pair : m.physical_elements().archetypes())
        v(pair.second);

    for (const auto& pair : m.physical_elements().archetype_kinds())
        v(pair.second);

    for (const auto& pair : m.physical_elements().parts())
        v(pair.second);

    for (const auto& pair : m.physical_elements().helpers())
        v(pair.second);
}

template<typename TraversalVisitor>
inline void shared_elements_traversal(const entities::model& m,
    TraversalVisitor& v) {
    for (auto& pair : m.structural_elements().modules())
        v(pair.second);

    for (auto& pair : m.structural_elements().object_templates())
        v(pair.second);

    for (auto& pair : m.structural_elements().builtins())
        v(pair.second);

    for (auto& pair : m.structural_elements().enumerations())
        v(pair.second);

    for (auto& pair : m.structural_elements().primitives())
        v(pair.second);

    for (auto& pair : m.structural_elements().objects())
        v(pair.second);

    for (auto& pair : m.structural_elements().exceptions())
        v(pair.second);

    for (auto& pair : m.structural_elements().visitors())
        v(pair.second);

    for (auto& pair : m.structural_elements().assistants())
        v(pair.second);

    for (const auto& pair : m.decoration_elements().licences())
        v(pair.second);

    for (const auto& pair : m.decoration_elements().modelines())
        v(pair.second);

    for (const auto& pair : m.decoration_elements().modeline_groups())
        v(pair.second);

    for (const auto& pair : m.decoration_elements().generation_markers())
        v(pair.second);

    for (const auto& pair : m.variability_elements().profiles())
        v(pair.second);

    for (const auto& pair : m.variability_elements().profile_templates())
        v(pair.second);

    for (const auto& pair : m.variability_elements().feature_template_bundles())
        v(pair.second);

    for (const auto& pair : m.variability_elements().feature_bundles())
        v(pair.second);

    if (m.variability_elements().initializer())
        v(m.variability_elements().initializer());

    for (const auto& pair : m.templating_elements().logic_less_templates())
        v(pair.second);

    for (const auto& pair : m.serialization_elements().type_registrars())
        v(pair.second);

    for (const auto& pair : m.visual_studio_elements().solutions())
        v(pair.second);

    for (const auto& pair : m.visual_studio_elements().projects())
        v(pair.second);

    for (auto& pair : m.structural_elements().entry_points())
        v(pair.second);

    for (auto& pair : m.orm_elements().common_odb_options())
        v(pair.second);

    for (const auto& pair : m.visual_studio_elements().msbuild_targets())
        v(pair.second);

    for (const auto& pair : m.build_elements().cmakelists())
        v(pair.second);

    for (const auto& pair : m.physical_elements().backends())
        v(pair.second);

    for (const auto& pair : m.physical_elements().facets())
        v(pair.second);

    for (const auto& pair : m.physical_elements().archetypes())
        v(pair.second);

    for (const auto& pair : m.physical_elements().archetype_kinds())
        v(pair.second);

    for (const auto& pair : m.physical_elements().parts())
        v(pair.second);

    for (const auto& pair : m.physical_elements().helpers())
        v(pair.second);
}

template<typename TraversalVisitor>
inline void shared_elements_traversal(entities::model& m,
    TraversalVisitor& v) {
    for (auto& pair : m.structural_elements().modules())
        v(pair.second);

    for (auto& pair : m.structural_elements().object_templates())
        v(pair.second);

    for (auto& pair : m.structural_elements().builtins())
        v(pair.second);

    for (auto& pair : m.structural_elements().enumerations())
        v(pair.second);

    for (auto& pair : m.structural_elements().primitives())
        v(pair.second);

    for (auto& pair : m.structural_elements().objects())
        v(pair.second);

    for (auto& pair : m.structural_elements().exceptions())
        v(pair.second);

    for (auto& pair : m.structural_elements().visitors())
        v(pair.second);

    for (auto& pair : m.structural_elements().assistants())
        v(pair.second);

    for (const auto& pair : m.decoration_elements().licences())
        v(pair.second);

    for (const auto& pair : m.decoration_elements().modelines())
        v(pair.second);

    for (const auto& pair : m.decoration_elements().modeline_groups())
        v(pair.second);

    for (const auto& pair : m.decoration_elements().generation_markers())
        v(pair.second);

    for (const auto& pair : m.variability_elements().profiles())
        v(pair.second);

    for (const auto& pair : m.variability_elements().profile_templates())
        v(pair.second);

    for (const auto& pair : m.variability_elements().feature_template_bundles())
        v(pair.second);

    for (const auto& pair : m.variability_elements().feature_bundles())
        v(pair.second);

    if (m.variability_elements().initializer())
        v(m.variability_elements().initializer());

    for (const auto& pair : m.templating_elements().logic_less_templates())
        v(pair.second);

    for (const auto& pair : m.serialization_elements().type_registrars())
        v(pair.second);

    for (const auto& pair : m.visual_studio_elements().solutions())
        v(pair.second);

    for (const auto& pair : m.visual_studio_elements().projects())
        v(pair.second);

    for (auto& pair : m.structural_elements().entry_points())
        v(pair.second);

    for (auto& pair : m.orm_elements().common_odb_options())
        v(pair.second);

    for (const auto& pair : m.visual_studio_elements().msbuild_targets())
        v(pair.second);

    for (const auto& pair : m.build_elements().cmakelists())
        v(pair.second);

    for (const auto& pair : m.physical_elements().backends())
        v(pair.second);

    for (const auto& pair : m.physical_elements().facets())
        v(pair.second);

    for (const auto& pair : m.physical_elements().archetypes())
        v(pair.second);

    for (const auto& pair : m.physical_elements().archetype_kinds())
        v(pair.second);

    for (const auto& pair : m.physical_elements().parts())
        v(pair.second);

    for (const auto& pair : m.physical_elements().helpers())
        v(pair.second);
}
/**@}*/

}

#endif
