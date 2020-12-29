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
#ifndef DOGEN_LOGICAL_TYPES_ENTITIES_MAPPING_DESTINATION_HPP
#define DOGEN_LOGICAL_TYPES_ENTITIES_MAPPING_DESTINATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen.identification/types/entities/logical_name.hpp"
#include "dogen.identification/types/entities/technical_space.hpp"

namespace dogen::logical::entities::mapping {

class destination final {
public:
    destination(const destination&) = default;
    destination(destination&&) = default;
    ~destination() = default;

public:
    destination();

public:
    destination(
        const dogen::identification::entities::logical_name& name,
        const dogen::identification::entities::technical_space technical_space);

public:
    const dogen::identification::entities::logical_name& name() const;
    dogen::identification::entities::logical_name& name();
    void name(const dogen::identification::entities::logical_name& v);
    void name(const dogen::identification::entities::logical_name&& v);

    dogen::identification::entities::technical_space technical_space() const;
    void technical_space(const dogen::identification::entities::technical_space v);

public:
    bool operator==(const destination& rhs) const;
    bool operator!=(const destination& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(destination& other) noexcept;
    destination& operator=(destination other);

private:
    dogen::identification::entities::logical_name name_;
    dogen::identification::entities::technical_space technical_space_;
};

}

namespace std {

template<>
inline void swap(
    dogen::logical::entities::mapping::destination& lhs,
    dogen::logical::entities::mapping::destination& rhs) {
    lhs.swap(rhs);
}

}

#endif
