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
 * @file error.hpp
 * @author Caden Shmookler (cshmookler@gmail.com)
 * @brief Utilities for creating and manipulating error messages.
 * @date 2025-01-18
 */

// Standard includes
#include <string>

// Append a trace to an error. Each trace contains the file name, function name,
// and line number where this macro is expanded.
#define RES_TRACE(trace)                                                       \
    res::error_t {                                                             \
        (trace).string() + "\n" + __FILE__ + ":" + __FUNCTION__                \
          + "():" + std::to_string(__LINE__)                                   \
    }

// Append a trace to an error with an additional error message.
#define RES_ERROR(trace, error)                                                \
    res::error_t {                                                             \
        RES_TRACE(trace).string() + " -> " + (error)                           \
    }

// Create a new error with a trace.
#define RES_NEW_ERROR(error) RES_ERROR(res::error_t{ "" }, (error))

namespace res {

/**
 * @brief Represents an error message with traces.
 */
class error_t {
    std::string error_;

  public:
    // All constructors must be explicit so construction is never ambiguous. If
    // a function returns a res::optional_t<std::string>, then returning a
    // std::string must never construct a res::error_t unless explicitly casted
    // to a res::error_t. For example:
    //
    // res::optional_t<std::string> example(bool success) {
    //     if (success) {
    //         return "success";
    //     } else {
    //         return res::error_t("error");
    //     }
    // }

    explicit error_t(const std::string& error) : error_(error) {
    }

    explicit error_t(std::string&& error) : error_(std::move(error)) {
    }

    /**
     * @brief Get a const reference to the stored error message.
     */
    [[nodiscard]] const std::string& string() const {
        return this->error_;
    }

    /**
     * @brief Get a mutable reference to the stored error message.
     */
    [[nodiscard]] std::string& string() {
        return this->error_;
    }
};

} // namespace res
