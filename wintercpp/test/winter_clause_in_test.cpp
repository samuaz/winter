//
// Created by samuaz on 3/10/21.
//

#include <wintercpp/winter.h>

#include <cstddef>
#include <memory>
#include <set>

#include "gtest/gtest.h"
#include "wintercpp/data/sql/column/winter_data_sql_column.h"
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

TEST(winteInClause, canCreateInWithValues) {
    std::vector<int> values {1,2,3};
    auto      inClause = In::Values(values);
    ASSERT_EQ(inClause.Query(), "IN (?,?,?)");
}

TEST(winteInClause, canCreateInWithSubClause) {
    std::shared_ptr<QueryTestTableMin> testTable = std::make_shared<QueryTestTableMin>();
    auto      selectShared = std::shared_ptr<Select>(new Select({testTable->col1}));
    auto      inClause = In(selectShared);
    ASSERT_EQ(inClause.Query(), "IN (SELECT QueryTestTableMin.col1)");
}
