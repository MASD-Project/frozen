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
#ifndef DOGEN_VARIABILITY_TYPES_ENTITIES_TEXT_COLLECTION_HPP
#define DOGEN_VARIABILITY_TYPES_ENTITIES_TEXT_COLLECTION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <string>
#include <algorithm>
#include "dogen.variability/types/entities/value.hpp"

namespace dogen::variability::entities {

/**
 * @brief Represents a collection of text values.
 */
class text_collection final : public dogen::variability::entities::value {
public:
    text_collection() = default;
    text_collection(const text_collection&) = default;
    text_collection(text_collection&&) = default;

    virtual ~text_collection() noexcept { }

public:
    explicit text_collection(const std::list<std::string>& content);

public:
    using value::accept;

    virtual void accept(const value_visitor& v) const override;
    virtual void accept(value_visitor& v) const override;
    virtual void accept(const value_visitor& v) override;
    virtual void accept(value_visitor& v) override;
public:
    void to_stream(std::ostream& s) const override;

public:
    const std::list<std::string>& content() const;
    std::list<std::string>& content();
    void content(const std::list<std::string>& v);
    void content(const std::list<std::string>&& v);

public:
    bool operator==(const text_collection& rhs) const;
    bool operator!=(const text_collection& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::variability::entities::value& other) const override;

public:
    void swap(text_collection& other) noexcept;
    text_collection& operator=(text_collection other);

private:
    std::list<std::string> content_;
};

}

namespace std {

template<>
inline void swap(
    dogen::variability::entities::text_collection& lhs,
    dogen::variability::entities::text_collection& rhs) {
    lhs.swap(rhs);
}

}

#endif
