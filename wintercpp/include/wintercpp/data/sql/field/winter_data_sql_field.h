//
// Created by Samuel Azcona on 14/03/2020.
//

#ifndef WINTER_DATA_SQL_FIELD
#define WINTER_DATA_SQL_FIELD

#include <wintercpp/data/sql/field/winter_data_sql_abstract_field.h>
#include <wintercpp/data/sql/field/winter_data_sql_data_type.h>

namespace winter::data::sql_impl {

    class Field : public virtual AbstractField {
       public:
        explicit Field(const DataType& value) :
            value_(value) {
            //using T = std::decay_t<decltype(value)>;
            type_ = GetFieldType(value);
        }

        Field(const std::string& name, const DataType& value) :
            name_(name), value_(value) {
            //using T = std::decay_t<decltype(value)>;
            type_ = GetFieldType(value);
        }

        Field(const Field& field) :
            name_(field.name_), value_(field.value_), type_(field.type_) {}

        explicit Field(const Field* field) :
            name_(field->name_), value_(field->value_), type_(field->type_) {}

        const DataType& value() const;

        const FieldType& type() const override;

        const std::string& name() const override;

        void value(DataType value);

        ~Field() override = default;

       protected:
        std::string name_;
        DataType    value_;
        FieldType   type_;
    };

}  // namespace winter::data::sql_impl

#endif /* WINTER_DATA_SQL_FIELD */
