//
// Created by samuaz on 6/1/22.
//

#ifndef WINTERCPP_WINTER_DATA_SQL_MARIADB_IMPL_RESULT_ROW_H
#define WINTERCPP_WINTER_DATA_SQL_MARIADB_IMPL_RESULT_ROW_H

#include <wintercpp/winter_mysql.h>

#include <mariadb/conncpp.hpp>

namespace winter::data::sql_impl::mysql::connection::mariadb_impl {

#define MARIADB_RESULT_ROW_TEMPLATE_IMPL winter::data::sql_impl::mysql::ResultRow<::sql::ResultSet>

class ResultRow : public virtual MARIADB_RESULT_ROW_TEMPLATE_IMPL {
 public:
  ResultRow(const data::sql_impl::PreparedStatement& preparedStatement, const shared_ptr<sql::ResultSet>& resultSet) :
      MARIADB_RESULT_ROW_TEMPLATE_IMPL(preparedStatement, resultSet) {}
};
}  // namespace winter::data::sql_impl::mysql::connection::mariadb_impl
#endif	// WINTERCPP_WINTER_DATA_SQL_MARIADB_IMPL_RESULT_ROW_H
