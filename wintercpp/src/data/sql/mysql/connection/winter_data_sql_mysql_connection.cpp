/**
 * @author AZCONA VARGAS, SAMUEL EDUARDO -
 * samuel@theopencompany.tech/samuaz@gmail.com
 * @YEAR 2019
 */

#include <mysql/jdbc.h>
#include <wintercpp/data/response/winter_data_response_status.h>
#include <wintercpp/data/sql/exception/winter_sql_exception.h>
#include <wintercpp/data/sql/mysql/connection/winter_data_sql_mysql_connection.h>

#include <optional>
#include <string>

#include "jdbc/cppconn/sqlstring.h"

using namespace winter;
using namespace winter::descriptor;
using namespace winter::data::sql::exception;
using namespace winter::data::sql::mysql;
using namespace winter::data::sql::mysql::connection;

Connection::Connection(::sql::Connection *conn) : SQLConnection<Connection, ::sql::Connection, MysqlResponse>(conn){};

MysqlResponse
Connection::Execute(const PreparedStatement &query) noexcept(false) {
  std::scoped_lock<std::recursive_mutex> lock(conn_mtx_);
  try {
    Reconnect();
    return CreateResponse(query, GeneratePrepareStatement(query));
  } catch (::sql::SQLException &e) {
    //return MysqlResponse(query.id(), query.type(), ResponseStatus::ERROR, e.what());
    throw SqlException::Create(__FILE__, __FUNCTION__, __LINE__, ("query: " + query.statement_template() + " " + e.what()), e.getErrorCode());
  }
}

void Connection::Reconnect() {
  std::scoped_lock<std::recursive_mutex> lock(conn_mtx_);
  try {
    if (conn_) {
      if (conn_->isClosed()) {
	conn_->reconnect();
      }
    } else {
      throw SqlException::Create(__FILE__, __FUNCTION__, __LINE__, "cant connect to database, conn_ is null");
    }
  } catch (::sql::SQLException &e) {
    throw SqlException::Create(__FILE__, __FUNCTION__, __LINE__, (std::string("cant connect to database, ") + e.what()), e.getErrorCode());
  }
}

MysqlResponse
Connection::CreateResponse(const PreparedStatement &prepared_statement, const std::shared_ptr< ::sql::PreparedStatement> &prep_stmt) {

  if (prep_stmt != nullptr) {
    auto no_result_query = [&](int update_count) -> MysqlResponse {
      if (update_count > 0) {
	return MysqlResponse(prepared_statement.id(), prepared_statement.type(), {}, ResponseStatus::kSuccess, "SUCCESS", update_count);
      } else {
	return MysqlResponse(prepared_statement.id(), prepared_statement.type(), {}, ResponseStatus::kSuccess, "SUCCESS, but No rows affected", update_count);
      }
    };

    auto result_query = [&](const std::shared_ptr< ::sql::ResultSet> &result_set) -> MysqlResponse {
      if (result_set != nullptr) {
	if (result_set->first()) {
	  std::vector<MysqlResultRow> result_rows;
	  do {
	    result_rows.emplace_back(prepared_statement, result_set);
	  } while (result_set->next());
	  return MysqlResponse(prepared_statement.id(), prepared_statement.type(), result_rows, ResponseStatus::kSuccess, "SUCCESS", result_set->rowsCount());
	} else {
	  return MysqlResponse(prepared_statement.id(), prepared_statement.type(), ResponseStatus::kError, "No elements on resultset ");
	}
      } else {
	return MysqlResponse(prepared_statement.id(), prepared_statement.type(), ResponseStatus::kError, "::sql::ResultSet is null");
      }
    };

    switch (prepared_statement.type()) {
      case StatementType::kInsert:
      case StatementType::kUpdate:
      case StatementType::kDelete:
      case StatementType::kCreate:
      case StatementType::kDrop:
      case StatementType::kTruncate:
	return no_result_query(prep_stmt->executeUpdate());
      case StatementType::kSelect:
	return result_query(std::shared_ptr< ::sql::ResultSet>(prep_stmt->executeQuery()));
      default: {
	bool is_result_query = prep_stmt->execute();
	if (is_result_query) {
	  return result_query(std::shared_ptr< ::sql::ResultSet>(prep_stmt->getResultSet()));
	} else {
	  return no_result_query(prep_stmt->getUpdateCount());
	}
      }
    }
  }
  return MysqlResponse(prepared_statement.id(), prepared_statement.type(), ResponseStatus::kError, "::sql::PreparedStatement is null");
}

std::shared_ptr< ::sql::PreparedStatement>
Connection::GeneratePrepareStatement(
    const PreparedStatement &query) {
  std::scoped_lock<std::recursive_mutex> lock(conn_mtx_);
  std::shared_ptr< ::sql::PreparedStatement> _prep_stmt(
      conn_->prepareStatement(::sql::SQLString(query.statement_template())));
  auto values = query.values();
  for (std::size_t i = 0; i != values.size(); ++i) {
    auto field = values[i].get();
    std::size_t position = i + 1;
    switch (field->type()) {
      case FieldType::kNull:
	_prep_stmt->setNull(position, 0);
	break;
      case FieldType::kChar:
      case FieldType::kDate:
      case FieldType::kDateTime:
      case FieldType::kBigInt:
      case FieldType::kString:
	_prep_stmt->setString(
	    position,
	    dynamic_cast<PreparedStatementField<std::string> *>(field)->value());
	break;
      case FieldType::kEnum:
      case FieldType::KShort:
      case FieldType::kSchar:
      case FieldType::kInt:
	_prep_stmt->setInt(
	    position,
	    dynamic_cast<PreparedStatementField<int> *>(field)->value());
	break;
      case FieldType::kUshort:
      case FieldType::kUchar:
      case FieldType::KUint:
	_prep_stmt->setUInt(
	    position,
	    dynamic_cast<PreparedStatementField<unsigned int> *>(field)->value());
	break;
      case FieldType::kBoolean:
	_prep_stmt->setBoolean(
	    position,
	    dynamic_cast<PreparedStatementField<bool> *>(field)->value());
	break;
      case FieldType::kDouble:
	_prep_stmt->setDouble(
	    position,
	    dynamic_cast<PreparedStatementField<double> *>(field)->value());
	break;
      case FieldType::kFloat:
	_prep_stmt->setDouble(
	    position,
	    dynamic_cast<PreparedStatementField<double> *>(field)->value());
	break;
      case FieldType::kLong:
	_prep_stmt->setInt64(
	    position,
	    dynamic_cast<PreparedStatementField<long> *>(field)->value());
	break;
      case FieldType::kUlong:
	_prep_stmt->setUInt64(
	    position,
	    dynamic_cast<PreparedStatementField<unsigned long> *>(field)->value());
	break;
      case FieldType::kBlob:
	_prep_stmt->setBlob(
	    position,
	    dynamic_cast<PreparedStatementField<std::istream *> *>(field)->value());
	break;
    }
  }
  return _prep_stmt;
}

::sql::transaction_isolation
Connection::IsolationLevel(
    const TransactionIsolationType &isolation) {
  switch (isolation) {
    case TransactionIsolationType::DEFAULT:
      return ::sql::enum_transaction_isolation::TRANSACTION_REPEATABLE_READ;
    case TransactionIsolationType::REPEATABLE_READ:
      return ::sql::enum_transaction_isolation::TRANSACTION_REPEATABLE_READ;
    case TransactionIsolationType::READ_COMMITTED:
      return ::sql::enum_transaction_isolation::TRANSACTION_READ_COMMITTED;
    case TransactionIsolationType::READ_UNCOMMITTED:
      return ::sql::enum_transaction_isolation::TRANSACTION_READ_UNCOMMITTED;
    case TransactionIsolationType::SERIALIZABLE:
      return ::sql::enum_transaction_isolation::TRANSACTION_SERIALIZABLE;
  }
  return static_cast< ::sql::enum_transaction_isolation>(isolation);
}

void Connection::PrepareTransaction(const TransactionIsolationType &isolation) {
  std::scoped_lock<std::recursive_mutex> lock(conn_mtx_);
  conn_->setAutoCommit(false);
  conn_->setTransactionIsolation(IsolationLevel(isolation));
  conn_->createStatement()->execute("START TRANSACTION");
}

void Connection::Commit() const {
  conn_->commit();
}

void Connection::Rollback() const {
  conn_->rollback();
}

winter::data::sql::mysql::connection::Connection *
Connection::Create(const Config &mysql_config) {
  try {
    ::sql::ConnectOptionsMap connectionProperties;
    connectionProperties["hostName"] = mysql_config.host();
    connectionProperties["userName"] = mysql_config.user_name();
    connectionProperties["password"] = mysql_config.password();
    connectionProperties["schema"] = mysql_config.schema();
    connectionProperties["port"] = mysql_config.port();
    connectionProperties["OPT_RECONNECT"] = mysql_config.is_opt_reconnect();
    connectionProperties["OPT_CONNECT_TIMEOUT"] = mysql_config.opt_connect_timeout();
    return new Connection(mysql_config.driver().connect(connectionProperties));
  } catch (std::runtime_error &ex) {
    throw WinterException(ex.what());
  }
}
