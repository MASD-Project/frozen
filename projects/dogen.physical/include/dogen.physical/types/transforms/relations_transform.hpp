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
#ifndef DOGEN_PHYSICAL_TYPES_TRANSFORMS_RELATIONS_TRANSFORM_HPP
#define DOGEN_PHYSICAL_TYPES_TRANSFORMS_RELATIONS_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <unordered_map>
#include "dogen.identification/types/entities/physical_meta_id.hpp"
#include "dogen.physical/types/entities/relations.hpp"
#include "dogen.physical/types/entities/meta_model.hpp"
#include "dogen.physical/types/entities/model.hpp"
#include "dogen.physical/types/transforms/context.hpp"

namespace dogen::physical::transforms {

/**
 * @brief Updates the relation information in the physical model.
 */
class relations_transform final {
private:
    /**
     * @brief Indexes relations per archetypes.
     */
    static std::unordered_map<identification::entities::physical_meta_id,
                              entities::relations>
    obtain_relations_for_archetype(const entities::meta_model& pmm);

public:
    static void apply(const context& ctx, entities::model& m);
};

}

#endif
