#ifndef WINTER_DATA_SQL_RESULT_ROW
#define WINTER_DATA_SQL_RESULT_ROW
#include <wintercpp/data/sql/column/winter_data_sql_column.h>

#include <cstddef>
#include <cstdint>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <variant>

#include "wintercpp/data/response/winter_data_response.h"
#include "wintercpp/data/sql/statement/winter_data_sql_query.h"
#include "wintercpp/exception/generic/winter_internal_exception.h"

namespace winter::data::sql {

using namespace winter::exception;

template <typename TResultSet>
class ResultRow {
  class DataTypeResult;

 public:
  virtual void Create(const PreparedStatement &prepared_statement, const TResultSet &result_set) = 0;

  ResultRow &operator=(const ResultRow &) = default;

  virtual ~ResultRow() = default;

  DataTypeResult
  operator[](const winter::data::sql::Column &column) const {
    auto column_name = column.name();
    return this->operator[](column_name);
  }

  DataTypeResult
  operator[](const std::string &column_name) const {
    if (rows_.find(column_name) == rows_.end()) {
      return DataTypeResult(winter::data::response::Response<DataType>::Error("value for column " + column_name + " not found"));
    } else {
      return DataTypeResult(winter::data::response::Response<DataType>::Success(rows_.at(column_name)));
    }
  }

  template <typename T>
  winter::data::response::Response<T>
  Value(const winter::data::sql::Column &column) const {
    auto column_name = column.name();
    return Value(column_name);
  }

  template <typename T>
  winter::data::response::Response<T>
  Value(const std::string &column_name) const {
    return this[column_name].template as<T>();
  }

 protected:
  const Rows &
  rows() const {
    return rows_;
  }

  const Rows &
  set_rows(const Rows &rows) {
    return rows_ = rows;
  }

  void
  AddRow(std::string name, const std::optional<DataType> &sqlType) {
    rows_.insert(std::pair(name, sqlType));
  }

 private:
  Rows rows_;

  class DataTypeResult {
   public:
    explicit DataTypeResult(winter::data::response::Response<DataType> res) : res_(res) {}

    template <typename T>
    T as() {
      if (res_) {
	return std::get<T>(res_.Value());
      }
      throw WinterInternalException::Create(__FILE__, __FUNCTION__, __LINE__, res_.message());
    }

   private:
    winter::data::response::Response<DataType> res_;
  };
};

}  // namespace winter::data::sql

#endif /* WINTER_DATA_SQL_RESULT_ROW */
