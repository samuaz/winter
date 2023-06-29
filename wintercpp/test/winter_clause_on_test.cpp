//
// Created by samuaz on 3/10/21.
//

#include <wintercpp/winter.h>

#include <cstddef>
#include <memory>
#include <set>

#include "gtest/gtest.h"
#include "wintercpp/data/sql/statement/clause/winter_data_sql_clause_on.h"
#include "wintercpp/data/sql/statement/clause/winter_data_sql_clause_operator.h"

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

TEST(winteOnClause, canCreateOnWithColumnAndCondition) {
    std::shared_ptr<QueryTestTableMin> testTable = std::make_shared<QueryTestTableMin>();
    auto      on = On(testTable->col1, Condition::IS_NOT_NULL);
    ASSERT_EQ(on.Query(), "ON QueryTestTableMin.col1 IS NOT NULL");
}

TEST(winteOnClause, canCreateOnWithColumnConditionColumn) {
    std::shared_ptr<QueryTestTableMin> testTable = std::make_shared<QueryTestTableMin>();
    auto      on = On(testTable->col1, Condition::EQ, testTable->col2);
    ASSERT_EQ(on.Query(), "ON QueryTestTableMin.col1 = QueryTestTableMin.col2");
}

TEST(winteOnClause, canCreateOnWithClauseConditionClause) {
    std::shared_ptr<QueryTestTableMin> testTable = std::make_shared<QueryTestTableMin>();
    auto      selectShared = std::shared_ptr<Select>(new Select({testTable->col1}));
    auto      on = On(selectShared, Condition::EQ, selectShared);
    ASSERT_EQ(on.Query(), "ON (SELECT QueryTestTableMin.col1) = (SELECT QueryTestTableMin.col1)");
}

TEST(winteOnClause, canCreateOnWithClauseConditionColumn) {
    std::shared_ptr<QueryTestTableMin> testTable = std::make_shared<QueryTestTableMin>();
    auto      selectShared = std::shared_ptr<Select>(new Select({testTable->col1}));
    auto      on = On(selectShared, Condition::EQ, testTable->col1);
    ASSERT_EQ(on.Query(), "ON (SELECT QueryTestTableMin.col1) = QueryTestTableMin.col1");
}

TEST(winteOnClause, canCreateOnWithClauseAnd) {
    std::shared_ptr<QueryTestTableMin> testTable = std::make_shared<QueryTestTableMin>();
    auto      selectShared = std::shared_ptr<Select>(new Select({testTable->col1}));
    auto      on = On(selectShared, Condition::IS_NOT_NULL);
    ASSERT_EQ(on.Query(), "ON (SELECT QueryTestTableMin.col1) IS NOT NULL");
}