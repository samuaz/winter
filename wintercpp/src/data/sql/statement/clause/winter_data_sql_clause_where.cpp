#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_where.h>
#include <wintercpp/data/sql/statement/winter_data_sql_statement_util.h>
#include <wintercpp/exception/generic/winter_exception.h>
#include <wintercpp/exception/generic/winter_internal_exception.h>
#include <wintercpp/util/winter_string_util.h>

#include "wintercpp/data/sql/statement/clause/winter_data_sql_clause_predicate.h"
#include "wintercpp/data/sql/statement/winter_data_sql_statement_values.h"

using namespace winter::util::string;
using namespace winter::data::sql_impl;

Where::Where(const Predicate& predicate) :
    predicate_(predicate) {}

Where::Where(const StatementValue& statement_value) :
    predicate_(statement_value) {}

Where::Where(
    const StatementValue& statement_value, Condition condition) :
    predicate_(statement_value, condition) {}

std::vector<std::shared_ptr<winter::data::sql_impl::AbstractPreparedStatementField>> Where::Fields() const {
    return predicate_.fields();
}

std::string
Where::Query() const {
    std::ostringstream builder;
    bool               isColumn = predicate_.lstatementValue() ? IsColumn(predicate_.lstatementValue().value()) : false;
    bool               haveRStatement = predicate_.rstatementValue().has_value();

    if (isColumn && predicate_.has_fields()) {
        const auto&       field = predicate_.field();
        const std::string value_str = field->IsCustomValue() ? field->custom_value().value() : PlaceHolder();
        builder << predicate_.lstatementStr()
                << Space()
                << predicate_.conditionStr()
                << Space()
                << value_str;
    } else if (isColumn && ! haveRStatement) {
        builder << predicate_.lstatementStr()
                << Space()
                << predicate_.conditionStr();
    } else if (haveRStatement) {
        builder << predicate_.lstatementStr()
                << Space()
                << predicate_.conditionStr()
                << Space()
                << predicate_.rstatementStr();
    } else {
        builder << predicate_.lstatementStr()
                << Space()
                << predicate_.conditionStr();
    }
    return replace_value(query_template_, query_param_, builder.str());
}