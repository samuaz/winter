//
// Created by samuaz on 6/1/22.
//

#ifndef WINTERCPP_WINTER_DATA_SQL_MARIADB_IMPL_TRANSACTION_H
#define WINTERCPP_WINTER_DATA_SQL_MARIADB_IMPL_TRANSACTION_H

#include <wintercpp/data/sql/mariadb/connection/winter_data_sql_mariadb_impl_connection.h>
#include <wintercpp/winter_mysql_core.h>

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
            TransactionIsolationType isolationType,
            bool partialCommit) :
            winter::data::sql_impl::Transaction<
                winter::data::mariadb::Transaction,
                winter::data::mariadb::connection::Connection,
                winter::data::mariadb::Response>(
                connection, isolationType, partialCommit) {}
    };

}  // namespace winter::data::mariadb

#endif  // WINTERCPP_WINTER_DATA_SQL_MARIADB_IMPL_TRANSACTION_H
