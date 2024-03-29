//
// Created by samuaz on 3/10/21.
//

#include <wintercpp/winter.h>

#include <cstddef>
#include <memory>
#include <set>

#include "gtest/gtest.h"
#include "wintercpp/data/sql/statement/clause/winter_data_sql_clause_predicate.h"

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

TEST(winteSetClause, canCreateSetClause) {
    std::shared_ptr<QueryTestTableMin> testTable = std::make_shared<QueryTestTableMin>();
    auto      setClause = Set(Set::Add(testTable->col1, "hola"));
    ASSERT_EQ(setClause.Query(), "SET QueryTestTableMin.col1=?");
}

TEST(winteSetClause, canCreateSetClauseMultipleValue) {
    std::shared_ptr<QueryTestTableMin> testTable = std::make_shared<QueryTestTableMin>();
    auto      setClause = Set({
        Set::Add(testTable->col1, "hola"), 
        Set::Add(testTable->col2, "hola"), 
        Set::Add(testTable->col3, "hola")
        });
    ASSERT_EQ(setClause.Query(), "SET QueryTestTableMin.col1=?,QueryTestTableMin.col2=?,QueryTestTableMin.col3=?");
}