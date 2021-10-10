//
// Created by Samuel Azcona on 25/03/2020.
//

#ifndef WINTER_DATA_SQL_RESPONSE
#define WINTER_DATA_SQL_RESPONSE

#include <wintercpp/data/response/winter_data_response_status.h>
#include <wintercpp/data/response/winter_data_result_response_collection.h>
#include <wintercpp/data/sql/statement/winter_data_sql_statement_type.h>
#include <wintercpp/template/winter_response_template.h>

#include <optional>
#include <string>
#include <utility>

namespace winter::data::sql {

template <typename TImplementation, typename TResultRow>
class Response : public winter::templates::Response<
		     TImplementation,
		     std::vector<TResultRow>,
		     winter::data::ResponseStatus> {
  using winter::templates::Response<
      TImplementation,
      std::vector<TResultRow>,
      winter::data::ResponseStatus>::Value;

  using winter::templates::Response<
      TImplementation,
      std::vector<TResultRow>,
      winter::data::ResponseStatus>::status;

 public:
  Response(
      std::string transaction_id,
      StatementType type,
      winter::data::ResponseStatus status,
      std::string message) : winter::templates::Response<TImplementation, std::vector<TResultRow>, winter::data::ResponseStatus>(status, message), transaction_id_(std::move(transaction_id)), type_(type) {}

  Response(
      std::string transaction_id,
      StatementType type,
      std::vector<TResultRow> result,
      winter::data::ResponseStatus status,
      std::string message,
      int row_affected) : winter::templates::Response<TImplementation, std::vector<TResultRow>, winter::data::ResponseStatus>(result, status, message), transaction_id_(std::move(transaction_id)), type_(type), row_affected_(row_affected) {}

  Response(const Response&) = delete;
  Response& operator=(const Response&) = delete;

  virtual ~Response() = default;

  int row_affected() const {
    return row_affected_;
  }

  const std::string&
  transaction_id() const {
    return transaction_id_;
  }

  StatementType
  type() const {
    return type_;
  }

  std::optional<TResultRow>
  RequireSingleOrNullopt() const {
    return winter::data::response::RequireSingleOrNullopt(Value()).Value();
  }

  std::optional<TResultRow>
  FirstOrNullopt() const {
    return winter::data::response::FirstOrNullopt(Value()).Value();
  }

  bool
  IsSuccess() const override {
    if (status() == ResponseStatus::kError) {
      return false;
    }
    return true;
  };

  bool
  IsError() const override {
    return !IsSuccess();
  };

 private:
  const std::string transaction_id_{};
  const StatementType type_{0};
  const int row_affected_{0};
};

}  // namespace winter::data::sql

#endif /* WINTER_DATA_SQL_RESPONSE */
