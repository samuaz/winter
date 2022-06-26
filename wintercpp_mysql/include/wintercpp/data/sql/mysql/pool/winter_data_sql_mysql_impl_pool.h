//
// Created by samuaz on 6/1/22.
//

#ifndef WINTERCPP_WINTER_DATA_SQL_MYSQL_IMPL_POOL_H
#define WINTERCPP_WINTER_DATA_SQL_MYSQL_IMPL_POOL_H

#include <wintercpp/data/sql/mysql/connection/winter_data_sql_mysql_impl_connection.h>
#include <wintercpp/data/sql/mysql/connection/winter_data_sql_mysql_impl_connection_config.h>
#include <wintercpp/template/winter_connection_pool_singleton_template.h>
#include <wintercpp/template/winter_connection_pool_template.h>
#include <wintercpp/winter_mysql_core.h>

#include <mysql/jdbc.h>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

namespace winter::data::mysql::connection {

class Pool : public virtual winter::templates::SinglePool<
		 winter::data::mysql::connection::Pool,
		 winter::data::mysql::connection::Connection,
		 winter::data::mysql::connection::Config> {
  friend class SinglePool<
      winter::data::mysql::connection::Pool,
      winter::data::mysql::connection::Connection,
      winter::data::mysql::connection::Config>;

 protected:
  explicit Pool(
      const winter::descriptor::PoolDescriptor& pool_descriptor,
      std::optional<winter::data::mysql::connection::Config> mysql_config);
  winter::data::mysql::connection::Connection* CreateConn() override;
  ~Pool() override = default;
};

}  // namespace winter::data::mysql::connection

#endif	// WINTERCPP_WINTER_DATA_SQL_MYSQL_IMPL_POOL_H
