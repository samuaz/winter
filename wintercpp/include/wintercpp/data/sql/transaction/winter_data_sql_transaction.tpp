#include <wintercpp/data/sql/transaction/winter_data_sql_transaction.h>

#include <algorithm>
#include <cstddef>
#include <string>
#include <utility>

namespace winter::data::sql_impl {

#define TRANSACTION_TEMPLATE            \
    template<typename TSQLConnection,   \
             typename TResponse>
#define TRANSACTION Transaction<TSQLConnection, TResponse>

    TRANSACTION_TEMPLATE
    TRANSACTION::Transaction(std::shared_ptr<TSQLConnection> connection,
                             TransactionIsolationType        isolation_type,
                             bool                            partial_commit) :
        connection_(std::move(connection)),
        isolation_type_(isolation_type), partial_commit_(partial_commit) {
        connection_->PrepareTransaction(isolation_type_);
    }

    TRANSACTION_TEMPLATE
    TRANSACTION &TRANSACTION::This() {
        return dynamic_cast<TTransactionImpl &>(*this);
    }

    TRANSACTION_TEMPLATE
    template<typename T>
    T TRANSACTION::Execute(
        const std::function<T(TTransactionImpl &)> &statements) {
        return statements(This());
    }

    TRANSACTION_TEMPLATE
    TResponse TRANSACTION::Execute(
        const PreparedStatement &prepared_statement) {
        operations_status_.emplace(prepared_statement.id(), false);
        TResponse response = [&]() -> TResponse {
            return connection_->Execute(prepared_statement);
        }();
        operations_status_[prepared_statement.id()] = response.IsSuccess();
        return response;
    }

    TRANSACTION_TEMPLATE
    TResponse TRANSACTION::Execute(IStatement &statement) {
        return Execute(statement.prepared_statement());
    }

    /* template <typename TTransactionImpl, typename TConnectionImpl, typename
    TConnectionType, typename TResponse> template <typename T> T
    Transaction<TTransactionImpl, TConnectionImpl, TConnectionType,
    TResponse>::operator()(const std::function<T(TTransactionImpl &)>
    &statements) { return Execute<T>(statements);
    }

    template <typename TTransactionImpl, typename TConnectionImpl, typename
    TConnectionType, typename TResponse> TResponse Transaction<TTransactionImpl,
    TConnectionImpl, TConnectionType, TResponse>::operator()(const
    PreparedStatement &prepared_statement) { return Execute(prepared_statement);
    }

    template <typename TTransactionImpl, typename TConnectionImpl, typename
    TConnectionType, typename TResponse> TResponse Transaction<TTransactionImpl,
    TConnectionImpl, TConnectionType, TResponse>::operator()(IStatement
    &statement) { Execute(statement);
    } */

    TRANSACTION_TEMPLATE
    TransactionIsolationType TRANSACTION::isolation() const {
        return isolation_type_;
    }

    TRANSACTION_TEMPLATE
    bool TRANSACTION::ignore_error() const {
        return partial_commit_;
    }

    TRANSACTION_TEMPLATE
    void TRANSACTION::Commit() const {
        connection_->Commit();
    }

    TRANSACTION_TEMPLATE
    void TRANSACTION::Rollback() const {
        connection_->Rollback();
    }

    TRANSACTION_TEMPLATE
    TRANSACTION::~Transaction() {
        // if any of the operations_status fail that means returns false, we
        // rollback then we commit check in this way because any_of can give
        // better performance than all_of, if we found the first false the loop
        // ends.
        bool fail = std::any_of(std::begin(operations_status_),
                                std::end(operations_status_),
                                [](const pair<std::string, bool> &i) {
                                    return ! i.second;
                                });

        if (fail) {
            if (Transaction::ignore_error()) {
                Transaction::Commit();
            } else {
                Transaction::Rollback();
            }
        } else {
            Transaction::Commit();
        }
    }

}  // namespace winter::data::sql_impl
