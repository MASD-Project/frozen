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
#include "dogen.logical/types/entities/orm/object_properties.hpp"

namespace dogen::logical::entities::orm {

object_properties::object_properties()
    : generate_mapping_(static_cast<bool>(0)),
      is_value_(static_cast<bool>(0)),
      has_primary_key_(static_cast<bool>(0)) { }

object_properties::object_properties(object_properties&& rhs)
    : odb_options_(std::move(rhs.odb_options_)),
      schema_name_(std::move(rhs.schema_name_)),
      capitalised_schema_name_(std::move(rhs.capitalised_schema_name_)),
      letter_case_(std::move(rhs.letter_case_)),
      generate_mapping_(std::move(rhs.generate_mapping_)),
      type_mappings_(std::move(rhs.type_mappings_)),
      odb_pragmas_(std::move(rhs.odb_pragmas_)),
      table_name_(std::move(rhs.table_name_)),
      is_value_(std::move(rhs.is_value_)),
      has_primary_key_(std::move(rhs.has_primary_key_)) { }

object_properties::object_properties(
    const dogen::logical::entities::orm::odb_options& odb_options,
    const std::string& schema_name,
    const std::string& capitalised_schema_name,
    const boost::optional<dogen::logical::entities::orm::letter_case>& letter_case,
    const bool generate_mapping,
    const std::list<dogen::logical::entities::orm::type_mapping>& type_mappings,
    const std::list<std::string>& odb_pragmas,
    const std::string& table_name,
    const bool is_value,
    const bool has_primary_key)
    : odb_options_(odb_options),
      schema_name_(schema_name),
      capitalised_schema_name_(capitalised_schema_name),
      letter_case_(letter_case),
      generate_mapping_(generate_mapping),
      type_mappings_(type_mappings),
      odb_pragmas_(odb_pragmas),
      table_name_(table_name),
      is_value_(is_value),
      has_primary_key_(has_primary_key) { }

void object_properties::swap(object_properties& other) noexcept {
    using std::swap;
    swap(odb_options_, other.odb_options_);
    swap(schema_name_, other.schema_name_);
    swap(capitalised_schema_name_, other.capitalised_schema_name_);
    swap(letter_case_, other.letter_case_);
    swap(generate_mapping_, other.generate_mapping_);
    swap(type_mappings_, other.type_mappings_);
    swap(odb_pragmas_, other.odb_pragmas_);
    swap(table_name_, other.table_name_);
    swap(is_value_, other.is_value_);
    swap(has_primary_key_, other.has_primary_key_);
}

bool object_properties::operator==(const object_properties& rhs) const {
    return odb_options_ == rhs.odb_options_ &&
        schema_name_ == rhs.schema_name_ &&
        capitalised_schema_name_ == rhs.capitalised_schema_name_ &&
        letter_case_ == rhs.letter_case_ &&
        generate_mapping_ == rhs.generate_mapping_ &&
        type_mappings_ == rhs.type_mappings_ &&
        odb_pragmas_ == rhs.odb_pragmas_ &&
        table_name_ == rhs.table_name_ &&
        is_value_ == rhs.is_value_ &&
        has_primary_key_ == rhs.has_primary_key_;
}

object_properties& object_properties::operator=(object_properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::logical::entities::orm::odb_options& object_properties::odb_options() const {
    return odb_options_;
}

dogen::logical::entities::orm::odb_options& object_properties::odb_options() {
    return odb_options_;
}

void object_properties::odb_options(const dogen::logical::entities::orm::odb_options& v) {
    odb_options_ = v;
}

void object_properties::odb_options(const dogen::logical::entities::orm::odb_options&& v) {
    odb_options_ = std::move(v);
}

const std::string& object_properties::schema_name() const {
    return schema_name_;
}

std::string& object_properties::schema_name() {
    return schema_name_;
}

void object_properties::schema_name(const std::string& v) {
    schema_name_ = v;
}

void object_properties::schema_name(const std::string&& v) {
    schema_name_ = std::move(v);
}

const std::string& object_properties::capitalised_schema_name() const {
    return capitalised_schema_name_;
}

std::string& object_properties::capitalised_schema_name() {
    return capitalised_schema_name_;
}

void object_properties::capitalised_schema_name(const std::string& v) {
    capitalised_schema_name_ = v;
}

void object_properties::capitalised_schema_name(const std::string&& v) {
    capitalised_schema_name_ = std::move(v);
}

const boost::optional<dogen::logical::entities::orm::letter_case>& object_properties::letter_case() const {
    return letter_case_;
}

boost::optional<dogen::logical::entities::orm::letter_case>& object_properties::letter_case() {
    return letter_case_;
}

void object_properties::letter_case(const boost::optional<dogen::logical::entities::orm::letter_case>& v) {
    letter_case_ = v;
}

void object_properties::letter_case(const boost::optional<dogen::logical::entities::orm::letter_case>&& v) {
    letter_case_ = std::move(v);
}

bool object_properties::generate_mapping() const {
    return generate_mapping_;
}

void object_properties::generate_mapping(const bool v) {
    generate_mapping_ = v;
}

const std::list<dogen::logical::entities::orm::type_mapping>& object_properties::type_mappings() const {
    return type_mappings_;
}

std::list<dogen::logical::entities::orm::type_mapping>& object_properties::type_mappings() {
    return type_mappings_;
}

void object_properties::type_mappings(const std::list<dogen::logical::entities::orm::type_mapping>& v) {
    type_mappings_ = v;
}

void object_properties::type_mappings(const std::list<dogen::logical::entities::orm::type_mapping>&& v) {
    type_mappings_ = std::move(v);
}

const std::list<std::string>& object_properties::odb_pragmas() const {
    return odb_pragmas_;
}

std::list<std::string>& object_properties::odb_pragmas() {
    return odb_pragmas_;
}

void object_properties::odb_pragmas(const std::list<std::string>& v) {
    odb_pragmas_ = v;
}

void object_properties::odb_pragmas(const std::list<std::string>&& v) {
    odb_pragmas_ = std::move(v);
}

const std::string& object_properties::table_name() const {
    return table_name_;
}

std::string& object_properties::table_name() {
    return table_name_;
}

void object_properties::table_name(const std::string& v) {
    table_name_ = v;
}

void object_properties::table_name(const std::string&& v) {
    table_name_ = std::move(v);
}

bool object_properties::is_value() const {
    return is_value_;
}

void object_properties::is_value(const bool v) {
    is_value_ = v;
}

bool object_properties::has_primary_key() const {
    return has_primary_key_;
}

void object_properties::has_primary_key(const bool v) {
    has_primary_key_ = v;
}

}
