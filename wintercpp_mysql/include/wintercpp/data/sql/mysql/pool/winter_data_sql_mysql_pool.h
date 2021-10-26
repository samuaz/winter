#include <memory>

//
// Created by AZCONA VARGAS, SAMUEL EDUARDO [AG-Contractor/5000] on 2019-11-21.
//

#ifndef WINTER_DATA_SQL_MYSQL_POOL
#define WINTER_DATA_SQL_MYSQL_POOL

#include <wintercpp/data/sql/mysql/connection/winter_data_sql_mysql_connection.h>
#include <wintercpp/template/winter_connection_pool_singleton_template.h>
#include <wintercpp/template/winter_connection_pool_template.h>

#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

namespace winter::data::sql::mysql::connection {

using namespace winter::templates;

class Pool final : public virtual SinglePool<
		       Pool,
		       winter::data::sql::mysql::connection::Connection,
		       Config> {
  friend class SinglePool<
      Pool,
      winter::data::sql::mysql::connection::Connection,
      Config>;

 private:
  explicit Pool(
      winter::descriptor::PoolDescriptor pool_descriptor,
      std::optional<Config> mysql_config);
  winter::data::sql::mysql::connection::Connection *CreateConn() override;
  ~Pool() override = default;
};

}  // namespace winter::data::sql::mysql::connection

typedef winter::data::sql::mysql::connection::Pool MysqlPool;

#endif /* WINTER_DATA_SQL_MYSQL_POOL */
