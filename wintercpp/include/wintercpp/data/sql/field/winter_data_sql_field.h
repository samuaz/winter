//
// Created by Samuel Azcona on 14/03/2020.
//

#ifndef WINTER_DATA_SQL_FIELD
#define WINTER_DATA_SQL_FIELD

#include <wintercpp/data/sql/field/winter_data_sql_data_type.h>
#include <wintercpp/data/sql/field/winter_data_sql_field_type.h>

namespace winter::data::sql_impl {

    /**
     * @brief Field class
     * This class represents a field in a table.
     * It contains the name of the field, the value and the type.
     * It inherits from AbstractField.
     * @tparam DataType
     * @tparam FieldType
     * @tparam name
     */
    class Field {
       public:
        explicit Field(const DataType& value) :
            value_(value) {
            type_ = GetFieldType(value);
        }

        Field(const std::string& name, const DataType& value) :
            name_(name), value_(value) {
            type_ = GetFieldType(value);
        }

        Field(const Field& field) :
            name_(field.name_), value_(field.value_), type_(field.type_) {}

        explicit Field(const Field* field) :
            name_(field->name_), value_(field->value_), type_(field->type_) {}

        /**
         * @brief  returns the value of the field.
         *
         * @return const DataType&
         */
        const DataType& value() const;

        /**
         * @brief Returns the type of the field.
         *
         * @return const FieldType&
         */
        const FieldType& type() const;

        /**
         * @brief Returns the name of the field.
         *
         * @return const std::string&
         */
        const std::string& name() const;

        /**
         * @brief Sets the value of the field.
         *
         * @param value
         */
        void value(DataType value);

        //~Field() = default;

       protected:
        std::string name_;
        DataType    value_;
        FieldType   type_;
    };

}  // namespace winter::data::sql_impl

#endif /* WINTER_DATA_SQL_FIELD */
