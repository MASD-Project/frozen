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
#ifndef DOGEN_PHYSICAL_TYPES_TRANSFORMS_COMPUTE_NAME_INDICES_TRANSFORM_HPP
#define DOGEN_PHYSICAL_TYPES_TRANSFORMS_COMPUTE_NAME_INDICES_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen.identification/types/entities/logical_meta_id.hpp"
#include "dogen.identification/types/entities/archetype_name_set.hpp"
#include "dogen.physical/types/transforms/minimal_context.hpp"
#include "dogen.physical/types/entities/meta_model.hpp"

namespace dogen::physical::transforms {

/**
 * @brief Updates the meta-name indices in the meta-model.
 */
class compute_name_indices_transform final {
private:
    /**
     * @brief Updates the supplied container with information from the
     * current archetype.
     */
    static void update_physical_meta_names_by_logical_meta_name(
        const entities::archetype& arch,
        std::unordered_map<identification::entities::logical_meta_id,
        identification::entities::archetype_name_set>&
        physical_meta_names_by_logical_meta_name);

    /**
     * @brief Obtains all of the archetype meta-names in the physical
     * dimension, organised by logical meta-name.
     */
    static std::unordered_map<identification::entities::logical_meta_id,
                              identification::entities::archetype_name_set>
    obtain_physical_meta_names_by_logical_meta_name(
        const physical::entities::meta_model& mm);

    /**
     * @brief Indexes technical spaces for archetype.
     */
    static std::unordered_map<identification::entities::physical_meta_id,
                              identification::entities::technical_space>
    obtain_technical_space_for_archetype(
        const physical::entities::meta_model& mm);

public:
    /**
     * @brief Apply the transform to the meta-model.
     */
    static void apply(const physical::transforms::minimal_context& ctx,
        physical::entities::meta_model& mm);
};

}

#endif
