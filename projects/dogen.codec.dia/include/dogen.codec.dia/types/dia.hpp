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
#ifndef DOGEN_CODEC_DIA_TYPES_DIA_HPP
#define DOGEN_CODEC_DIA_TYPES_DIA_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

/**
 * @brief Codec.Dia is a unidirectional transformation model that transforms
 * a Dia @e diagram into an codec @e model.
 *
 * By that we mean that it is a model designed to transform a representation of
 * a user model in Dia diagram format to its counterpart in the codec format,
 * taking into account any special masd meta-data which the user may have encoded
 * into the Dia diagram. Note that the Dia diagram format contains a representation
 * of UML. We pass that meta-data straight through into the codec model,
 * without any further processing.
 *
 * @section codec_dia_0 Dia diagrams as DAGs
 *
 * Dia diagrams are made up of @e objects, identified by IDs. These objects
 * contain a number of UML model elements, which we are interested in. For
 * instance:
 *
 * @li UML class
 * @li UML generalisation
 * @li UML notes
 *
 * and so on. Each of these objects will contribute to am codec element.
 * However, we need to be aware of object containment - e.g. if a class is
 * contained in a package. This is because the codec element names are scoped
 * by the packages. So, to make our life easier we created a DAG of Dia objects
 * that provides us with the information in dependency order. That is, we process
 * dia objects in such a way that when a dependency exists, we know that the object
 * in which we depend on has already been processed. Please note that to ensure no
 * cycles we had to ignore some of the UML objects such as UML aggregation -
 * but fortunately, these objects do not provide sufficient information as
 * required for dogen transformations, so not much was lost. Instead, one must
 * manually declare attributes in a class.
 *
 * See @ref grapher for details on how the the DAG is built.
 *
 * @section codec_dia_1 Intermediate processing
 *
 * To make the code easier to read and maintain, we created a numeber of
 * intermediate stages between a Dia diagram and an codec model:
 *
 * @li Dia object -> processed object -> profile -> codec element
 *
 * This may look a bit excessive at first glance, but it was done because
 * the shape of the Dia objects is a bit too generic for our purposes, and
 * the resulting processing code was full of loops and look-ups. Instead,
 * we make the generic Dia object into a very concrete processed object -
 * still preserving most of the semantics of Dia - and then from those we
 * build a profile. A profile allows us to quickly scan for UML and masd
 * type information without getting lost in the intricacies of the generic
 * Dia structure. With these in hand, the @ref transformer is able to
 * create the corresponding masd entity, and the transformation code is
 * not obscured.
 *
 * @section codec_dia_2 Dia meta-data
 *
 * There are a couple of conventions on how to model in Dia that one
 * needs to follow in order to comply with Dogen:
 *
 * @li any public attribute in a class is automatically converted into a
 * masd property rather than a member variable. This means that it is
 * expected that a getter and a setter will be generated.
 *
 * @li a number of stereotypes were added, as per the definitions in the
 * MASD UML profile. For details, see the Dogen UML profile.
 *
 * @li any type without any stereotype assumes a default stereotype, again
 * as per MASD UML profile.
 *
 * @li any UML Note with the marker #DOGEN masd.codec.dia.comment=true will
 * be used as the documentation of the current package - or the model, if
 * place at the top-level. Only one such note is expected per containing
 * entity.
 *
 * For details on the stereotypes see the MASD UML profile.
 */
namespace dogen::codec::dia {
}

#endif
