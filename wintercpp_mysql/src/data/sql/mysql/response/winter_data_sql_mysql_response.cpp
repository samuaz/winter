#include <wintercpp/data/sql/mysql/response/winter_data_sql_mysql_response.h>

using namespace winter::data::sql_impl;
using namespace winter::data::sql_impl::mysql;

MysqlResponse
MysqlResponse::Error(const std::string &transactionId, StatementType type, const std::string &message) {
  return {transactionId, type, ResponseStatus::kError, message};
}

MysqlResponse
MysqlResponse::Success(const std::string &transactionId, StatementType type, const std::vector<MysqlResultRow> &result, int row_affected, const std::string &message) {
  return {transactionId, type, result, ResponseStatus::kSuccess, message, row_affected};
}

winter::data::sql_impl::mysql::Response::~Response() = default;
