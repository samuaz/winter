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

namespace winter::data::sql_impl::mysql {

template <typename TResultRow>
class Response : public winter::data::sql_impl::Response<winter::data::sql_impl::mysql::Response<TResultRow>, TResultRow> {
 public:
  Response(
      std::string transaction_id,
      StatementType type,
      winter::data::ResponseStatus status,
      std::string message) :
      winter::data::sql_impl::Response<winter::data::sql_impl::mysql::Response<TResultRow>, TResultRow>(transaction_id, type, status, message) {}

  Response(
      std::string transaction_id,
      StatementType type,
      std::vector<TResultRow> result,
      winter::data::ResponseStatus status,
      std::string message,
      int row_affected) :
      winter::data::sql_impl::Response<winter::data::sql_impl::mysql::Response<TResultRow>, TResultRow>(transaction_id, type, result, status, message, row_affected) {}

  static winter::data::sql_impl::mysql::Response<TResultRow> Error(const std::string &transactionId, StatementType type, const std::string &message);

  static winter::data::sql_impl::mysql::Response<TResultRow> Success(const std::string &transactionId, StatementType type, const std::vector<TResultRow> &result, int row_affected, const std::string &message = "Success");

  ~Response();
};

// typedef winter::data::sql_impl::mysql::Response MysqlResponse;

}  // namespace winter::data::sql_impl::mysql
#include "winter_data_sql_mysql_response.tpp"

#endif /* WINTER_DATA_SQL_MYSQL_RESPONSE */
