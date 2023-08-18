//
// Created by Samuel Azcona on 16/06/2020.
//

#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_set.h>
#include <wintercpp/data/sql/statement/winter_data_sql_statement_util.h>
#include <wintercpp/exception/generic/winter_exception.h>
#include <wintercpp/exception/generic/winter_internal_exception.h>
#include <wintercpp/util/winter_string_util.h>

#include <string>
#include <utility>

#include "wintercpp/data/sql/statement/clause/winter_data_sql_clause_predicate.h"

namespace winter::data::sql_impl {

    Set::Set(const std::vector<PreparedStatementField> &fields) :
        predicate_(fields) {}

    Set::Set(const PreparedStatementField &field) :
        predicate_(field) {}

    Set::Set(const Predicate &predicate) :
        predicate_(predicate) {}

    std::vector<PreparedStatementField> Set::Fields() const {
        return predicate_.fields();
    }

    std::string
    Set::Query() const {
        return winter::util::string::replace_value(
            query_template_,
            query_param_,
            commaSeparatedEqualValue(predicate_.fields()));
    }
}  // namespace winter::data::sql_impl