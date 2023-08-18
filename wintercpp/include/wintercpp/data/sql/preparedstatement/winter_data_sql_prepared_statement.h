//
// Created by Samuel Azcona on 14/03/2020.
//

#ifndef WINTERCPP_DATA_SQL_PREPARED_STATEMENT_H
#define WINTERCPP_DATA_SQL_PREPARED_STATEMENT_H

#include <wintercpp/data/sql/column/winter_data_sql_column.h>
#include <wintercpp/data/sql/field/winter_data_sql_field_type.h>
#include <wintercpp/data/sql/preparedstatement/winter_data_sql_prepared_statement_field.h>
#include <wintercpp/data/sql/statement/winter_data_sql_statement_type.h>
#include <wintercpp/data/sql/statement/winter_data_sql_statement_values.h>
#include <wintercpp/exception/generic/winter_exception.h>
#include <wintercpp/exception/generic/winter_internal_exception.h>
#include <wintercpp/util/winter_random.h>

#include <memory>
#include <set>
#include <string>
#include <vector>
namespace winter::data::sql_impl {

    class PreparedStatement {
       public:
        PreparedStatement() = default;

        PreparedStatement(const StatementType &statement_type,
                          const std::string   &statement_template,
                          const std::string   &id = winter::random::uuid());

        PreparedStatement(const StatementType               &statement_type,
                          const std::string                 &statement_template,
                          const std::vector<StatementValue> &fields,
                          const std::string                 &id = winter::random::uuid());

        PreparedStatement(
            const StatementType                       &statement_type,
            const std::string                         &query,
            const std::vector<PreparedStatementField> &fields,
            const std::string                         &id = winter::random::uuid());

        PreparedStatement(
            const StatementType          &statement_type,
            const std::string            &statement_template,
            const PreparedStatementField &field,
            const std::string            &id = winter::random::uuid());

        const std::string &id() const;

        void set_id(const std::string &id);

        const std::vector<PreparedStatementField>
            &values() const;

        void set_values(
            const std::vector<PreparedStatementField>
                &values);

        PreparedStatement &AddValue(const PreparedStatementField &field);

        template<typename T>
        void AddAll(const T &fields) {
            fields_.insert(fields_.end(), fields.begin(), fields.end());
        }

        const std::string &statement_template() const;

        void set_statement_template(const std::string &statement_template);

        const StatementType &type() const;

        void set_type(const StatementType &statement_type);

        bool operator==(const PreparedStatement &rhs) const;

        bool operator!=(const PreparedStatement &rhs) const;

        // void entityId(AbstractPreparedStatementField *field);

        // void entityId(std::shared_ptr<AbstractPreparedStatementField> field);

        // const AbstractPreparedStatementField &entityId() const;

        const PreparedStatementField &FindByName(
            const std::string &name);

        PreparedStatementField FindByField(
            const std::string &name);

        bool FieldIsPresent(const std::string &name);

        int SearchFieldIndex(const std::string &name);

        const std::vector<StatementValue> &statementValues() const;

        void statementValues(std::vector<StatementValue> statement_value);

        PreparedStatement &AddStatementValue(const StatementValue &statement_value);

        PreparedStatement &AddStatementValue(const std::vector<StatementValue> &statement_values);

        virtual ~PreparedStatement() = default;

       private:
        std::string   id_ {};
        StatementType type_ {};
        // std::shared_ptr<AbstractPreparedStatementField> _entityId;
        std::string                         statement_template_ {};
        std::vector<StatementValue>         statement_values_;
        std::vector<PreparedStatementField> fields_;

        std::vector<PreparedStatementField>::iterator
        FindValue(const std::string &name);
    };
}  // namespace winter::data::sql_impl

#endif  // WINTERCPP_WINTER_DATA_SQL_PREPARED_STATEMENT_H
