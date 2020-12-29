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
#include "dogen.utility/types/io/list_io.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.variability/io/entities/feature_io.hpp"
#include "dogen.variability/types/helpers/template_instantiator.hpp"
#include "dogen.variability/io/entities/feature_template_repository_io.hpp"
#include "dogen.variability/types/transforms/feature_template_instantiation_transform.hpp"

namespace {

const std::string transform_id(
    "variability.transforms.feature_template_instantiation_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

namespace dogen::variability::transforms {

std::list<entities::feature>
feature_template_instantiation_transform::apply(const context& ctx,
    const entities::feature_template_repository& ftrp) {
    tracing::scoped_transform_tracer stp(lg,
        "feature template instantiation transform",
        transform_id, "feature_repository", *ctx.tracer(), ftrp);

    unsigned int counter(0);
    std::list<entities::feature> r;
    const auto& tids(ctx.template_instantiation_domains());
    helpers::template_instantiator ti(ctx.compatibility_mode());
    for (const auto& ft : ftrp.templates()) {
        r.splice(r.end(), ti.instantiate(tids, ft));
        ++counter;
    }

    BOOST_LOG_SEV(lg, trace)  << "Instantiated features: " << r;
    BOOST_LOG_SEV(lg, debug) << "Total number of templates instantiated: "
                             << counter;

    stp.end_transform(r);
    return r;
}

}
