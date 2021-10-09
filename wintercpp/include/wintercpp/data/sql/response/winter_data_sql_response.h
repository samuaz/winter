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
  Response() = default;

  explicit Response(StatementType type) : type_(type) {}

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

  int row_affected() const {
    return row_affected_;
  }

  void
  set_row_affected(int row_affected) {
    row_affected_ = row_affected;
  }

  const std::string &
  transaction_id() const {
    return transaction_id_;
  }

  void
  set_transaction_id(const std::string &transaction_id) {
    transaction_id_ = transaction_id;
  }

  StatementType
  type() const {
    return type_;
  }

  void
  set_type(StatementType type) {
    type_ = type;
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
  std::string transaction_id_{};
  StatementType type_{0};
  int row_affected_{0};
};
}  // namespace winter::data::sql

#endif /* WINTER_DATA_SQL_RESPONSE */
