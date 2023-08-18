//
// Created by samuaz on 3/10/21.
//

#include <wintercpp/winter.h>

#include <cstddef>
#include <memory>
#include <set>

#include "gtest/gtest.h"
#include "wintercpp/data/sql/statement/clause/winter_data_sql_clause_values.h"

using namespace winter::data::sql_impl;

struct QueryTestTableMin : public UUIDTable {
    QueryTestTableMin() :
        UUIDTable("QueryTestTableMin", true, DatabaseType::kGeneric) {}
    const Column col1 = String("col1");
    const Column col2 = Int("col2");
    const Column col3 = Boolean("col3");
    const Column col4 = String("col4");
    const Column col5 = String("col5");
};

TEST(winteValuesClause, canCreateValuesClause) {
    std::shared_ptr<QueryTestTableMin> testTable = std::make_shared<QueryTestTableMin>();
    auto      valuesClause = Values({Values::Add(testTable->col1, "hola")});
    ASSERT_EQ(valuesClause.Query(), "(QueryTestTableMin.col1) VALUES (?)");
}

TEST(winteValuesClause, canCreateValuesClauseMultipleValue) {
    std::shared_ptr<QueryTestTableMin> testTable = std::make_shared<QueryTestTableMin>();
    auto      valuesClause = Values({
        Values::Add(testTable->col1, "hola"), 
        Values::Add(testTable->col2, 10), 
        Values::Add(testTable->col3, true)
        });
    ASSERT_EQ(valuesClause.Query(), "(QueryTestTableMin.col1, QueryTestTableMin.col2, QueryTestTableMin.col3) VALUES (?,?,?)");
}