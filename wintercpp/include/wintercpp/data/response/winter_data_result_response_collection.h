#ifndef WINTER_DATA_RESULT_RESPONSE_COLLECTION
#define WINTER_DATA_RESULT_RESPONSE_COLLECTION

#include <mysql/jdbc.h>
#include <wintercpp/data/response/winter_data_response_status.h>
#include <wintercpp/data/sql/column/winter_data_sql_column.h>
#include <wintercpp/data/sql/mysql/connection/winter_data_sql_mysql_result_row.h>
#include <wintercpp/exception/generic/winter_exception.h>

#include <optional>
#include <string>
#include <utility>

#include "wintercpp/exception/generic/winter_exception.h"

namespace winter::data::response {

/**
 * @brief returns single element, nullopt if there are no elements or throws an exception if there is more than one element
 *
 * @return std::optional<ResultRow>
 */
template <typename T>
Response<T>
RequireSingleOrNullopt(std::vector<T> result) {
  if (result.empty()) {
    return Response<T>::Error("Collection is empty");
  }

  if (result.size() > 1) {
    throw WinterException("Collection has more than one element");
  }

  return Response<T>::Success(*result.begin());
}

/**
 * @brief returns single element, nullopt if there are no elements or throws an exception if there is more than one element
 *
 * @return std::optional<ResultRow>
 */
template <typename T>
Response<T>
RequireSingleOrNullopt(Response<std::vector<T> > result) {
  if (!result.HasValue()) {
    return nullopt;
  }
  return RequireSingleOrNullopt(result.Value());
}

/**
 * @brief returns the first element. or nullopt if the ResultRow collection is empty
 *
 * @return std::optional<ResultRow>
 */
template <typename T>
Response<T>
FirstOrNullopt(std::vector<T> result) {
  if (result.empty()) {
    return Response<T>::Error("Collection is empty");
  }

  return Response<T>::Success(*result().begin());
}

/**
 * @brief returns the first element. or nullopt if the ResultRow collection is empty
 *
 * @return std::optional<ResultRow>
 */
template <typename T>
Response<T>
FirstOrNullopt(Response<std::vector<T> > result) {
  if (!result.HasValue()) {
    return Response<T>::Error("Collection is empty");
  }
  return FirstOrNullopt(result.Value());
}

//typedef winter::data::sql::mysql::Response MysqlResponse;

}  // namespace winter::data::response

#endif /* WINTER_DATA_RESULT_RESPONSE_COLLECTION */

/*
template <typename T>
class Collection final : public virtual winter::templates::Response<
                             winter::data::response::Collection<T>,
                             std::vector<T>,
                             winter::data::ResponseStatus> {
 public:
  using winter::templates::Response<
      winter::data::response::Collection<T>,
      std::vector<T>,
      winter::data::ResponseStatus>::HasValue;

  using winter::templates::Response<
      winter::data::response::Collection<T>,
      std::vector<T>,
      winter::data::ResponseStatus>::Value;

  Collection();

  Collection(
      winter::data::ResponseStatus status,
      std::string message);


  std::optional<T> RequireSingleOrNullopt() {
    auto result = Value();
    if (!HasValue() && result->empty()) {
      return nullopt;
    }

    if (result->size() > 1) {
      throw WinterException("Collection has more than one element");
    }

    return std::optional(*result->begin());
  }

  std::optional<T> FirstOrNullopt() {
    auto result = Value();
    if (!HasValue()) {
      return nullopt;
    }

    if (result->empty()) {
      return nullopt;
    }

    return std::optional(*result()->begin());
  }

  static Collection Error(const std::string &message);

  ~Collection();
}; */