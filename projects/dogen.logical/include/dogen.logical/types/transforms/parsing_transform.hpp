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
#ifndef DOGEN_LOGICAL_TYPES_TRANSFORMS_PARSING_TRANSFORM_HPP
#define DOGEN_LOGICAL_TYPES_TRANSFORMS_PARSING_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen.logical/types/entities/model.hpp"
#include "dogen.logical/types/entities/attribute.hpp"
#include "dogen.identification/types/entities/technical_space.hpp"
#include "dogen.logical/types/entities/structural/primitive.hpp"
#include "dogen.logical/types/transforms/context_fwd.hpp"

namespace dogen::logical::transforms {

/**
 * @brief Expands all encoded representations that require parsing
 * into their logical form.
 *
 * As an example, all local attributes have unparsed types - strings
 * following a well defined notation - that need to be parsed into
 * name trees. All such forms of encodings are processed by this
 * transform.
 *
 * It is also responsible for reading all meta-data that requires
 * parsing such as parent names, enumeration underlying types and so
 * forth.
 */
class parsing_transform final {
private:
    /**
     * @brief Parses all attributes in the supplied attribute list.
     */
    static void parse_attributes(
        const identification::entities::technical_space ts,
        std::list<entities::attribute>& attrs);

    /**
     * @brief Parses the underlying element in the supplied primitive.
     */
    static void parse_underlying_element(
        const identification::entities::technical_space ts,
        entities::structural::primitive& p);

private:
    /**
     * @brief Parses all objects.
     */
    static void parse_objects(entities::model& m);

    /**
     * @brief Parses all object templates.
     */
    static void parse_object_templates(entities::model& m);

    /**
     * @brief Parses all primitives
     */
    static void parse_primitives(entities::model& m);

    /**
     * @brief Parses all feature template bundles.
     */
    static void parse_feature_template_bundles(entities::model& m);

    /**
     * @brief Parses all feature bundles.
     */
    static void parse_feature_bundles(entities::model& m);


public:
    /**
     * Execute the transform against the model.
     */
    static void apply(const context& ctx, entities::model& m);
};

}

#endif
