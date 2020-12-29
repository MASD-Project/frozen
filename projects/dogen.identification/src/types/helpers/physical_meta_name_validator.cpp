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
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.identification/types/helpers/validation_error.hpp"
#include "dogen.identification/types/helpers/physical_meta_name_validator.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory(
        "identification.helpers.physical_meta_name_validator"));

const std::string empty_simple("Simple name is empty.");
const std::string empty_qualified("Qualified name is empty.");
const std::string empty_meta_model("Meta-model name is empty.");
const std::string empty_backend("Backend name is empty.");
const std::string empty_part("Part name is empty.");
const std::string empty_facet("Facet name is empty.");
const std::string non_empty_backend("Backend name is not empty.");
const std::string non_empty_facet("Facet name is not empty.");
const std::string empty_archetype("Archetype is empty.");
const std::string non_empty_archetype("Archetype is not empty.");

}

namespace dogen::identification::helpers {

void physical_meta_name_validator::common_validation(
    const entities::physical_meta_name& mn, const bool is_meta_model) {
    /*
     * Simple name must be populated.
     */
    if (mn.simple().empty()) {
        BOOST_LOG_SEV(lg, error) << empty_simple;
        BOOST_THROW_EXCEPTION(validation_error(empty_simple));
    }

    /*
     * ID must be populated.
     */
    if (mn.id().value().empty()) {
        BOOST_LOG_SEV(lg, error) << empty_qualified;
        BOOST_THROW_EXCEPTION(validation_error(empty_qualified));
    }

    /*
     * All locations must belong to a meta-model.
     */
    const auto& l(mn.location());
    if (l.meta_model().empty()) {
        BOOST_LOG_SEV(lg, error) << empty_meta_model;
        BOOST_THROW_EXCEPTION(validation_error(empty_meta_model));
    }

    if (!is_meta_model) {
        /*
         * All locations must belong to a backend.
         */
        if (l.backend().empty()) {
            BOOST_LOG_SEV(lg, error) << empty_backend;
            BOOST_THROW_EXCEPTION(validation_error(empty_backend));
        }
    }
}

void physical_meta_name_validator::
validate_meta_model_name(const entities::physical_meta_name& mn) {
    common_validation(mn, true/*is_meta_model*/);

    /*
     * Backend must not be populated.
     */
    const auto& l(mn.location());
    if (!l.backend().empty()) {
        BOOST_LOG_SEV(lg, error) << non_empty_backend;
        BOOST_THROW_EXCEPTION(validation_error(non_empty_backend));
    }

    /*
     * Facet must not be populated.
     */
    if (!l.facet().empty()) {
        BOOST_LOG_SEV(lg, error) << non_empty_facet;
        BOOST_THROW_EXCEPTION(validation_error(non_empty_facet));
    }

    /*
     * Archetype must not be populated.
     */
    if (!l.archetype().empty()) {
        BOOST_LOG_SEV(lg, error) << non_empty_archetype;
        BOOST_THROW_EXCEPTION(validation_error(non_empty_archetype));
    }
}

void physical_meta_name_validator::
validate_backend_name(const entities::physical_meta_name& mn) {
    common_validation(mn, false/*is_meta_model*/);

    /*
     * Backend must be populated.
     */
    const auto& l(mn.location());
    if (l.backend().empty()) {
        BOOST_LOG_SEV(lg, error) << empty_backend;
        BOOST_THROW_EXCEPTION(validation_error(empty_backend));
    }

    /*
     * Facet must not be populated.
     */
    if (!l.facet().empty()) {
        BOOST_LOG_SEV(lg, error) << non_empty_facet;
        BOOST_THROW_EXCEPTION(validation_error(non_empty_facet));
    }

    /*
     * Archetype must not be populated.
     */
    if (!l.archetype().empty()) {
        BOOST_LOG_SEV(lg, error) << non_empty_archetype;
        BOOST_THROW_EXCEPTION(validation_error(non_empty_archetype));
    }
}

void physical_meta_name_validator::
validate_part_name(const entities::physical_meta_name& mn) {
    common_validation(mn, false/*is_meta_model*/);
    /*
     * Backend must be populated.
     */
    const auto& l(mn.location());
    if (l.backend().empty()) {
        BOOST_LOG_SEV(lg, error) << empty_backend;
        BOOST_THROW_EXCEPTION(validation_error(empty_backend));
    }

    /*
     * Part must be populated.
     */
    if (l.part().empty()) {
        BOOST_LOG_SEV(lg, error) << empty_part;
        BOOST_THROW_EXCEPTION(validation_error(empty_part));
    }

    /*
     * Facet must not be populated.
     */
    if (!l.facet().empty()) {
        BOOST_LOG_SEV(lg, error) << non_empty_facet;
        BOOST_THROW_EXCEPTION(validation_error(non_empty_facet));
    }

    /*
     * Archetype must not be populated.
     */
    if (!l.archetype().empty()) {
        BOOST_LOG_SEV(lg, error) << non_empty_archetype;
        BOOST_THROW_EXCEPTION(validation_error(non_empty_archetype));
    }
}


void physical_meta_name_validator::
validate_facet_name(const entities::physical_meta_name& mn) {
    common_validation(mn, false/*is_meta_model*/);

    /*
     * Backend must be populated.
     */
    const auto& l(mn.location());
    if (l.backend().empty()) {
        BOOST_LOG_SEV(lg, error) << empty_backend;
        BOOST_THROW_EXCEPTION(validation_error(empty_backend));
    }

    /*
     * Part must be populated. FIXME: disabled until part processing
     * is implemented correctly.
     */
    if (l.part().empty()) {
        BOOST_LOG_SEV(lg, error) << empty_part;
        // BOOST_THROW_EXCEPTION(validation_error(empty_part));
    }

    /*
     * Facet must be populated.
     */
    if (l.facet().empty()) {
        BOOST_LOG_SEV(lg, error) << empty_facet;
        BOOST_THROW_EXCEPTION(validation_error(empty_facet));
    }

    /*
     * Archetype must not be populated.
     */
    if (!l.archetype().empty()) {
        BOOST_LOG_SEV(lg, error) << non_empty_archetype;
        BOOST_THROW_EXCEPTION(validation_error(non_empty_archetype));
    }
}

void physical_meta_name_validator::
validate_archetype_name(const entities::physical_meta_name& mn) {
    common_validation(mn, false/*is_meta_model*/);

    /*
     * All locations must belong to a facet.
     */
    const auto& l(mn.location());
    if (l.facet().empty()) {
        BOOST_LOG_SEV(lg, error) << empty_facet;
        BOOST_THROW_EXCEPTION(validation_error(empty_facet));
    }

    /*
     * Archetype must be populated
     */
    if (l.archetype().empty()) {
        BOOST_LOG_SEV(lg, error) << empty_archetype;
        BOOST_THROW_EXCEPTION(validation_error(empty_archetype));
    }
}

}
