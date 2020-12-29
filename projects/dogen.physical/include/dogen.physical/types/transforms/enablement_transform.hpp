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
#ifndef DOGEN_PHYSICAL_TYPES_TRANSFORMS_ENABLEMENT_TRANSFORM_HPP
#define DOGEN_PHYSICAL_TYPES_TRANSFORMS_ENABLEMENT_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <unordered_map>
#include "dogen.variability/types/entities/feature.hpp"
#include "dogen.variability/types/entities/feature_model.hpp"
#include "dogen.identification/types/entities/physical_meta_name_indices.hpp"
#include "dogen.identification/types/entities/archetype_name_set.hpp"
#include "dogen.identification/types/entities/logical_meta_physical_id.hpp"
#include "dogen.physical/types/entities/model.hpp"
#include "dogen.physical/types/transforms/context.hpp"
#include "dogen.physical/types/entities/region.hpp"
#include "dogen.physical/types/entities/enablement_properties.hpp"

namespace dogen::physical::transforms {

/**
 * @brief Calculates the value of the enablement and overwrite
 * properties for each artefact.
 */
class enablement_transform final {
private:
    /**
     * @brief Stores the configuration at the artefact level for the
     * archetype enablement.
     */
    struct feature_group {
        variability::entities::feature facet_enabled;
        variability::entities::feature archetype_enabled;
        variability::entities::feature facet_overwrite;
        variability::entities::feature archetype_overwrite;
    };

private:
    /**
     * @brief Creates the feature groups for all physical meta-model
     * items.
     */
    static std::unordered_map<identification::entities::physical_meta_id,
                              feature_group>
    make_feature_group(const variability::entities::feature_model& fm,
        const identification::entities::physical_meta_name_indices& idx);

    /**
     * @brief Reads the configuration for each artefact set regarding
     * enablement, and then uses it to populate the correspondent
     * artefacts.
     */
    static void populate_enablement_properties(
        const std::unordered_map<identification::entities::physical_meta_id,
        feature_group>& fgs, entities::model& m);

private:
    static void compute_enablement_for_artefact(
        const entities::archetype_properties& archetype_properties,
        entities::artefact& a);

    static void compute_enablement_for_region(
        const std::unordered_map<identification::entities::logical_meta_id,
        identification::entities::archetype_name_set>& pmn_by_lmid,
        const std::unordered_map<identification::entities::physical_meta_id,
        entities::archetype_properties> archetype_properties,
        std::unordered_set<identification::entities::logical_meta_physical_id>&
        enabled_archetype_for_element, entities::region& pr);

public:
    static void apply(const context& ctx, entities::model& m);
};

}

#endif
