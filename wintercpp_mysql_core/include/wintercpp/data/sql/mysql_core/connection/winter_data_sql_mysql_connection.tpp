/**
 * @author AZCONA VARGAS, SAMUEL EDUARDO -
 * samuel@theopencompany.tech/samuaz@gmail.com
 * @YEAR 2019
 */

#include <wintercpp/data/response/winter_data_response_status.h>
#include <wintercpp/data/sql/mysql_core/connection/winter_data_sql_mysql_connection.h>
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
TResponse MYSQL_CONNECTION_INTERFACE::Execute(
    const PreparedStatement& query) noexcept(false) {
    std::scoped_lock<std::recursive_mutex> lock(
        MYSQL_CONNECTION_INTERFACE::conn_mtx());
    try {
        Reconnect();
        return CreateResponse(query, GeneratePrepareStatement(query));
    } catch (TSqlException& e) {
        // return MysqlResponse(query.id(), query.type(), ResponseStatus::ERROR,
        // e.what());
        throw SqlException::Create(
            __FILE__,
            __FUNCTION__,
            __LINE__,
            ("query: " + query.statement_template() + " " + e.what()),
            e.getErrorCode());
    }
}

CONNECTION_TEMPLATES
void MYSQL_CONNECTION_INTERFACE::Reconnect() {
    std::scoped_lock<std::recursive_mutex> lock(
        MYSQL_CONNECTION_INTERFACE::conn_mtx());
    try {
        if (MYSQL_CONNECTION_INTERFACE::conn().isClosed()) {
            MYSQL_CONNECTION_INTERFACE::conn().reconnect();
        }
    } catch (TSqlException& e) {
        throw SqlException::Create(
            __FILE__,
            __FUNCTION__,
            __LINE__,
            (std::string("cant connect to database, ") + e.what()),
            e.getErrorCode());
    }
}

CONNECTION_TEMPLATES
TResponse MYSQL_CONNECTION_INTERFACE::CreateResponse(
    const PreparedStatement&                   prepared_statement,
    const std::shared_ptr<TpreparedStatement>& prep_stmt) {
    if (prep_stmt != nullptr) {
        switch (prepared_statement.type()) {
            case StatementType::kInsert:
            case StatementType::kUpdate:
            case StatementType::kDelete:
            case StatementType::kCreate:
            case StatementType::kDrop:
            case StatementType::kTruncate:
                return NoResultQuery(prepared_statement,
                                     prep_stmt->executeUpdate());
            case StatementType::kSelect:
                return ResultQuery(
                    prepared_statement,
                    std::shared_ptr<TResultSet>(prep_stmt->executeQuery()));
            default: {
                bool is_result_query = prep_stmt->execute();
                if (is_result_query) {
                    return ResultQuery(
                        prepared_statement,
                        std::shared_ptr<TResultSet>(prep_stmt->getResultSet()));
                } else {
                    return NoResultQuery(prepared_statement,
                                         prep_stmt->getUpdateCount());
                }
            }
        }
    }
    return TResponse(prepared_statement.id(),
                     prepared_statement.type(),
                     ResponseStatus::kError,
                     "::sql::PreparedStatement is null");
}

CONNECTION_TEMPLATES
TResponse MYSQL_CONNECTION_INTERFACE::ResultQuery(
    const PreparedStatement&           prepared_statement,
    const std::shared_ptr<TResultSet>& result_set) const {
    if (result_set != nullptr) {
        if (result_set->rowsCount() > 0) {
            std::vector<TResultRow> result_rows;
            while (result_set->next()) {
                result_rows.emplace_back(prepared_statement, result_set);
            };
            return TResponse(prepared_statement.id(),
                             prepared_statement.type(),
                             result_rows,
                             ResponseStatus::kSuccess,
                             "SUCCESS",
                             result_set->rowsCount());
        } else {
            return TResponse(prepared_statement.id(),
                             prepared_statement.type(),
                             ResponseStatus::kError,
                             "No elements on resultset ");
        }
    } else {
        return TResponse(prepared_statement.id(),
                         prepared_statement.type(),
                         ResponseStatus::kError,
                         "::sql::ResultSet is null");
    }
}

CONNECTION_TEMPLATES
TResponse MYSQL_CONNECTION_INTERFACE::NoResultQuery(
    const PreparedStatement& prepared_statement, int update_count) const {
    if (update_count > 0) {
        return TResponse(prepared_statement.id(),
                         prepared_statement.type(),
                         {},
                         ResponseStatus::kSuccess,
                         "SUCCESS",
                         update_count);
    } else {
        return TResponse(prepared_statement.id(),
                         prepared_statement.type(),
                         {},
                         ResponseStatus::kSuccess,
                         "SUCCESS, but No rows affected",
                         update_count);
    }
}

CONNECTION_TEMPLATES
std::shared_ptr<TpreparedStatement>
MYSQL_CONNECTION_INTERFACE::GeneratePrepareStatement(
    const PreparedStatement& query) {
    // create a lock for the current connection
    std::scoped_lock<std::recursive_mutex> lock(
        MYSQL_CONNECTION_INTERFACE::conn_mtx());

    // create a prepared statement from the query template
    std::shared_ptr<TpreparedStatement> _prep_stmt(
        MYSQL_CONNECTION_INTERFACE::conn().prepareStatement(
            query.statement_template()));

    // get the values for the given ? parameter
    auto values = query.values();

    // inside the foreach we set each value with his specific order as it was
    // declared on the query creation
    for (std::size_t i = 0; i != values.size(); ++i) {
        auto field = values[i].get();
        int  position = i + 1;
        switch (field->type()) {
            case FieldType::kNull: _prep_stmt->setNull(position, 0); break;
            case FieldType::kBigInt:
                _prep_stmt->setBigInt(
                    position,
                    dynamic_cast<PreparedStatementField<std::string>*>(field)
                        ->value());
                break;
            case FieldType::kChar:
            case FieldType::kDate:
            case FieldType::kDateTime:
            case FieldType::KDecimal:
            case FieldType::kTimeStamp:
            case FieldType::kString:
                _prep_stmt->setString(
                    position,
                    dynamic_cast<PreparedStatementField<std::string>*>(field)
                        ->value());
                break;
            case FieldType::kEnum:
            case FieldType::KShort:
            case FieldType::kSchar:
            case FieldType::kInt:
                _prep_stmt->setInt(
                    position,
                    dynamic_cast<PreparedStatementField<int32_t>*>(field)
                        ->value());
                break;
            case FieldType::kUshort:
            case FieldType::kUchar:
            case FieldType::KUint:
                _prep_stmt->setUInt(
                    position,
                    dynamic_cast<PreparedStatementField<uint32_t>*>(field)
                        ->value());
                break;
            case FieldType::kBoolean:
                _prep_stmt->setBoolean(
                    position,
                    dynamic_cast<PreparedStatementField<bool>*>(field)
                        ->value());
                break;
            case FieldType::kFloat:
            case FieldType::kDouble:
                _prep_stmt->setDouble(
                    position,
                    dynamic_cast<PreparedStatementField<double>*>(field)
                        ->value());
                break;
            case FieldType::kLong:
                _prep_stmt->setInt64(
                    position,
                    dynamic_cast<PreparedStatementField<int64_t>*>(field)
                        ->value());
                break;
            case FieldType::kUlong:
                _prep_stmt->setUInt64(
                    position,
                    dynamic_cast<PreparedStatementField<uint64_t>*>(field)
                        ->value());
                break;
            case FieldType::kBlob:
                _prep_stmt->setBlob(
                    position,
                    dynamic_cast<PreparedStatementField<std::istream*>*>(field)
                        ->value());
                break;
        }
    }
    return _prep_stmt;
}

CONNECTION_TEMPLATES
void MYSQL_CONNECTION_INTERFACE::PrepareTransaction(
    const TransactionIsolationType& isolation) {
    std::scoped_lock<std::recursive_mutex> lock(
        MYSQL_CONNECTION_INTERFACE::conn_mtx());
    MYSQL_CONNECTION_INTERFACE::conn().setAutoCommit(false);
    MYSQL_CONNECTION_INTERFACE::conn().setTransactionIsolation(
        IsolationLevel(isolation));
    MYSQL_CONNECTION_INTERFACE::conn().createStatement()->execute(
        "START TRANSACTION");
}

CONNECTION_TEMPLATES
void MYSQL_CONNECTION_INTERFACE::Commit() const {
    MYSQL_CONNECTION_INTERFACE::conn().commit();
}

CONNECTION_TEMPLATES
void MYSQL_CONNECTION_INTERFACE::Rollback() const {
    MYSQL_CONNECTION_INTERFACE::conn().rollback();
}
