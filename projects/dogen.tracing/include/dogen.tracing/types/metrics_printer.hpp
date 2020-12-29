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
#ifndef DOGEN_TRACING_TYPES_METRICS_PRINTER_HPP
#define DOGEN_TRACING_TYPES_METRICS_PRINTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <ostream>
#include <boost/shared_ptr.hpp>
#include "dogen/types/tracing_format.hpp"
#include "dogen.tracing/types/metrics.hpp"

namespace dogen::tracing {

class metrics_printer final {
private:
    static void print_plain(std::ostream& o, unsigned int fill_level,
        const bool disable_guids, const boost::shared_ptr<const metrics> tm);

    static void print_org_mode(std::ostream& o, unsigned int fill_level,
        const bool disable_guids, const boost::shared_ptr<const metrics> tm);

    static void print_graphviz(std::ostream& table_stream,
        std::ostream& vertex_stream, const bool disable_guids,
        const std::string& parent_id,
        const boost::shared_ptr<const metrics> tm);

    static void print_graphviz(std::ostream& o,
        const bool disable_guids, const boost::shared_ptr<const metrics> tm);

public:
    static std::string
    print(const bool disable_guids, const tracing_format tf,
        const boost::shared_ptr<const metrics> tm);
};

}

#endif
