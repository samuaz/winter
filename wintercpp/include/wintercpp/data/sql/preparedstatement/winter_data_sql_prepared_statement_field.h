//
// Created by Samuel Azcona on 14/03/2020.
//

#ifndef WINTERCPP_DATA_SQL_PREPARED_STATEMENT_FIELD_H
#define WINTERCPP_DATA_SQL_PREPARED_STATEMENT_FIELD_H

#include <memory>
#include <optional>
#include <string>

#include "../field/winter_data_sql_field.h"
#include "winter_data_sql_abstract_prepared_statement_field.h"
#include "wintercpp/data/sql/field/winter_data_sql_data_type.h"

namespace winter::data::sql_impl {

    class PreparedStatementField :
        public virtual Field,
        public virtual AbstractPreparedStatementField {
       public:
        explicit PreparedStatementField(const DataType &value) :
            Field(value) {}

        PreparedStatementField(const std::string &name, const DataType &value) :
            Field(name, value), custom_value_(std::nullopt) {}

        PreparedStatementField(const std::string &name, const DataType &value, const std::optional<std::string> &custom_value) :
            Field(name, value),
            custom_value_(custom_value) {}

        PreparedStatementField(const PreparedStatementField &field) :
            Field(field), custom_value_(field.custom_value_) {}

        explicit PreparedStatementField(const PreparedStatementField *field) :
            Field(field),
            custom_value_(field->custom_value_) {}

        const std::optional<std::string> &custom_value() const override {
            return custom_value_;
        }

        void set_custom_value(const std::string &custom_value) {
            PreparedStatementField::custom_value_ = custom_value;
        }

        bool IsCustomValue() override {
            return custom_value_.has_value() && ! custom_value_.value().empty();
        }

       private:
        std::optional<std::string> custom_value_;
    };

    template<typename T>
    using QUERY_FIELD = std::shared_ptr<PreparedStatementField>;

}  // namespace winter::data::sql_impl

#endif  // WINTERCPP_DATA_SQL_PREPARED_STATEMENT_FIELD_H
