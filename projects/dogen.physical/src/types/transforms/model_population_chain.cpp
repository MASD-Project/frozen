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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.physical/io/entities/model_io.hpp"
#include "dogen.physical/types/transforms/transform_exception.hpp"
#include "dogen.physical/types/transforms/paths_transform.hpp"
#include "dogen.physical/types/transforms/enablement_transform.hpp"
#include "dogen.physical/types/transforms/generability_transform.hpp"
#include "dogen.physical/types/transforms/legacy_paths_transform.hpp"
#include "dogen.physical/types/transforms/relations_transform.hpp"
#include "dogen.physical/types/transforms/meta_model_properties_transform.hpp"
#include "dogen.physical/types/transforms/model_population_chain.hpp"

namespace {

const std::string transform_id("physical.transforms.model_population_chain");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

namespace dogen::physical::transforms {

void model_population_chain::apply(const context& ctx, entities::model& m) {
    tracing::scoped_chain_tracer stp(lg, "model population", transform_id,
        m.name().id().value(), *ctx.tracer(), m);

    /*
     * We start by reading all of the properties associated with the
     * meta-model. These are in effect, its configuration.
     */
    meta_model_properties_transform::apply(ctx, m);

    /*
     * The relations transform must be executed prior to the path
     * related transforms.
     */
    relations_transform::apply(ctx, m);

    /*
     * The paths and enablement transforms must be done after the
     * meta-model properties transform, as they use that data as
     * input.
     */
    paths_transform::apply(ctx, m);
    legacy_paths_transform::apply(ctx, m);

    /*
     * Update enablement for all artefacts.
     */
    enablement_transform::apply(ctx, m);

    /*
     * There are no particular dependencies on the next set of
     * transforms.
     */
    generability_transform::apply(ctx, m);

    stp.end_chain(m);
}

}
