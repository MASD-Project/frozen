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
#ifndef DOGEN_LOGICAL_TYPES_TRANSFORMS_HELPER_PROPERTIES_TRANSFORM_HPP
#define DOGEN_LOGICAL_TYPES_TRANSFORMS_HELPER_PROPERTIES_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen.physical/types/entities/meta_model.hpp"
#include "dogen.logical/types/entities/model.hpp"
#include "dogen.logical/types/transforms/context.hpp"
#include "dogen.variability/types/entities/feature.hpp"
#include "dogen.variability/types/entities/configuration.hpp"
#include "dogen.variability/types/entities/feature_model.hpp"
#include "dogen.logical/types/entities/streaming_properties.hpp"

namespace dogen::logical::transforms {

/**
 * @brief Populates all of the helper properties from the PMM.
 *
 * Note that this is a gigantic hack, helpers are just a temporary
 * physical concept bolted in to the logical model and will be removed
 * with the PMM. It is just here for now so we can move on to the next
 * phase of refactoring. Note also that to determine enablement of
 * helpers we rely on an orchestration transform, as it needs the PM
 * and that was just one hack too far.
 */
class helper_properties_transform final {
private:
    /**
     * @brief Reads the helper related configuration from the model.
     */
    static std::unordered_map<identification::entities::logical_id, std::string>
    make_configuration(const variability::entities::feature_model& fm,
        const entities::model& m);

private:
    /**
     * @brief Unpack the helpers to generate a mapping of helper
     * family to facet. The container has helpers by family, by owning
     * file formatter.
     */
    static std::unordered_map<std::string, std::unordered_set<std::string>>
    facets_for_family(const physical::entities::meta_model& pmm);

    static void populate_helper_properties(const std::unordered_map<
        identification::entities::logical_id, std::string>& helper_families,
        const std::unordered_map<identification::entities::logical_id,
        logical::entities::streaming_properties>& streaming_properties,
        const std::unordered_map<std::string, std::unordered_set<std::string>>&
        facets_for_family, entities::model& m);

public:
    static void apply(const context& ctx, entities::model& m);
};

}

#endif
