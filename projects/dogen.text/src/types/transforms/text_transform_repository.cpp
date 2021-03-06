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
#include "dogen.text/types/transforms/model_to_text_transform.hpp"
#include "dogen.text/types/transforms/text_transform_repository.hpp"

namespace std {

inline bool operator==(const std::shared_ptr<dogen::text::transforms::model_to_text_transform>& lhs,
const std::shared_ptr<dogen::text::transforms::model_to_text_transform>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen::text::transforms {

text_transform_repository::text_transform_repository(const std::unordered_map<dogen::identification::entities::logical_meta_id, std::forward_list<std::shared_ptr<dogen::text::transforms::model_to_text_transform> > >& model_to_text_transforms_by_meta_name)
    : model_to_text_transforms_by_meta_name_(model_to_text_transforms_by_meta_name) { }

void text_transform_repository::swap(text_transform_repository& other) noexcept {
    using std::swap;
    swap(model_to_text_transforms_by_meta_name_, other.model_to_text_transforms_by_meta_name_);
}

bool text_transform_repository::operator==(const text_transform_repository& rhs) const {
    return model_to_text_transforms_by_meta_name_ == rhs.model_to_text_transforms_by_meta_name_;
}

text_transform_repository& text_transform_repository::operator=(text_transform_repository other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<dogen::identification::entities::logical_meta_id, std::forward_list<std::shared_ptr<dogen::text::transforms::model_to_text_transform> > >& text_transform_repository::model_to_text_transforms_by_meta_name() const {
    return model_to_text_transforms_by_meta_name_;
}

std::unordered_map<dogen::identification::entities::logical_meta_id, std::forward_list<std::shared_ptr<dogen::text::transforms::model_to_text_transform> > >& text_transform_repository::model_to_text_transforms_by_meta_name() {
    return model_to_text_transforms_by_meta_name_;
}

void text_transform_repository::model_to_text_transforms_by_meta_name(const std::unordered_map<dogen::identification::entities::logical_meta_id, std::forward_list<std::shared_ptr<dogen::text::transforms::model_to_text_transform> > >& v) {
    model_to_text_transforms_by_meta_name_ = v;
}

void text_transform_repository::model_to_text_transforms_by_meta_name(const std::unordered_map<dogen::identification::entities::logical_meta_id, std::forward_list<std::shared_ptr<dogen::text::transforms::model_to_text_transform> > >&& v) {
    model_to_text_transforms_by_meta_name_ = std::move(v);
}

}
