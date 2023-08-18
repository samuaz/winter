//
// Created by samuaz on 3/10/21.
//

#include <wintercpp/winter.h>

#include <cstddef>
#include <memory>
#include <set>

#include "gtest/gtest.h"

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

TEST(winteOrClause, canCreateSubClause) {
    std::shared_ptr<QueryTestTableMin> testTable = std::make_shared<QueryTestTableMin>();
    Select                            *select = new Select({testTable->col1});
    select->AddClause(From(testTable));
    auto      selectShared = std::shared_ptr<Select>(select);
    Predicate predicate = Predicate(selectShared, Condition::LESS_EQ, selectShared);
    auto      orClause = Or(predicate);
    ASSERT_EQ(orClause.Query(), "OR (SELECT QueryTestTableMin.col1 FROM QueryTestTableMin) <= (SELECT QueryTestTableMin.col1 FROM QueryTestTableMin)");
}

TEST(winteOrClause, canCreateSubClauseAndValue) {
    std::shared_ptr<QueryTestTableMin> testTable = std::make_shared<QueryTestTableMin>();
    Select                            *select = new Select({testTable->col1});
    select->AddClause(From(testTable));
    auto      selectShared = std::shared_ptr<Select>(select);
    Predicate predicate = Predicate::Make(selectShared, Condition::LESS_EQ, 10);
    auto      orClause = Or(predicate);
    ASSERT_EQ(orClause.Query(), "OR (SELECT QueryTestTableMin.col1 FROM QueryTestTableMin) <= ?");
}

TEST(winteOrClause, canCreateSubColumnAndValue) {
    std::shared_ptr<QueryTestTableMin> testTable = std::make_shared<QueryTestTableMin>();
    Predicate                          predicate = Predicate::Make(testTable->col1, Condition::LESS_EQ, 10);
    auto                               orClause = Or(predicate);
    ASSERT_EQ(orClause.Query(), "OR QueryTestTableMin.col1 <= ?");
}

TEST(winteOrClause, canCreateSubColumnAndCondition) {
    std::shared_ptr<QueryTestTableMin> testTable = std::make_shared<QueryTestTableMin>();
    Predicate                          predicate = Predicate::Make(testTable->col1, Condition::IS_NOT_NULL);
    auto                               orClause = Or(predicate);
    ASSERT_EQ(orClause.Query(), "OR QueryTestTableMin.col1 IS NOT NULL");
}

TEST(winteOrClause, canCreateSubClauseAndCondition) {
    std::shared_ptr<QueryTestTableMin> testTable = std::make_shared<QueryTestTableMin>();
    Select                            *select = new Select({testTable->col1});
    select->AddClause(From(testTable));
    auto      selectShared = std::shared_ptr<Select>(select);
    Predicate predicate = Predicate::Make(selectShared, Condition::IS_NOT_NULL);
    auto      orClause = Or(predicate);
    ASSERT_EQ(orClause.Query(), "OR (SELECT QueryTestTableMin.col1 FROM QueryTestTableMin) IS NOT NULL");
}