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
#ifndef DOGEN_PHYSICAL_TYPES_TRANSFORMS_META_MODEL_PRODUCTION_CHAIN_HPP
#define DOGEN_PHYSICAL_TYPES_TRANSFORMS_META_MODEL_PRODUCTION_CHAIN_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <boost/shared_ptr.hpp>
#include "dogen.physical/types/transforms/minimal_context.hpp"
#include "dogen.physical/types/entities/backend.hpp"
#include "dogen.physical/types/entities/meta_model.hpp"

namespace dogen::physical::transforms {

/**
 * @brief Produces a complete physical meta-model from a set of
 * initial parts.
 */
class meta_model_production_chain final {
public:
    /**
     * @brief Apply the transform to generate a meta-model.
     */
    static boost::shared_ptr<physical::entities::meta_model>
    apply(const physical::transforms::minimal_context& ctx,
        const std::list<entities::backend>& bes);
};

}

#endif
