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
#ifndef DOGEN_TEXT_TYPES_TRANSFORMS_HELPER_REGISTRAR_HPP
#define DOGEN_TEXT_TYPES_TRANSFORMS_HELPER_REGISTRAR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <memory>
#include "dogen.text/types/transforms/helper_transform.hpp"
#include "dogen.text/types/transforms/helper_repository.hpp"

namespace dogen::text::transforms {

class helper_registrar final {
private:
    /**
     * @brief Ensures the transform passes a modicum of sanity checks.
     */
    void validate(std::shared_ptr<helper_transform> ht) const;

public:
    /**
     * @brief Ensures the registrar is ready to be used.
     */
    void validate() const;

public:
    /**
     * @brief Registers a helper transform.
     */
    void register_helper_transform(std::shared_ptr<helper_transform> ht);

public:
    const helper_repository& repository() const;

private:
    helper_repository repository_;
};

template<typename HelperTransform>
inline void register_helper(helper_registrar& rg) {
    const auto f(std::make_shared<HelperTransform>());
    rg.register_helper_transform(f);
}

}

#endif
