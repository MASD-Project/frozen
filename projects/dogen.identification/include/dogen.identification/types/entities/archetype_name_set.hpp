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
#ifndef DOGEN_IDENTIFICATION_TYPES_ENTITIES_ARCHETYPE_NAME_SET_HPP
#define DOGEN_IDENTIFICATION_TYPES_ENTITIES_ARCHETYPE_NAME_SET_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <algorithm>
#include <unordered_map>
#include "dogen.identification/types/entities/logical_meta_id.hpp"
#include "dogen.identification/types/entities/physical_meta_id.hpp"
#include "dogen.identification/types/entities/physical_meta_name.hpp"
#include "dogen.identification/hash/entities/physical_meta_id_hash.hpp"

namespace dogen::identification::entities {

class archetype_name_set final {
public:
    archetype_name_set() = default;
    archetype_name_set(const archetype_name_set&) = default;
    archetype_name_set(archetype_name_set&&) = default;
    ~archetype_name_set() = default;

public:
    archetype_name_set(
        const dogen::identification::entities::logical_meta_id& logical_meta_id,
        const std::list<dogen::identification::entities::physical_meta_name>& meta_names,
        const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::identification::entities::physical_meta_id>& canonical_locations,
        const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::identification::entities::physical_meta_id>& archetype_for_label);

public:
    /**
     * @brief Identifier of the meta-element in the logical dimension.
     */
    /**@{*/
    const dogen::identification::entities::logical_meta_id& logical_meta_id() const;
    dogen::identification::entities::logical_meta_id& logical_meta_id();
    void logical_meta_id(const dogen::identification::entities::logical_meta_id& v);
    void logical_meta_id(const dogen::identification::entities::logical_meta_id&& v);
    /**@}*/

    /**
     * @brief All meta-names that belong to this group.
     */
    /**@{*/
    const std::list<dogen::identification::entities::physical_meta_name>& meta_names() const;
    std::list<dogen::identification::entities::physical_meta_name>& meta_names();
    void meta_names(const std::list<dogen::identification::entities::physical_meta_name>& v);
    void meta_names(const std::list<dogen::identification::entities::physical_meta_name>&& v);
    /**@}*/

    /**
     * @brief Maps a concrete archetype location to its canonical form, if the canonical
     * form is supported. Otherwise no such mapping will exist.
     */
    /**@{*/
    const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::identification::entities::physical_meta_id>& canonical_locations() const;
    std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::identification::entities::physical_meta_id>& canonical_locations();
    void canonical_locations(const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::identification::entities::physical_meta_id>& v);
    void canonical_locations(const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::identification::entities::physical_meta_id>&& v);
    /**@}*/

    /**
     * @brief Maps a label to archetype ID within the present logical manifold.
     */
    /**@{*/
    const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::identification::entities::physical_meta_id>& archetype_for_label() const;
    std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::identification::entities::physical_meta_id>& archetype_for_label();
    void archetype_for_label(const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::identification::entities::physical_meta_id>& v);
    void archetype_for_label(const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::identification::entities::physical_meta_id>&& v);
    /**@}*/

public:
    bool operator==(const archetype_name_set& rhs) const;
    bool operator!=(const archetype_name_set& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(archetype_name_set& other) noexcept;
    archetype_name_set& operator=(archetype_name_set other);

private:
    dogen::identification::entities::logical_meta_id logical_meta_id_;
    std::list<dogen::identification::entities::physical_meta_name> meta_names_;
    std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::identification::entities::physical_meta_id> canonical_locations_;
    std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::identification::entities::physical_meta_id> archetype_for_label_;
};

}

namespace std {

template<>
inline void swap(
    dogen::identification::entities::archetype_name_set& lhs,
    dogen::identification::entities::archetype_name_set& rhs) {
    lhs.swap(rhs);
}

}

#endif
