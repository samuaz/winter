#include <wintercpp/data/sql/mysql/connection/winter_data_sql_mysql_impl_connection.h>

using namespace winter::data::mysql;

int32_t winter::data::mysql::connection::Connection::IsolationLevel(const TransactionIsolationType &isolation) {
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
}