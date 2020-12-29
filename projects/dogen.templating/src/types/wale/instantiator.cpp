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
#include "dogen.utility/types/io/unordered_map_io.hpp"
#include "dogen.utility/types/filesystem/path.hpp"
#include "dogen.utility/types/filesystem/file.hpp"
#include "dogen.templating/types/wale/key_extractor.hpp"
#include "dogen.templating/types/wale/formatter.hpp"
#include "dogen.templating/types/helpers/kvp_validator.hpp"
#include "dogen.templating/types/wale/instantiator.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("templating.wale.instantiator"));

}

namespace dogen::templating::wale {

std::string instantiator::
read_content(const boost::filesystem::path& template_path) const {
    BOOST_LOG_SEV(lg, debug) << "Reading content. Path: " << template_path;
    using utility::filesystem::read_file_content;
    return read_file_content(template_path);
}

std::unordered_set<std::string>
instantiator::get_expected_keys(const std::string& s) const {
    key_extractor ke;
    const auto r(ke.extract(s));
    return r;
}

std::string instantiator::format(const text_template& tt) const {
    formatter fmt;
    return fmt.format(tt);
}

void instantiator::validate(const text_template& tt) const {
    helpers::kvp_validator v;
    v.validate(tt.expected_keys(), tt.supplied_kvps());
}

std::string instantiator::instantiate(const std::string& template_content,
    const std::unordered_map<std::string, std::string>& kvps) const {
    BOOST_LOG_SEV(lg, debug) << "Executing instantiator.";

    /*
     * Create the template for the supplied path.
     */
    text_template tt;
    tt.supplied_kvps(kvps);
    tt.content(template_content);
    tt.expected_keys(get_expected_keys(tt.content()));

    /*
     * Validate the template
     */
    validate(tt);

    /*
     * Obtain the output of instantiation.
     */
    const auto r(format(tt));
    BOOST_LOG_SEV(lg, debug) << "Finished instantiation. Result: " << r;
    return r;
}

std::string
instantiator::instantiate(const boost::filesystem::path& template_path,
    const std::unordered_map<std::string, std::string>& kvps) const {
    BOOST_LOG_SEV(lg, debug) << "Executing instantiator.";

    /*
     * Create the template for the supplied path.
     */
    text_template tt;
    tt.supplied_kvps(kvps);
    tt.content(read_content(template_path));
    tt.expected_keys(get_expected_keys(tt.content()));

    /*
     * Validate the template
     */
    validate(tt);

    /*
     * Obtain the output of instantiation.
     */
    const auto r(format(tt));
    BOOST_LOG_SEV(lg, debug) << "Finished instantiation. Result: " << r;
    return r;
}

}
