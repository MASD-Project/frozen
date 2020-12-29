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
#ifndef DOGEN_LOGICAL_TYPES_HELPERS_CONFIGURATION_MODEL_SET_ADAPTER_HPP
#define DOGEN_LOGICAL_TYPES_HELPERS_CONFIGURATION_MODEL_SET_ADAPTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen.variability/types/entities/configuration_model_set.hpp"
#include "dogen.logical/types/entities/input_model_set.hpp"

namespace dogen::logical::helpers {

/**
 * @brief Adapts a logical model set into its counterpart in
 * variability, extracting all of the configuration information.
 */
class configuration_model_set_adapter final {
private:
    /**
     * @brief Adapts a single model.
     */
    static variability::entities::configuration_model
    adapt(const entities::model& m);

public:
    /**
     * @brief Adapts all models in a model set.
     */
    static variability::entities::configuration_model_set
    adapt(const entities::input_model_set& ms);
};

}

#endif
