//
// Created by Samuel Azcona on 27/03/2020.
//

#ifndef WINTER_DATA_SQL_SELECT
#define WINTER_DATA_SQL_SELECT

#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause.h>
#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_from.h>
#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_where.h>
#include <wintercpp/data/sql/statement/winter_data_sql_statement.h>
#include <wintercpp/data/sql/statement/winter_data_sql_statement_values.h>

#include <string>
#include <vector>

namespace winter::data::sql_impl {

    class Select final : public virtual Statement<Select> {
       public:
        Select();

        explicit Select(const std::vector<StatementValue> &statement_value);

        explicit Select(const std::string &query);

        Select &operator<<(std::vector<StatementValue> statement_value);

        using Statement<Select>::prepared_statement;
        using Statement<Select>::operator<<;

        ~Select() override = default;

       protected:
        void BuildStatement() override;

       private:
        using Statement<Select>::prepared_statement_;
        using Statement<Select>::type_;
        std::vector<StatementValue> value_;

        void writeColumns();
    };

}  // namespace winter::data::sql_impl

#endif /* WINTER_DATA_SQL_SELECT */
