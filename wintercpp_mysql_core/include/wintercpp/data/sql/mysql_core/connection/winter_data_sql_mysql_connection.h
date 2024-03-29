/**
 * @author AZCONA VARGAS, SAMUEL EDUARDO -
 * samuel@theopencompany.tech/samuaz@gmail.com
 * @YEAR 2019
 */

#ifndef WINTER_DATA_SQL_MYSQL_CONNECTION
#define WINTER_DATA_SQL_MYSQL_CONNECTION

#include <wintercpp/data/response/winter_data_response.h>
#include <wintercpp/data/response/winter_data_response_status.h>
#include <wintercpp/data/sql/connection/winter_data_sql_connection.h>
#include <wintercpp/data/sql/mysql_core/connection/winter_data_sql_mysql_connection_config.h>
#include <wintercpp/data/sql/mysql_core/connection/winter_data_sql_mysql_result_row.h>
#include <wintercpp/data/sql/preparedstatement/winter_data_sql_prepared_statement_field.h>
#include <wintercpp/exception/database/winter_database_exception.h>

namespace winter::data::sql_impl::mysql::connection {

#define CONNECTION_TEMPLATES              \
    template<typename TDriver,            \
             typename TConfig,            \
             typename TIsolationType,     \
             typename TSqlConnection,     \
             typename TResponse,          \
             typename TpreparedStatement, \
             typename TResultSet,         \
             typename TResultRow,         \
             typename TSqlException>
#define MYSQL_CONNECTION_INTERFACE                                            \
    winter::data::sql_impl::mysql::connection::Connection<TDriver,            \
                                                          TConfig,            \
                                                          TIsolationType,     \
                                                          TSqlConnection,     \
                                                          TResponse,          \
                                                          TpreparedStatement, \
                                                          TResultSet,         \
                                                          TResultRow,         \
                                                          TSqlException>

    CONNECTION_TEMPLATES
    class Connection : public virtual SQLConnection<TSqlConnection, TResponse> {
       public:
        using SQLConnection<TSqlConnection, TResponse>::SQLConnection;

        TResponse Execute(const PreparedStatement &query) noexcept(
            false) override;

        void PrepareTransaction(
            const TransactionIsolationType &isolation) override;

        void Commit() const override;

        void Rollback() const override;

        std::shared_ptr<TpreparedStatement> GeneratePrepareStatement(
            const PreparedStatement &query);

        virtual ~Connection() = default;

       protected:
        void Reconnect();

       private:
        virtual TIsolationType IsolationLevel(
            const TransactionIsolationType &isolation)
            = 0;

        TResponse CreateResponse(
            const PreparedStatement                   &prepared_statement,
            const std::shared_ptr<TpreparedStatement> &prep_stmt);

        TResponse ResultQuery(
            const PreparedStatement           &prepared_statement,
            const std::shared_ptr<TResultSet> &result_set) const;

        TResponse NoResultQuery(const PreparedStatement &prepared_statement,
                                int                      update_count) const;
    };

}  // namespace winter::data::sql_impl::mysql::connection

// typedef winter::data::sql_impl::mysql::connection::Connection
// MysqlConnection;
#include "winter_data_sql_mysql_connection.tpp"
#endif /* WINTER_DATA_SQL_MYSQL_CONNECTION */
