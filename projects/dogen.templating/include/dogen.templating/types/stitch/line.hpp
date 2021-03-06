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
#ifndef DOGEN_TEMPLATING_TYPES_STITCH_LINE_HPP
#define DOGEN_TEMPLATING_TYPES_STITCH_LINE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <algorithm>
#include "dogen.templating/types/stitch/block.hpp"

namespace dogen::templating::stitch {

class line final {
public:
    line() = default;
    line(const line&) = default;
    line(line&&) = default;
    ~line() = default;

public:
    explicit line(const std::list<dogen::templating::stitch::block>& blocks);

public:
    const std::list<dogen::templating::stitch::block>& blocks() const;
    std::list<dogen::templating::stitch::block>& blocks();
    void blocks(const std::list<dogen::templating::stitch::block>& v);
    void blocks(const std::list<dogen::templating::stitch::block>&& v);

public:
    bool operator==(const line& rhs) const;
    bool operator!=(const line& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(line& other) noexcept;
    line& operator=(line other);

private:
    std::list<dogen::templating::stitch::block> blocks_;
};

}

namespace std {

template<>
inline void swap(
    dogen::templating::stitch::line& lhs,
    dogen::templating::stitch::line& rhs) {
    lhs.swap(rhs);
}

}

#endif
