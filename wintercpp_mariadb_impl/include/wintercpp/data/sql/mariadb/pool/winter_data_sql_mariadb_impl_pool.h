//
// Created by samuaz on 6/1/22.
//

#ifndef WINTERCPP_WINTER_DATA_SQL_MARIADB_IMPL_POOL_H
#define WINTERCPP_WINTER_DATA_SQL_MARIADB_IMPL_POOL_H

#include <wintercpp/data/sql/mariadb/connection/winter_data_sql_mariadb_impl_connection.h>
#include <wintercpp/data/sql/mariadb/connection/winter_data_sql_mariadb_impl_connection_config.h>
#include <wintercpp/data/sql/mysql/connection/winter_data_sql_mysql_connection.h>
#include <wintercpp/template/winter_connection_pool_singleton_template.h>
#include <wintercpp/template/winter_connection_pool_template.h>

#include <mariadb/conncpp.hpp>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

namespace winter::data::sql_impl::mysql::connection::mariadb_impl {

class Pool : public virtual winter::templates::SinglePool<
		 winter::data::sql_impl::mysql::connection::mariadb_impl::Pool,
		 winter::data::sql_impl::mysql::connection::mariadb_impl::Connection,
		 winter::data::sql_impl::mysql::connection::mariadb_impl::Config> {
  friend class SinglePool<
      winter::data::sql_impl::mysql::connection::mariadb_impl::Pool,
      winter::data::sql_impl::mysql::connection::mariadb_impl::Connection,
      winter::data::sql_impl::mysql::connection::mariadb_impl::Config>;

 protected:
  explicit Pool(
      const winter::descriptor::PoolDescriptor& pool_descriptor,
      std::optional<winter::data::sql_impl::mysql::connection::mariadb_impl::Config> mysql_config);
  winter::data::sql_impl::mysql::connection::mariadb_impl::Connection* CreateConn() override;
  ~Pool() override = default;
};

}  // namespace winter::data::sql_impl::mysql::connection::mariadb_impl

#endif	// WINTERCPP_WINTER_DATA_SQL_MARIADB_IMPL_POOL_H
