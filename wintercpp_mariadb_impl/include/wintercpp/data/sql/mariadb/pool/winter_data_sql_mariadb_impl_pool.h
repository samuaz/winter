//
// Created by samuaz on 6/1/22.
//

#ifndef WINTERCPP_WINTER_DATA_SQL_MARIADB_IMPL_POOL_H
#define WINTERCPP_WINTER_DATA_SQL_MARIADB_IMPL_POOL_H

#include <wintercpp/data/sql/mariadb/connection/winter_data_sql_mariadb_impl_connection.h>
#include <wintercpp/data/sql/mariadb/connection/winter_data_sql_mariadb_impl_connection_config.h>
#include <wintercpp/winter_mysql.h>

#include <mariadb/conncpp.hpp>

namespace winter::data::sql_impl::mysql::connection::mariadb_impl {

#define MARIADB_POOL_IMPL winter::data::sql_impl::mysql::connection::Pool<winter::data::sql_impl::mysql::connection::mariadb_impl::Connection, winter::data::sql_impl::mysql::connection::mariadb_impl::Config>

class Pool : public virtual MARIADB_POOL_IMPL {
 public:
  Pool(const PoolDescriptor& poolDescriptor, const optional<winter::data::sql_impl::mysql::connection::mariadb_impl::Config>& mysqlConfig) :
      MARIADB_POOL_IMPL(poolDescriptor, mysqlConfig) {}
};

}  // namespace winter::data::sql_impl::mysql::connection::mariadb_impl
#endif	// WINTERCPP_WINTER_DATA_SQL_MARIADB_IMPL_POOL_H
