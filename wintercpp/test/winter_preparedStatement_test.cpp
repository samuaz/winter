//
// Created by samuaz on 3/10/21.
//

#include <wintercpp/winter.h>

#include <cstddef>
#include <set>

#include "gtest/gtest.h"
#include "wintercpp/data/sql/column/winter_data_sql_column.h"
#include "wintercpp/data/sql/field/winter_data_sql_field_type.h"
#include "wintercpp/data/sql/preparedstatement/winter_data_sql_abstract_prepared_statement_field.h"
#include "wintercpp/data/sql/preparedstatement/winter_data_sql_prepared_statement.h"
#include "wintercpp/data/sql/preparedstatement/winter_data_sql_prepared_statement_field.h"
#include "wintercpp/data/sql/statement/winter_data_sql_statement_type.h"
#include "wintercpp/data/sql/table/winter_data_sql_uuid_table.h"

using namespace winter::data::sql_impl;

TEST(preparedStatement, canCreate) {
auto preparedStatement = PreparedStatement(StatementType::kNative, "template $test");
ASSERT_FALSE(preparedStatement.id().empty());
ASSERT_EQ(preparedStatement.statement_template(), "template $test");
}

TEST(preparedStatement, canAddColumns) {
Table table = UUIDTable("TestTable", false, DatabaseType::kGeneric);
Column col = Column(table, "test_column_1", FieldType::kLong);
Column col2 = Column(table, "test_column_2", FieldType::kBoolean);
Column col3 = Column(table, "test_column_3", FieldType::kString);
auto preparedStatement = PreparedStatement(StatementType::kNative, "template $test");
preparedStatement.AddColumn({col, col2, col3});
ASSERT_EQ(preparedStatement.columns().size(), 3);
}

TEST(preparedStatement, canFindFields) {
auto preparedStatement = PreparedStatement(StatementType::kNative, "template $test");
preparedStatement.AddValue(new PreparedStatementField<std::string>("name", "name"));
preparedStatement.AddValue(new PreparedStatementField<std::string>("lastName", "lastName"));
const AbstractPreparedStatementField & foundField = preparedStatement.FindByName("name");
auto foundField2 = preparedStatement.FindByField("lastName");
ASSERT_EQ(foundField.name(), "name");
ASSERT_EQ(foundField2->name(), "lastName");
}

TEST(preparedStatement, fieldIsPresent) {
auto preparedStatement = PreparedStatement(StatementType::kNative, "template $test");
preparedStatement.AddValue(new PreparedStatementField<std::string>("name", "name"));
ASSERT_TRUE(preparedStatement.FieldIsPresent("name"));
}

TEST(preparedStatement, searchByIndex) {
auto preparedStatement = PreparedStatement(StatementType::kNative, "template $test");
preparedStatement.AddValue(new PreparedStatementField<std::string>("name", "name"));
preparedStatement.AddValue(new PreparedStatementField<std::string>("lastName", "lastName"));
ASSERT_EQ(preparedStatement.SearchFieldIndex("name"), 0);
ASSERT_EQ(preparedStatement.SearchFieldIndex("lastName"), 1);
}
