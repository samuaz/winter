//
// Created by samuaz on 3/10/21.
//

#include <wintercpp/winter.h>

#include <cstddef>
#include <memory>
#include <set>

#include "gtest/gtest.h"
#include "wintercpp/data/sql/column/winter_data_sql_column.h"
#include "wintercpp/data/sql/statement/clause/winter_data_sql_clause_from.h"
#include "wintercpp/data/sql/statement/winter_data_sql_select.h"

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

TEST(winteFromClause, canCreateFrom) {
    std::shared_ptr<QueryTestTableMin> testTable = std::make_shared<QueryTestTableMin>();
    auto      fromClause = From(testTable);
    ASSERT_EQ(fromClause.Query(), "FROM QueryTestTableMin");
}

TEST(winteFromClause, canCreateFromWithSubClause) {
    std::shared_ptr<QueryTestTableMin> testTable = std::make_shared<QueryTestTableMin>();
    auto      selectShared = std::shared_ptr<Select>(new Select({testTable->col1}));
    auto      fromClause = From(selectShared);
    ASSERT_EQ(fromClause.Query(), "FROM (SELECT QueryTestTableMin.col1)");
}
