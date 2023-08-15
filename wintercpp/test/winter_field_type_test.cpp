//
// Created by samuaz on 3/10/21.
//

#include <wintercpp/winter.h>

#include <cstddef>
#include <set>

#include "gtest/gtest.h"
#include "wintercpp/data/sql/column/winter_data_sql_column.h"
#include "wintercpp/data/sql/field/winter_data_sql_field_type.h"
#include "wintercpp/data/sql/function/winter_data_sql_function_min.h"
#include "wintercpp/data/sql/table/winter_data_sql_table.h"


using namespace winter::data::sql_impl;

struct MyCustomType {
    int value;
};

TEST(GetFieldTypeTest, PrimitiveTypes) {
    // Testing primitive types
    ASSERT_EQ(GetFieldType<uint8_t>(), FieldType::kUchar);
    ASSERT_EQ(GetFieldType<uint16_t>(), FieldType::kUshort);
    ASSERT_EQ(GetFieldType<uint32_t>(), FieldType::KUint);
    ASSERT_EQ(GetFieldType<uint64_t>(), FieldType::kBigInt);
    ASSERT_EQ(GetFieldType<int8_t>(), FieldType::kSchar);
    ASSERT_EQ(GetFieldType<int16_t>(), FieldType::KShort);
    ASSERT_EQ(GetFieldType<int32_t>(), FieldType::kInt);
    ASSERT_EQ(GetFieldType<int64_t>(), FieldType::kLong);
    ASSERT_EQ(GetFieldType<char>(), FieldType::kChar);
    ASSERT_EQ(GetFieldType<short>(), FieldType::KShort);
    ASSERT_EQ(GetFieldType<long>(), FieldType::kLong);
    ASSERT_EQ(GetFieldType<long double>(), FieldType::KDecimal);
    ASSERT_EQ(GetFieldType<double>(), FieldType::kDouble);
    ASSERT_EQ(GetFieldType<float>(), FieldType::kFloat);
    ASSERT_EQ(GetFieldType<bool>(), FieldType::kBoolean);
}

TEST(GetFieldTypeTest, OtherTypes) {
    // Testing other types
    ASSERT_EQ(GetFieldType<std::string>(), FieldType::kString);
    ASSERT_EQ(GetFieldType<std::istream*>(), FieldType::kBlob);
    ASSERT_EQ(GetFieldType<nullptr_t>(), FieldType::kNull);
    ASSERT_EQ(GetFieldType<std::nullopt_t>(), FieldType::kNull);
}

TEST(GetFieldTypeTest, UnsupportedType) {
    // Testing unsupported type
    EXPECT_THROW(GetFieldType<MyCustomType>(), winter::exception::WinterInternalException);
}
