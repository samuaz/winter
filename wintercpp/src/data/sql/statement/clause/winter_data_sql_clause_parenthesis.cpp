//
// Created by Samuel Azcona on 18/06/2020.
//

#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_parenthesis.h>

winter::data::sql_impl::Parenthesis::Parenthesis(
    winter::data::sql_impl::Clause *clause) :
    Clause("($clause)", "$clause") {
    set_statement_template(winter::util::string::replace_value(
        statement_template(),
        "$clause",
        clause->Prepare().statement_template()));
}

        std::string winter::data::sql_impl::Parenthesis::Parenthesis::name() const {
            return "On";
    };


winter::data::sql_impl::Parenthesis::Parenthesis(const std::string &clause) :
    Clause("($clause)", "$clause") {
    set_statement_template(winter::util::string::replace_value(
        statement_template(), "$clause", clause));
}

winter::data::sql_impl::PreparedStatement
winter::data::sql_impl::Parenthesis::Prepare() {
    return winter::data::sql_impl::PreparedStatement(StatementType::kClause,
                                                     statement_template());
}
