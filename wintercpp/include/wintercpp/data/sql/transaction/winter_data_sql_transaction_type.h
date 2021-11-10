//
// Created by Samuel Azcona on 30/03/2020.
//

#ifndef WINTERCPP_WINTER_DATA_SQL_TRANSACTION_TYPE_H
#define WINTERCPP_WINTER_DATA_SQL_TRANSACTION_TYPE_H
namespace winter::data::sql_impl {

enum class TransactionIsolationType {
  DEFAULT = 0,
  READ_COMMITTED = 1,
  READ_UNCOMMITTED = 2,
  REPEATABLE_READ = 3,
  SERIALIZABLE = 4
};
}
#endif	// WINTERCPP_WINTER_DATA_SQL_TRANSACTION_TYPE_H
