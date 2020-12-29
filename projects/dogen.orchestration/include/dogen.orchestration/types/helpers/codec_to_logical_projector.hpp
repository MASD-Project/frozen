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
#ifndef DOGEN_ORCHESTRATION_TYPES_HELPERS_CODEC_TO_LOGICAL_PROJECTOR_HPP
#define DOGEN_ORCHESTRATION_TYPES_HELPERS_CODEC_TO_LOGICAL_PROJECTOR_HPP

#include "dogen.identification/types/entities/name.hpp"
#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <iosfwd>
#include <boost/shared_ptr.hpp>
#include "dogen.variability/types/entities/potential_binding.hpp"
#include "dogen.codec/types/entities/attribute.hpp"
#include "dogen.codec/types/entities/element.hpp"
#include "dogen.identification/types/entities/logical_location.hpp"
#include "dogen.identification/types/entities/logical_id.hpp"
#include "dogen.logical/types/entities/element.hpp"
#include "dogen.logical/types/entities/structural/enumerator.hpp"
#include "dogen.logical/types/entities/attribute.hpp"
#include "dogen.logical/types/entities/structural/enumeration.hpp"
#include "dogen.logical/types/entities/structural/primitive.hpp"
#include "dogen.logical/types/entities/structural/exception.hpp"
#include "dogen.logical/types/entities/structural/entry_point.hpp"
#include "dogen.logical/types/entities/structural/assistant.hpp"
#include "dogen.logical/types/entities/element.hpp"
#include "dogen.logical/types/entities/structural/object.hpp"
#include "dogen.logical/types/entities/structural/module.hpp"
#include "dogen.logical/types/entities/structural/builtin.hpp"
#include "dogen.logical/types/entities/structural/object_template.hpp"
#include "dogen.logical/types/entities/decoration/licence.hpp"
#include "dogen.logical/types/entities/decoration/modeline.hpp"
#include "dogen.logical/types/entities/decoration/modeline_group.hpp"
#include "dogen.logical/types/entities/decoration/generation_marker.hpp"
#include "dogen.logical/types/entities/variability/profile.hpp"
#include "dogen.logical/types/entities/variability/profile_template.hpp"
#include "dogen.logical/types/entities/variability/feature_template_bundle.hpp"
#include "dogen.logical/types/entities/variability/feature_bundle.hpp"
#include "dogen.logical/types/entities/variability/initializer.hpp"
#include "dogen.logical/types/entities/mapping/fixed_mappable.hpp"
#include "dogen.logical/types/entities/mapping/extensible_mappable.hpp"
#include "dogen.logical/types/entities/templating/logic_less_template.hpp"
#include "dogen.logical/types/entities/serialization/type_registrar.hpp"
#include "dogen.logical/types/entities/visual_studio/solution.hpp"
#include "dogen.logical/types/entities/visual_studio/project.hpp"
#include "dogen.logical/types/entities/visual_studio/msbuild_targets.hpp"
#include "dogen.logical/types/entities/orm/common_odb_options.hpp"
#include "dogen.logical/types/entities/build/cmakelists.hpp"
#include "dogen.logical/types/entities/physical/backend.hpp"
#include "dogen.logical/types/entities/physical/facet.hpp"
#include "dogen.logical/types/entities/physical/archetype.hpp"
#include "dogen.logical/types/entities/physical/archetype_kind.hpp"
#include "dogen.logical/types/entities/physical/part.hpp"
#include "dogen.logical/types/entities/physical/helper.hpp"
#include "dogen.logical/types/entities/stereotypes.hpp"

namespace dogen::orchestration::helpers {

/**
 * @brief Projects elements from the codec space into the logical
 * space.
 */
class codec_to_logical_projector final {
private:
    /**
     * @brief Ensure the string is not empty.
     */
    /**@{*/
    void ensure_not_empty(const std::string& s) const;
    void ensure_not_empty(
        const identification::entities::logical_id& element_id,
        const std::string& s) const;
    void ensure_not_empty(
        const identification::entities::logical_id& element_id,
        const identification::entities::name& n) const;
    /**@{*/

    /**
     * @brief Ensure the string is empty.
     */
    void ensure_empty(const identification::entities::logical_id& element_id,
        const std::string& s) const;

    /**
     * @brief Ensure the attributes are empty.
     */
    void ensure_empty(const identification::entities::logical_id& element_id,
        const std::list<codec::entities::attribute>& cattrs) const;

private:
    /**
     * @brief Creates a list of potential bindings from a list of stereotypes.
     */
    std::list<variability::entities::potential_binding> to_potential_binding(
        const std::list<identification::entities::stereotype>& sts) const;

private:
    /**
     * @brief Creates a logical name using the element name provided.
     *
     * @param n may be a simple name or a qualified name, via a scope
     * operator.
     *
     * @pre n must not be empty.
     */
    identification::entities::logical_name
    to_name(const std::string& n, const bool is_container) const;

    /**
     * @brief Creates a logical name using the element name provided, and
     * places it in the location provided.
     *
     * @param l location for the name.
     * @param n may be a simple name or a qualified name, via a scope
     * operator.
     *
     * @pre n must not be empty.
     */
    identification::entities::logical_name
    to_name(const identification::entities::logical_location& l,
        const std::string& n, const bool is_container) const;

    /**
     * @brief Converts an codec attribute to a modeline field.
     *
     * @pre name and value of the codec attribute must not be empty.
     * @pre value of the codec attribute must be empty.
     */
    logical::entities::decoration::modeline_field
    to_modeline_field(const identification::entities::logical_name& owner,
        const codec::entities::attribute& cattr) const;

    /**
     * @brief Converts an codec attribute to an logical attribute.
     *
     * @pre name of the codec attribute must not be empty.
     */
    logical::entities::attribute
    to_attribute(const identification::entities::logical_name& owner,
        const codec::entities::attribute& cattr) const;

    /**
     * @brief Converts an codec attribute to an logical enumerator.
     *
     * @pre name of the codec attribute must not be empty.
     * @pre type and value of the codec attribute must be empty.
     */
    logical::entities::structural::enumerator
    to_enumerator(const identification::entities::logical_name& owner,
        const codec::entities::attribute& cattr) const;

private:
    /**
     * @brief Populates the meta-model element attributes using the
     * codec element.
     */
    void populate_element(const identification::entities::logical_location& l,
        const logical::entities::stereotypes& sts,
        const codec::entities::element& ce,
        const bool is_container, logical::entities::element& e) const;

public:
    /**
     * @brief Converts an codec element with a stereotype of
     * masd::object to a logical object.
     */
    boost::shared_ptr<logical::entities::structural::object>
    to_object(const identification::entities::logical_location& l,
        const logical::entities::stereotypes& sts,
        const codec::entities::element& ce) const;

    /**
     * @brief Converts an codec element with a stereotype of
     * masd::object_template to a logical object template.
     */
    boost::shared_ptr<logical::entities::structural::object_template>
    to_object_template(const identification::entities::logical_location& l,
        const logical::entities::stereotypes& sts,
        const codec::entities::element& ce) const;

    /**
     * @brief Converts an codec element with a stereotype of
     * masd::exception to a logical exception.
     */
    boost::shared_ptr<logical::entities::structural::exception>
    to_exception(const identification::entities::logical_location& l,
        const logical::entities::stereotypes& sts,
        const codec::entities::element& ce) const;

    /**
     * @brief Converts an codec element with a stereotype of
     * masd::primitive to a logical primitive.
     */
    boost::shared_ptr<logical::entities::structural::primitive>
    to_primitive(const identification::entities::logical_location& l,
        const logical::entities::stereotypes& sts,
        const codec::entities::element& ce) const;

    /**
     * @brief Converts an codec element with a stereotype of
     * masd::enumeration to a logical enumeration.
     */
    boost::shared_ptr<logical::entities::structural::enumeration>
    to_enumeration(const identification::entities::logical_location& l,
        const logical::entities::stereotypes& sts,
        const codec::entities::element& ce) const;

    /**
     * @brief Converts an codec element with a stereotype of
     * masd::module to a logical module.
     */
    boost::shared_ptr<logical::entities::structural::module>
    to_module(const identification::entities::logical_location& l,
        const logical::entities::stereotypes& sts,
        const codec::entities::element& ce) const;

    /**
     * @brief Converts an codec element with a stereotype of
     * masd::builtin to a logical builtin.
     */
    boost::shared_ptr<logical::entities::structural::builtin>
    to_builtin(const identification::entities::logical_location& l,
        const logical::entities::stereotypes& sts,
        const codec::entities::element& ce) const;

    /**
     * @brief Converts an codec element with a stereotype of
     * @e masd::entry_point to a logical entry_point.
     */
    boost::shared_ptr<logical::entities::structural::entry_point>
    to_entry_point(const identification::entities::logical_location& l,
        const logical::entities::stereotypes& sts,
        const codec::entities::element& ce) const;

    /**
     * @brief Converts an codec element with a stereotype of
     * @e masd::assistant to a logical entry_point.
     */
    boost::shared_ptr<logical::entities::structural::assistant>
    to_assistant(const identification::entities::logical_location& l,
        const logical::entities::stereotypes& sts,
        const codec::entities::element& ce) const;

public:
    /**
     * @brief Converts an codec element with a stereotype of
     * masd::modeline_group to a logical modeline group.
     */
    boost::shared_ptr<logical::entities::decoration::modeline_group>
    to_modeline_group(const identification::entities::logical_location& l,
        const logical::entities::stereotypes& sts,
        const codec::entities::element& ce) const;

    /**
     * @brief Converts an codec element with a stereotype of
     * masd::modeline to a logical modeline.
     */
    boost::shared_ptr<logical::entities::decoration::modeline>
    to_modeline(const identification::entities::logical_location& l,
        const logical::entities::stereotypes& sts,
        const codec::entities::element& ce) const;

    /**
     * @brief Converts an codec element with a stereotype of
     * masd::generation_marker to a logical generation marker.
     */
    boost::shared_ptr<logical::entities::decoration::generation_marker>
    to_generation_marker(const identification::entities::logical_location& l,
        const logical::entities::stereotypes& sts,
        const codec::entities::element& ce) const;

    /**
     * @brief Converts an codec element with a stereotype of
     * masd::licence to a logical licence.
     */
    boost::shared_ptr<logical::entities::decoration::licence>
    to_licence(const identification::entities::logical_location& l,
        const logical::entities::stereotypes& sts,
        const codec::entities::element& ce) const;

private:
    /**
     * @brief Populates the abstract profile properties.
     */
    void populate_abstract_profile(
        const identification::entities::logical_location& l,
        const codec::entities::element& ce,
        logical::entities::variability::abstract_profile& ap) const;

    /**
     * @brief Populates the abstract profile entry properties.
     */
    void populate_abstract_profile_entry(
        const identification::entities::logical_name& n,
        const codec::entities::attribute& cattr,
        logical::entities::variability::abstract_profile_entry& ape) const;

    /**
     * @brief Populates the abstract feature properties.
     */
    void populate_abstract_feature(
        const identification::entities::logical_name& pn,
        const codec::entities::attribute& cattr,
        logical::entities::variability::abstract_feature& af) const;

public:
    /**
     * @brief Converts an codec element with a stereotype of
     * masd::to_variability::profile to a variability profile.
     */
    boost::shared_ptr<logical::entities::variability::profile>
    to_variability_profile(const identification::entities::logical_location& l,
        const logical::entities::stereotypes& sts,
        const codec::entities::element& ce) const;

    /**
     * @brief Converts an codec element with a stereotype of
     * masd::to_variability::profile_template to a variability profile
     * template.
     */
    boost::shared_ptr<logical::entities::variability::profile_template>
    to_variability_profile_template(
        const identification::entities::logical_location& l,
        const logical::entities::stereotypes& sts,
        const codec::entities::element& ce) const;

    /**
     * @brief Converts an codec element with a stereotype of
     * masd::variability::feature_template_bundle to a variability
     * feature template bundle.
     */
    boost::shared_ptr<logical::entities::variability::feature_template_bundle>
    to_variability_feature_template_bundle(
        const identification::entities::logical_location& l,
        const logical::entities::stereotypes& sts,
        const codec::entities::element& ce) const;

    /**
     * @brief Converts an codec element with a stereotype of
     * masd::variability::feature_bundle to a variability feature
     * group.
     */
    boost::shared_ptr<logical::entities::variability::feature_bundle>
    to_variability_feature_bundle(
        const identification::entities::logical_location& l,
        const logical::entities::stereotypes& sts,
        const codec::entities::element& ce) const;

    /**
     * @brief Converts an codec element with a stereotype of
     * masd::variability::initializer to a logical
     * variability feature template group registrar.
     */
    boost::shared_ptr<logical::entities::variability::initializer>
    to_variability_initializer(
        const identification::entities::logical_location& l,
        const logical::entities::stereotypes& sts,
        const codec::entities::element& ce) const;

public:
    /**
     * @brief Converts an codec element with a stereotype of
     * masd::mapping::fixed_mappable to a fixed mappable element.
     */
    boost::shared_ptr<logical::entities::mapping::fixed_mappable>
    to_fixed_mappable(const identification::entities::logical_location& l,
        const logical::entities::stereotypes& sts,
        const codec::entities::element& ce) const;

    /**
     * @brief Converts an codec element with a stereotype of
     * masd::mapping::extensible_mappable to a extensible mappable
     * element.
     */
    boost::shared_ptr<logical::entities::mapping::extensible_mappable>
    to_extensible_mappable(const identification::entities::logical_location& l,
        const logical::entities::stereotypes& sts,
        const codec::entities::element& ce) const;

public:
    /**
     * @brief Converts an codec element with a stereotype of
     * masd::templating::logic_less_template to a logic-less template.
     */
    boost::shared_ptr<logical::entities::templating::logic_less_template>
    to_logic_less_template(const identification::entities::logical_location& l,
        const logical::entities::stereotypes& sts,
        const codec::entities::element& ce) const;

public:
    /**
     * @brief Converts an codec element with a stereotype of
     * masd::serialization::type_registrar to a logic-less template.
     */
    boost::shared_ptr<logical::entities::serialization::type_registrar>
    to_type_registrar(const identification::entities::logical_location& l,
        const logical::entities::stereotypes& sts,
        const codec::entities::element& ce) const;

public:
    /**
     * @brief Converts an codec element with a stereotype of
     * @e masd::visual_studio::solution.
     */
    boost::shared_ptr<logical::entities::visual_studio::solution>
    to_visual_studio_solution(
        const identification::entities::logical_location& l,
        const logical::entities::stereotypes& sts,
        const codec::entities::element& ce) const;

    /**
     * @brief Converts an codec element with a stereotype of
     * @e masd::visual_studio::project.
     */
    boost::shared_ptr<logical::entities::visual_studio::project>
    to_visual_studio_project(
        const identification::entities::logical_location& l,
        const logical::entities::stereotypes& sts,
        const codec::entities::element& ce) const;

    /**
     * @brief Converts an codec element with a stereotype of
     * @e masd::visual_studio::project.
     */
    boost::shared_ptr<logical::entities::visual_studio::msbuild_targets>
    to_visual_studio_msbuild_targets(
        const identification::entities::logical_location& l,
        const logical::entities::stereotypes& sts,
        const codec::entities::element& ce) const;

public:
    /**
     * @brief Converts an codec element with a stereotype of
     * @e masd::orm::common_odb_options.
     */
    boost::shared_ptr<logical::entities::orm::common_odb_options>
    to_orm_common_odb_options(
        const identification::entities::logical_location& l,
        const logical::entities::stereotypes& sts,
        const codec::entities::element& ce) const;

public:
    /**
     * @brief Converts an codec element with a stereotype of
     * @e masd::build::cmakelists.
     */
    boost::shared_ptr<logical::entities::build::cmakelists>
    to_build_cmakelists(const identification::entities::logical_location& l,
        const logical::entities::stereotypes& sts,
        const codec::entities::element& ce) const;

public:
    /**
     * @brief Converts an codec element with a stereotype of
     * @e masd::physical::backend.
     */
    boost::shared_ptr<logical::entities::physical::backend>
    to_physical_backend(const identification::entities::logical_location& l,
        const logical::entities::stereotypes& sts,
        const codec::entities::element& ce) const;

    /**
     * @brief Converts an codec element with a stereotype of
     * @e masd::physical::facet.
     */
    boost::shared_ptr<logical::entities::physical::facet>
    to_physical_facet(const identification::entities::logical_location& l,
        const logical::entities::stereotypes& sts,
        const codec::entities::element& ce) const;

    /**
     * @brief Converts an codec element with a stereotype of
     * @e masd::physical::archetype.
     */
    boost::shared_ptr<logical::entities::physical::archetype>
    to_physical_archetype(const identification::entities::logical_location& l,
        const logical::entities::stereotypes& sts,
        const codec::entities::element& ce) const;

    /**
     * @brief Converts an codec element with a stereotype of
     * @e masd::physical::archetype_kind.
     */
    boost::shared_ptr<logical::entities::physical::archetype_kind>
    to_physical_archetype_kind(
        const identification::entities::logical_location& l,
        const logical::entities::stereotypes& sts,
        const codec::entities::element& ce) const;

    /**
     * @brief Converts an codec element with a stereotype of
     * @e masd::physical::part.
     */
    boost::shared_ptr<logical::entities::physical::part>
    to_physical_part(const identification::entities::logical_location& l,
        const logical::entities::stereotypes& sts,
        const codec::entities::element& ce) const;

    /**
     * @brief Converts an codec element with a stereotype of
     * @e masd::physical::helper.
     */
    boost::shared_ptr<logical::entities::physical::helper>
    to_physical_helper(const identification::entities::logical_location& l,
        const logical::entities::stereotypes& sts,
        const codec::entities::element& ce) const;
};

}

#endif
