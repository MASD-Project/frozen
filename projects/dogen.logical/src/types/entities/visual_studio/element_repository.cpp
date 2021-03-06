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
#include "dogen.logical/types/entities/visual_studio/project.hpp"
#include "dogen.logical/types/entities/visual_studio/solution.hpp"
#include "dogen.logical/types/entities/visual_studio/msbuild_targets.hpp"
#include "dogen.logical/types/entities/visual_studio/element_repository.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::logical::entities::visual_studio::solution>& lhs,
const boost::shared_ptr<dogen::logical::entities::visual_studio::solution>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::logical::entities::visual_studio::project>& lhs,
const boost::shared_ptr<dogen::logical::entities::visual_studio::project>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::logical::entities::visual_studio::msbuild_targets>& lhs,
const boost::shared_ptr<dogen::logical::entities::visual_studio::msbuild_targets>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen::logical::entities::visual_studio {

element_repository::element_repository(
    const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::visual_studio::solution> >& solutions,
    const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::visual_studio::project> >& projects,
    const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::visual_studio::msbuild_targets> >& msbuild_targets)
    : solutions_(solutions),
      projects_(projects),
      msbuild_targets_(msbuild_targets) { }

void element_repository::swap(element_repository& other) noexcept {
    using std::swap;
    swap(solutions_, other.solutions_);
    swap(projects_, other.projects_);
    swap(msbuild_targets_, other.msbuild_targets_);
}

bool element_repository::operator==(const element_repository& rhs) const {
    return solutions_ == rhs.solutions_ &&
        projects_ == rhs.projects_ &&
        msbuild_targets_ == rhs.msbuild_targets_;
}

element_repository& element_repository::operator=(element_repository other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::visual_studio::solution> >& element_repository::solutions() const {
    return solutions_;
}

std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::visual_studio::solution> >& element_repository::solutions() {
    return solutions_;
}

void element_repository::solutions(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::visual_studio::solution> >& v) {
    solutions_ = v;
}

void element_repository::solutions(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::visual_studio::solution> >&& v) {
    solutions_ = std::move(v);
}

const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::visual_studio::project> >& element_repository::projects() const {
    return projects_;
}

std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::visual_studio::project> >& element_repository::projects() {
    return projects_;
}

void element_repository::projects(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::visual_studio::project> >& v) {
    projects_ = v;
}

void element_repository::projects(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::visual_studio::project> >&& v) {
    projects_ = std::move(v);
}

const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::visual_studio::msbuild_targets> >& element_repository::msbuild_targets() const {
    return msbuild_targets_;
}

std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::visual_studio::msbuild_targets> >& element_repository::msbuild_targets() {
    return msbuild_targets_;
}

void element_repository::msbuild_targets(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::visual_studio::msbuild_targets> >& v) {
    msbuild_targets_ = v;
}

void element_repository::msbuild_targets(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::visual_studio::msbuild_targets> >&& v) {
    msbuild_targets_ = std::move(v);
}

}
