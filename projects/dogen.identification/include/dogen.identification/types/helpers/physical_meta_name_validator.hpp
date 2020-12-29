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
#ifndef DOGEN_IDENTIFICATION_TYPES_HELPERS_PHYSICAL_META_NAME_VALIDATOR_HPP
#define DOGEN_IDENTIFICATION_TYPES_HELPERS_PHYSICAL_META_NAME_VALIDATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen.identification/types/entities/physical_meta_name.hpp"

namespace dogen::identification::helpers {

/**
 * @brief Checks the validity of physical meta-names.
 *
 * Note that the components of the meta-name are hierarchical, so
 * archetypes require a backend, part and facet and parts require a
 * backend. The exception is facet, which does not require a part.
 */
class physical_meta_name_validator final {
private:
    /**
     * @brief Validation rules that are common to all types of
     * meta-names.
     */
    static void common_validation(const entities::physical_meta_name& mn,
        const bool is_meta_model);

public:
    /**
     * @brief Checks if the meta-name is valid as a meta-model name.
     */
    static void validate_meta_model_name(
        const entities::physical_meta_name& mn);

    /**
     * @brief Checks if the meta-name is valid as a backend name.
     */
    static void validate_backend_name(
        const entities::physical_meta_name& mn);

    /**
     * @brief Checks if the name is valid as a facet name.
     */
    static void validate_part_name(
        const entities::physical_meta_name& mn);

    /**
     * @brief Checks if the name is valid as a facet name.
     */
    static void validate_facet_name(
        const entities::physical_meta_name& mn);

    /**
     * @brief Checks if the name is valid as an archetype name.
     */
    static void validate_archetype_name(
        const entities::physical_meta_name& mn);
};

}

#endif
