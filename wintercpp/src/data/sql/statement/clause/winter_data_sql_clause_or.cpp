//
// Created by Samuel Azcona on 21/05/2020.
//

#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_or.h>
#include <wintercpp/data/sql/statement/winter_data_sql_statement_util.h>
#include <wintercpp/exception/generic/winter_exception.h>
#include <wintercpp/exception/generic/winter_internal_exception.h>
#include <wintercpp/util/winter_string_util.h>

#include <memory>
#include <string>

#include "wintercpp/data/sql/statement/winter_data_sql_statement_values.h"

using namespace winter::util::string;

winter::data::sql_impl::Or::Or(const Predicate &predicate) :
    statement_value_(predicate.lstatementValue()),
    field_(predicate.field()), condition_(predicate.condition()),
    is_predicate_(true) {}

winter::data::sql_impl::Or::Or(const StatementValue &statement_value) :
    statement_value_(statement_value),
    condition_(winter::data::sql_impl::Condition::NONE) {}

winter::data::sql_impl::Or::Or(const StatementValue             &statement_value,
                               winter::data::sql_impl::Condition condition) :
    statement_value_(statement_value),
    condition_(condition) {}

std::vector<std::shared_ptr<winter::data::sql_impl::AbstractPreparedStatementField>> winter::data::sql_impl::Or::Or::Fields() const {
    std::vector<std::shared_ptr<winter::data::sql_impl::AbstractPreparedStatementField>> fields;
    fields.push_back(field_);
    return fields;
}

std::string
winter::data::sql_impl::Or::Query() const {
    std::ostringstream builder;

    auto subqueryfn = [&]() -> std::string {
        if (auto sharedColumn = std::get_if<std::shared_ptr<Column>>(&statement_value_)) {
            return sharedColumn->get()->FullName();
        } else if (auto column = std::get_if<Column>(&statement_value_)) {
            return column->FullName();
        } else if (auto clause = std::get_if<std::shared_ptr<Clause>>(&statement_value_)) {
            return clause->get()->Query();
        }
        std::string typeName = StatementValueType(statement_value_.index());
        std::string error = "invalid statement_value " + typeName + "not supported";
        throw ::winter::exception::WinterInternalException::Create(
            __FILE__,
            __FUNCTION__,
            __LINE__,
            (error));
    };

    auto subquery = subqueryfn();

    if (is_predicate_) {
        if (field_->IsCustomValue()) {
            builder << subquery
                    << Space() << condition(condition_) << Space()
                    << field_->custom_value();
        } else {
            builder << subquery
                    << Space() << condition(condition_) << Space()
                    << PlaceHolder();
        }

        return replace_value(query_template_, query_param_, builder.str());
    }

    builder << subquery
            << ((condition_ != Condition::NONE)
                    ? Space() + condition(condition_)
                    : "");

    return replace_value(query_template_, query_param_, builder.str());
}
