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
#ifndef DOGEN_PHYSICAL_TYPES_HELPERS_PATH_GENERATOR_HPP
#define DOGEN_PHYSICAL_TYPES_HELPERS_PATH_GENERATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>

namespace dogen::physical::helpers {

class path_generator final {
public:
    path_generator() = default;
    path_generator(const path_generator&) = default;
    path_generator(path_generator&&) = default;
    ~path_generator() = default;
    path_generator& operator=(const path_generator&) = default;

public:
    bool operator==(const path_generator& rhs) const;
    bool operator!=(const path_generator& rhs) const {
        return !this->operator==(rhs);
    }

};

}

#endif
