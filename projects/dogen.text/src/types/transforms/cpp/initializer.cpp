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
#include "dogen.text/types/transforms/cpp/build/initializer.hpp"
#include "dogen.text/types/transforms/cpp/hash/initializer.hpp"
#include "dogen.text/types/transforms/cpp/io/initializer.hpp"
#include "dogen.text/types/transforms/cpp/lexical_cast/initializer.hpp"
#include "dogen.text/types/transforms/cpp/odb/initializer.hpp"
#include "dogen.text/types/transforms/cpp/serialization/initializer.hpp"
#include "dogen.text/types/transforms/cpp/tests/initializer.hpp"
#include "dogen.text/types/transforms/cpp/test_data/initializer.hpp"
#include "dogen.text/types/transforms/cpp/types/initializer.hpp"
#include "dogen.text/types/transforms/cpp/visual_studio/initializer.hpp"
#include "dogen.text/types/transforms/cpp/initializer.hpp"

namespace dogen::text::transforms::cpp {

void initializer::
initialize(text_transform_registrar& ttrg, helper_registrar& hrg) {
    types::initializer::initialize(ttrg, hrg);
    hash::initializer::initialize(ttrg, hrg);
    odb::initializer::initialize(ttrg, hrg);
    io::initializer::initialize(ttrg, hrg);
    lexical_cast::initializer::initialize(ttrg, hrg);
    test_data::initializer::initialize(ttrg, hrg);
    serialization::initializer::initialize(ttrg, hrg);
    tests::initializer::initialize(ttrg, hrg);
    visual_studio::initializer::initialize(ttrg, hrg);
    build::initializer::initialize(ttrg, hrg);
}

}
