//
// Created by Samuel Azcona on 16/06/2020.
//

#ifndef WINTER_DATA_SQL_CLAUSE_SET
#define WINTER_DATA_SQL_CLAUSE_SET

#include <wintercpp/data/sql/column/winter_data_sql_column.h>
#include <wintercpp/data/sql/preparedstatement/winter_data_sql_prepared_statement_field.h>
#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause.h>

#include <memory>
#include <optional>

#include "wintercpp/data/sql/field/winter_data_sql_data_type.h"
#include "wintercpp/data/sql/statement/clause/winter_data_sql_clause_and.h"
#include "wintercpp/data/sql/statement/clause/winter_data_sql_clause_predicate.h"

namespace winter::data::sql_impl {

    class Set : public virtual Clause {
       public:
        explicit Set(const std::vector<std::shared_ptr<AbstractPreparedStatementField>> &fields);
        explicit Set(const std::shared_ptr<AbstractPreparedStatementField> &field);
        explicit Set(const Predicate &predicate);

        std::string                                                  Query() const override;
        std::vector<std::shared_ptr<AbstractPreparedStatementField>> Fields() const override;

        static std::shared_ptr<PreparedStatementField> Add(const Column &column, const DataType &value, const std::optional<std::string> &custom_value_ = nullopt) {
            return Set::Add(column.FullName(), value, custom_value_);
        }

        static std::shared_ptr<PreparedStatementField> Add(const std::string &name, const DataType &value, const std::optional<std::string> &custom_value_ = nullopt) {
            return std::make_shared<PreparedStatementField>(name, value, custom_value_);
        }

       private:
        const Predicate   predicate_;
        const std::string query_template_ = "SET $fields";
        const std::string query_param_ = "$fields";
    };
}  // namespace winter::data::sql_impl

#endif /* WINTER_DATA_SQL_CLAUSE_SET */
