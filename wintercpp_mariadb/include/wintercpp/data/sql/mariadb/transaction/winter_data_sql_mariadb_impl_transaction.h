//
// Created by samuaz on 6/1/22.
//

#ifndef WINTERCPP_WINTER_DATA_SQL_MARIADB_IMPL_TRANSACTION_H
#define WINTERCPP_WINTER_DATA_SQL_MARIADB_IMPL_TRANSACTION_H

#include <wintercpp/winter_mysql_core.h>
#include <wintercpp/data/sql/mariadb/connection/winter_data_sql_mariadb_impl_connection.h>
#include <wintercpp/data/sql/mariadb/response/winter_data_sql_mariadb_impl_response.h>
#include <wintercpp/winter.h>

namespace winter::data::mariadb {

    using namespace winter::data::sql_impl::mysql::connection;

    class Transaction :
        public virtual winter::data::sql_impl::Transaction<
            winter::data::mariadb::Transaction,
            winter::data::mariadb::connection::Connection,
            winter::data::mariadb::Response> {
       public:
        Transaction(
            const shared_ptr<winter::data::mariadb::connection::Connection>&
                                     connection,
            TransactionIsolationType isolationType = TransactionIsolationType::DEFAULT,
            bool                     partialCommit = false) :
            winter::data::sql_impl::Transaction<
                winter::data::mariadb::Transaction,
                winter::data::mariadb::connection::Connection,
                winter::data::mariadb::Response>(
                connection, isolationType, partialCommit) {}
    };

}  // namespace winter::data::mariadb

#endif  // WINTERCPP_WINTER_DATA_SQL_MARIADB_IMPL_TRANSACTION_H
