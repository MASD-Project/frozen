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
#include <ostream>
#include "dogen.logical/io/entities/element_io.hpp"
#include "dogen.logical/io/entities/orm/odb_targets_io.hpp"
#include "dogen.logical/types/entities/element_visitor.hpp"
#include "dogen.logical/types/entities/visual_studio/msbuild_targets.hpp"

namespace dogen::logical::entities::visual_studio {

msbuild_targets::msbuild_targets(
    const dogen::identification::entities::logical_name& name,
    const std::string& documentation,
    const dogen::identification::entities::codec_provenance& provenance,
    const dogen::identification::entities::logical_id& contained_by,
    const bool in_global_module,
    const dogen::logical::entities::stereotypes& stereotypes,
    const dogen::identification::entities::logical_meta_name& meta_name,
    const dogen::identification::entities::technical_space intrinsic_technical_space,
    const boost::shared_ptr<dogen::variability::entities::configuration>& configuration,
    const std::list<dogen::identification::entities::label>& labels,
    const dogen::logical::entities::generability_status generability_status,
    const std::unordered_map<dogen::identification::entities::technical_space, boost::optional<dogen::logical::entities::decoration::element_properties> >& decoration,
    const std::list<dogen::logical::entities::helper_properties>& helper_properties,
    const dogen::logical::entities::orm::odb_targets& odb_targets)
    : dogen::logical::entities::element(
      name,
      documentation,
      provenance,
      contained_by,
      in_global_module,
      stereotypes,
      meta_name,
      intrinsic_technical_space,
      configuration,
      labels,
      generability_status,
      decoration,
      helper_properties),
      odb_targets_(odb_targets) { }

void msbuild_targets::accept(const element_visitor& v) const {
    v.visit(*this);
}

void msbuild_targets::accept(element_visitor& v) const {
    v.visit(*this);
    }

void msbuild_targets::accept(const element_visitor& v) {
    v.visit(*this);
}

void msbuild_targets::accept(element_visitor& v) {
    v.visit(*this);
}

void msbuild_targets::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::logical::entities::visual_studio::msbuild_targets\"" << ", "
      << "\"__parent_0__\": ";
    dogen::logical::entities::element::to_stream(s);
    s << ", "
      << "\"odb_targets\": " << odb_targets_
      << " }";
}

void msbuild_targets::swap(msbuild_targets& other) noexcept {
    dogen::logical::entities::element::swap(other);

    using std::swap;
    swap(odb_targets_, other.odb_targets_);
}

bool msbuild_targets::equals(const dogen::logical::entities::element& other) const {
    const msbuild_targets* const p(dynamic_cast<const msbuild_targets* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool msbuild_targets::operator==(const msbuild_targets& rhs) const {
    return dogen::logical::entities::element::compare(rhs) &&
        odb_targets_ == rhs.odb_targets_;
}

msbuild_targets& msbuild_targets::operator=(msbuild_targets other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::logical::entities::orm::odb_targets& msbuild_targets::odb_targets() const {
    return odb_targets_;
}

dogen::logical::entities::orm::odb_targets& msbuild_targets::odb_targets() {
    return odb_targets_;
}

void msbuild_targets::odb_targets(const dogen::logical::entities::orm::odb_targets& v) {
    odb_targets_ = v;
}

void msbuild_targets::odb_targets(const dogen::logical::entities::orm::odb_targets&& v) {
    odb_targets_ = std::move(v);
}

}
