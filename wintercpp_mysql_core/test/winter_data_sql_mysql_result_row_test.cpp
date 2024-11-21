//
// Created by samuaz on 3/10/21.
//

#include <_types/_uint64_t.h>
#include <gmock/gmock.h>
#include <sys/_types/_int64_t.h>
#include <sys/types.h>
#include <wintercpp/winter_mysql_core.h>

#include <istream>
#include <memory>
#include <string>

#include "gtest/gtest.h"
#include "wintercpp/data/sql/preparedstatement/winter_data_sql_prepared_statement.h"
#include "wintercpp/data/sql/table/winter_data_sql_table.h"

struct ResultSet {
    virtual std::string getString(const std::string& name) const = 0;
    virtual int         getInt(const std::string& name) const = 0;
    virtual uint        getUInt(const std::string& name) const = 0;
    virtual int64_t     getInt64(const std::string& name) const = 0;
    virtual uint64_t    getUInt64(const std::string& name) const = 0;
    virtual double      getDouble(const std::string& name) const = 0;
    virtual bool        getBoolean(const std::string& name) const = 0;
    virtual iostream*   getBlob(const std::string& name) const = 0;
    virtual bool        isNull(const std::string& name) const = 0;
    virtual int         rowsCount() = 0;
};

class MockResultSet : public ResultSet {
   public:
    MOCK_CONST_METHOD1(getString, std::string(const std::string& name));
    MOCK_CONST_METHOD1(getInt, int(const std::string& name));
    MOCK_CONST_METHOD1(getUInt, uint(const std::string& name));
    MOCK_CONST_METHOD1(getInt64, int64_t(const std::string& name));
    MOCK_CONST_METHOD1(getUInt64, uint64_t(const std::string& name));
    MOCK_CONST_METHOD1(getDouble, double(const std::string& name));
    MOCK_CONST_METHOD1(getBoolean, bool(const std::string& name));
    MOCK_CONST_METHOD1(getBlob, iostream*(const std::string& name));
    MOCK_CONST_METHOD1(isNull, bool(const std::string& name));
    MOCK_METHOD0(rowsCount, int());
};

TEST(CreateTests, FunAddValue_NullResultSet) {
    MockResultSet* mockResultSet = new MockResultSet;
    using namespace winter::data::sql_impl;

    EXPECT_CALL(*mockResultSet, rowsCount()).WillOnce(testing::Return(1));
    EXPECT_CALL(*mockResultSet, getString("TestTable.hello")).WillOnce(testing::Return("world"));
    EXPECT_CALL(*mockResultSet, isNull("TestTable.hello")).WillOnce(testing::Return(false));

    Table table("TestTable", DatabaseType::kGeneric);

    Column col(table, "hello", FieldType::kString);

    PreparedStatement prepared;

    prepared.AddStatementValue(col);

    auto mockresult = std::shared_ptr<ResultSet>(mockResultSet);

    winter::data::sql_impl::mysql::ResultRow<ResultSet> result(prepared, mockresult);

    auto value1 = result["TestTable.hello"].as<string>();

    ASSERT_EQ(value1, "world");
}
