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
#ifndef DOGEN_LOGICAL_TYPES_ENTITIES_ORM_MODULE_PROPERTIES_HPP
#define DOGEN_LOGICAL_TYPES_ENTITIES_ORM_MODULE_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <boost/optional.hpp>
#include "dogen.logical/types/entities/orm/letter_case.hpp"

namespace dogen::logical::entities::orm {

class module_properties final {
public:
    module_properties() = default;
    module_properties(const module_properties&) = default;
    ~module_properties() = default;

public:
    module_properties(module_properties&& rhs);

public:
    module_properties(
        const std::string& schema_name,
        const std::string& capitalised_schema_name,
        const boost::optional<dogen::logical::entities::orm::letter_case>& letter_case);

public:
    /**
     * @brief Name of the database schema in which to place this element.
     */
    /**@{*/
    const std::string& schema_name() const;
    std::string& schema_name();
    void schema_name(const std::string& v);
    void schema_name(const std::string&& v);
    /**@}*/

    /**
     * @brief Schema name with the correct capitalisation.
     */
    /**@{*/
    const std::string& capitalised_schema_name() const;
    std::string& capitalised_schema_name();
    void capitalised_schema_name(const std::string& v);
    void capitalised_schema_name(const std::string&& v);
    /**@}*/

    /**
     * @brief What case to use for the database identifiers.
     */
    /**@{*/
    const boost::optional<dogen::logical::entities::orm::letter_case>& letter_case() const;
    boost::optional<dogen::logical::entities::orm::letter_case>& letter_case();
    void letter_case(const boost::optional<dogen::logical::entities::orm::letter_case>& v);
    void letter_case(const boost::optional<dogen::logical::entities::orm::letter_case>&& v);
    /**@}*/

public:
    bool operator==(const module_properties& rhs) const;
    bool operator!=(const module_properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(module_properties& other) noexcept;
    module_properties& operator=(module_properties other);

private:
    std::string schema_name_;
    std::string capitalised_schema_name_;
    boost::optional<dogen::logical::entities::orm::letter_case> letter_case_;
};

}

namespace std {

template<>
inline void swap(
    dogen::logical::entities::orm::module_properties& lhs,
    dogen::logical::entities::orm::module_properties& rhs) {
    lhs.swap(rhs);
}

}

#endif
