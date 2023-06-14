#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_where.h>
#include <wintercpp/data/sql/statement/winter_data_sql_statement_util.h>
#include <wintercpp/exception/generic/winter_exception.h>
#include <wintercpp/exception/generic/winter_internal_exception.h>
#include <wintercpp/util/winter_string_util.h>

#include "wintercpp/data/sql/statement/clause/winter_data_sql_clause.h"
#include "wintercpp/data/sql/statement/clause/winter_data_sql_clause_predicate.h"
#include "wintercpp/data/sql/statement/winter_data_sql_statement_values.h"

using namespace winter::util::string;
using namespace winter::data::sql_impl;

Where::Where(const Predicate& predicate) :
    predicate_(predicate),
    _is_predicate(true) {}

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
    bool               isColumn = IsClause(predicate_.lstatementValue());

    if (isColumn && predicate_.has_fields()) {
        const auto&       field = predicate_.field();
        const std::string value_str = field->IsCustomValue() ? field->custom_value() : PlaceHolder();
        builder << predicate_.lstatementStr()
                << predicate_.conditionStr()
                << value_str;
    } else if (isColumn) {
        builder << predicate_.lstatementStr()
                << predicate_.conditionStr();
    } else {
        builder << predicate_.lstatementStr();
    }
    return replace_value(query_template_, query_param_, builder.str());
}