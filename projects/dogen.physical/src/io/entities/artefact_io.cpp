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
#include "dogen.physical/io/entities/artefact_io.hpp"
#include "dogen.physical/io/entities/operation_io.hpp"
#include "dogen.physical/io/entities/path_properties_io.hpp"
#include "dogen.variability/io/entities/configuration_io.hpp"
#include "dogen.identification/io/entities/physical_name_io.hpp"
#include "dogen.physical/io/entities/relation_properties_io.hpp"
#include "dogen.identification/io/entities/technical_space_io.hpp"
#include "dogen.physical/io/entities/enablement_properties_io.hpp"
#include "dogen.identification/io/entities/logical_provenance_io.hpp"
#include "dogen.identification/io/entities/physical_meta_name_io.hpp"
#include "dogen.identification/io/entities/logical_meta_physical_id_io.hpp"

namespace boost {

inline std::ostream& operator<<(std::ostream& s, const boost::shared_ptr<dogen::variability::entities::configuration>& v) {
    s << "{ " << "\"__type__\": " << "\"boost::shared_ptr\"" << ", "
      << "\"memory\": " << "\"" << static_cast<void*>(v.get()) << "\"" << ", ";

    if (v)
        s << "\"data\": " << *v;
    else
        s << "\"data\": ""\"<null>\"";
    s << " }";
    return s;
}

}

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::vector<boost::filesystem::path>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << "\"" << (*i).generic_string() << "\"";
    }
    s << "] ";
    return s;
}

}

namespace dogen::physical::entities {

std::ostream& operator<<(std::ostream& s, const artefact& v) {
    s << " { "
      << "\"__type__\": " << "\"dogen::physical::entities::artefact\"" << ", "
      << "\"meta_name\": " << v.meta_name() << ", "
      << "\"configuration\": " << v.configuration() << ", "
      << "\"provenance\": " << v.provenance() << ", "
      << "\"name\": " << v.name() << ", "
      << "\"id\": " << v.id() << ", "
      << "\"technical_space\": " << v.technical_space() << ", "
      << "\"file_path\": " << "\"" << v.file_path().generic_string() << "\"" << ", "
      << "\"content\": " << "\"" << tidy_up_string(v.content()) << "\"" << ", "
      << "\"path_properties\": " << v.path_properties() << ", "
      << "\"dependencies\": " << v.dependencies() << ", "
      << "\"unified_diff\": " << "\"" << tidy_up_string(v.unified_diff()) << "\"" << ", "
      << "\"operation\": " << v.operation() << ", "
      << "\"enablement_properties\": " << v.enablement_properties() << ", "
      << "\"formatting_input\": " << "\"" << tidy_up_string(v.formatting_input()) << "\"" << ", "
      << "\"relations\": " << v.relations()
      << " }";
    return(s);
}

}
