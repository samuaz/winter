//
// Created by Samuel Azcona on 21/05/2020.
//

#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_and.h>
#include <wintercpp/data/sql/statement/winter_data_sql_statement_util.h>
#include <wintercpp/exception/generic/winter_exception.h>
#include <wintercpp/exception/generic/winter_internal_exception.h>
#include <wintercpp/util/winter_string_util.h>

#include <string>

#include "wintercpp/data/sql/statement/winter_data_sql_statement_values.h"

using namespace winter::util::string;

winter::data::sql_impl::And::And(const Predicate &predicate) :
    statement_value_(predicate.statementValue()),
    field_(predicate.field()),
    condition_(predicate.condition()),
    is_predicate_(true) {}

winter::data::sql_impl::And::And(StatementValue statement_value) :
    statement_value_(std::move(statement_value)),
    condition_(winter::data::sql_impl::Condition::NONE) {}

winter::data::sql_impl::And::And(StatementValue                    statement_value,
                                 winter::data::sql_impl::Condition condition) :
    statement_value_(std::move(statement_value)),
    condition_(condition) {}

std::vector<std::shared_ptr<winter::data::sql_impl::AbstractPreparedStatementField>> winter::data::sql_impl::And::And::Fields() const {
    std::vector<std::shared_ptr<winter::data::sql_impl::AbstractPreparedStatementField>> fields;
    fields.push_back(field_);
    return fields;
}

std::string
winter::data::sql_impl::And::Query() const {
    std::ostringstream builder;

    if (auto columnValue = std::get_if<std::shared_ptr<Column>>(&statement_value_)) {
        if (is_predicate_) {
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
