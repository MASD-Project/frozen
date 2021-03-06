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
#ifndef DOGEN_VARIABILITY_TYPES_ENTITIES_FEATURE_TEMPLATE_REPOSITORY_HPP
#define DOGEN_VARIABILITY_TYPES_ENTITIES_FEATURE_TEMPLATE_REPOSITORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <algorithm>
#include "dogen.variability/types/entities/feature_template.hpp"

namespace dogen::variability::entities {

/**
 * @brief Stores a set of feature templates.
 */
class feature_template_repository final {
public:
    feature_template_repository() = default;
    feature_template_repository(const feature_template_repository&) = default;
    feature_template_repository(feature_template_repository&&) = default;
    ~feature_template_repository() = default;

public:
    explicit feature_template_repository(const std::list<dogen::variability::entities::feature_template>& templates);

public:
    const std::list<dogen::variability::entities::feature_template>& templates() const;
    std::list<dogen::variability::entities::feature_template>& templates();
    void templates(const std::list<dogen::variability::entities::feature_template>& v);
    void templates(const std::list<dogen::variability::entities::feature_template>&& v);

public:
    bool operator==(const feature_template_repository& rhs) const;
    bool operator!=(const feature_template_repository& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(feature_template_repository& other) noexcept;
    feature_template_repository& operator=(feature_template_repository other);

private:
    std::list<dogen::variability::entities::feature_template> templates_;
};

}

namespace std {

template<>
inline void swap(
    dogen::variability::entities::feature_template_repository& lhs,
    dogen::variability::entities::feature_template_repository& rhs) {
    lhs.swap(rhs);
}

}

#endif
