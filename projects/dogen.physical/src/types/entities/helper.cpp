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
#include "dogen.physical/types/entities/helper.hpp"

namespace dogen::physical::entities {

helper::helper()
    : technical_space_(static_cast<dogen::identification::entities::technical_space>(0)) { }

helper::helper(
    const std::string& description,
    const dogen::identification::entities::physical_meta_name& meta_name,
    const std::list<dogen::identification::entities::label>& labels,
    const std::list<std::string>& depends,
    const std::list<std::string>& generates,
    const std::string& generated_by,
    const dogen::identification::entities::technical_space technical_space,
    const dogen::physical::entities::relations& relations,
    const dogen::identification::entities::physical_meta_id& part,
    const std::string& family,
    const std::list<dogen::identification::entities::physical_meta_id>& owning_formatters,
    const std::list<dogen::identification::entities::physical_meta_id>& owning_facets)
    : description_(description),
      meta_name_(meta_name),
      labels_(labels),
      depends_(depends),
      generates_(generates),
      generated_by_(generated_by),
      technical_space_(technical_space),
      relations_(relations),
      part_(part),
      family_(family),
      owning_formatters_(owning_formatters),
      owning_facets_(owning_facets) { }

void helper::swap(helper& other) noexcept {
    using std::swap;
    swap(description_, other.description_);
    swap(meta_name_, other.meta_name_);
    swap(labels_, other.labels_);
    swap(depends_, other.depends_);
    swap(generates_, other.generates_);
    swap(generated_by_, other.generated_by_);
    swap(technical_space_, other.technical_space_);
    swap(relations_, other.relations_);
    swap(part_, other.part_);
    swap(family_, other.family_);
    swap(owning_formatters_, other.owning_formatters_);
    swap(owning_facets_, other.owning_facets_);
}

bool helper::operator==(const helper& rhs) const {
    return description_ == rhs.description_ &&
        meta_name_ == rhs.meta_name_ &&
        labels_ == rhs.labels_ &&
        depends_ == rhs.depends_ &&
        generates_ == rhs.generates_ &&
        generated_by_ == rhs.generated_by_ &&
        technical_space_ == rhs.technical_space_ &&
        relations_ == rhs.relations_ &&
        part_ == rhs.part_ &&
        family_ == rhs.family_ &&
        owning_formatters_ == rhs.owning_formatters_ &&
        owning_facets_ == rhs.owning_facets_;
}

helper& helper::operator=(helper other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& helper::description() const {
    return description_;
}

std::string& helper::description() {
    return description_;
}

void helper::description(const std::string& v) {
    description_ = v;
}

void helper::description(const std::string&& v) {
    description_ = std::move(v);
}

const dogen::identification::entities::physical_meta_name& helper::meta_name() const {
    return meta_name_;
}

dogen::identification::entities::physical_meta_name& helper::meta_name() {
    return meta_name_;
}

void helper::meta_name(const dogen::identification::entities::physical_meta_name& v) {
    meta_name_ = v;
}

void helper::meta_name(const dogen::identification::entities::physical_meta_name&& v) {
    meta_name_ = std::move(v);
}

const std::list<dogen::identification::entities::label>& helper::labels() const {
    return labels_;
}

std::list<dogen::identification::entities::label>& helper::labels() {
    return labels_;
}

void helper::labels(const std::list<dogen::identification::entities::label>& v) {
    labels_ = v;
}

void helper::labels(const std::list<dogen::identification::entities::label>&& v) {
    labels_ = std::move(v);
}

const std::list<std::string>& helper::depends() const {
    return depends_;
}

std::list<std::string>& helper::depends() {
    return depends_;
}

void helper::depends(const std::list<std::string>& v) {
    depends_ = v;
}

void helper::depends(const std::list<std::string>&& v) {
    depends_ = std::move(v);
}

const std::list<std::string>& helper::generates() const {
    return generates_;
}

std::list<std::string>& helper::generates() {
    return generates_;
}

void helper::generates(const std::list<std::string>& v) {
    generates_ = v;
}

void helper::generates(const std::list<std::string>&& v) {
    generates_ = std::move(v);
}

const std::string& helper::generated_by() const {
    return generated_by_;
}

std::string& helper::generated_by() {
    return generated_by_;
}

void helper::generated_by(const std::string& v) {
    generated_by_ = v;
}

void helper::generated_by(const std::string&& v) {
    generated_by_ = std::move(v);
}

dogen::identification::entities::technical_space helper::technical_space() const {
    return technical_space_;
}

void helper::technical_space(const dogen::identification::entities::technical_space v) {
    technical_space_ = v;
}

const dogen::physical::entities::relations& helper::relations() const {
    return relations_;
}

dogen::physical::entities::relations& helper::relations() {
    return relations_;
}

void helper::relations(const dogen::physical::entities::relations& v) {
    relations_ = v;
}

void helper::relations(const dogen::physical::entities::relations&& v) {
    relations_ = std::move(v);
}

const dogen::identification::entities::physical_meta_id& helper::part() const {
    return part_;
}

dogen::identification::entities::physical_meta_id& helper::part() {
    return part_;
}

void helper::part(const dogen::identification::entities::physical_meta_id& v) {
    part_ = v;
}

void helper::part(const dogen::identification::entities::physical_meta_id&& v) {
    part_ = std::move(v);
}

const std::string& helper::family() const {
    return family_;
}

std::string& helper::family() {
    return family_;
}

void helper::family(const std::string& v) {
    family_ = v;
}

void helper::family(const std::string&& v) {
    family_ = std::move(v);
}

const std::list<dogen::identification::entities::physical_meta_id>& helper::owning_formatters() const {
    return owning_formatters_;
}

std::list<dogen::identification::entities::physical_meta_id>& helper::owning_formatters() {
    return owning_formatters_;
}

void helper::owning_formatters(const std::list<dogen::identification::entities::physical_meta_id>& v) {
    owning_formatters_ = v;
}

void helper::owning_formatters(const std::list<dogen::identification::entities::physical_meta_id>&& v) {
    owning_formatters_ = std::move(v);
}

const std::list<dogen::identification::entities::physical_meta_id>& helper::owning_facets() const {
    return owning_facets_;
}

std::list<dogen::identification::entities::physical_meta_id>& helper::owning_facets() {
    return owning_facets_;
}

void helper::owning_facets(const std::list<dogen::identification::entities::physical_meta_id>& v) {
    owning_facets_ = v;
}

void helper::owning_facets(const std::list<dogen::identification::entities::physical_meta_id>&& v) {
    owning_facets_ = std::move(v);
}

}
