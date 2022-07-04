//
// Created by Samuel Azcona on 15/03/2020.
//

#ifndef WINTER_DATA_SQL_TRANSACTION
#define WINTER_DATA_SQL_TRANSACTION

#include <wintercpp/data/sql/connection/winter_data_sql_connection.h>
#include <wintercpp/data/sql/preparedstatement/winter_data_sql_prepared_statement.h>
#include <wintercpp/data/sql/statement/winter_data_sql_statement.h>

#include <deque>
#include <iostream>
#include <map>

#include "wintercpp/data/response/winter_data_response_status.h"

namespace winter::data::sql_impl {

    /**
     * Abstract interface of SQL Transaction
     *
     */
    class ITransaction {
       public:
        virtual void                     Rollback() const = 0;
        virtual void                     Commit() const = 0;
        virtual TransactionIsolationType isolation() const = 0;
        virtual bool                     ignore_error() const = 0;
    };

    template<typename TTransactionImpl,
             typename TSQLConnection,
             typename TResponse>
    class Transaction : public virtual ITransaction {
       public:
        /**
         * @brief
         * @param connection SQL connection type implementation, example:
         * MysqlConnection, MariaDBConnection, PostgreSQLConnection
         * @param isolation_type The level of the SQL isolation level, if not
         * passet the default isolation is TransactionIsolationType::DEFAULT,
         * then will use the sql engine default
         * @param partial_commit Default FALSE, when true will commit even if
         * one of the operations of the transaction fails, @warning this will
         * break the atomicity
         * @return
         */
        explicit Transaction(std::shared_ptr<TSQLConnection> connection,
                             TransactionIsolationType        isolation_type = TransactionIsolationType::DEFAULT,
                             bool                            partial_commit = false);

        /**
         * Execute the SQL statements lamda function, this lamda need to receive
         * the transaction implementation as parameter and return T, in most
         * cases T is represented by winter::data::response in this funcion this
         * transaction instances is delagated to the lambda function that then
         * is the owner to execute the transaction
         *
         * @brief receive a lambda That Returns T and receive Transaction
         * implementation as parameter, this is useful for example to receive
         * and sql statement as a lambda
         * @param std::function<T(TTransactionImpl &)>
         * @return T
         */
        template<typename T>
        T Execute(const std::function<T(TTransactionImpl &)> &statements);

        /**
         * Execute the SQL the prepared statement from
         * IStatement.prepared_statement() inside this transaction scope,
         * delegating to the Exceute(const PreparedStatement
         * &prepared_statement) method
         *
         * @see TResponse Execute(const PreparedStatement &prepared_statement);
         * @brief receive a lambda That Returns T and receive Transaction
         * implementation as parameter, this is useful for example to receive
         * and sql statement as a lambda
         * @param IStatement interface implementation
         * @return TResponse
         */
        TResponse Execute(IStatement &statement);

        /**
         * Execute the SQL the prepared statement from
         * IStatement.prepared_statement() inside this transaction scope
         *
         * @brief receive a lambda That Returns T and receive Transaction
         * implementation as parameter, this is useful for example to receive
         * and sql statement as a lambda
         * @param IStatement interface implementation
         * @return TResponse
         */
        TResponse Execute(const PreparedStatement &prepared_statement);

        /*   template <typename T>
        T operator()(const std::function<T(TTransactionImpl &)> &statements);

        TResponse operator()(const PreparedStatement &prepared_statement);

        TResponse operator()(IStatement &statement); */

        /**
         * @brief returns the current isolation level of given transaction
         * @return TransactionIsolationType
         */
        TransactionIsolationType isolation() const override;

        /**
         * @brief return if transaction is configured to do partials commit,
         * this means force commit the valid operations Although others have
         * failed
         * @warning be careful if this is true will break the transaction
         * atomicity
         * @return bool
         */
        bool ignore_error() const override;

        /**
         * @brief Manually Commit the transaction
         * @return (void)
         */
        void Commit() const override;

        /**
         * @brief Manually Rollback the transaction
         * @return (void)
         */
        void Rollback() const override;

        /**
         * @brief returns the status of the transaction SUCCESS OR ERROR, if one
         * of the operations failed, status is set to ERROR, only if all
         * operations are successful status set to success
         * @return winter::data::ResponseStatus
         */
        winter::data::ResponseStatus status() const;

        ~Transaction();

       private:
        std::shared_ptr<TSQLConnection> connection_;
        TransactionIsolationType        isolation_type_;
        bool                            partial_commit_;
        std::map<std::string, bool>     operations_status_;
        TTransactionImpl               &This();

        void status(const ResponseStatus &status);
    };

}  // namespace winter::data::sql_impl

#include "winter_data_sql_transaction.tpp"

#endif /* WINTER_DATA_SQL_TRANSACTION */
