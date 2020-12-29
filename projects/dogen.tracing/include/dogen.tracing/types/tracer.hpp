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
#ifndef DOGEN_TRACING_TYPES_TRACER_HPP
#define DOGEN_TRACING_TYPES_TRACER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <stack>
#include <regex>
#include <string>
#include <sstream>
#include <unordered_map>
#include <boost/optional.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include "dogen.tracing/types/backend.hpp"
#include "dogen/types/configuration.hpp"
#include "dogen.tracing/types/backend_factory_registrar.hpp"

namespace dogen::tracing {

/**
 * @brief Handles all of the tracing-related work.
 */
class tracer final {
public:
    /**
     * @brief Registrar that keeps track of the available transforms.
     */
    static backend_factory_registrar& registrar();

public:
    tracer(const tracer&) = default;

public:
    tracer(const configuration& cfg, const std::string& activity);

public:
    const boost::shared_ptr<tracing::backend> backend() const {
        return backend_;
    }

private:
    template<typename Ioable>
    std::string to_string(const Ioable& ioable) const {
        std::ostringstream s;
        s << ioable;
        return s.str();
    }

    std::string last_transform_instance_id() const;
    void push_parent_id(const std::string& id) const;
    void pop_parent_id() const;

public:
    /**
     * @brief Starts a tracing run.
     */
    template<typename Ioable>
    void start_run(const std::string& input_id, const Ioable& input) const {
        if (backend_)
            backend_->start_run(input_id, to_string(input));
    }

    void add_references_graph(const std::string& root_vertex,
        const std::unordered_map<std::string, std::list<std::string>>&
        edges_per_model) const;

private:
    /**
     * @brief Converts the supplied strings, if any, into regular
     * expressions.
     */
    static std::vector<std::regex>
    make_filter_regexes(const std::vector<std::string>& filter_regexes);

    /**
     * @brief Returns true if the supplied transform ID is selected by
     * the current set of filtering regexes, false otherwise.
     */
    bool is_transform_enabled(const std::string& transform_id) const;

public:
    /**
     * @brief Starts a transform chain.
     */
    /**@{*/
    void start_chain(const std::string& transform_id,
        const std::string& transform_instance_id) const;
    void start_chain(const std::string& transform_id,
        const std::string& transform_instance_id,
        const std::string& model_id) const;
    template<typename Ioable>
    void start_chain(const std::string& transform_id,
        const std::string& transform_instance_id,
        const std::string& model_id,
        const Ioable& input) const {
        if (backend_) {
            if (is_transform_enabled(transform_id)) {
                backend_->start_chain(last_transform_instance_id(),
                    transform_id, transform_instance_id, model_id,
                    to_string(input));
            } else {
                backend_->start_chain(last_transform_instance_id(),
                    transform_id, transform_instance_id, model_id);
            }
            push_parent_id(transform_instance_id);
        }
    }
    /**@}*/

    /**
     * @brief Starts a leaf transform.
     */
    /**@{*/
    void start_transform(const std::string& transform_id,
        const std::string& transform_instance_id) const;
    void start_transform(const std::string& transform_id,
        const std::string& transform_instance_id,
        const std::string& model_id) const;
    template<typename Ioable>
    void start_transform(const std::string& transform_id,
        const std::string& transform_instance_id,
        const std::string& model_id,
        const Ioable& input) const {
        if (backend_) {
            if (is_transform_enabled(transform_id)) {
                backend_->start_transform(last_transform_instance_id(),
                    transform_id, transform_instance_id, model_id,
                    to_string(input));
            } else {
                backend_->start_transform(last_transform_instance_id(),
                    transform_id, transform_instance_id, model_id);
            }
        }
    }
    /**@}*/

    /**
     * @brief Ends a transform chain.
     */
    /**@{*/
    void end_chain(const std::string& transform_id,
        const std::string& transform_instance_id) const;
    template<typename Ioable>
    void end_chain(const std::string& transform_id,
        const std::string& transform_instance_id,
        const std::string& model_id,
        const Ioable& output) const {
        if (backend_) {
            pop_parent_id();
            if (is_transform_enabled(transform_id)) {
                backend_->end_chain(last_transform_instance_id(), transform_id,
                    transform_instance_id, model_id, to_string(output));
            } else {
                backend_->end_chain(last_transform_instance_id(),
                    transform_id, transform_instance_id);
            }
        }
    }
    /**@}*/

    /**
     * @brief Ends a leaf transform.
     */
    /**@{*/
    void end_transform(const std::string& transform_id,
        const std::string& transform_instance_id) const;
    template<typename Ioable>
    void end_transform(const std::string& transform_id,
        const std::string& transform_instance_id, const std::string& model_id,
        const Ioable& output) const {
        if (backend_) {
            if (is_transform_enabled(transform_id)) {
                backend_->end_transform(last_transform_instance_id(),
                    transform_id, transform_instance_id, model_id,
                    to_string(output));
            } else {
                backend_->end_transform(last_transform_instance_id(),
                    transform_id, transform_instance_id);
            }
        }
    }
    /**@}*/

    /**
     * @brief Ends a tracing run.
     */
    void end_run() const;

public:
    bool operator==(const tracer& rhs) const;

private:
    boost::shared_ptr<tracing::backend> backend_;
    const std::vector<std::regex> filter_regexes_;
    static backend_factory_registrar registrar_;
    mutable std::stack<std::string> parent_id_;
};

/*
 * Helper method to register transforms.
 */
template<typename Transform>
inline void register_backend_factory() {
    auto t(boost::make_shared<Transform>());
    auto& rg(tracer::registrar());
    rg.register_backend_factory(t);
}

}

#endif
