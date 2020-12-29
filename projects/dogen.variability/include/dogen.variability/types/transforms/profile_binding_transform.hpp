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
#ifndef DOGEN_VARIABILITY_TYPES_TRANSFORMS_PROFILE_BINDING_TRANSFORM_HPP
#define DOGEN_VARIABILITY_TYPES_TRANSFORMS_PROFILE_BINDING_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <unordered_set>
#include "dogen.variability/types/entities/binding_point.hpp"
#include "dogen.variability/types/entities/feature.hpp"
#include "dogen.variability/types/entities/feature_model.hpp"
#include "dogen.variability/types/entities/profile_repository.hpp"
#include "dogen.variability/types/entities/configuration_model.hpp"
#include "dogen.variability/types/entities/configuration_model_set.hpp"
#include "dogen.variability/types/transforms/context.hpp"

namespace dogen::variability::transforms {

/**
 * @brief Binds configurations to profiles.
 */
class profile_binding_transform final {
private:
    struct feature_group {
        entities::feature profile;
    };

    static feature_group
    make_feature_group(const entities::feature_model& fm);

    static std::string obtain_profile_name(const feature_group& fg,
        const entities::configuration& cfg);

private:
    /**
     * @brief Given a binding point, returns the well-known name of
     * its the default profile.
     */
    static std::string get_default_profile_name_for_binding_point(
        const entities::binding_point bp);

private:
    /**
     * @brief Resolves potential binds into profiles, and handles the
     * base layer merging.
     */
    static void handle_potential_bindings(
        const bool has_base_layer,
        const entities::profile_repository& prp,
        entities::configuration& cfg);

    /**
     * @brief Binds profiles to the supplied configuration.
     */
    static void bind(const entities::profile_repository& prp,
        const feature_group& fg, entities::configuration& cfg);

private:
    /**
     * @brief Runs the transform on a single configuration model.
     */
    static void apply(const entities::profile_repository& prp,
        const entities::feature_model& fm,
        entities::configuration_model& cm);

public:
    /**
     * @brief Runs the transform on an entire configuration model set.
     */
    static void apply(const context& ctx,
        const entities::feature_model& fm,
        const entities::profile_repository& prp,
        entities::configuration_model_set& cms);
};

}

#endif
