/**
 * @author AZCONA VARGAS, SAMUEL EDUARDO -
 * samuel@theopencompany.tech/samuaz@gmail.com
 * @YEAR 2019
 */

#ifndef WINTER_DATA_SQL_MYSQL_CONNECTION
#define WINTER_DATA_SQL_MYSQL_CONNECTION

#include <jdbc/cppconn/connection.h>
#include <mysql/jdbc.h>
#include <wintercpp/data/response/winter_data_response.h>
#include <wintercpp/data/sql/connection/winter_data_sql_connection.h>
#include <wintercpp/data/sql/mysql/connection/winter_data_sql_mysql_connection_config.h>
#include <wintercpp/data/sql/mysql/connection/winter_data_sql_mysql_result_row.h>
#include <wintercpp/data/sql/mysql/response/winter_data_sql_mysql_response.h>
#include <wintercpp/data/sql/preparedstatement/winter_data_sql_prepared_statement_field.h>
#include <wintercpp/exception/database/winter_database_exception.h>

#include "wintercpp/data/response/winter_data_response_status.h"

namespace winter::data::sql::mysql::connection {

class Connection final : public virtual SQLConnection<Connection, ::sql::Connection, MysqlResponse> {
 public:

  using SQLConnection<Connection, ::sql::Connection, MysqlResponse>::SQLConnection;

  static winter::data::sql::mysql::connection::Connection *Create(const winter::data::sql::mysql::connection::Config &mysql_config);

  MysqlResponse Execute(const PreparedStatement &query) noexcept(false) override;

  void PrepareTransaction(const TransactionIsolationType &isolation) override;

  void Commit() const override;

  void Rollback() const override;

  std::shared_ptr< ::sql::PreparedStatement> GeneratePrepareStatement(
      const PreparedStatement &query);

  virtual ~Connection() = default;

 protected:
  void Reconnect();

 private:
  ::sql::transaction_isolation IsolationLevel(
      const TransactionIsolationType &isolation);

  MysqlResponse CreateResponse(const PreparedStatement &prepared_statement, const std::shared_ptr< ::sql::PreparedStatement> &prep_stmt);
};

}  // namespace winter::data::sql::mysql::connection

typedef winter::data::sql::mysql::connection::Connection MysqlConnection;

#endif /* WINTER_DATA_SQL_MYSQL_CONNECTION */
