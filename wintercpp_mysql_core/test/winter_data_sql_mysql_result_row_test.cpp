//
// Created by samuaz on 3/10/21.
//

#include <_types/_uint64_t.h>
#include <sys/_types/_int64_t.h>
#include <sys/types.h>
#include <wintercpp/winter.h>
#include <wintercpp/winter_mysql_core.h>

#include <cstddef>
#include <istream>
#include <memory>
#include <set>
#include <string>

#include "gtest/gtest.h"
#include <gmock/gmock.h>
#include "wintercpp/data/sql/preparedstatement/winter_data_sql_prepared_statement.h"

struct ResultSet {
    virtual std::string getString(const std::string& name) const = 0;
    virtual int getInt(const std::string& name) const = 0;
    virtual uint getUInt(const std::string& name) const = 0;
    virtual int64_t getInt64(const std::string& name) const = 0;
    virtual uint64_t getUInt64(const std::string& name) const = 0;
    virtual double getDouble(const std::string& name) const = 0;
    virtual bool getBoolean(const std::string& name)const  = 0;
    virtual iostream* getBlob(const std::string& name) const = 0;
    virtual bool isNull(const std::string& name) const = 0;
    virtual int rowsCount() = 0;
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


class CreateTests : public ::testing::Test {
   protected:
    void SetUp() override {
        // Set up any common objects or resources here
        // (e.g., create mock objects or initialize variables)
    }

    void TearDown() override {
        // Clean up any common objects or resources here
        // (e.g., delete mock objects or reset variables)
    }
};

TEST_F(CreateTests, FunAddValue_NullResultSet) {

    MockResultSet mockResultSet;
    EXPECT_CALL(mockResultSet, getString("hello"))
        .WillOnce(testing::Return("world"));

    winter::data::sql_impl::PreparedStatement prepared;
    auto mockresult = std::make_shared<ResultSet>(new MockResultSet());

    winter::data::sql_impl::mysql::ResultRow<ResultSet> result(prepared, mockresult);

    auto value = result.Value<std::string>("hello").Value();

    ASSERT_EQ(value, "world");
}
