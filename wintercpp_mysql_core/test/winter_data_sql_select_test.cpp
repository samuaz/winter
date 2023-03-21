//
// Created by samuaz on 3/10/21.
//

#include <gtest/gtest.h>
#include <wintercpp/winter.h>

#include <iostream>
#include <memory>
#include <optional>

#include "gmock/gmock-matchers.h"
#include "gmock/gmock-more-matchers.h"
#include "wintercpp/data/sql/column/winter_data_sql_column.h"
#include "wintercpp/data/sql/statement/clause/winter_data_sql_clause_or.h"
#include "wintercpp/data/sql/statement/clause/winter_data_sql_clause_where.h"

using namespace winter;
using namespace winter::data::sql_impl;
struct QueryTestTable : public UUIDTable {
    QueryTestTable() :
        UUIDTable("QueryTestTable", true, DatabaseType::kGeneric) {}
    const Column col1 = String("col1");
    const Column col2 = String("col2");
    const Column col3 = String("col3");
    const Column col4 = String("col4");
    const Column col5 = String("col5");
};

struct QueryTestTable2 : public UUIDTable {
    QueryTestTable2() :
        UUIDTable("QueryTestTable2", true, DatabaseType::kGeneric) {}
    const Column col1 = String("col1");
    const Column col2 = String("col2");
    const Column col3 = String("col3");
    const Column col4 = String("col4");
    const Column col5 = String("col5");
};

TEST(winterSqlTable, canConstructSelectQuery) {
    std::shared_ptr<QueryTestTable> testTable = std::shared_ptr<QueryTestTable>(new QueryTestTable());

    auto query = Select() << From(testTable) << Where(Where::make_predicate(testTable->col1, winter::data::sql_impl::Condition::EQ, "samuel"));

    EXPECT_EQ(query.prepared_statement().statement_template(), "SELECT * FROM QueryTestTable WHERE QueryTestTable.col1 = ?");
}

TEST(winterSqlTable, canConstructSelectQueryWhereAndOr) {
    std::shared_ptr<QueryTestTable> testTable = std::shared_ptr<QueryTestTable>(new QueryTestTable());

    auto query = Select() << From(testTable) << Where(Where::make_predicate(testTable->col1, winter::data::sql_impl::Condition::EQ, "samuel")) << And(And::MakePredicate(testTable->col2, winter::data::sql_impl::Condition::EQ, "Azcona")) << Or(Or::MakePredicate(testTable->col1, winter::data::sql_impl::Condition::EQ, "Eduardo"));

    EXPECT_EQ(query.prepared_statement().statement_template(), "SELECT * FROM QueryTestTable WHERE QueryTestTable.col1 = ? AND QueryTestTable.col2 = ? OR QueryTestTable.col1 = ?");
}

TEST(winterSqlTable, canConstructSelectQueryWhereWithoutPredicate) {
    std::shared_ptr<QueryTestTable> testTable = std::shared_ptr<QueryTestTable>(new QueryTestTable());

    auto query = Select() << From(testTable) << Where(testTable->col3, winter::data::sql_impl::Condition::IS_NULL) << And(And::MakePredicate(testTable->col2, winter::data::sql_impl::Condition::EQ, "Azcona")) << Or(Or::MakePredicate(testTable->col1, winter::data::sql_impl::Condition::EQ, "Eduardo"));

    EXPECT_EQ(query.prepared_statement().statement_template(), "SELECT * FROM QueryTestTable WHERE QueryTestTable.col3 IS NULL AND QueryTestTable.col2 = ? OR QueryTestTable.col1 = ?");
}

TEST(winterSqlTable, canConstructSelectPartialFieldsQueryWhereWithoutPredicate) {
    std::shared_ptr<QueryTestTable> testTable = std::shared_ptr<QueryTestTable>(new QueryTestTable());

    auto query = Select({testTable->col1, testTable->col2, testTable->col3}) << From(testTable) << Where(testTable->col3, winter::data::sql_impl::Condition::IS_NULL) << And(And::MakePredicate(testTable->col2, winter::data::sql_impl::Condition::EQ, "Azcona")) << Or(Or::MakePredicate(testTable->col1, winter::data::sql_impl::Condition::EQ, "Eduardo"));

    EXPECT_EQ(query.prepared_statement().statement_template(), "SELECT QueryTestTable.col1, QueryTestTable.col2, QueryTestTable.col3 FROM QueryTestTable WHERE QueryTestTable.col3 IS NULL AND QueryTestTable.col2 = ? OR QueryTestTable.col1 = ?");
}

TEST(winterSqlTable, canConstructSelectOneFieldQueryWhereWithoutPredicate) {
    std::shared_ptr<QueryTestTable> testTable = std::shared_ptr<QueryTestTable>(new QueryTestTable());

    auto query = Select({testTable->col1}) << From(testTable) << Where(testTable->col3, winter::data::sql_impl::Condition::IS_NULL) << And(And::MakePredicate(testTable->col2, winter::data::sql_impl::Condition::EQ, "Azcona")) << Or(Or::MakePredicate(testTable->col1, winter::data::sql_impl::Condition::EQ, "Eduardo"));

    EXPECT_EQ(query.prepared_statement().statement_template(), "SELECT QueryTestTable.col1 FROM QueryTestTable WHERE QueryTestTable.col3 IS NULL AND QueryTestTable.col2 = ? OR QueryTestTable.col1 = ?");
}

TEST(winterSqlTable, canConstructSelecFromMultipleTables) {
    std::shared_ptr<QueryTestTable>  testTable = std::shared_ptr<QueryTestTable>(new QueryTestTable());
    std::shared_ptr<QueryTestTable2> testTable2 = std::shared_ptr<QueryTestTable2>(new QueryTestTable2());

    auto query = Select({testTable->col1, testTable2->col3}) << From({testTable, testTable2}) << Where(testTable->col3, winter::data::sql_impl::Condition::IS_NULL) << And(And::MakePredicate(testTable->col2, winter::data::sql_impl::Condition::EQ, "Azcona")) << Or(Or::MakePredicate(testTable2->col1, winter::data::sql_impl::Condition::EQ, "Eduardo"));

    EXPECT_EQ(query.prepared_statement().statement_template(), "SELECT QueryTestTable.col1, QueryTestTable2.col3 FROM QueryTestTable, QueryTestTable2 WHERE QueryTestTable.col3 IS NULL AND QueryTestTable.col2 = ? OR QueryTestTable2.col1 = ?");
}