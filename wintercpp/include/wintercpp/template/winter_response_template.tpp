//#include "winter_response_template.h"

namespace winter::templates {
    using namespace winter::exception;

    template<typename TImplementation,
             typename TResultType,
             typename TStatusType>
    // requires std::is_enum_v<TStatusType>
    Response<TImplementation, TResultType, TStatusType>::Response(
        TStatusType status, const std::string &message) :
        status_(status),
        message_(message) {}

    template<typename TImplementation,
             typename TResultType,
             typename TStatusType>
    // requires std::is_enum_v<TStatusType>
    Response<TImplementation, TResultType, TStatusType>::Response(
        const std::optional<TResultType> &result,
        TStatusType                       status,
        const std::string                &message) :
        result_(result),
        status_(status), message_(message) {}

    template<typename TImplementation,
             typename TResultType,
             typename TStatusType>
    // requires std::is_enum_v<TStatusType>
    Response<TImplementation, TResultType, TStatusType>::operator bool()
        const noexcept {
        return this->HasValue();
    }

    template<typename TImplementation,
             typename TResultType,
             typename TStatusType>
    // requires std::is_enum_v<TStatusType>
    bool Response<TImplementation, TResultType, TStatusType>::HasValue()
        const noexcept {
        return HasValue<TResultType>();
    }

    template<typename TImplementation,
             typename TResultType,
             typename TStatusType>
    // requires std::is_enum_v<TStatusType>
    template<typename T, std::enable_if_t<! std::is_pointer<T>::value> *>
    bool Response<TImplementation, TResultType, TStatusType>::HasValue() const {
        return result_.has_value();
    }

    template<typename TImplementation,
             typename TResultType,
             typename TStatusType>
    // requires std::is_enum_v<TStatusType>
    template<typename T, std::enable_if_t<std::is_pointer<T>::value> *>
    bool Response<TImplementation, TResultType, TStatusType>::HasValue() const {
        return result_.has_value() && *result_ != NULL;
    }

    template<typename TImplementation,
             typename TResultType,
             typename TStatusType>
    // requires std::is_enum_v<TStatusType>
    auto Response<TImplementation, TResultType, TStatusType>::operator->() {
        return result_.value();
    }

    template<typename TImplementation,
             typename TResultType,
             typename TStatusType>
    // requires std::is_enum_v<TStatusType>
    auto Response<TImplementation, TResultType, TStatusType>::operator->()
        const {
        return result_.value();
    }

    template<typename TImplementation,
             typename TResultType,
             typename TStatusType>
    // requires std::is_enum_v<TStatusType>
    auto Response<TImplementation, TResultType, TStatusType>::operator()() {
        return result_.value();
    }

    template<typename TImplementation,
             typename TResultType,
             typename TStatusType>
    // requires std::is_enum_v<TStatusType>
    auto Response<TImplementation, TResultType, TStatusType>::operator()()
        const {
        return result_.value();
    }

    template<typename TImplementation,
             typename TResultType,
             typename TStatusType>
    // requires std::is_enum_v<TStatusType>
    auto Response<TImplementation, TResultType, TStatusType>::operator*() {
        return result_.value();
    }

    template<typename TImplementation,
             typename TResultType,
             typename TStatusType>
    // requires std::is_enum_v<TStatusType>
    auto Response<TImplementation, TResultType, TStatusType>::operator*()
        const {
        return result_.value();
    }

    template<typename TImplementation,
             typename TResultType,
             typename TStatusType>
    // requires std::is_enum_v<TStatusType>
    auto Response<TImplementation, TResultType, TStatusType>::Value() {
        return result_.value();
    }

    template<typename TImplementation,
             typename TResultType,
             typename TStatusType>
    // requires std::is_enum_v<TStatusType>
    auto Response<TImplementation, TResultType, TStatusType>::Value() const {
        return result_.value();
    }

    template<typename TImplementation,
             typename TResultType,
             typename TStatusType>
    // requires std::is_enum_v<TStatusType>
    TStatusType Response<TImplementation, TResultType, TStatusType>::status()
        const {
        return status_;
    }

    template<typename TImplementation,
             typename TResultType,
             typename TStatusType>
    // requires std::is_enum_v<TStatusType>
    const std::string &
    Response<TImplementation, TResultType, TStatusType>::message() const {
        return message_;
    }

    template<typename TImplementation,
             typename TResultType,
             typename TStatusType>
    // requires std::is_enum_v<TStatusType>
    const std::optional<TResultType>
        &Response<TImplementation, TResultType, TStatusType>::result() const {
        return result_;
    }

    template<typename TImplementation,
             typename TResultType,
             typename TStatusType>
    // requires std::is_enum_v<TStatusType>
    auto Response<TImplementation, TResultType, TStatusType>::ReturnOrThrow() {
        try {
            if (HasValue()) {
                return result_.value();
            } else {
                throw WinterInternalException::Create(
                    __FILE__, __FUNCTION__, __LINE__, message_);
            }
        } catch (const std::exception &ex) {
            throw WinterInternalException::Create(
                __FILE__, __FUNCTION__, __LINE__, ex.what());
        }
    }

    template<typename TImplementation,
             typename TResultType,
             typename TStatusType>
    // requires std::is_enum_v<TStatusType>
    template<typename T>
    T Response<TImplementation, TResultType, TStatusType>::Then(
        const std::function<T(void)> &on_success,
        const std::function<T(void)> &on_error) {
        if (HasValue() || IsSuccess()) {
            return on_success();
        } else {
            return on_error();
        }
    }

    template<typename TImplementation,
             typename TResultType,
             typename TStatusType>
    // requires std::is_enum_v<TStatusType>
    template<typename T>
    T Response<TImplementation, TResultType, TStatusType>::Then(
        const std::function<T(const TImplementation &)> &on_success,
        const std::function<T(const TImplementation &)> &on_error) {
        if (HasValue() || IsSuccess()) {
            return on_success(This());
        } else {
            return on_error(This());
        }
    }

    template<typename TImplementation,
             typename TResultType,
             typename TStatusType>
    // requires std::is_enum_v<TStatusType>
    template<typename T>
    T Response<TImplementation, TResultType, TStatusType>::Then(
        const std::function<T(const TImplementation &)> &execute) {
        return execute(This());
    }

    template<typename TImplementation,
             typename TResultType,
             typename TStatusType>
    // requires std::is_enum_v<TStatusType>
    template<typename T>
    T Response<TImplementation, TResultType, TStatusType>::Then(
        const std::function<T(void)> &execute) {
        return execute();
    }

    template<typename TImplementation,
             typename TResultType,
             typename TStatusType>
    // requires std::is_enum_v<TStatusType>
    template<typename T>
    std::optional<T>
    Response<TImplementation, TResultType, TStatusType>::OnSuccess(
        const std::function<std::optional<T>(void)> &callback) {
        if (HasValue() || IsSuccess()) { return callback(); }
        return std::nullopt;
    }

    template<typename TImplementation,
             typename TResultType,
             typename TStatusType>
    // requires std::is_enum_v<TStatusType>
    template<typename T>
    std::optional<T>
    Response<TImplementation, TResultType, TStatusType>::OnSuccess(
        const std::function<std::optional<T>(const TImplementation &)>
            &callback) {
        if (HasValue() || IsSuccess()) { return callback(This()); }
        return std::nullopt;
    }

    template<typename TImplementation,
             typename TResultType,
             typename TStatusType>
    // requires std::is_enum_v<TStatusType>
    template<typename T>
    std::optional<T>
    Response<TImplementation, TResultType, TStatusType>::OnError(
        const std::function<std::optional<T>(void)> &callback) {
        if (! HasValue() || IsError()) { return callback(); }
        return std::nullopt;
    }

    template<typename TImplementation,
             typename TResultType,
             typename TStatusType>
    // requires std::is_enum_v<TStatusType>
    void
    Response<TImplementation, TResultType, TStatusType>::OnError(
        const std::function<void(void)> &callback) {
        if (! HasValue() || IsError()) { callback(); }
    }

    template<typename TImplementation,
             typename TResultType,
             typename TStatusType>
    // requires std::is_enum_v<TStatusType>
    template<typename T>
    std::optional<T>
    Response<TImplementation, TResultType, TStatusType>::OnError(
        const std::function<std::optional<T>(const TImplementation &)>
            &callback) {
        if (! HasValue() || IsError()) { return callback(This()); }
        return std::nullopt;
    }

    template<typename TImplementation,
             typename TResultType,
             typename TStatusType>
    // requires std::is_enum_v<TStatusType>
    template<typename Functor>
    auto Response<TImplementation, TResultType, TStatusType>::operator>>(
        const Functor &functor) {
        return functor(This());
    }

    template<typename TImplementation,
             typename TResultType,
             typename TStatusType>
    // requires std::is_enum_v<TStatusType>
    template<typename Functor>
    auto Response<TImplementation, TResultType, TStatusType>::operator<<(
        const Functor &functor) {
        return functor();
    }

    template<typename TImplementation,
             typename TResultType,
             typename TStatusType>
    // requires std::is_enum_v<TStatusType>
    TImplementation &
    Response<TImplementation, TResultType, TStatusType>::This() {
        return dynamic_cast<TImplementation &>(*this);
    }

}  // namespace winter::templates
