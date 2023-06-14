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

#include "wintercpp/data/sql/statement/clause/winter_data_sql_clause_predicate.h"
#include "wintercpp/data/sql/statement/winter_data_sql_statement_values.h"

using namespace winter::util::string;

winter::data::sql_impl::Or::Or(const Predicate &predicate) :
    predicate_(predicate),
    is_predicate_(true) {}

winter::data::sql_impl::Or::Or(const StatementValue &statement_value) :
    predicate_(statement_value) {}

winter::data::sql_impl::Or::Or(const StatementValue             &statement_value,
                               winter::data::sql_impl::Condition condition) :
    predicate_(statement_value, condition) {}

std::vector<std::shared_ptr<winter::data::sql_impl::AbstractPreparedStatementField>> winter::data::sql_impl::Or::Or::Fields() const {
    return predicate_.fields();
}

std::string
winter::data::sql_impl::Or::Query() const {
    std::ostringstream builder;

    if (is_predicate_) {
        const auto &field = predicate_.field();
        if (field->IsCustomValue()) {
            builder << predicate_.lstatementStr()
                    << Space() << predicate_.conditionStr() << Space()
                    << field->custom_value();
        } else {
            builder << predicate_.lstatementStr()
                    << Space() << predicate_.conditionStr() << Space()
                    << PlaceHolder();
        }

        return replace_value(query_template_, query_param_, builder.str());
    }

    builder << predicate_.lstatementStr()
            << predicate_.conditionStr();

    return replace_value(query_template_, query_param_, builder.str());
}
