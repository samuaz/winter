//
// Created by samuaz on 3/10/21.
//

#include <wintercpp/winter.h>

#include <cstddef>
#include <set>

#include "gtest/gtest.h"
#include "wintercpp/data/sql/column/winter_data_sql_column.h"
#include "wintercpp/data/sql/field/winter_data_sql_field_type.h"
#include "wintercpp/data/sql/function/winter_data_sql_function_min.h"
#include "wintercpp/data/sql/table/winter_data_sql_table.h"


using namespace winter::data::sql_impl;

TEST(winterSqlFunction, minFunction) {
Table table("TestTable", TableType::kLong, DatabaseType::kMysql);
Column name(table, "testColumn", FieldType::kBigInt);
Min min(name);
//min.Prepare();
//ASSERT_EQ(min.statement_template(), "MIN($min) AS min_$columnName");
ASSERT_EQ(min.Query() , "MIN(TestTable.testColumn) AS min_TestTable_testColumn");
ASSERT_EQ(min.name() , "min_TestTable_testColumn");
}