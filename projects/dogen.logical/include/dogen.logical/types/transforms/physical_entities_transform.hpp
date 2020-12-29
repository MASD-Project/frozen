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
#ifndef DOGEN_LOGICAL_TYPES_TRANSFORMS_PHYSICAL_ENTITIES_TRANSFORM_HPP
#define DOGEN_LOGICAL_TYPES_TRANSFORMS_PHYSICAL_ENTITIES_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen.variability/types/entities/configuration.hpp"
#include "dogen.logical/types/entities/model.hpp"
#include "dogen.logical/types/entities/physical/relations.hpp"
#include "dogen.logical/types/transforms/context_fwd.hpp"

namespace dogen::logical::transforms {

/**
 * @brief Transforms all physical entities in the logical model.
 *
 * Must execute after the containment transform.
 */
class physical_entities_transform final {
private:
    /**
     * @brief Processes all of the logical representations of
     * backends.
     */
    static void process_backends(const context& ctx, entities::model& m);

    /**
     * @brief Processes all of the logical representations of facets.
     */
    static void process_facets(const context& ctx, entities::model& m);

    /**
     * @brief Processes all of the logical representations of parts.
     */
    static void process_parts(const context& ctx, entities::model& m);

    /**
     * @brief Processes all of the logical representations of
     * archetype kinds.
     */
    static void process_archetype_kinds(entities::model& m);

    /**
     * @brief Processes all of the logical representations of
     * archetypes.
     */
    static void process_archetypes(const context& ctx, entities::model& m);

    /**
     * @brief Processes all of the logical representations of
     * helpers.
     */
    static void process_helpers(const context& ctx, entities::model& m);

    /**
     * @brief Reads all data related to physical relations.
     */
    static entities::physical::relations process_relations(const context& ctx,
        const variability::entities::configuration& cfg);

public:
    /**
     * Execute the transform against the model.
     */
    static void apply(const context& ctx, entities::model& m);
};

}

#endif
