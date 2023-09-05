//
// Created by samuaz on 3/10/21.
//

#include <gtest/gtest.h>
#include <wintercpp/winter.h>

#include <optional>

#include "gmock/gmock-matchers.h"
#include "gmock/gmock-more-matchers.h"
#include "wintercpp/data/sql/column/winter_data_sql_column.h"

using namespace winter;
using namespace winter::data::sql_impl;

struct TestTable : public UUIDTable {
    TestTable() :
        UUIDTable("TestTable", true, DatabaseType::kGeneric) {}
    const Column col1 = String("col1");
    const Column col2 = String("col2");
    const Column col3 = String("id2");
};

TEST(winterSqlTable, canGetTableName) {
    TestTable testTable;
    EXPECT_EQ(testTable.name(), "TestTable");
}

TEST(winterSqlTable, canGetIdColumnName) {
    TestTable testTable;
    EXPECT_EQ(testTable.id().name(), "id");
}

TEST(winterSqlTable, canGenerateUUID) {
    TestTable testTable;
    EXPECT_THAT(testTable.GenerateId(), Not(testing::IsEmpty()));
}

TEST(winterSqlTable, checkTableType) {
    TestTable testTable;
    EXPECT_EQ(testTable.tableType(), TableType::kUUID);
}

TEST(winterSqlTable, columnsSize) {
    TestTable testTable;
    // size should be 3 because we have the default id column + 2 declared columns
    EXPECT_THAT(testTable.columns(), testing::SizeIs(4));
}

TEST(winterSqlTable, canRegisterColumn) {
    TestTable testTable;
    testTable.RegisterColumn("col3", FieldType::kString);
    // size should be 4 because we have the default id column + 2 declared columns + the new column we register
    EXPECT_THAT(testTable.columns(), testing::SizeIs(5));
    auto newColumn = *std::next(testTable.columns().begin(), 4);
    EXPECT_EQ(newColumn->name(), "col3");
}

TEST(winterSqlTable, canTemporalCreateColumnForTableWithoutGlobalRegister) {
    TestTable testTable;
    Column    column = Column(testTable, "col3", FieldType::kString);
    // size should be 4 because we have the default id column + 2 declared columns + the new column we register
    EXPECT_THAT(testTable.columns(), testing::SizeIs(4));
}
