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
#include "dogen/io/configuration_io.hpp"
#include "dogen.cli/io/configuration_io.hpp"
#include "dogen.cli/io/cli_configuration_io.hpp"
#include "dogen.utility/io/log/logging_configuration_io.hpp"

namespace boost {

inline std::ostream& operator<<(std::ostream& s, const boost::optional<dogen::utility::log::logging_configuration>& v) {
    s << "{ " << "\"__type__\": " << "\"boost::optional\"" << ", ";

    if (v)
        s << "\"data\": " << *v;
    else
        s << "\"data\": ""\"<null>\"";
    s << " }";
    return s;
}

}

namespace dogen::cli {

std::ostream& operator<<(std::ostream& s, const configuration& v) {
    s << " { "
      << "\"__type__\": " << "\"dogen::cli::configuration\"" << ", "
      << "\"logging\": " << v.logging() << ", "
      << "\"api\": " << v.api() << ", "
      << "\"cli\": " << v.cli()
      << " }";
    return(s);
}

}
