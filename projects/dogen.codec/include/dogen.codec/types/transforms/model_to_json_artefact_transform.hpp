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
#ifndef DOGEN_CODEC_TYPES_TRANSFORMS_MODEL_TO_JSON_ARTEFACT_TRANSFORM_HPP
#define DOGEN_CODEC_TYPES_TRANSFORMS_MODEL_TO_JSON_ARTEFACT_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <map>
#include <string>
#include <iosfwd>
#include <unordered_map>
#include <boost/optional.hpp>
#include <boost/filesystem/path.hpp>
#include "dogen.codec/types/entities/model.hpp"
#include "dogen.codec/types/entities/element.hpp"
#include "dogen.codec/types/entities/attribute.hpp"
#include "dogen.codec/types/entities/artefact.hpp"
#include "dogen.codec/types/transforms/context.hpp"

namespace dogen::codec::transforms {

/**
 * @brief Transforms the supplied codec model into an artefact encoded
 * using JSON.
 */
class model_to_json_artefact_transform final {
private:
    static std::string tidy_up_string(std::string s);

private:
    static void insert_documentation(std::ostream& s, const std::string& d);
    static void insert_tagged_values(std::ostream& s,
        const std::list<identification::entities::tagged_value>& tvs);
    static void insert_stereotypes(std::ostream& s,
        const std::list<identification::entities::stereotype>& sts);
    static void insert_parents(std::ostream& s,
        const std::list<std::string>& parents);
    static void insert_attribute(std::ostream& s,
        const codec::entities::attribute& a);
    static void insert_element(std::ostream& s,
        const codec::entities::element& e);
    static std::string to_string(const codec::entities::model& m);

public:
    static entities::artefact
    apply(const transforms::context& ctx, const boost::filesystem::path& p,
        const entities::model& m);
};

}

#endif
