#include <wintercpp/data/sql/transaction/winter_data_sql_transaction.h>

#include <algorithm>
#include <cstddef>
#include <string>
#include <utility>

namespace winter::data::sql {

template <typename TTransactionImpl, typename TConnectionImpl, typename TConnectionType, typename TResponse>
Transaction<TTransactionImpl, TConnectionImpl, TConnectionType, TResponse>::Transaction(
    std::shared_ptr<SQLConnection<TConnectionImpl, TConnectionType, TResponse> >
	connection,
    TransactionIsolationType isolation_type,
    bool partial_commit) : connection_(std::move(connection)),
			   isolation_type_(isolation_type),
			   partial_commit_(partial_commit) {
  connection_->PrepareTransaction(isolation_type_);
}

template <typename TTransactionImpl, typename TConnectionImpl, typename TConnectionType, typename TResponse>
TTransactionImpl &
Transaction<TTransactionImpl, TConnectionImpl, TConnectionType, TResponse>::This() {
  return dynamic_cast<TTransactionImpl &>(*this);
}

template <typename TTransactionImpl, typename TConnectionImpl, typename TConnectionType, typename TResponse>
template <typename T>
T Transaction<TTransactionImpl, TConnectionImpl, TConnectionType, TResponse>::Execute(
    const std::function<T(TTransactionImpl &)> &statements) {
  return statements(This());
}

template <typename TTransactionImpl, typename TConnectionImpl, typename TConnectionType, typename TResponse>
TResponse
Transaction<TTransactionImpl, TConnectionImpl, TConnectionType, TResponse>::Execute(
    const PreparedStatement &prepared_statement) {
  operations_status_.emplace(prepared_statement.id(), false);
  TResponse response = [&]() -> TResponse {
    return connection_->Execute(prepared_statement);
  }();
  operations_status_[prepared_statement.id()] = response.IsSuccess();
  return response;
}

template <typename TTransactionImpl, typename TConnectionImpl, typename TConnectionType, typename TResponse>
TResponse
Transaction<TTransactionImpl, TConnectionImpl, TConnectionType, TResponse>::Execute(IStatement &statement) {
  return Execute(statement.prepared_statement());
}

/* template <typename TTransactionImpl, typename TConnectionImpl, typename TConnectionType, typename TResponse>
template <typename T>
T Transaction<TTransactionImpl, TConnectionImpl, TConnectionType, TResponse>::operator()(const std::function<T(TTransactionImpl &)> &statements) {
  return Execute<T>(statements);
}

template <typename TTransactionImpl, typename TConnectionImpl, typename TConnectionType, typename TResponse>
TResponse Transaction<TTransactionImpl, TConnectionImpl, TConnectionType, TResponse>::operator()(const PreparedStatement &prepared_statement) {
  return Execute(prepared_statement);
}

template <typename TTransactionImpl, typename TConnectionImpl, typename TConnectionType, typename TResponse>
TResponse Transaction<TTransactionImpl, TConnectionImpl, TConnectionType, TResponse>::operator()(IStatement &statement) {
  Execute(statement);
} */

template <typename TTransactionImpl, typename TConnectionImpl, typename TConnectionType, typename TResponse>
TransactionIsolationType
Transaction<TTransactionImpl, TConnectionImpl, TConnectionType, TResponse>::isolation() const {
  return isolation_type_;
}

template <typename TTransactionImpl, typename TConnectionImpl, typename TConnectionType, typename TResponse>
bool Transaction<TTransactionImpl, TConnectionImpl, TConnectionType, TResponse>::ignore_error() const {
  return partial_commit_;
}

template <typename TTransactionImpl, typename TConnectionImpl, typename TConnectionType, typename TResponse>
void Transaction<TTransactionImpl, TConnectionImpl, TConnectionType, TResponse>::Commit() const {
  connection_->Commit();
}

template <typename TTransactionImpl, typename TConnectionImpl, typename TConnectionType, typename TResponse>
void Transaction<TTransactionImpl, TConnectionImpl, TConnectionType, TResponse>::Rollback() const {
  connection_->Rollback();
}

template <typename TTransactionImpl, typename TConnectionImpl, typename TConnectionType, typename TResponse>
Transaction<TTransactionImpl, TConnectionImpl, TConnectionType, TResponse>::~Transaction() {
  // if any of the operations_status fail that means returns false, we rollback then we commit
  // check in this way because any_of can give better performance than all_of, if we found the first false the loop ends.
  bool fail = std::any_of(
      std::begin(operations_status_),
      std::end(operations_status_),
      [](const pair<std::string, bool> &i) { return !i.second; });

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

}  // namespace winter::data::sql
