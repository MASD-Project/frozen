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
#include "dogen.text/io/entities/model_io.hpp"
#include "dogen.logical/io/entities/model_io.hpp"
#include "dogen.physical/io/entities/model_io.hpp"
#include "dogen.text/io/entities/logical_physical_region_io.hpp"
#include "dogen.identification/io/entities/logical_provenance_io.hpp"

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::text::entities::logical_physical_region>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace dogen::text::entities {

std::ostream& operator<<(std::ostream& s, const model& v) {
    s << " { "
      << "\"__type__\": " << "\"dogen::text::entities::model\"" << ", "
      << "\"provenance\": " << v.provenance() << ", "
      << "\"logical\": " << v.logical() << ", "
      << "\"physical\": " << v.physical() << ", "
      << "\"logical_physical_regions\": " << v.logical_physical_regions()
      << " }";
    return(s);
}

}
