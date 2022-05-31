/**
 * @author Samuel Azcona
 * @email samuel@theopencompany.dev
 * @create date 2021-08-25 04:21:24
 * @modify date 2021-08-25 04:21:24
 * @desc [description]
 */

#ifndef WINTER_DATA_SQL_MYSQL_RESULT_ROW
#define WINTER_DATA_SQL_MYSQL_RESULT_ROW

#include <wintercpp/data/sql/mysql/winter_sql_mysql_driver.h>

#if WITH_MYSQL
#include <mysql/jdbc.h>
#elif WITH_MARIADB
#include <mariadb/conncpp.hpp>
#else
#error "NO WINTER_MYSQL_DRIVER"
#endif

#include <wintercpp/data/sql/column/winter_data_sql_column.h>
#include <wintercpp/data/sql/connection/winter_data_sql_result_row.h>
#include <wintercpp/data/sql/field/winter_data_sql_field_type.h>

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <variant>

namespace winter::data::sql_impl::mysql {

class ResultRow final : public virtual winter::data::sql_impl::ResultRow<std::shared_ptr< ::sql::ResultSet> > {
 public:
  // using winter::data::sql_impl::ResultRow<std::shared_ptr<::sql::ResultSet>>::operator[];
  // using winter::data::sql_impl::ResultRow<std::shared_ptr<::sql::ResultSet>>::Value;

  explicit ResultRow(const PreparedStatement &prepared_statement, const std::shared_ptr< ::sql::ResultSet> &result_set) {
    Create(prepared_statement, result_set);
  };

 private:
  void
  Create(const PreparedStatement &prepared_statement, const std::shared_ptr< ::sql::ResultSet> &result_set) override {
    if (result_set != nullptr) {
      if (result_set->first()) {
	auto columns = prepared_statement.columns();
	for (const auto &column : columns) {
	  std::string column_name = column->name();
	  if (result_set->isNull(column_name)) {
	    AddRow(column_name, std::nullopt);
	  } else {
	    CreateRow(column_name, column->type(), result_set);
	  }
	}
      }
    }
  };

  void
  CreateRow(const std::string &value_name, FieldType type, const std::shared_ptr< ::sql::ResultSet> &result) {
    switch (type) {
      case FieldType::kNull: {
	if (result->isNull(value_name)) {
	  AddRow(value_name, std::nullopt);
	}
      } break;
      case FieldType::kChar:
      case FieldType::kDate:
      case FieldType::kDateTime:
      case FieldType::KDecimal:
      case FieldType::kTimeStamp:
      case FieldType::kString:
	AddRow(value_name, std::string(result->getString(value_name).c_str()));
	break;
      case FieldType::kSchar:
      case FieldType::KShort:
      case FieldType::kInt:
	AddRow(value_name, result->getInt(value_name));
	break;
      case FieldType::kEnum:
      case FieldType::kUchar:
      case FieldType::kUshort:
      case FieldType::KUint:
	AddRow(value_name, result->getUInt(value_name));
	break;
      case FieldType::kBigInt:
      case FieldType::kLong:
	AddRow(value_name, result->getInt64(value_name));
	break;
      case FieldType::kUlong:
	AddRow(value_name, result->getUInt64(value_name));
	break;
      case FieldType::kFloat:
      case FieldType::kDouble:
	AddRow(value_name, result->getDouble(value_name));
	break;
      case FieldType::kBoolean:
	AddRow(value_name, result->getBoolean(value_name));
	break;
      case FieldType::kBlob:
	AddRow(value_name, result->getBlob(value_name));
	break;
    }
  }
};

typedef winter::data::sql_impl::mysql::ResultRow MysqlResultRow;

}  // namespace winter::data::sql_impl::mysql

#endif /* WINTER_DATA_SQL_MYSQL_RESULT_ROW */
