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
#ifndef DOGEN_LEXICAL_CAST_REPORTING_STYLE_LC_HPP
#define DOGEN_LEXICAL_CAST_REPORTING_STYLE_LC_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/lexical_cast.hpp>
#include "dogen/types/reporting_style.hpp"

namespace boost {

template<>
inline std::string lexical_cast(const dogen::reporting_style& v) {
    using dogen::reporting_style;

    switch (v) {
    case reporting_style::invalid:
        return "reporting_style::invalid";
    case reporting_style::plain:
        return "reporting_style::plain";
    case reporting_style::org_mode:
        return "reporting_style::org_mode";
    default:
        throw boost::bad_lexical_cast();
    }
}

template<>
inline dogen::reporting_style lexical_cast(const std::string & s) {
    using dogen::reporting_style;

    if (s == "invalid" || s == "reporting_style::invalid")
        return reporting_style::invalid;
    if (s == "plain" || s == "reporting_style::plain")
        return reporting_style::plain;
    if (s == "org_mode" || s == "reporting_style::org_mode")
        return reporting_style::org_mode;
    throw boost::bad_lexical_cast();
}

}

#endif
