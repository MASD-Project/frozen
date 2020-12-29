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
#include <boost/make_shared.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/string/splitter.hpp"
#include "dogen.variability/io/entities/value_type_io.hpp"
#include "dogen.variability/types/entities/text.hpp"
#include "dogen.variability/types/entities/number.hpp"
#include "dogen.variability/types/entities/boolean.hpp"
#include "dogen.variability/types/entities/key_value_pair.hpp"
#include "dogen.variability/types/entities/text_collection.hpp"
#include "dogen.variability/types/entities/comma_separated.hpp"
#include "dogen.variability/types/entities/comma_separated_collection.hpp"
#include "dogen.variability/types/helpers/building_exception.hpp"
#include "dogen.variability/types/helpers/value_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("variability.helpers.value_factory"));

const std::string invalid_numeric_value("Invalid numeric value: ");
const std::string invalid_boolean_value("Invalid boolean value: ");
const std::string value_type_not_supported(
    "Value type is not supported by factory: ");
const std::string expected_at_most_one_element("Expected at most one element");
const std::string empty_collection("Collection is empty");

/**
 * @brief Provides support for "true" and "false" as Boolean values.
 */
class locale_bool {
public:
    locale_bool() {}
    locale_bool(bool data) : data(data) {}

public:
    operator bool() const { return data; }

    [[maybe_unused]]
    friend std::istream& operator>>(std::istream &s, locale_bool &b) {
        s >> std::boolalpha >> b.data;
        return s;
    }

private:
    bool data;
};

}

namespace dogen::variability::helpers {

int value_factory::to_int(const std::string& s) const {
    try {
        return boost::lexical_cast<int>(s);
    } catch (const boost::bad_lexical_cast& /*e*/) {
        BOOST_LOG_SEV(lg, error) << invalid_numeric_value << s;
        BOOST_THROW_EXCEPTION(building_exception(invalid_numeric_value + s));
    }
}

bool value_factory::to_bool(const std::string& s) const {
    try {
        return boost::lexical_cast<locale_bool>(s);
    } catch (const boost::bad_lexical_cast& /*e*/) {
        BOOST_LOG_SEV(lg, error) << invalid_boolean_value << s;
        BOOST_THROW_EXCEPTION(building_exception(invalid_boolean_value + s));
    }
}

void value_factory::
ensure_at_most_one_element(const std::list<std::string>& raw_values) const {

    if (raw_values.empty())
        return;

    const auto i(++raw_values.begin());
    if (i != raw_values.end()) {
        BOOST_LOG_SEV(lg, error) << expected_at_most_one_element;
        BOOST_THROW_EXCEPTION(building_exception(expected_at_most_one_element));
    }
}

void value_factory::
ensure_non_empty(const std::list<std::string>& raw_values) const {
    if (raw_values.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_collection;
        BOOST_THROW_EXCEPTION(building_exception(empty_collection));
    }
}

bool value_factory::is_collection(const entities::value_type vt) const {
    return vt == entities::value_type::text_collection;
}

boost::shared_ptr<entities::value>
value_factory::make_text(const std::string& v) const {
    return boost::make_shared<entities::text>(v);
}

boost::shared_ptr<entities::value> value_factory::make_text_collection(
    const std::list<std::string>& v) const {
    auto r(boost::make_shared<entities::text_collection>(v));
    return r;
}

boost::shared_ptr<entities::value>
value_factory::make_boolean(const std::string& v) const {
    return boost::make_shared<entities::boolean>(to_bool(v));
}

boost::shared_ptr<entities::value>
value_factory::make_boolean(const bool v) const {
    return boost::make_shared<entities::boolean>(v);
}

boost::shared_ptr<entities::value>
value_factory::make_number(const std::string& v) const {
    return boost::make_shared<entities::number>(to_int(v));
}

boost::shared_ptr<entities::value>
value_factory::make_number(const int v) const {
    return boost::make_shared<entities::number>(v);
}

boost::shared_ptr<entities::value> value_factory::
make_kvp(const std::list<std::pair<std::string, std::string>>& v) const {
    return boost::make_shared<entities::key_value_pair>(v);
}

boost::shared_ptr<entities::value> value_factory::
make_comma_separated(const std::string& v) const {
    using utility::string::splitter;
    const auto splitted(splitter::split_csv(v));
    return boost::make_shared<entities::comma_separated>(splitted);
}

boost::shared_ptr<entities::value> value_factory::
make_comma_separated_collection(const std::list<std::string>& v) const {
    using utility::string::splitter;
    std::list<std::list<std::string>> value;
    for (const auto& entry: v)
        value.push_back(splitter::split_csv(entry));

    return boost::make_shared<entities::comma_separated_collection>(value);
}

boost::shared_ptr<entities::value> value_factory::
make(const entities::value_type& vt, const std::list<std::string>& v) const {
    ensure_non_empty(v);

    using entities::value_type;
    switch (vt) {
     case value_type::text:
        return make_text(v.front());
    case value_type::text_collection:
        return make_text_collection(v);
    case value_type::boolean:
        return make_boolean(v.front());
    case value_type::number:
        return make_number(v.front());
    case value_type::comma_separated:
        return make_comma_separated(v.front());
    case value_type::comma_separated_collection:
        return make_comma_separated_collection(v);
    default:
        break;
    }

    const auto s(boost::lexical_cast<std::string>(vt));
    BOOST_LOG_SEV(lg, error) << value_type_not_supported << s;
    BOOST_THROW_EXCEPTION(building_exception(value_type_not_supported + s));
}

boost::shared_ptr<entities::value> value_factory::
make(const entities::feature& f, const std::list<std::string>& v) const {
    ensure_non_empty(v);
    if (!is_collection(f.value_type()))
        ensure_at_most_one_element(v);

    return make(f.value_type(), v);
}

boost::shared_ptr<entities::value>
value_factory::make(const entities::feature& f,
    const std::list<std::pair<std::string, std::string>>& v) const {
    if (f.value_type() != entities::value_type::key_value_pair) {
        const auto s(boost::lexical_cast<std::string>(f.value_type()));
        BOOST_LOG_SEV(lg, error) << value_type_not_supported << s;
        BOOST_THROW_EXCEPTION(building_exception(value_type_not_supported + s));;
    }
    return make_kvp(v);
}

}
