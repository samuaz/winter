//
// Created by samuaz on 3/10/21.
//

#include <wintercpp/winter.h>

#include <cstddef>
#include <memory>
#include <set>

#include "gtest/gtest.h"

// AND (SELECT columna4 FROM tabla2 WHERE columna5 = 'bar') < (SELECT columna6 FROM tabla3 WHERE columna7 = 'baz')
// AND (SELECT columna4 FROM tabla2 WHERE columna5 = 'bar') < 10
// AND table.column < 10
// AND table.column NOT NULL
// AND LOWER(lastName) LIKE 'a%'

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

TEST(winteAndClause, canCreateSubClause) {
    std::shared_ptr<QueryTestTableMin> testTable = std::make_shared<QueryTestTableMin>();
    Select                            *select = new Select({testTable->col1});
    select->AddClause(From(testTable));
    auto      selectShared = std::shared_ptr<Select>(select);
    Predicate predicate = Predicate(selectShared, Condition::LESS_EQ, selectShared);
    auto      andClause = And(predicate);
    ASSERT_EQ(andClause.Query(), "AND (SELECT QueryTestTableMin.col1 FROM QueryTestTableMin) <= (SELECT QueryTestTableMin.col1 FROM QueryTestTableMin)");
}

TEST(winteAndClause, canCreateSubClauseAndValue) {
    std::shared_ptr<QueryTestTableMin> testTable = std::make_shared<QueryTestTableMin>();
    Select                            *select = new Select({testTable->col1});
    select->AddClause(From(testTable));
    auto      selectShared = std::shared_ptr<Select>(select);
    Predicate predicate = Predicate::Make(selectShared, Condition::LESS_EQ, 10);
    auto      andClause = And(predicate);
    ASSERT_EQ(andClause.Query(), "AND (SELECT QueryTestTableMin.col1 FROM QueryTestTableMin) <= ?");
}

TEST(winteAndClause, canCreateSubColumnAndValue) {
    std::shared_ptr<QueryTestTableMin> testTable = std::make_shared<QueryTestTableMin>();
    Predicate                          predicate = Predicate::Make(testTable->col1, Condition::LESS_EQ, 10);
    auto                               andClause = And(predicate);
    ASSERT_EQ(andClause.Query(), "AND QueryTestTableMin.col1 <= ?");
}

TEST(winteAndClause, canCreateSubColumnAndCondition) {
    std::shared_ptr<QueryTestTableMin> testTable = std::make_shared<QueryTestTableMin>();
    Predicate                          predicate = Predicate::Make(testTable->col1, Condition::IS_NOT_NULL);
    auto                               andClause = And(predicate);
    ASSERT_EQ(andClause.Query(), "AND QueryTestTableMin.col1 IS NOT NULL");
}

TEST(winteAndClause, canCreateSubClauseAndCondition) {
    std::shared_ptr<QueryTestTableMin> testTable = std::make_shared<QueryTestTableMin>();
    Select                            *select = new Select({testTable->col1});
    select->AddClause(From(testTable));
    auto      selectShared = std::shared_ptr<Select>(select);
    Predicate predicate = Predicate::Make(selectShared, Condition::IS_NOT_NULL);
    auto      andClause = And(predicate);
    ASSERT_EQ(andClause.Query(), "AND (SELECT QueryTestTableMin.col1 FROM QueryTestTableMin) IS NOT NULL");
}