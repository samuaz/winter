//
// Created by samuaz on 6/1/22.
//

#ifndef WINTERCPP_WINTER_DATA_SQL_MYSQL_IMPL_RESPONSE_H
#define WINTERCPP_WINTER_DATA_SQL_MYSQL_IMPL_RESPONSE_H

#include <mysql/jdbc.h>
#include <wintercpp/data/sql/mysql/connection/winter_data_sql_mysql_impl_result_row.h>
#include <wintercpp/data/sql/mysql_core/response/winter_data_sql_mysql_response.h>
#include <wintercpp/winter_mysql_core.h>

namespace winter::data::mysql {

#define MYSQL_RESPONSE_IMPL                  \
    winter::data::sql_impl::mysql::Response< \
        winter::data::mysql::connection::ResultRow>

    class Response : public virtual MYSQL_RESPONSE_IMPL {
       public:
        Response(const string& transactionId,
                 StatementType type,
                 ResponseStatus status,
                 const string& message) :
            MYSQL_RESPONSE_IMPL(transactionId, type, status, message) {}

        Response(
            const string& transactionId,
            StatementType type,
            const vector<winter::data::mysql::connection::ResultRow>& result,
            ResponseStatus status,
            const string& message,
            int rowAffected) :
            MYSQL_RESPONSE_IMPL(
                transactionId, type, result, status, message, rowAffected) {}
    };
}  // namespace winter::data::mysql
#endif  // WINTERCPP_WINTER_DATA_SQL_MYSQL_IMPL_RESPONSE_H
