//
// Created by Samuel Azcona on 21/05/2020.
//

#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_and.h>
#include <wintercpp/data/sql/statement/winter_data_sql_statement_util.h>
#include <wintercpp/util/winter_string_util.h>

using namespace winter::util::string;

winter::data::sql_impl::And::And(const Predicate &predicate) :
    Clause("AND $and", "$and"), column_(predicate.column()),
    field_(predicate.field()), condition_(predicate.condition()),
    is_predicate_(true) {}

winter::data::sql_impl::And::And(Column column) :
    Clause("AND $and", "$and"), column_(std::move(column)),
    condition_(winter::data::sql_impl::Condition::NONE) {}

winter::data::sql_impl::And::And(Column                            column,
                                 winter::data::sql_impl::Condition condition) :
    Clause("AND $and", "$and"),
    column_(std::move(column)), condition_(condition) {}

std::string winter::data::sql_impl::And::And::name() {
    throw exception::WinterInternalException::Create(
        __FILE__,
        __FUNCTION__,
        __LINE__,
        ("invalid call to name function on clause"));
};

winter::data::sql_impl::FieldType winter::data::sql_impl::And::fieldType() {
    throw exception::WinterInternalException::Create(
        __FILE__,
        __FUNCTION__,
        __LINE__,
        ("invalid call to fieldtype function on clause"));
}

winter::data::sql_impl::PreparedStatement
winter::data::sql_impl::And::Prepare() {
    std::ostringstream builder;
    if (is_predicate_) {
        if (field_->IsCustomValue()) {
            builder << column_->TableName() << Dot() << column_->name()
                    << Space() << condition(condition_) << Space()
                    << field_->custom_value();
        } else {
            builder << column_->TableName() << Dot() << column_->name()
                    << Space() << condition(condition_) << Space()
                    << PlaceHolder();
        }
        BuildQuery() << builder.str();
        return PreparedStatement(
            StatementType::kClause,
            replace_value(statement_template(), param(), query()),
            field_);
    }

    builder << column_->TableName() << Dot() << column_->name()
            << ((condition_ != Condition::NONE)
                    ? Space() + condition(condition_)
                    : "");

    BuildQuery() << builder.str();
    return PreparedStatement(
        StatementType::kClause,
        replace_value(statement_template(), param(), query()));
}
