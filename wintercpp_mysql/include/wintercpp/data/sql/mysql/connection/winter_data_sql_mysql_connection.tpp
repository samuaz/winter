/**
 * @author AZCONA VARGAS, SAMUEL EDUARDO -
 * samuel@theopencompany.tech/samuaz@gmail.com
 * @YEAR 2019
 */

#include <wintercpp/data/response/winter_data_response_status.h>
#include <wintercpp/data/sql/mysql/connection/winter_data_sql_mysql_connection.h>
#include <wintercpp/exception/generic/winter_internal_exception.h>
#include <wintercpp/exception/sql/winter_sql_exception.h>

#include <cstdint>
#include <optional>
#include <string>

using namespace winter;
using namespace winter::descriptor;
using namespace winter::exception;
using namespace winter::data::sql_impl::mysql;
using namespace winter::data::sql_impl::mysql::connection;

CONNECTION_TEMPLATES
TResponse
MYSQL_CONNECTION_INTERFACE::Execute(const PreparedStatement &query) noexcept(false) {
  std::scoped_lock<std::recursive_mutex> lock(MYSQL_CONNECTION_INTERFACE::conn_mtx());
  try {
    Reconnect();
    return CreateResponse(query, GeneratePrepareStatement(query));
  } catch (TSqlException &e) {
    // return MysqlResponse(query.id(), query.type(), ResponseStatus::ERROR, e.what());
    throw SqlException::Create(__FILE__, __FUNCTION__, __LINE__, ("query: " + query.statement_template() + " " + e.what()), e.getErrorCode());
  }
}

CONNECTION_TEMPLATES
void MYSQL_CONNECTION_INTERFACE::Reconnect() {
  std::scoped_lock<std::recursive_mutex> lock(MYSQL_CONNECTION_INTERFACE::conn_mtx());
  try {
    if (MYSQL_CONNECTION_INTERFACE::conn().isClosed()) {
      MYSQL_CONNECTION_INTERFACE::conn().reconnect();
    }
  } catch (TSqlException &e) {
    throw SqlException::Create(__FILE__, __FUNCTION__, __LINE__, (std::string("cant connect to database, ") + e.what()), e.getErrorCode());
  }
}

CONNECTION_TEMPLATES
TResponse
MYSQL_CONNECTION_INTERFACE::CreateResponse(const PreparedStatement &prepared_statement, const std::shared_ptr<TpreparedStatement> &prep_stmt) {
  if (prep_stmt != nullptr) {
    auto no_result_query = [&](int update_count) -> TResponse {
      if (update_count > 0) {
	return TResponse(prepared_statement.id(), prepared_statement.type(), {}, ResponseStatus::kSuccess, "SUCCESS", update_count);
      } else {
	return TResponse(prepared_statement.id(), prepared_statement.type(), {}, ResponseStatus::kSuccess, "SUCCESS, but No rows affected", update_count);
      }
    };

    auto result_query = [&](const std::shared_ptr<TResultSet> &result_set) -> TResponse {
      if (result_set != nullptr) {
	if (result_set->first()) {
	  std::vector<TResultRow> result_rows;
	  do {
	    result_rows.emplace_back(prepared_statement, result_set);
	  } while (result_set->next());
	  return MysqlResponse(prepared_statement.id(), prepared_statement.type(), result_rows, ResponseStatus::kSuccess, "SUCCESS", result_set->rowsCount());
	} else {
	  return TResponse(prepared_statement.id(), prepared_statement.type(), ResponseStatus::kError, "No elements on resultset ");
	}
      } else {
	return TResponse(prepared_statement.id(), prepared_statement.type(), ResponseStatus::kError, "::sql::ResultSet is null");
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
	return result_query(std::shared_ptr<TResultSet>(prep_stmt->executeQuery()));
      default: {
	bool is_result_query = prep_stmt->execute();
	if (is_result_query) {
	  return result_query(std::shared_ptr<TResultSet>(prep_stmt->getResultSet()));
	} else {
	  return no_result_query(prep_stmt->getUpdateCount());
	}
      }
    }
  }
  return TResponse(prepared_statement.id(), prepared_statement.type(), ResponseStatus::kError, "::sql::PreparedStatement is null");
}

CONNECTION_TEMPLATES
std::shared_ptr<TpreparedStatement>
MYSQL_CONNECTION_INTERFACE::GeneratePrepareStatement(
    const PreparedStatement &query) {
  std::scoped_lock<std::recursive_mutex> lock(MYSQL_CONNECTION_INTERFACE::conn_mtx());
  std::shared_ptr<TpreparedStatement> _prep_stmt(
      MYSQL_CONNECTION_INTERFACE::conn().prepareStatement(query.statement_template()));
  auto values = query.values();
  for (std::size_t i = 0; i != values.size(); ++i) {
    auto field = values[i].get();
    int position = i + 1;
    switch (field->type()) {
      case FieldType::kNull:
	_prep_stmt->setNull(position, 0);
	break;
      case FieldType::kBigInt:
	_prep_stmt->setBigInt(
	    position,
	    dynamic_cast<PreparedStatementField<std::string> *>(field)->value());
	break;
      case FieldType::kChar:
      case FieldType::kDate:
      case FieldType::kDateTime:
      case FieldType::KDecimal:
      case FieldType::kTimeStamp:
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
	    dynamic_cast<PreparedStatementField<int32_t> *>(field)->value());
	break;
      case FieldType::kUshort:
      case FieldType::kUchar:
      case FieldType::KUint:
	_prep_stmt->setUInt(
	    position,
	    dynamic_cast<PreparedStatementField<uint32_t> *>(field)->value());
	break;
      case FieldType::kBoolean:
	_prep_stmt->setBoolean(
	    position,
	    dynamic_cast<PreparedStatementField<bool> *>(field)->value());
	break;
      case FieldType::kFloat:
      case FieldType::kDouble:
	_prep_stmt->setDouble(
	    position,
	    dynamic_cast<PreparedStatementField<double> *>(field)->value());
	break;
      case FieldType::kLong:
	_prep_stmt->setInt64(
	    position,
	    dynamic_cast<PreparedStatementField<int64_t> *>(field)->value());
	break;
      case FieldType::kUlong:
	_prep_stmt->setUInt64(
	    position,
	    dynamic_cast<PreparedStatementField<uint64_t> *>(field)->value());
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

/* ::sql::transaction_isolation
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
} */

/*CONNECTION_TEMPLATES
TIsolationType
MYSQL_CONNECTION_INTERFACE::IsolationLevel(
    const TransactionIsolationType &isolation) {
  switch (isolation) {
    case TransactionIsolationType::DEFAULT:
      return ::sql::TRANSACTION_REPEATABLE_READ;
    case TransactionIsolationType::REPEATABLE_READ:
      return ::sql::TRANSACTION_REPEATABLE_READ;
    case TransactionIsolationType::READ_COMMITTED:
      return ::sql::TRANSACTION_READ_COMMITTED;
    case TransactionIsolationType::READ_UNCOMMITTED:
      return ::sql::TRANSACTION_READ_UNCOMMITTED;
    case TransactionIsolationType::SERIALIZABLE:
      return ::sql::TRANSACTION_SERIALIZABLE;
    default:
      return ::sql::TRANSACTION_REPEATABLE_READ;
  }
  /// return static_cast< ::sql::enum_transaction_isolation>(isolation);
}*/

CONNECTION_TEMPLATES
void MYSQL_CONNECTION_INTERFACE::PrepareTransaction(const TransactionIsolationType &isolation) {
  std::scoped_lock<std::recursive_mutex> lock(MYSQL_CONNECTION_INTERFACE::conn_mtx());
  MYSQL_CONNECTION_INTERFACE::conn().setAutoCommit(false);
  MYSQL_CONNECTION_INTERFACE::conn().setTransactionIsolation(IsolationLevel(isolation));
  MYSQL_CONNECTION_INTERFACE::conn().createStatement()->execute("START TRANSACTION");
}

CONNECTION_TEMPLATES
void MYSQL_CONNECTION_INTERFACE::Commit() const {
  MYSQL_CONNECTION_INTERFACE::conn().commit();
}

CONNECTION_TEMPLATES
void MYSQL_CONNECTION_INTERFACE::Rollback() const {
  MYSQL_CONNECTION_INTERFACE::conn().rollback();
}

CONNECTION_TEMPLATES
MYSQL_CONNECTION_INTERFACE *
MYSQL_CONNECTION_INTERFACE::Create(const TConfig &mysql_config) {
/*  ::sql::ConnectOptionsMap connectionProperties;

  try {
#if WITH_MYSQL
    connectionProperties["hostName"] = mysql_config.host();
    connectionProperties["userName"] = mysql_config.user_name();
    connectionProperties["password"] = mysql_config.password();
    connectionProperties["schema"] = mysql_config.schema();
    connectionProperties["port"] = mysql_config.port();
    connectionProperties["OPT_RECONNECT"] = mysql_config.is_opt_reconnect();
    connectionProperties["OPT_CONNECT_TIMEOUT"] = mysql_config.opt_connect_timeout();
    auto otherProps = mysql_config.properties();
    connectionProperties.insert(otherProps.begin(), otherProps.end());
    return new Connection(mysql_config.driver().connect(connectionProperties));
#elif WITH_MARIADB
    connectionProperties["hostName"] = mysql_config.host();
    connectionProperties["user"] = mysql_config.user_name();
    connectionProperties["password"] = mysql_config.password();
    connectionProperties["schema"] = mysql_config.schema();
    connectionProperties["port"] = std::to_string(mysql_config.port());
    connectionProperties["OPT_RECONNECT"] = std::to_string(mysql_config.is_opt_reconnect());
    connectionProperties["OPT_CONNECT_TIMEOUT"] = std::to_string(mysql_config.opt_connect_timeout());

    std::string url = mysql_config.host() + ":" + std::to_string(mysql_config.port()) + "/" + mysql_config.schema();

    return new Connection(mysql_config.driver().connect("jdbc:mariadb://" + url, connectionProperties));
#else
    static_assert(false, "MYSQL CONNECTOR NOT DEFINED");
#endif
  } catch (std::runtime_error &ex) {
    throw WinterInternalException::Create(__FILE__, __FUNCTION__, __LINE__, ex.what());
  }
  */
  throw WinterInternalException::Create(__FILE__, __FUNCTION__, __LINE__);
}
