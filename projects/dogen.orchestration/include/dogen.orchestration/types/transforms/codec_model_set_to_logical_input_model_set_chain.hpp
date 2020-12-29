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
#ifndef DOGEN_ORCHESTRATION_TYPES_TRANSFORMS_CODEC_MODEL_SET_TO_LOGICAL_INPUT_MODEL_SET_CHAIN_HPP
#define DOGEN_ORCHESTRATION_TYPES_TRANSFORMS_CODEC_MODEL_SET_TO_LOGICAL_INPUT_MODEL_SET_CHAIN_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen.codec/types/entities/model_set.hpp"
#include "dogen.logical/types/entities/input_model_set.hpp"
#include "dogen.orchestration/types/transforms/context_fwd.hpp"

namespace dogen::orchestration::transforms {

/**
 * @brief Converts an codec model set into a logical model set.
 *
 * @pre all codec transforms must have been applied to the
 * codec model set.
 */
class codec_model_set_to_logical_input_model_set_chain final {
public:
    static logical::entities::input_model_set
    apply(const context& ctx, const codec::entities::model_set& ms);
};

}

#endif
