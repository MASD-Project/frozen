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
#include "dogen.physical/io/entities/helper_io.hpp"
#include "dogen.physical/io/entities/relations_io.hpp"
#include "dogen.identification/io/entities/label_io.hpp"
#include "dogen.identification/io/entities/technical_space_io.hpp"
#include "dogen.identification/io/entities/physical_meta_id_io.hpp"
#include "dogen.identification/io/entities/physical_meta_name_io.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::identification::entities::label>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

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

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::identification::entities::physical_meta_id>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace dogen::physical::entities {

std::ostream& operator<<(std::ostream& s, const helper& v) {
    s << " { "
      << "\"__type__\": " << "\"dogen::physical::entities::helper\"" << ", "
      << "\"description\": " << "\"" << tidy_up_string(v.description()) << "\"" << ", "
      << "\"meta_name\": " << v.meta_name() << ", "
      << "\"labels\": " << v.labels() << ", "
      << "\"depends\": " << v.depends() << ", "
      << "\"generates\": " << v.generates() << ", "
      << "\"generated_by\": " << "\"" << tidy_up_string(v.generated_by()) << "\"" << ", "
      << "\"technical_space\": " << v.technical_space() << ", "
      << "\"relations\": " << v.relations() << ", "
      << "\"part\": " << v.part() << ", "
      << "\"family\": " << "\"" << tidy_up_string(v.family()) << "\"" << ", "
      << "\"owning_formatters\": " << v.owning_formatters() << ", "
      << "\"owning_facets\": " << v.owning_facets()
      << " }";
    return(s);
}

}
