//
// Created by Samuel Azcona on 17/05/2020.
//

#ifndef WINTER_RESPONSE_TEMPLATE
#define WINTER_RESPONSE_TEMPLATE

#include <wintercpp/data/response/winter_data_response_status.h>
#include <wintercpp/exception/generic/winter_exception.h>

#include <functional>
#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include <type_traits>

template <typename T>
struct std::is_pointer<std::shared_ptr<T> > : std::true_type {
};

template <typename T>
struct std::is_pointer<std::optional<std::shared_ptr<T> > > : std::true_type {
};

/* template <typename T>
struct std::is_pointer<T *> : std::true_type {};

template <typename T>
struct std::is_pointer<T &> : std::false_type {}; */

namespace winter::data {
class AbstractResponse {
  virtual const std::string &message() const = 0;
};
}  // namespace winter::data

namespace winter::templates {
template <typename TImplementation, typename TResultType, typename TStatusType>
class Response : public virtual data::AbstractResponse {
 public:
  Response();

  virtual ~Response() = default;

  virtual bool IsSuccess() const = 0;

  virtual bool IsError() const = 0;

  Response(TStatusType status, std::string message);

  Response(
      const std::optional<TResultType> &result,
      TStatusType status,
      std::string message);

  explicit operator bool() const noexcept;

  bool HasValue() const noexcept;

  auto operator->();

  auto operator->() const;

  auto operator()();

  auto operator()() const;

  auto operator*();

  auto operator*() const;

  auto Value();

  auto Value() const;

  TStatusType status() const;

  void set_status(TStatusType status);

  const std::string &message() const;

  void set_message(const std::string &message);

  const std::optional<TResultType> &result() const;

  void set_result(const TResultType &result);

  auto ReturnOrThrow();

  template <typename T>
  T Then(
      const std::function<T(void)> &on_success,
      const std::function<T(void)> &on_error);

  template <typename T>
  T Then(
      const std::function<T(const TImplementation &)> &on_success,
      const std::function<T(const TImplementation &)> &on_error);

  template <typename T>
  T Then(const std::function<T(const TImplementation &)> &execute);

  template <typename T>
  T Then(const std::function<T(void)> &execute);

  template <typename T>
  std::optional<T> OnSuccess(
      const std::function<std::optional<T>(void)> &callback);

  template <typename T>
  std::optional<T> OnSuccess(
      const std::function<std::optional<T>(const TImplementation &)>
	  &callback);

  template <typename T>
  std::optional<T> OnError(
      const std::function<std::optional<T>(void)> &callback);

  template <typename T>
  std::optional<T> OnError(
      const std::function<std::optional<T>(const TImplementation &)> &callback);

  template <typename Functor>
  auto operator>>(const Functor &functor);

  template <typename Functor>
  auto operator<<(const Functor &functor);

 protected:
  std::optional<TResultType> result_;

  TStatusType status_{};

  std::string message_{};

 private:
  TImplementation &
  This() {
    return dynamic_cast<TImplementation &>(*this);
  }

  template <typename T = TResultType, std::enable_if_t<!std::is_pointer<T>::value> * = nullptr>
  bool HasValue() const;

  template <typename T = TResultType, std::enable_if_t<std::is_pointer<T>::value> * = nullptr>
  bool HasValue() const;
};

}  // namespace winter::templates

#include "winter_response_template.tpp"

#endif /* WINTER_RESPONSE_TEMPLATE */
