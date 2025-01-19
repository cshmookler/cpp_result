#pragma once

/*****************************************************************************/
/*  Copyright (c) 2025 Caden Shmookler                                       */
/*                                                                           */
/*  This software is provided 'as-is', without any express or implied        */
/*  warranty. In no event will the authors be held liable for any damages    */
/*  arising from the use of this software.                                   */
/*                                                                           */
/*  Permission is granted to anyone to use this software for any purpose,    */
/*  including commercial applications, and to alter it and redistribute it   */
/*  freely, subject to the following restrictions:                           */
/*                                                                           */
/*  1. The origin of this software must not be misrepresented; you must not  */
/*     claim that you wrote the original software. If you use this software  */
/*     in a product, an acknowledgment in the product documentation would    */
/*     be appreciated but is not required.                                   */
/*  2. Altered source versions must be plainly marked as such, and must not  */
/*     be misrepresented as being the original software.                     */
/*  3. This notice may not be removed or altered from any source             */
/*     distribution.                                                         */
/*****************************************************************************/

/**
 * @file result.hpp
 * @author Caden Shmookler (cshmookler@gmail.com)
 * @brief A result type indicating success or failure.
 * @date 2025-01-18
 */

// Standard includes
#include <memory>

// Local includes
#include "error.hpp"

namespace res {

/**
 * @brief Indicates success or failure. Contains an error message for failure
 * and an empty string for success.
 */
class result_t {
    std::unique_ptr<error_t> error_;

    static inline const error_t success_error = error_t{ "Success" };

  public:
    result_t() {
    }

    result_t(const error_t& error) : error_(std::make_unique<error_t>(error)) {
    }

    result_t(error_t&& error)
    : error_(
        std::make_unique<error_t>(std::forward<error_t>(std::move(error)))) {
    }

    result_t(const result_t& result) {
        if (result.success()) {
            this->error_ = nullptr;
        } else {
            this->error_ = std::make_unique<error_t>(*(result.error_));
        }
    }
    result_t(result_t&&) = default;
    result_t& operator=(const result_t& result) {
        if (this == &result) {
            return *this;
        }

        if (result.success()) {
            this->error_ = nullptr;
        } else {
            this->error_ = std::make_unique<error_t>(*(result.error_));
        }

        return *this;
    }
    result_t& operator=(result_t&&) = default;
    ~result_t() = default;

    /**
     * @return true if this result represents success and false otherwise.
     */
    [[nodiscard]] bool success() const {
        return this->error_ == nullptr;
    }

    /**
     * @return true if this result represents failure and false otherwise.
     */
    [[nodiscard]] bool failure() const {
        return ! this->success();
    }

    /**
     * @return a copy of the error stored within this result or a
     * generic success message if this result represents success.
     */
    [[nodiscard]] error_t error() {
        if (this->success()) {
            return success_error;
        }

        return *(this->error_);
    }
};

/**
 * @brief A result indicating success.
 */
inline const result_t success = {};

} // namespace res
