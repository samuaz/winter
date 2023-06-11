#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_where.h>
#include <wintercpp/data/sql/statement/winter_data_sql_statement_util.h>
#include <wintercpp/exception/generic/winter_exception.h>
#include <wintercpp/exception/generic/winter_internal_exception.h>
#include <wintercpp/util/winter_string_util.h>

#include "wintercpp/data/sql/statement/clause/winter_data_sql_clause.h"

using namespace winter::util::string;
using namespace winter::data::sql_impl;

Where::Where(const Predicate& predicate) :
    statement_value_(predicate.statementValue()),
    field_(predicate.field()),
    condition_(predicate.condition()),
    _is_predicate(true) {}

Where::Where(StatementValue statement_value) :
    statement_value_(std::move(statement_value)),
    condition_(Condition::NONE) {}

Where::Where(
    StatementValue statement_value, Condition condition) :
    statement_value_(std::move(statement_value)),
    condition_(condition) {}

std::vector<std::shared_ptr<winter::data::sql_impl::AbstractPreparedStatementField>> Where::Fields() const {
    std::vector<std::shared_ptr<winter::data::sql_impl::AbstractPreparedStatementField>> fields;
    fields.push_back(field_);
    return fields;
}

std::string
Where::Query() const {
    std::ostringstream builder;
    if (auto columnValue = std::get_if<std::shared_ptr<Column>>(&statement_value_)) {
        if (_is_predicate) {
            if (field_->IsCustomValue()) {
                builder << columnValue->get()->TableName() << Dot() << columnValue->get()->name()
                        << Space() << condition(condition_) << Space()
                        << field_->custom_value();
            } else {
                builder << columnValue->get()->TableName() << Dot() << columnValue->get()->name()
                        << Space() << condition(condition_) << Space()
                        << PlaceHolder();
            }

            return replace_value(query_template_, query_param_, builder.str());
        }

        builder << columnValue->get()->TableName() << Dot() << columnValue->get()->name()
                << ((condition_ != Condition::NONE)
                        ? Space() + condition(condition_)
                        : "");
        return replace_value(query_template_, query_param_, builder.str());
    } else if (auto clauseValue = std::get_if<std::shared_ptr<Clause>>(&statement_value_)) {
        builder << clauseValue->get()->Query();
        return replace_value(query_template_, query_param_, builder.str());
    }

    std::string typeName = StatementValueType(statement_value_.index());
    std::string error = "invalid statement_value " + typeName + "not supported";

    throw ::winter::exception::WinterInternalException::Create(
        __FILE__,
        __FUNCTION__,
        __LINE__,
        (error));
}