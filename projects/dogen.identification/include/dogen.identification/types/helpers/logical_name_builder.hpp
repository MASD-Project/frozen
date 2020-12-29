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
#ifndef DOGEN_IDENTIFICATION_TYPES_HELPERS_LOGICAL_NAME_BUILDER_HPP
#define DOGEN_IDENTIFICATION_TYPES_HELPERS_LOGICAL_NAME_BUILDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include "dogen.identification/types/entities/logical_name.hpp"
#include "dogen.identification/types/entities/logical_location.hpp"
#include "dogen.identification/types/helpers/logical_location_builder.hpp"

namespace dogen::identification::helpers {

/**
 * @brief Builds a name.
 *
 * If setup in model name mode, the following will hold:
 *
 * @li the simple name will be set from the model name (and cannot be
 * set individually);
 * @li the model name will not contribute to the qualified name.
 */
class logical_name_builder {
public:
    explicit logical_name_builder(const bool model_name_mode_ = false);

public:
    void simple_name(const std::string& sn);
    void model_name(const std::string& mn);
    void model_name(const entities::logical_location& l);
    void external_modules(const std::string& em);
    void external_modules(const std::list<std::string>& em);
    void model_modules(const std::string& mm);
    void model_modules(const std::list<std::string>& mm);
    void internal_modules(const std::string& im);
    void internal_modules(const std::list<std::string>& im);
    void location(const entities::logical_location& l);
    void is_container(const bool is_container);

public:
    entities::logical_name build();

public:
    /**
     * @brief One shot-builder method that, given a list of names,
     * performs some heuristics to build a vaguely plausible name.
     *
     * @param names List of names. By copy non-const by design.
     */
    static entities::logical_name build(std::list<std::string> names);

    /**
     * @brief One shot-builder method that, given a string encoded
     * with a list of names, splits it into a list of names and
     * performs some heuristics to build a vaguely plausible name.
     *
     * @param names String encodes a list of names.
     */
    static entities::logical_name build(const std::string& names);

private:
    const bool model_name_mode_;
    entities::logical_name name_;
    logical_location_builder location_builder_;
};

}

#endif
