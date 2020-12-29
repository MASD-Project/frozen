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
#include "dogen.physical/types/features/filesystem.hpp"
#include "dogen.physical/types/transforms/update_outputting_properties_transform.hpp"

namespace {

const std::string
transform_id("physical.transforms.update_outputting_properties_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

namespace dogen::physical::transforms {

void update_outputting_properties_transform::
apply(const context& ctx, entities::model& m) {
    tracing::scoped_transform_tracer stp(lg,
        "update outputting properties transform", transform_id,
        m.name().simple(), *ctx.tracer(), m);

    const auto fm(*ctx.feature_model());
    const auto fg(features::filesystem::make_feature_group(fm));
    const auto scfg(features::filesystem::make_static_configuration(fg, m));

    auto& op(m.outputting_properties());
    op.force_write(scfg.force_write);
    op.delete_extra_files(scfg.delete_extra_files);
    op.delete_empty_directories(scfg.delete_empty_directories);

    if (!scfg.ignore_files_matching_regex.empty()) {
        auto& ifmr(op.ignore_files_matching_regex());
        const auto& c(scfg.ignore_files_matching_regex);

        ifmr.reserve(c.size());
        for (const auto& e : c)
            ifmr.push_back(e);
    }

    stp.end_transform(m);
}

}
