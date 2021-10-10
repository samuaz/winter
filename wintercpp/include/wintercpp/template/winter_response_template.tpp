namespace winter::templates {

template <typename TImplementation, typename TResultType, typename TStatusType>
Response<TImplementation, TResultType, TStatusType>::Response(
    TStatusType status,
    std::string message) : status_(status),
			   message_(std::move(message)) {}

template <typename TImplementation, typename TResultType, typename TStatusType>
Response<TImplementation, TResultType, TStatusType>::Response(
    const std::optional<TResultType> &result,
    TStatusType status,
    std::string message) : result_(std::move(result)),
			   status_(status),
			   message_(std::move(message)) {}

template <typename TImplementation, typename TResultType, typename TStatusType>
Response<TImplementation, TResultType, TStatusType>::operator bool()
    const noexcept {
  return this->HasValue();
}

template <typename TImplementation, typename TResultType, typename TStatusType>
bool Response<TImplementation, TResultType, TStatusType>::HasValue()
    const noexcept {
  return HasValue<TResultType>();
}

template <typename TImplementation, typename TResultType, typename TStatusType>
template <typename T, std::enable_if_t<!std::is_pointer<T>::value> *>
bool Response<TImplementation, TResultType, TStatusType>::HasValue() const {
  return result_.has_value();
}

template <typename TImplementation, typename TResultType, typename TStatusType>
template <typename T, std::enable_if_t<std::is_pointer<T>::value> *>
bool Response<TImplementation, TResultType, TStatusType>::HasValue() const {
  return result_.has_value() && *result_ != NULL;
}

template <typename TImplementation, typename TResultType, typename TStatusType>
auto Response<TImplementation, TResultType, TStatusType>::operator->() {
  return result_.value();
}

template <typename TImplementation, typename TResultType, typename TStatusType>
auto Response<TImplementation, TResultType, TStatusType>::operator->() const {
  return result_.value();
}

template <typename TImplementation, typename TResultType, typename TStatusType>
auto Response<TImplementation, TResultType, TStatusType>::operator()() {
  return result_.value();
}

template <typename TImplementation, typename TResultType, typename TStatusType>
auto Response<TImplementation, TResultType, TStatusType>::operator()() const {
  return result_.value();
}

template <typename TImplementation, typename TResultType, typename TStatusType>
auto Response<TImplementation, TResultType, TStatusType>::operator*() {
  return result_.value();
}

template <typename TImplementation, typename TResultType, typename TStatusType>
auto Response<TImplementation, TResultType, TStatusType>::operator*() const {
  return result_.value();
}

template <typename TImplementation, typename TResultType, typename TStatusType>
auto Response<TImplementation, TResultType, TStatusType>::Value() {
  return result_.value();
}

template <typename TImplementation, typename TResultType, typename TStatusType>
auto Response<TImplementation, TResultType, TStatusType>::Value() const {
  return result_.value();
}

template <typename TImplementation, typename TResultType, typename TStatusType>
TStatusType
Response<TImplementation, TResultType, TStatusType>::status()
    const {
  return status_;
}

template <typename TImplementation, typename TResultType, typename TStatusType>
const std::string &
Response<TImplementation, TResultType, TStatusType>::message() const {
  return message_;
}

template <typename TImplementation, typename TResultType, typename TStatusType>
const std::optional<TResultType> &
Response<TImplementation, TResultType, TStatusType>::result() const {
  return result_;
}

template <typename TImplementation, typename TResultType, typename TStatusType>
auto Response<TImplementation, TResultType, TStatusType>::ReturnOrThrow() {
  try {
    if (HasValue()) {
      return result_.value();
    } else {
      throw WinterException(message_);
    }
  } catch (const std::exception &ex) {
    throw WinterException(ex.what());
  }
}

template <typename TImplementation, typename TResultType, typename TStatusType>
template <typename T>
T Response<TImplementation, TResultType, TStatusType>::Then(
    const std::function<T(void)> &on_success,
    const std::function<T(void)> &on_error) {
  if (HasValue() || IsSuccess()) {
    return on_success();
  } else {
    return on_error();
  }
}

template <typename TImplementation, typename TResultType, typename TStatusType>
template <typename T>
T Response<TImplementation, TResultType, TStatusType>::Then(
    const std::function<T(const TImplementation &)> &on_success,
    const std::function<T(const TImplementation &)> &on_error) {
  if (HasValue() || IsSuccess()) {
    return on_success(This());
  } else {
    return on_error(This());
  }
}

template <typename TImplementation, typename TResultType, typename TStatusType>
template <typename T>
T Response<TImplementation, TResultType, TStatusType>::Then(
    const std::function<T(const TImplementation &)> &execute) {
  return execute(This());
}

template <typename TImplementation, typename TResultType, typename TStatusType>
template <typename T>
T Response<TImplementation, TResultType, TStatusType>::Then(
    const std::function<T(void)> &execute) {
  return execute();
}

template <typename TImplementation, typename TResultType, typename TStatusType>
template <typename T>
std::optional<T>
Response<TImplementation, TResultType, TStatusType>::OnSuccess(
    const std::function<std::optional<T>(void)> &callback) {
  if (HasValue() || IsSuccess()) {
    return callback();
  }
  return std::nullopt;
}

template <typename TImplementation, typename TResultType, typename TStatusType>
template <typename T>
std::optional<T>
Response<TImplementation, TResultType, TStatusType>::OnSuccess(
    const std::function<std::optional<T>(const TImplementation &)> &callback) {
  if (HasValue() || IsSuccess()) {
    return callback(This());
  }
  return std::nullopt;
}

template <typename TImplementation, typename TResultType, typename TStatusType>
template <typename T>
std::optional<T>
Response<TImplementation, TResultType, TStatusType>::OnError(
    const std::function<std::optional<T>(void)> &callback) {
  if (!HasValue() || IsError()) {
    return callback();
  }
  return std::nullopt;
}

template <typename TImplementation, typename TResultType, typename TStatusType>
template <typename T>
std::optional<T>
Response<TImplementation, TResultType, TStatusType>::OnError(
    const std::function<std::optional<T>(const TImplementation &)> &callback) {
  if (!HasValue() || IsError()) {
    return callback(This());
  }
  return std::nullopt;
}

template <typename TImplementation, typename TResultType, typename TStatusType>
template <typename Functor>
auto Response<TImplementation, TResultType, TStatusType>::operator>>(const Functor &functor) {
  return functor(This());
}

template <typename TImplementation, typename TResultType, typename TStatusType>
template <typename Functor>
auto Response<TImplementation, TResultType, TStatusType>::operator<<(const Functor &functor) {
  return functor();
}

template <typename TImplementation, typename TResultType, typename TStatusType>
TImplementation &Response<TImplementation, TResultType, TStatusType>::This() {
  return dynamic_cast<TImplementation &>(*this);
}

}  // namespace winter::templates
