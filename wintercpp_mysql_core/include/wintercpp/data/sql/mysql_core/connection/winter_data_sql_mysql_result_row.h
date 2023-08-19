/**
 * @author Samuel Azcona
 * @email samuel@theopencompany.dev
 * @create date 2021-08-25 04:21:24
 * @modify date 2021-08-25 04:21:24
 * @desc [description]
 */

#ifndef WINTER_DATA_SQL_MYSQL_RESULT_ROW
#define WINTER_DATA_SQL_MYSQL_RESULT_ROW

#include <wintercpp/data/sql/column/winter_data_sql_column.h>
#include <wintercpp/data/sql/connection/winter_data_sql_result_row.h>
#include <wintercpp/data/sql/field/winter_data_sql_field_type.h>

#include <__tuple>
#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <variant>

#include "wintercpp/data/sql/statement/clause/winter_data_sql_clause.h"
#include "wintercpp/data/sql/statement/winter_data_sql_statement_values.h"
#include "wintercpp/exception/generic/winter_internal_exception.h"

namespace winter::data::sql_impl::mysql {

    template<typename TResultSet>
    class ResultRow :
        public virtual winter::data::sql_impl::ResultRow<
            std::shared_ptr<TResultSet>> {
       public:
        // using
        // winter::data::sql_impl::ResultRow<std::shared_ptr<::sql::ResultSet>>::operator[];
        // using
        // winter::data::sql_impl::ResultRow<std::shared_ptr<::sql::ResultSet>>::Value;

        using winter::data::sql_impl::ResultRow<
            std::shared_ptr<TResultSet>>::AddRow;

        explicit ResultRow(const PreparedStatement           &prepared_statement,
                           const std::shared_ptr<TResultSet> &result_set) {
            Create(prepared_statement, result_set);
        };

       private:
        // we are creating always the result row with the next position from the resultset for that reason we can not move the cursor here
        void Create(const PreparedStatement           &prepared_statement,
                    const std::shared_ptr<TResultSet> &result_set) override {
            auto funAddValue = [&](const std::string &name, const FieldType &type) {
                if (result_set->isNull(name)) {
                    AddRow(name, std::nullopt);
                } else {
                    CreateRow(name, type, result_set);
                }
            };

            if (result_set != nullptr) {
                if (result_set->rowsCount() > 0) {
                    auto statement_values = prepared_statement.statementValues();
                    for (const auto &statement_value : statement_values) {
                        if (auto columnValue = std::get_if<Column>(&statement_value)) {
                            funAddValue(columnValue->FullName(), columnValue->type());
                        } else if (auto sharedColumnValue = std::get_if<std::shared_ptr<Column>>(&statement_value)) {
                            funAddValue(columnValue->FullName(), columnValue->type());
                        } else if (auto clauseValue = std::get_if<std::shared_ptr<winter::data::sql_impl::Clause>>(&statement_value)) {
                            auto name = clauseValue->get()->Alias();
                            auto type = clauseValue->get()->FieldType();
                            if (! name.has_value()) {
                                throw WinterInternalException("Alias not found on clause");
                            }
                            if (! type.has_value()) {
                                throw WinterInternalException("FieldType not found on clause");
                            }
                            funAddValue(name.value(), type.value());
                        }
                    }
                }
            }
        };

        void CreateRow(const std::string &value_name,

                       FieldType                          type,
                       const std::shared_ptr<TResultSet> &result) {
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
                    AddRow(value_name,
                           std::string(result->getString(value_name).c_str()));
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

    // typedef winter::data::sql_impl::mysql::ResultRow MysqlResultRow;

}  // namespace winter::data::sql_impl::mysql

#endif /* WINTER_DATA_SQL_MYSQL_RESULT_ROW */
