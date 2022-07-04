//
// Created by Samuel Azcona on 21/05/2020.
//

#ifndef WINTERCPP_WINTER_DATA_SQL_CLAUSE_TYPE_H
#define WINTERCPP_WINTER_DATA_SQL_CLAUSE_TYPE_H
namespace winter::data::sql_impl {

    enum class ClauseType : int { WHERE,
                                  IN };
}
#endif  // WINTERCPP_WINTER_DATA_SQL_CLAUSE_TYPE_H
