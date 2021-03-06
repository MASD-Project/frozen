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
#ifndef DOGEN_LOGICAL_TYPES_HELPERS_DECORATION_CONFIGURATION_HPP
#define DOGEN_LOGICAL_TYPES_HELPERS_DECORATION_CONFIGURATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include <boost/optional.hpp>
#include "dogen.identification/types/entities/logical_id.hpp"

namespace dogen::logical::helpers {

class decoration_configuration final {
public:
    decoration_configuration() = default;
    decoration_configuration(const decoration_configuration&) = default;
    ~decoration_configuration() = default;

public:
    decoration_configuration(decoration_configuration&& rhs);

public:
    decoration_configuration(
        const boost::optional<bool>& enabled,
        const std::list<std::string>& copyright_notices,
        const dogen::identification::entities::logical_id& licence_name,
        const dogen::identification::entities::logical_id& modeline_group_name,
        const dogen::identification::entities::logical_id& marker_name);

public:
    const boost::optional<bool>& enabled() const;
    boost::optional<bool>& enabled();
    void enabled(const boost::optional<bool>& v);
    void enabled(const boost::optional<bool>&& v);

    const std::list<std::string>& copyright_notices() const;
    std::list<std::string>& copyright_notices();
    void copyright_notices(const std::list<std::string>& v);
    void copyright_notices(const std::list<std::string>&& v);

    const dogen::identification::entities::logical_id& licence_name() const;
    dogen::identification::entities::logical_id& licence_name();
    void licence_name(const dogen::identification::entities::logical_id& v);
    void licence_name(const dogen::identification::entities::logical_id&& v);

    const dogen::identification::entities::logical_id& modeline_group_name() const;
    dogen::identification::entities::logical_id& modeline_group_name();
    void modeline_group_name(const dogen::identification::entities::logical_id& v);
    void modeline_group_name(const dogen::identification::entities::logical_id&& v);

    const dogen::identification::entities::logical_id& marker_name() const;
    dogen::identification::entities::logical_id& marker_name();
    void marker_name(const dogen::identification::entities::logical_id& v);
    void marker_name(const dogen::identification::entities::logical_id&& v);

public:
    bool operator==(const decoration_configuration& rhs) const;
    bool operator!=(const decoration_configuration& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(decoration_configuration& other) noexcept;
    decoration_configuration& operator=(decoration_configuration other);

private:
    boost::optional<bool> enabled_;
    std::list<std::string> copyright_notices_;
    dogen::identification::entities::logical_id licence_name_;
    dogen::identification::entities::logical_id modeline_group_name_;
    dogen::identification::entities::logical_id marker_name_;
};

}

namespace std {

template<>
inline void swap(
    dogen::logical::helpers::decoration_configuration& lhs,
    dogen::logical::helpers::decoration_configuration& rhs) {
    lhs.swap(rhs);
}

}

#endif
