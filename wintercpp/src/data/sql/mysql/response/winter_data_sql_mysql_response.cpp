#include <wintercpp/data/sql/mysql/response/winter_data_sql_mysql_response.h>

using namespace winter::data::sql;
using namespace winter::data::sql::mysql;

MysqlResponse::Response() = default;

MysqlResponse::Response(
    std::string transactionId,
    StatementType type,
    winter::data::ResponseStatus status,
    std::string message) : winter::data::sql::
			       Response<MysqlResponse, MysqlResultRow>(
				   transactionId,
				   type,
				   status,
				   std::move(message)) {}

MysqlResponse::Response(StatementType type) : winter::data::sql::
						  Response<MysqlResponse, MysqlResultRow>(type) {}

MysqlResponse
MysqlResponse::Error(const std::string &transactionId, StatementType type, const std::string &message) {
  return {transactionId, type, ResponseStatus::kError, message};
}

MysqlResponse::Response(
    std::string transaction_id,
    StatementType type,
    std::vector<MysqlResultRow> result,
    winter::data::ResponseStatus status,
    std::string message,
    int row_affected) : winter::data::sql::
			    Response<MysqlResponse, MysqlResultRow>(
				transaction_id,
				type,
				result,
				status,
				message,
				row_affected) {}

winter::data::sql::mysql::Response::~Response() = default;
