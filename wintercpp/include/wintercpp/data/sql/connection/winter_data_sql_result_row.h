#ifndef WINTER_DATA_SQL_RESULT_ROW
#define WINTER_DATA_SQL_RESULT_ROW

#include <wintercpp/data/response/winter_data_response.h>
#include <wintercpp/data/sql/column/winter_data_sql_column.h>
#include <wintercpp/data/sql/field/winter_data_sql_data_type.h>
#include <wintercpp/data/sql/preparedstatement/winter_data_sql_prepared_statement.h>

#include <cstddef>
#include <cstdint>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <variant>

namespace winter::data::sql_impl {

using namespace winter::exception;

class DataTypeResult {
 public:
  explicit DataTypeResult(winter::data::response::Response<DataType> res) :res_(res) {}

  template <typename T>
  T as() const;

 private:
  winter::data::response::Response<DataType> res_;
};

template <typename TResultSet>
class ResultRow {
 public:
  virtual void Create(const PreparedStatement &prepared_statement, const TResultSet &result_set) = 0;

  ResultRow &operator=(const ResultRow &) = default;

  virtual ~ResultRow() = default;

  DataTypeResult
  operator[](const winter::data::sql_impl::Column &column) const;

  DataTypeResult
  operator[](const std::string &column_name) const;

  template <typename T>
  winter::data::response::Response<T>
  Value(const winter::data::sql_impl::Column &column) const;

  template <typename T>
  winter::data::response::Response<T>
  Value(const std::string &column_name) const;

 protected:
  const Rows &
  rows() const;

  const Rows &
  set_rows(const Rows &rows);

  void
  AddRow(std::string name, const std::optional<DataType> &sqlType);

 private:
  Rows rows_;
};

}  // namespace winter::data::sql_impl

#include "winter_data_sql_result_row.tpp"

#endif /* WINTER_DATA_SQL_RESULT_ROW */
