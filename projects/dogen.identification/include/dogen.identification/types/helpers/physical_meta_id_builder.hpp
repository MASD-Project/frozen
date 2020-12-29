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
#ifndef DOGEN_IDENTIFICATION_TYPES_HELPERS_PHYSICAL_META_ID_BUILDER_HPP
#define DOGEN_IDENTIFICATION_TYPES_HELPERS_PHYSICAL_META_ID_BUILDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include "dogen.identification/types/entities/physical_meta_id.hpp"
#include "dogen.identification/types/entities/physical_meta_name.hpp"
#include "dogen.identification/types/entities/physical_meta_location.hpp"

namespace dogen::identification::helpers {

/**
 * @brief Builds qualified meta-names according to the geometry of
 * physical space.
 *
 * If the meta-names and locations are not valid for the requests in
 * question, we throw.
 */
class physical_meta_id_builder final {
private:
    /**
     * @brief Converts a plain string into a physical meta-ID.
     */
    static entities::physical_meta_id to_meta_id(const std::string& s);

public:
    /**
     * @brief Builds a qualified name for the meta-model region in
     * physical space.
     */
    /**@{*/
    static entities::physical_meta_id
    build_meta_model(const entities::physical_meta_location& l);
    static entities::physical_meta_id
    build_meta_model(const entities::physical_meta_name& mn);
    /**@}*/

    /**
     * @brief Builds a qualified name for the backend region in
     * physical space.
     */
    /**@{*/
    static entities::physical_meta_id
    build_backend(const entities::physical_meta_location& l);
    static entities::physical_meta_id
    build_backend(const entities::physical_meta_name& n);
    /**@}*/

    /**
     * @brief Builds a qualified name for the part region in
     * physical space.
     */
    /**@{*/
    static entities::physical_meta_id
    build_part(const entities::physical_meta_location& l);
    static entities::physical_meta_id
    build_part(const entities::physical_meta_name& n);
    /**@}*/

    /**
     * @brief Builds a qualified name for the facet region in physical
     * space.
     */
    /**@{*/
    static entities::physical_meta_id
    build_facet(const entities::physical_meta_location& l,
        const bool add_canonical = false);
    static entities::physical_meta_id
    build_facet(const entities::physical_meta_name& n,
        const bool add_canonical = false);
    /**@}*/

    /**
     * @brief Builds a qualified name for the complete archetype.
     */
    /**@{*/
    static entities::physical_meta_id
    build_archetype(const entities::physical_meta_location& l);
    static entities::physical_meta_id
    build_archetype(const entities::physical_meta_name& n);
    /**@}*/
};

}

#endif
