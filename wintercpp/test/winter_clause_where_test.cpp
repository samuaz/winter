//
// Created by samuaz on 3/10/21.
//

#include <wintercpp/winter.h>

#include <cstddef>
#include <memory>
#include <set>

#include "gtest/gtest.h"
#include "wintercpp/data/sql/statement/winter_data_sql_statement_values.h"

using namespace winter::data::sql_impl;

struct QueryTestTableMin : public UUIDTable {
    QueryTestTableMin() :
        UUIDTable("QueryTestTableMin", true, DatabaseType::kGeneric) {}
    const Column col1 = String("col1");
    const Column col2 = String("col2");
    const Column col3 = String("col3");
    const Column col4 = String("col4");
    const Column col5 = String("col5");
};

TEST(winteSelectClause, canCreateSelectClause) {
    std::shared_ptr<QueryTestTableMin> testTable = std::make_shared<QueryTestTableMin>();
    auto      whereClause = Where(Predicate::Make(testTable->col1, Condition::EQ, "hola"));
    ASSERT_EQ(whereClause.Query(), "WHERE QueryTestTableMin.col1 = ?");
}

TEST(winteSelectClause, canCreateSelectClauseCustomValue) {
    std::shared_ptr<QueryTestTableMin> testTable = std::make_shared<QueryTestTableMin>();
    auto      whereClause = Where(Predicate::Make(testTable->col1, Condition::EQ, "hola", "HEX(?)"));
    ASSERT_EQ(whereClause.Query(), "WHERE QueryTestTableMin.col1 = HEX(?)");
}

TEST(winteSelectClause, canCreateSelectSingleColumn) {
    std::shared_ptr<QueryTestTableMin> testTable = std::make_shared<QueryTestTableMin>();
    auto      whereClause = Where(Predicate::Make(testTable->col1, Condition::IS_NOT_NULL));
    ASSERT_EQ(whereClause.Query(), "WHERE QueryTestTableMin.col1 IS NOT NULL");
}

TEST(winteSelectClause, canCreateSelectClauseTwoColumns) {
    std::shared_ptr<QueryTestTableMin> testTable = std::make_shared<QueryTestTableMin>();
    auto      whereClause = Where(Predicate::Make(testTable->col1, Condition::EQ, testTable->col2));
    ASSERT_EQ(whereClause.Query(), "WHERE QueryTestTableMin.col1 = QueryTestTableMin.col2");
}

TEST(winteSelectClause, canCreateSelectClauseColumnWithStatement) {
    std::shared_ptr<QueryTestTableMin> testTable = std::make_shared<QueryTestTableMin>();
    auto      selectShared = std::shared_ptr<IStatement>(new Select({testTable->col1}));
    auto      whereClause = Where(Predicate::Make(testTable->col1, Condition::EQ, selectShared));
    ASSERT_EQ(whereClause.Query(), "WHERE QueryTestTableMin.col1 = (SELECT QueryTestTableMin.col1)");
}

TEST(winteSelectClause, canCreateSelectClauseTwoWithStatement) {
    std::shared_ptr<QueryTestTableMin> testTable = std::make_shared<QueryTestTableMin>();
    auto      selectShared = std::shared_ptr<IStatement>(new Select({testTable->col1}));
    auto      whereClause = Where(Predicate::Make(selectShared, Condition::EQ, selectShared));
    ASSERT_EQ(whereClause.Query(), "WHERE (SELECT QueryTestTableMin.col1) = (SELECT QueryTestTableMin.col1)");
}

TEST(winteSelectClause, canCreateSelectClauseWithStatement) {
    std::shared_ptr<QueryTestTableMin> testTable = std::make_shared<QueryTestTableMin>();
    auto      selectShared = std::shared_ptr<Select>(new Select({testTable->col1}));
    auto      whereClause = Where(Predicate::Make(selectShared, Condition::IS_NOT_NULL));
    ASSERT_EQ(whereClause.Query(), "WHERE (SELECT QueryTestTableMin.col1) IS NOT NULL");
}

