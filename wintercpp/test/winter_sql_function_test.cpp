//
// Created by samuaz on 3/10/21.
//

#include <wintercpp/winter.h>

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
ASSERT_EQ(min.Query() , "MIN(TestTable.testColumn) AS min_TestTable_testColumn");
ASSERT_EQ(min.Alias() , "min_TestTable_testColumn");
}

TEST(winterSqlFunction, minFunctionWithDifferentAlias) {
Table table("TestTable", TableType::kLong, DatabaseType::kMysql);
Column name(table, "testColumn", FieldType::kBigInt);
Min min(name, "min_custom_name", FieldType::kString);
ASSERT_EQ(min.Query() , "MIN(TestTable.testColumn) AS min_custom_name");
ASSERT_EQ(min.Alias() , "min_custom_name");
}