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
#include "dogen.logical/types/entities/orm/model_properties.hpp"

namespace dogen::logical::entities::orm {

model_properties::model_properties(model_properties&& rhs)
    : schema_name_(std::move(rhs.schema_name_)),
      capitalised_schema_name_(std::move(rhs.capitalised_schema_name_)),
      letter_case_(std::move(rhs.letter_case_)),
      database_systems_(std::move(rhs.database_systems_)) { }

model_properties::model_properties(
    const std::string& schema_name,
    const std::string& capitalised_schema_name,
    const boost::optional<dogen::logical::entities::orm::letter_case>& letter_case,
    const std::vector<dogen::logical::entities::orm::database_system>& database_systems)
    : schema_name_(schema_name),
      capitalised_schema_name_(capitalised_schema_name),
      letter_case_(letter_case),
      database_systems_(database_systems) { }

void model_properties::swap(model_properties& other) noexcept {
    using std::swap;
    swap(schema_name_, other.schema_name_);
    swap(capitalised_schema_name_, other.capitalised_schema_name_);
    swap(letter_case_, other.letter_case_);
    swap(database_systems_, other.database_systems_);
}

bool model_properties::operator==(const model_properties& rhs) const {
    return schema_name_ == rhs.schema_name_ &&
        capitalised_schema_name_ == rhs.capitalised_schema_name_ &&
        letter_case_ == rhs.letter_case_ &&
        database_systems_ == rhs.database_systems_;
}

model_properties& model_properties::operator=(model_properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& model_properties::schema_name() const {
    return schema_name_;
}

std::string& model_properties::schema_name() {
    return schema_name_;
}

void model_properties::schema_name(const std::string& v) {
    schema_name_ = v;
}

void model_properties::schema_name(const std::string&& v) {
    schema_name_ = std::move(v);
}

const std::string& model_properties::capitalised_schema_name() const {
    return capitalised_schema_name_;
}

std::string& model_properties::capitalised_schema_name() {
    return capitalised_schema_name_;
}

void model_properties::capitalised_schema_name(const std::string& v) {
    capitalised_schema_name_ = v;
}

void model_properties::capitalised_schema_name(const std::string&& v) {
    capitalised_schema_name_ = std::move(v);
}

const boost::optional<dogen::logical::entities::orm::letter_case>& model_properties::letter_case() const {
    return letter_case_;
}

boost::optional<dogen::logical::entities::orm::letter_case>& model_properties::letter_case() {
    return letter_case_;
}

void model_properties::letter_case(const boost::optional<dogen::logical::entities::orm::letter_case>& v) {
    letter_case_ = v;
}

void model_properties::letter_case(const boost::optional<dogen::logical::entities::orm::letter_case>&& v) {
    letter_case_ = std::move(v);
}

const std::vector<dogen::logical::entities::orm::database_system>& model_properties::database_systems() const {
    return database_systems_;
}

std::vector<dogen::logical::entities::orm::database_system>& model_properties::database_systems() {
    return database_systems_;
}

void model_properties::database_systems(const std::vector<dogen::logical::entities::orm::database_system>& v) {
    database_systems_ = v;
}

void model_properties::database_systems(const std::vector<dogen::logical::entities::orm::database_system>&& v) {
    database_systems_ = std::move(v);
}

}
