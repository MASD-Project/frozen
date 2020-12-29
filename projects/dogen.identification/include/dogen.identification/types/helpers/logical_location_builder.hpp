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
#ifndef DOGEN_IDENTIFICATION_TYPES_HELPERS_LOGICAL_LOCATION_BUILDER_HPP
#define DOGEN_IDENTIFICATION_TYPES_HELPERS_LOGICAL_LOCATION_BUILDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include "dogen.identification/types/entities/logical_location.hpp"

namespace dogen::identification::helpers {

/**
 * @brief Builds a location.
 */
class logical_location_builder final {
public:
    void external_modules(const std::string& em);
    void external_modules(const std::list<std::string>& em);
    void model_modules(const std::string& mm);
    void model_modules(const std::list<std::string>& mm);
    void internal_modules(const std::string& im);
    void internal_modules(const std::list<std::string>& im);

    void location(const entities::logical_location& l);

public:
    entities::logical_location build();

private:
    entities::logical_location location_;
};

}

#endif
