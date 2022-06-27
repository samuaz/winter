//
// Created by Samuel Azcona on 26/05/2020.
//

#ifndef WINTERCPP_WINTER_DATA_SQL_STATEMENT_UTIL_H
#define WINTERCPP_WINTER_DATA_SQL_STATEMENT_UTIL_H

#include <wintercpp/data/sql/preparedstatement/winter_data_sql_prepared_statement.h>

#include <string>
#include <vector>

namespace winter::data::sql_impl {

    std::string CommaSeparatedValue(const std::vector<std::string> &elements);

    std::string CommaSeparatedStatement(
        const PreparedStatement &prepared_statement);

    std::string CommaSeparatedStatement(
        const std::deque<std::shared_ptr<AbstractPreparedStatementField> >
            &columns);

    std::string CommaSeparatedPlaceHolder(size_t size);

    std::string CommaSeparatedEqualValue(
        const std::vector<std::string> &elements);

    std::string CommaSeparatedEqualValue(
        const PreparedStatement &prepared_statement);

    std::string commaSeparatedEqualValue(
        const std::deque<std::shared_ptr<AbstractPreparedStatementField> >
            &columns);

    std::string Dot();

    std::string Space();

    std::string Comma();

    std::string Equal();

    std::string PlaceHolder();

    std::string Nothing();
}  // namespace winter::data::sql_impl

#endif  // WINTERCPP_WINTER_DATA_SQL_STATEMENT_UTIL_H
