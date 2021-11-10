//
// Created by AZCONA VARGAS, SAMUEL EDUARDO [AG-Contractor/5000] on 2019-12-14.
//

#ifndef WINTERCPP_DATA_SQL_STATEMENT_TYPE_H
#define WINTERCPP_DATA_SQL_STATEMENT_TYPE_H

namespace winter::data::sql_impl {

enum class StatementType {
  kNative = 0,
  kSelect,
  kInsert,
  kUpdate,
  kDelete,
  kCreate,
  kDrop,
  kTruncate,
  kClause
};
}
#endif	// WINTERCPP_WINTER_SQL_STATEMENT_TYPE_H