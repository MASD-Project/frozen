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
#ifndef DOGEN_LOGICAL_TYPES_TRANSFORMS_TECHNICAL_SPACE_TRANSFORM_HPP
#define DOGEN_LOGICAL_TYPES_TRANSFORMS_TECHNICAL_SPACE_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include "dogen.identification/types/entities/technical_space.hpp"
#include "dogen.identification/types/entities/technical_space_version.hpp"
#include "dogen.logical/types/entities/model.hpp"
#include "dogen.logical/types/transforms/context_fwd.hpp"

namespace dogen::logical::transforms {

/**
 * @brief Updates the technical space fields of the model and its
 * elements.
 */
class technical_space_transform final {
private:
    /**
     * @brief Converts string into its enumeration representation.
     */
    static identification::entities::technical_space_version
    to_technical_space_version(const std::string& s);

    /**
     * @brief Handles technical space related attributes.
     */
    static void processs_technical_space(
        const context& ctx, entities::model& m);

    /**
     * @brief Handles the version of the technical space.
     */
    static void processs_technical_space_version(
        const context& ctx, entities::model& m);

public:
    static void apply(const context& ctx, entities::model& m);
};

}

#endif