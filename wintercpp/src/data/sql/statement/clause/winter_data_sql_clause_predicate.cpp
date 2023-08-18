//
// Created by Samuel Azcona on 21/05/2020.
//

#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_predicate.h>
#include <wintercpp/util/winter_string_util.h>

#include <string>

#include "wintercpp/data/sql/statement/clause/winter_data_sql_clause_operator.h"
#include "wintercpp/data/sql/statement/winter_data_sql_statement_values.h"
#include "wintercpp/data/sql/statement/winter_data_sql_statement_values_utils.h"
#include "wintercpp/exception/generic/winter_internal_exception.h"

using namespace winter::util::string;
using namespace winter::data::sql_impl;

Predicate::Predicate(const StatementValue& statement_value) :
    l_statement_value_(statement_value),
    condition_(Condition::NONE) {}

Predicate::Predicate(const PreparedStatementField& field) :
    condition_(Condition::NONE), fields_(std::vector {field}) {}

Predicate::Predicate(const std::vector<PreparedStatementField>& fields) :
    condition_(Condition::NONE), fields_(fields) {}

Predicate::Predicate(
    const StatementValue& statement_value,
    Condition             conditionOperator) :
    l_statement_value_(statement_value),
    condition_(conditionOperator) {}

Predicate::Predicate(
    const StatementValue&         statement_value,
    const PreparedStatementField& field) :
    l_statement_value_(statement_value),
    condition_(Condition::NONE),
    fields_(std::vector {field}) {
}

Predicate::Predicate(
    const StatementValue&         statement_value,
    Condition                     conditionOperator,
    const PreparedStatementField& field) :
    l_statement_value_(statement_value),
    condition_(conditionOperator),
    fields_(std::vector {field}) {}

Predicate::Predicate(
    const StatementValue& l_statement_value,
    Condition             conditionOperator,
    const StatementValue& r_statement_value) :
    l_statement_value_(l_statement_value),
    condition_(conditionOperator), r_statement_value_(r_statement_value) {}

const std::optional<StatementValue>&
Predicate::lstatementValue() const {
    return l_statement_value_;
}

const std::optional<StatementValue>&
Predicate::rstatementValue() const {
    return r_statement_value_;
}

const std::vector<PreparedStatementField>&
Predicate::fields() const {
    return fields_;
}

const PreparedStatementField& Predicate::field() const {
    if (has_fields()) {
        return fields().front();
    }
    throw winter::exception::WinterInternalException::Create(
        __FILE__,
        __FUNCTION__,
        __LINE__,
        "Predicate Fields empty");
}

::Condition Predicate::condition() const {
    return condition_;
}

std::string Predicate::lstatementStr() const {
    return statementStr(l_statement_value_);
}

std::string Predicate::rstatementStr() const {
    return statementStr(r_statement_value_);
};

std::string Predicate::statementStr(std::optional<StatementValue> statement_value) const {
    if (statement_value) {
        auto        value = statement_value.value();
        bool        isClause = IsClause(value) || IsStatement(value);
        std::string clauseValue = GetStatementValue(value);
        return ((isClause) ? "(" + clauseValue + ")" : clauseValue);
    }
    return GetStatementValue(statement_value);
}

std::string Predicate::conditionStr() const {
    return ::condition(condition_);
};

bool Predicate::has_lstatement() const {
    return l_statement_value_.has_value();
};

bool Predicate::has_rstatement() const {
    return r_statement_value_.has_value();
};

bool Predicate::has_condition() const {
    return condition_ != Condition::NONE;
};

bool Predicate::has_fields() const {
    return ! fields_.empty();
};
