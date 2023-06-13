//
// Created by Samuel Azcona on 21/05/2020.
//

#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_and.h>
#include <wintercpp/data/sql/statement/winter_data_sql_statement.h>
#include <wintercpp/data/sql/statement/winter_data_sql_statement_util.h>
#include <wintercpp/data/sql/statement/winter_data_sql_statement_values.h>
#include <wintercpp/exception/generic/winter_exception.h>
#include <wintercpp/exception/generic/winter_internal_exception.h>
#include <wintercpp/util/winter_string_util.h>

#include <string>

#include "wintercpp/data/sql/statement/clause/winter_data_sql_clause_parenthesis.h"
#include "wintercpp/data/sql/statement/clause/winter_data_sql_clause_predicate.h"

using namespace winter::util::string;
using namespace winter::data::sql_impl;

And::And(const Predicate &predicate) :
    predicate_(predicate) {}

/* winter::data::sql_impl::And::And(const StatementValue &statement_value) :
    l_statement_value_(statement_value),
    condition_(winter::data::sql_impl::Condition::NONE) {}

winter::data::sql_impl::And::And(const StatementValue             &statement_value,
                                 winter::data::sql_impl::Condition condition) :
    l_statement_value_(statement_value),
    condition_(condition) {}

winter::data::sql_impl::And::And(const StatementValue             &l_statement_value,
                                 winter::data::sql_impl::Condition condition,
                                 const StatementValue             &r_statement_value) :
    l_statement_value_(l_statement_value),
    r_statement_value_(r_statement_value),
    condition_(condition) {} */

std::vector<std::shared_ptr<winter::data::sql_impl::AbstractPreparedStatementField>> And::And::Fields() const {
    std::vector<std::shared_ptr<winter::data::sql_impl::AbstractPreparedStatementField>> fields;
    fields.push_back(predicate_.field());
    return fields;
}

std::string
And::Query() const {
    std::ostringstream builder;
    auto               field = predicate_.field();
    auto               lstatement = predicate_.lstatementStr();
    auto               rstatement = predicate_.rstatementStr();
    auto               condition = predicate_.conditionStr();

    if (predicate_.has_field()) {
        if (field->IsCustomValue()) {
            builder << lstatement
                    << Space() << condition << Space()
                    << field->custom_value();
        } else {
            builder << lstatement
                    << Space() << condition << Space()
                    << PlaceHolder();
        }
        return replace_value(query_template_, query_param_, builder.str());
    }

    if (predicate_.has_rstatement()) {
        builder << lstatement
                << Space() << condition << Space()
                << rstatement;
        return replace_value(query_template_, query_param_, builder.str());
    }

    builder << lstatement
            << Space() << condition;
    return replace_value(query_template_, query_param_, builder.str());
}

/*     if (auto columnValue = std::get_if<std::shared_ptr<Column>>(&l_statement_value_)) {
        if (is_predicate_) {
            if (field_->IsCustomValue()) {
                builder << columnValue->get()->FullName()
                        << Space() << condition(condition_) << Space()
                        << field_->custom_value();
            } else {
                builder << columnValue->get()->FullName()
                        << Space() << condition(condition_) << Space()
                        << PlaceHolder();
            }
            return replace_value(query_template_, query_param_, builder.str());
        }

        builder << columnValue->get()->FullName()
                << ((condition_ != Condition::NONE)
                        ? Space() + condition(condition_)
                        : "");
        return replace_value(query_template_, query_param_, builder.str());
    } else if (auto clauseValue = std::get_if<std::shared_ptr<Clause>>(&l_statement_value_)) {
        builder << clauseValue->get()->Query();
        return replace_value(query_template_, query_param_, builder.str());
    } else if (auto statement = std::get_if<std::shared_ptr<IStatement>>(&l_statement_value_)) {
        builder << statement->get()->prepared_statement().statement_template() << Space() << condition(condition_) << Space();
        return replace_value(query_template_, query_param_, builder.str());
    }

    std::string typeName = StatementValueType(l_statement_value_.index());
    std::string error = "invalid statement_value " + typeName + "not supported";

    throw ::winter::exception::WinterInternalException::Create(
        __FILE__,
        __FUNCTION__,
        __LINE__,
        (error));
}
 */