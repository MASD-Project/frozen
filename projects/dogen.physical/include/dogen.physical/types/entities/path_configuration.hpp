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
#ifndef DOGEN_PHYSICAL_TYPES_ENTITIES_PATH_CONFIGURATION_HPP
#define DOGEN_PHYSICAL_TYPES_ENTITIES_PATH_CONFIGURATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen.physical/types/entities/path_contribution_type.hpp"

namespace dogen::physical::entities {

/**
 * @brief Describes how paths are handled within a part.
 */
class path_configuration final {
public:
    path_configuration(const path_configuration&) = default;
    path_configuration(path_configuration&&) = default;
    ~path_configuration() = default;

public:
    path_configuration();

public:
    path_configuration(
        const dogen::physical::entities::path_contribution_type external_modules,
        const dogen::physical::entities::path_contribution_type model_modules,
        const dogen::physical::entities::path_contribution_type facet,
        const dogen::physical::entities::path_contribution_type internal_modules);

public:
    /**
     * @brief What kind of contribution do the external modules make to the final path.
     */
    /**@{*/
    dogen::physical::entities::path_contribution_type external_modules() const;
    void external_modules(const dogen::physical::entities::path_contribution_type v);
    /**@}*/

    /**
     * @brief What kind of contribution do the model modules make to the final path.
     */
    /**@{*/
    dogen::physical::entities::path_contribution_type model_modules() const;
    void model_modules(const dogen::physical::entities::path_contribution_type v);
    /**@}*/

    /**
     * @brief What kind of contribution does the facet make to the final path.
     */
    /**@{*/
    dogen::physical::entities::path_contribution_type facet() const;
    void facet(const dogen::physical::entities::path_contribution_type v);
    /**@}*/

    /**
     * @brief What kind of contribution do the internal modules make to the final path.
     */
    /**@{*/
    dogen::physical::entities::path_contribution_type internal_modules() const;
    void internal_modules(const dogen::physical::entities::path_contribution_type v);
    /**@}*/

public:
    bool operator==(const path_configuration& rhs) const;
    bool operator!=(const path_configuration& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(path_configuration& other) noexcept;
    path_configuration& operator=(path_configuration other);

private:
    dogen::physical::entities::path_contribution_type external_modules_;
    dogen::physical::entities::path_contribution_type model_modules_;
    dogen::physical::entities::path_contribution_type facet_;
    dogen::physical::entities::path_contribution_type internal_modules_;
};

}

namespace std {

template<>
inline void swap(
    dogen::physical::entities::path_configuration& lhs,
    dogen::physical::entities::path_configuration& rhs) {
    lhs.swap(rhs);
}

}

#endif
