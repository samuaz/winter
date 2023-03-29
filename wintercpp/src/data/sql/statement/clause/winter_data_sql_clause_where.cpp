//
// Created by Samuel Azcona on 21/05/2020.
//

#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_where.h>
#include <wintercpp/data/sql/statement/winter_data_sql_statement_util.h>
#include <wintercpp/util/winter_string_util.h>

using namespace winter::util::string;

winter::data::sql_impl::Where::Where(const Predicate &predicate) :
    Clause("WHERE $where", "$where"), column_(predicate.column()),
    field_(predicate.field()), condition_(predicate.condition()),
    _is_predicate(true) {}

winter::data::sql_impl::Where::Where(Column column) :
    Clause("WHERE $where", "$where"), column_(std::move(column)),
    condition_(winter::data::sql_impl::Condition::NONE) {}

winter::data::sql_impl::Where::Where(
    Column column, winter::data::sql_impl::Condition condition) :
    Clause("WHERE $where", "$where"),
    column_(std::move(column)), condition_(condition) {}

std::string winter::data::sql_impl::Where::Where::name() {
    throw exception::WinterInternalException::Create(
        __FILE__,
        __FUNCTION__,
        __LINE__,
        ("invalid call to name function on clause"));
};

winter::data::sql_impl::FieldType winter::data::sql_impl::Where::fieldType() {
    throw exception::WinterInternalException::Create(
        __FILE__,
        __FUNCTION__,
        __LINE__,
        ("invalid call to fieldtype function on clause"));
}

winter::data::sql_impl::PreparedStatement
winter::data::sql_impl::Where::Prepare() {
    std::ostringstream builder;
    if (_is_predicate) {
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
