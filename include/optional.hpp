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
 * @file optional.hpp
 * @author Caden Shmookler (cshmookler@gmail.com)
 * @brief An alternative to std::optional that stores an error message.
 * @date 2025-01-18
 */

// Standard includes
#include <memory>

// Local includes
#include "error.hpp"

namespace res {

/*
 * @brief An exception thrown when attempting to access a value stored within an
 * optional_t that does not exist.
 */
class bad_optional_access_t : public std::exception {
    error_t error_;

  public:
    bad_optional_access_t(const error_t& error) : error_(error) {
    }

    bad_optional_access_t(error_t&& error) : error_(std::move(error)) {
    }

    const char* what() const noexcept override {
        return this->error_.string().c_str();
    }
};

/**
 * @brief Represents a value that may or may not exist. Contains an error
 * message explaining why the value does not exist.
 */
template<typename type_t>
class optional_t {
    std::unique_ptr<type_t> value_;
    std::unique_ptr<error_t> error_;

    static inline const error_t has_value_error{ "Has value" };
    static inline const std::string bad_optional_access_message{
        "Attempted to access a value from an optional_t that does not exist."
    };

  public:
    // This object will always contain a value if it does not contain an error.

    // Initialize with an error.
    optional_t(const error_t& error)
    : value_(nullptr), error_(std::make_unique<error_t>(error)) {
    }
    optional_t(error_t&& error)
    : value_(nullptr)
    , error_(
        std::make_unique<error_t>(std::forward<error_t>(std::move(error)))) {
    }
    optional_t& operator=(const error_t& error) {
        this->value_ = nullptr;
        this->error_ = std::make_unique<error_t>(error);
        return *this;
    }
    optional_t& operator=(error_t&& error) {
        this->value_ = nullptr;
        this->error_ =
          std::make_unique<error_t>(std::forward<error_t>(std::move(error)));
        return *this;
    }

    // Initialize with a value.
    optional_t(const type_t& value)
    : value_(std::make_unique<type_t>(value)), error_(nullptr) {
    }
    optional_t(type_t&& value)
    : value_(std::make_unique<type_t>(std::forward<type_t>(std::move(value))))
    , error_(nullptr) {
    }
    optional_t& operator=(const type_t& value) {
        this->value_ = std::make_unique<type_t>(value);
        this->error_ = nullptr;
        return *this;
    }
    optional_t& operator=(type_t&& value) {
        this->value_ =
          std::make_unique<type_t>(std::forward<type_t>(std::move(value)));
        this->error_ = nullptr;
        return *this;
    }

    // Initialize with another optional object.
    optional_t(const optional_t& optional) {
        if (optional.has_value()) {
            this->value_ = std::make_unique<type_t>(*(optional.value_));
            this->error_ = nullptr;
        } else {
            this->value_ = nullptr;
            this->error_ = std::make_unique<error_t>(*(optional.error_));
        }
    }
    optional_t(optional_t&&) = default;
    optional_t& operator=(const optional_t& optional) {
        if (this == &optional) {
            return *this;
        }

        if (optional.has_value()) {
            this->value_ = std::make_unique<type_t>(*(optional.value_));
            this->error_ = nullptr;
        } else {
            this->value_ = nullptr;
            this->error_ = std::make_unique<error_t>(*(optional.error_));
        }

        return *this;
    }
    optional_t& operator=(optional_t&&) = default;

    // Destructor
    ~optional_t() = default;

    [[nodiscard]] const type_t* operator->() const {
        if (! this->has_value()) {
            throw bad_optional_access_t{ RES_ERROR(
              this->error(), bad_optional_access_message) };
        }

        return this->value_.get();
    }
    [[nodiscard]] type_t* operator->() {
        if (! this->has_value()) {
            throw bad_optional_access_t{ RES_ERROR(
              this->error(), bad_optional_access_message) };
        }

        return this->value_.get();
    }

    /**
     * @brief Releases ownership of the value stored within this object.
     * NOTE: Use the 'delete' operator to destruct the value.
     *
     * @throw bad_optional_access_t if this object does not contain a value.
     * @return a pointer to the value stored within this object.
     */
    [[nodiscard]] type_t* release() {
        if (! this->has_value()) {
            throw bad_optional_access_t{ RES_ERROR(
              this->error(), bad_optional_access_message) };
        }

        return this->value_.release();
    }

    /**
     * @return true if this object contains a value and false otherwise.
     */
    [[nodiscard]] bool has_value() const {
        return this->value_ != nullptr;
    }

    /**
     * @throw bad_optional_access_t if this object does not contain a value.
     * @return a const reference to the value stored within this object.
     */
    [[nodiscard]] const type_t& value() const {
        return *(this->operator->());
    }

    /**
     * @throw bad_optional_access_t if this object does not contain a value.
     * @return a reference to the value stored within this object.
     */
    [[nodiscard]] type_t& value() {
        return *(this->operator->());
    }

    /**
     * @return true if this object contains an error and false otherwise.
     */
    [[nodiscard]] bool has_error() const {
        return this->error_ != nullptr;
    }

    /**
     * @return a copy of the value stored within this object or a generic
     * success message if this object does not contain an error.
     */
    [[nodiscard]] error_t error() const {
        if (! this->has_error()) {
            return has_value_error;
        }

        return *(this->error_);
    }
};

} // namespace res
