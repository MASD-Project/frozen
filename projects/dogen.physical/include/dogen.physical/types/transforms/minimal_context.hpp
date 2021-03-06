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
#ifndef DOGEN_PHYSICAL_TYPES_TRANSFORMS_MINIMAL_CONTEXT_HPP
#define DOGEN_PHYSICAL_TYPES_TRANSFORMS_MINIMAL_CONTEXT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/shared_ptr.hpp>
#include "dogen.tracing/types/tracer_fwd.hpp"

namespace dogen::physical::transforms {

/**
 * @brief Smallest possible context required for bootstrapping purposes.
 */
class minimal_context final {
public:
    minimal_context() = default;
    minimal_context(const minimal_context&) = default;
    minimal_context(minimal_context&&) = default;
    ~minimal_context() = default;

public:
    explicit minimal_context(const boost::shared_ptr<dogen::tracing::tracer>& tracer);

public:
    const boost::shared_ptr<dogen::tracing::tracer>& tracer() const;
    boost::shared_ptr<dogen::tracing::tracer>& tracer();
    void tracer(const boost::shared_ptr<dogen::tracing::tracer>& v);
    void tracer(const boost::shared_ptr<dogen::tracing::tracer>&& v);

public:
    bool operator==(const minimal_context& rhs) const;
    bool operator!=(const minimal_context& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(minimal_context& other) noexcept;
    minimal_context& operator=(minimal_context other);

private:
    boost::shared_ptr<dogen::tracing::tracer> tracer_;
};

}

namespace std {

template<>
inline void swap(
    dogen::physical::transforms::minimal_context& lhs,
    dogen::physical::transforms::minimal_context& rhs) {
    lhs.swap(rhs);
}

}

#endif
