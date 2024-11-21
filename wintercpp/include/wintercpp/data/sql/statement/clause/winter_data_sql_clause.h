//
// Created by Samuel Azcona on 23/05/2020.
//

#ifndef WINTERCPP_WINTER_DATA_SQL_CLAUSE_H
#define WINTERCPP_WINTER_DATA_SQL_CLAUSE_H

#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "wintercpp/data/sql/field/winter_data_sql_field_type.h"
#include "wintercpp/data/sql/preparedstatement/winter_data_sql_prepared_statement_field.h"
#include "wintercpp/data/sql/statement/winter_data_sql_statement.h"

namespace winter::data::sql_impl {

    class Clause {
       public:
        virtual std::string                         Query() const = 0;
        virtual std::vector<PreparedStatementField> Fields() const = 0;

        std::string operator()(const Clause& clause) {
            return "(" + clause.Query() + ")";
        }

        std::string operator()(const std::shared_ptr<Clause> clause) {
            return "(" + clause->Query() + ")";
        }

        std::string operator()(const std::shared_ptr<IStatement> statement) {
            return "(" + statement->prepared_statement().statement_template() + ")";
        }

        std::optional<std::string> Alias() const {
            return alias_;
        }

        std::optional<FieldType> FieldType() const {
            return field_type_;
        }

        void As(const std::string& alias, const winter::data::sql_impl::FieldType& field_type) {
            alias_ = alias;
            field_type_ = field_type;
        }

       protected:
        std::optional<winter::data::sql_impl::FieldType> field_type_;
        std::optional<std::string>                       alias_;
    };

}  // namespace winter::data::sql_impl

#endif  // WINTERCPP_WINTER_DATA_SQL_CLAUSE_H