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
#include "dogen.logical/types/entities/stereotypes.hpp"

namespace dogen::logical::entities {

stereotypes::stereotypes(
    const std::list<dogen::logical::entities::static_stereotypes>& static_stereotypes,
    const std::list<dogen::identification::entities::stereotype>& dynamic_stereotypes)
    : static_stereotypes_(static_stereotypes),
      dynamic_stereotypes_(dynamic_stereotypes) { }

void stereotypes::swap(stereotypes& other) noexcept {
    using std::swap;
    swap(static_stereotypes_, other.static_stereotypes_);
    swap(dynamic_stereotypes_, other.dynamic_stereotypes_);
}

bool stereotypes::operator==(const stereotypes& rhs) const {
    return static_stereotypes_ == rhs.static_stereotypes_ &&
        dynamic_stereotypes_ == rhs.dynamic_stereotypes_;
}

stereotypes& stereotypes::operator=(stereotypes other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::logical::entities::static_stereotypes>& stereotypes::static_stereotypes() const {
    return static_stereotypes_;
}

std::list<dogen::logical::entities::static_stereotypes>& stereotypes::static_stereotypes() {
    return static_stereotypes_;
}

void stereotypes::static_stereotypes(const std::list<dogen::logical::entities::static_stereotypes>& v) {
    static_stereotypes_ = v;
}

void stereotypes::static_stereotypes(const std::list<dogen::logical::entities::static_stereotypes>&& v) {
    static_stereotypes_ = std::move(v);
}

const std::list<dogen::identification::entities::stereotype>& stereotypes::dynamic_stereotypes() const {
    return dynamic_stereotypes_;
}

std::list<dogen::identification::entities::stereotype>& stereotypes::dynamic_stereotypes() {
    return dynamic_stereotypes_;
}

void stereotypes::dynamic_stereotypes(const std::list<dogen::identification::entities::stereotype>& v) {
    dynamic_stereotypes_ = v;
}

void stereotypes::dynamic_stereotypes(const std::list<dogen::identification::entities::stereotype>&& v) {
    dynamic_stereotypes_ = std::move(v);
}

}
