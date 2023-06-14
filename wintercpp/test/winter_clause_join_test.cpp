//
// Created by samuaz on 3/10/21.
//

#include <wintercpp/winter.h>

#include <cstddef>
#include <memory>
#include <set>

#include "gtest/gtest.h"
#include "wintercpp/data/sql/column/winter_data_sql_column.h"
#include "wintercpp/data/sql/statement/clause/winter_data_sql_clause_join.h"

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

TEST(winteJoinClause, canCreateJoinINNER) {
    std::shared_ptr<QueryTestTableMin> testTable = std::make_shared<QueryTestTableMin>();
    auto      join = Join(testTable, JoinType::INNER);
    ASSERT_EQ(join.Query(), "INNER JOIN QueryTestTableMin");
}

TEST(winteJoinClause, canCreateJoinLEFT) {
    std::shared_ptr<QueryTestTableMin> testTable = std::make_shared<QueryTestTableMin>();
    auto      join = Join(testTable, JoinType::LEFT);
    ASSERT_EQ(join.Query(), "LEFT JOIN QueryTestTableMin");
}

TEST(winteJoinClause, canCreateJoinRIGHT) {
    std::shared_ptr<QueryTestTableMin> testTable = std::make_shared<QueryTestTableMin>();
    auto      join = Join(testTable, JoinType::RIGHT);
    ASSERT_EQ(join.Query(), "RIGHT JOIN QueryTestTableMin");
}


TEST(winteJoinClause, canCreateJoinCROSS) {
    std::shared_ptr<QueryTestTableMin> testTable = std::make_shared<QueryTestTableMin>();
    auto      join = Join(testTable, JoinType::CROSS);
    ASSERT_EQ(join.Query(), "CROSS JOIN QueryTestTableMin");
}

TEST(winteJoinClause, canCreateJoinFULL) {
    std::shared_ptr<QueryTestTableMin> testTable = std::make_shared<QueryTestTableMin>();
    auto      join = Join(testTable, JoinType::FULL_JOIN);
    ASSERT_EQ(join.Query(), "FULL JOIN QueryTestTableMin");
}

