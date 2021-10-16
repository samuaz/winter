#ifndef WINTER_DATA_SQL_MYSQL_RESPONSE
#define WINTER_DATA_SQL_MYSQL_RESPONSE

//#include <mysql/jdbc.h>
#include <wintercpp/data/response/winter_data_response_status.h>
#include <wintercpp/data/response/winter_data_result_response_collection.h>
#include <wintercpp/data/sql/column/winter_data_sql_column.h>
#include <wintercpp/data/sql/mysql/connection/winter_data_sql_mysql_result_row.h>
#include <wintercpp/data/sql/response/winter_data_sql_response.h>

#include <string>
#include <utility>

namespace winter::data::sql::mysql {

class Response final : public virtual winter::data::sql::
			   Response<winter::data::sql::mysql::Response, MysqlResultRow> {
 public:
  Response(
      std::string transaction_id,
      StatementType type,
      winter::data::ResponseStatus status,
      std::string message) :
      winter::data::sql::Response<winter::data::sql::mysql::Response, MysqlResultRow>(transaction_id, type, status, message) {}

  Response(
      std::string transaction_id,
      StatementType type,
      std::vector<MysqlResultRow> result,
      winter::data::ResponseStatus status,
      std::string message,
      int row_affected) :
      winter::data::sql::Response<winter::data::sql::mysql::Response, MysqlResultRow>(transaction_id, type, result, status, message, row_affected) {}

  static Response Error(const std::string &transactionId, StatementType type, const std::string &message);

  static Response Success(const std::string &transactionId, StatementType type, const std::vector<MysqlResultRow> &result, int row_affected, const std::string &message = "Success");

  ~Response();
};

typedef winter::data::sql::mysql::Response MysqlResponse;

}  // namespace winter::data::sql::mysql

#endif /* WINTER_DATA_SQL_MYSQL_RESPONSE */
