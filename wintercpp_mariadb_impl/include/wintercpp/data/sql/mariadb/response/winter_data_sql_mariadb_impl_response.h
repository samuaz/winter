//
// Created by samuaz on 6/1/22.
//

#ifndef WINTERCPP_WINTER_DATA_SQL_MARIADB_IMPL_RESPONSE_H
#define WINTERCPP_WINTER_DATA_SQL_MARIADB_IMPL_RESPONSE_H

#include <wintercpp/data/sql/mariadb/connection/winter_data_sql_mariadb_impl_result_row.h>
#include <wintercpp/data/sql/mysql/response/winter_data_sql_mysql_response.h>
#include <wintercpp/winter_mysql.h>

#include <mariadb/conncpp.hpp>

namespace winter::data::mariadb {

#define MARIADB_RESPONSE_IMPL winter::data::sql_impl::mysql::Response<winter::data::mariadb::connection::ResultRow>

class Response : public virtual MARIADB_RESPONSE_IMPL {
 public:
  Response(
    const string& transactionId, 
    StatementType type, 
    ResponseStatus status, 
    const string& message) :
      MARIADB_RESPONSE_IMPL(transactionId, type, status, message) {}

  Response(
    const string& transactionId, 
    StatementType type, 
    const vector<winter::data::mariadb::connection::ResultRow>& result, 
    ResponseStatus status, 
    const string& message, 
    int rowAffected) :
      MARIADB_RESPONSE_IMPL(transactionId, type, result, status, message, rowAffected) {}
};
}  // namespace winter::data::mariadb
#endif	// WINTERCPP_WINTER_DATA_SQL_MARIADB_IMPL_RESPONSE_H
