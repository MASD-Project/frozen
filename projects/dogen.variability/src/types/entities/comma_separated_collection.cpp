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
#include <ostream>
#include <boost/algorithm/string.hpp>
#include "dogen.variability/io/entities/value_io.hpp"
#include "dogen.variability/types/entities/value_visitor.hpp"
#include "dogen.variability/types/entities/comma_separated_collection.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<std::string>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << "\"" << tidy_up_string(*i) << "\"";
    }
    s << "] ";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<std::list<std::string> >& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace dogen::variability::entities {

comma_separated_collection::comma_separated_collection(const std::list<std::list<std::string> >& content)
    : dogen::variability::entities::value(),
      content_(content) { }

void comma_separated_collection::accept(const value_visitor& v) const {
    v.visit(*this);
}

void comma_separated_collection::accept(value_visitor& v) const {
    v.visit(*this);
    }

void comma_separated_collection::accept(const value_visitor& v) {
    v.visit(*this);
}

void comma_separated_collection::accept(value_visitor& v) {
    v.visit(*this);
}

void comma_separated_collection::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::variability::entities::comma_separated_collection\"" << ", "
      << "\"__parent_0__\": ";
    dogen::variability::entities::value::to_stream(s);
    s << ", "
      << "\"content\": " << content_
      << " }";
}

void comma_separated_collection::swap(comma_separated_collection& other) noexcept {
    dogen::variability::entities::value::swap(other);

    using std::swap;
    swap(content_, other.content_);
}

bool comma_separated_collection::equals(const dogen::variability::entities::value& other) const {
    const comma_separated_collection* const p(dynamic_cast<const comma_separated_collection* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool comma_separated_collection::operator==(const comma_separated_collection& rhs) const {
    return dogen::variability::entities::value::compare(rhs) &&
        content_ == rhs.content_;
}

comma_separated_collection& comma_separated_collection::operator=(comma_separated_collection other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<std::list<std::string> >& comma_separated_collection::content() const {
    return content_;
}

std::list<std::list<std::string> >& comma_separated_collection::content() {
    return content_;
}

void comma_separated_collection::content(const std::list<std::list<std::string> >& v) {
    content_ = v;
}

void comma_separated_collection::content(const std::list<std::list<std::string> >&& v) {
    content_ = std::move(v);
}

}
