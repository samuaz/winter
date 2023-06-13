//
// Created by Samuel Azcona on 21/05/2020.
//

#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_predicate.h>
#include <wintercpp/util/winter_string_util.h>

#include <string>

#include "wintercpp/data/sql/statement/clause/winter_data_sql_clause_operator.h"
#include "wintercpp/data/sql/statement/winter_data_sql_statement_values.h"
#include "wintercpp/data/sql/statement/winter_data_sql_statement_values_utils.h"

using namespace winter::util::string;
using namespace winter::data::sql_impl;

Predicate::Predicate(const StatementValue& statement_value) :
    l_statement_value_(statement_value),
    condition_(Condition::NONE) {}

Predicate::Predicate(
    const StatementValue& statement_value,
    Condition             conditionOperator) :
    l_statement_value_(statement_value),
    condition_(conditionOperator) {}

Predicate::Predicate(
    const StatementValue&                                                          statement_value,
    const std::shared_ptr<winter::data::sql_impl::AbstractPreparedStatementField>& field) :
    l_statement_value_(statement_value),
    condition_(Condition::NONE),
    field_(field) {}

Predicate::Predicate(
    const winter::data::sql_impl::StatementValue&                                  statement_value,
    winter::data::sql_impl::Condition                                              conditionOperator,
    const std::shared_ptr<winter::data::sql_impl::AbstractPreparedStatementField>& field) :
    l_statement_value_(statement_value),
    condition_(conditionOperator),
    field_(field) {}

Predicate::Predicate(
    const StatementValue& l_statement_value,
    Condition             conditionOperator,
    const StatementValue& r_statement_value) :
    l_statement_value_(l_statement_value),
    condition_(conditionOperator), r_statement_value_(r_statement_value) {}

const winter::data::sql_impl::StatementValue&
Predicate::lstatementValue() const {
    return l_statement_value_;
}

const std::optional<winter::data::sql_impl::StatementValue>&
Predicate::rstatementValue() const {
    return r_statement_value_;
}

const std::shared_ptr<winter::data::sql_impl::AbstractPreparedStatementField>&
Predicate::field() const {
    return field_;
}

winter::data::sql_impl::Condition Predicate::condition() const {
    return condition_;
}

std::string Predicate::lstatementStr() const {
    bool        isClause = IsClause(l_statement_value_) || IsStatement(l_statement_value_);
    std::string clauseValue = GetStatementValue(l_statement_value_);
    return ((isClause) ? "(" + clauseValue + ")" : clauseValue);
}

std::string Predicate::rstatementStr() const {
    if (r_statement_value_) {
        auto        value = r_statement_value_.value();
        bool        isClause = IsClause(value) || IsStatement(value);
        std::string clauseValue = GetStatementValue(value);
        return ((isClause) ? "(" + clauseValue + ")" : clauseValue);
    }
    return GetStatementValue(r_statement_value_);
};

std::string Predicate::conditionStr() const {
    return ::condition(condition_);
};

bool Predicate::has_rstatement() const {
    return r_statement_value_.has_value();
};

bool Predicate::has_condition() const {
    return condition_ != Condition::NONE;
};

bool Predicate::has_field() const {
    return field_ != nullptr;
};
