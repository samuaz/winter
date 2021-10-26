#ifndef WINTER_DATA_RESULT_RESPONSE_COLLECTION
#define WINTER_DATA_RESULT_RESPONSE_COLLECTION

//#include <mysql/jdbc.h>
#include <wintercpp/data/response/winter_data_response.h>
#include <wintercpp/data/response/winter_data_response_status.h>
#include <wintercpp/data/sql/column/winter_data_sql_column.h>
#include <wintercpp/exception/generic/winter_exception.h>
#include <wintercpp/exception/generic/winter_internal_exception.h>

#include <optional>
#include <string>
#include <utility>

namespace winter::data::response {
using namespace winter::exception;

/**
 * @brief returns single element, nullopt if there are no elements or throws an exception if there is more than one element
 *
 * @return std::optional<ResultRow>
 */
template <typename T>
Response<T>
RequireSingleOrNullopt(const std::vector<T>& result) {
  if (result.empty()) {
    return Response<T>::Error("Collection is empty");
  }

  if (result.size() > 1) {
    throw WinterInternalException::Create(__FILE__, __FUNCTION__, __LINE__, "Collection has more than one element");
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
RequireSingleOrNullopt(const Response<std::vector<T>>& result) {
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
FirstOrNullopt(const std::vector<T>& result) {
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
FirstOrNullopt(const Response<std::vector<T>>& result) {
  if (!result.HasValue()) {
    return Response<T>::Error("Collection is empty");
  }
  return FirstOrNullopt(result.Value());
}

}  // namespace winter::data::response

#endif /* WINTER_DATA_RESULT_RESPONSE_COLLECTION */
