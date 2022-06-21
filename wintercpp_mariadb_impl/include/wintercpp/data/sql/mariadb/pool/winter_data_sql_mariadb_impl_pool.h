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

namespace winter::data::mariadb::connection {

class Pool : public virtual winter::templates::SinglePool<
		 winter::data::mariadb::connection::Pool,
		 winter::data::mariadb::connection::Connection,
		 winter::data::mariadb::connection::Config> {
  friend class SinglePool<
      winter::data::mariadb::connection::Pool,
      winter::data::mariadb::connection::Connection,
      winter::data::mariadb::connection::Config>;

 protected:
  explicit Pool(
      const winter::descriptor::PoolDescriptor& pool_descriptor,
      std::optional<winter::data::mariadb::connection::Config> mysql_config);
  winter::data::mariadb::connection::Connection* CreateConn() override;
  ~Pool() override = default;
};

}  // namespace winter::data::mariadb::connection

#endif	// WINTERCPP_WINTER_DATA_SQL_MARIADB_IMPL_POOL_H
