//
// Created by Samuel Azcona on 21/05/2020.
//

#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_or.h>
#include <wintercpp/data/sql/statement/winter_data_sql_statement_util.h>
#include <wintercpp/util/winter_string_util.h>

using namespace winter::util::string;

winter::data::sql_impl::Or::Or(const Predicate &predicate) :
    Clause("OR $or", "$or"), column_(predicate.column()),
    field_(predicate.field()), condition_(predicate.condition()),
    is_predicate_(true) {}

winter::data::sql_impl::Or::Or(Column column) :
    Clause("OR $or", "$or"), column_(std::move(column)),
    condition_(winter::data::sql_impl::Condition::NONE) {}

winter::data::sql_impl::Or::Or(Column                            column,
                               winter::data::sql_impl::Condition condition) :
    Clause("OR $or", "$or"),
    column_(std::move(column)), condition_(condition) {}

winter::data::sql_impl::PreparedStatement
winter::data::sql_impl::Or::Prepare() {
    if (is_predicate_) {
        if (field_->IsCustomValue()) {
            BuildQuery() << column_->TableName() << Dot() << column_->name()
                         << Space() << condition(condition_) << Space()
                         << field_->custom_value();
            return PreparedStatement(
                StatementType::kClause,
                replace_value(statement_template(), param(), query()),
                field_);
        } else {
            BuildQuery() << column_->TableName() << Dot() << column_->name()
                         << Space() << condition(condition_) << Space()
                         << PlaceHolder();
            return PreparedStatement(
                StatementType::kClause,
                replace_value(statement_template(), param(), query()),
                field_);
        }
    }

    BuildQuery() << column_->TableName() << Dot() << column_->name()
                 << ((condition_ != Condition::NONE)
                         ? Space() + condition(condition_)
                         : "");
    return PreparedStatement(
        StatementType::kClause,
        replace_value(statement_template(), param(), query()));
}
