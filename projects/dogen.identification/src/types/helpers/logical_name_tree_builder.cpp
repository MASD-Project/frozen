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
#include <sstream>
#include <boost/make_shared.hpp>
#include <boost/throw_exception.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/io/unordered_set_io.hpp"
#include "dogen.utility/types/io/list_io.hpp"
#include "dogen.identification/io/entities/logical_name_io.hpp"
#include "dogen.identification/io/entities/logical_location_io.hpp"
#include "dogen.identification/io/entities/logical_name_tree_io.hpp"
#include "dogen.identification/types/helpers/logical_name_builder.hpp"
#include "dogen.identification/types/helpers/building_error.hpp"
#include "dogen.identification/types/helpers/logical_name_tree_builder.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("identification.helpers.logical_name_tree_builder"));

}

namespace dogen::identification::helpers {

logical_name_tree_builder::logical_name_tree_builder()
    : root_(boost::make_shared<node>()), current_(root_) {}

void logical_name_tree_builder::add_name(const std::string& s) {
    BOOST_LOG_SEV(lg, debug) << "Pushing back name: '" << s << "'";
    names_.push_back(s);
}

void logical_name_tree_builder::add_builtin(const std::string& s) {
    BOOST_LOG_SEV(lg, debug) << "Pushing back builtin: '" << s << "'";

    logical_name_builder b;
    b.simple_name(s);
    current_->data(b.build());
}

void logical_name_tree_builder::finish_current_node() {
    BOOST_LOG_SEV(lg, debug) << "Finishing current node. names: " << names_;

    /*
     * if there are no names, we do not have any work to do.
     */
    if (names_.empty())
        return;

    current_->data(logical_name_builder::build(names_));
    names_.clear();
}

void logical_name_tree_builder::start_children() {
    BOOST_LOG_SEV(lg, debug) << "Starting children.";

    /*
     * We are done building the parent's name so flush it.
     */
    finish_current_node();

    /*
     * Create a child node, link it up to its parent, link the parent
     * to the child and then make the child the current node.
     */
    auto child(boost::make_shared<node>());
    child->parent(current_);
    current_->children().push_back(child);
    current_ = child;
}

void logical_name_tree_builder::next_child() {
    BOOST_LOG_SEV(lg, debug) << "Moving to next child.";

    /*
     * We are done building the current child's name so flush it.
     */
    finish_current_node();

    /*
     * We are currently sitting on a child node. We first need to move
     * back up to the parent; then add a new child node, link it to
     * the parent and link the parent to the child; finally, make the
     * new child the current node.
     */
    current_ = current_->parent().lock();
    auto child(boost::make_shared<node>());
    child->parent(current_);
    current_->children().push_back(child);
    current_ = child;
}

void logical_name_tree_builder::end_children() {
    BOOST_LOG_SEV(lg, debug) << "Children have ended.";

    /*
     * We are done building the current child's name so flush it.
     */
    finish_current_node();

    /*
     * All the children are done, so move back up to the parent.
     */
    current_ = current_->parent().lock();
}

entities::logical_name_tree
logical_name_tree_builder::make_name_tree(const node& n) {
    BOOST_LOG_SEV(lg, debug) << "Node: " << n.data();

    entities::logical_name_tree r;
    r.current(n.data());

    for (const auto& c : n.children()) {
        const auto cnt(make_name_tree(*c));
        r.children().push_back(cnt);
    }

    return r;
}

entities::logical_name_tree logical_name_tree_builder::build() {
    BOOST_LOG_SEV(lg, debug) << "Started building.";

    /*
     * Flush any pending work and build the name for it. This handles
     * the case of a parent without any children.
     */
    finish_current_node();

    /*
     * Convert the node representation into a tree representation.
     */
    auto r(make_name_tree(*root_));

    BOOST_LOG_SEV(lg, debug) << "Finished building. Final name: " << r;

    return r;
}

}
