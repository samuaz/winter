//
// Created by Samuel Azcona on 14/03/2020.
//

#ifndef WINTERCPP_DATA_SQL_PREPARED_STATEMENT_H
#define WINTERCPP_DATA_SQL_PREPARED_STATEMENT_H

#include <wintercpp/data/sql/column/winter_data_sql_column.h>
#include <wintercpp/data/sql/preparedstatement/winter_data_sql_abstract_prepared_statement_field.h>
#include <wintercpp/data/sql/statement/winter_data_sql_statement_type.h>
#include <wintercpp/util/winter_random.h>

#include <memory>
#include <set>
#include <string>
#include <vector>

#include "wintercpp/data/sql/field/winter_data_sql_field_type.h"
#include "wintercpp/exception/generic/winter_internal_exception.h"

namespace winter::data::sql_impl {

    class IStatementValue {
       public:
        virtual std::string        name() = 0;
        virtual const std::string &query() const = 0;
        virtual FieldType          fieldType() = 0;
    };

    typedef std::variant<Column, std::shared_ptr<IStatementValue>> StatementValues;

    class PreparedStatement {
       public:
        PreparedStatement() = default;

        PreparedStatement(const StatementType &statement_type,
                          std::string          statement_template,
                          std::string          id = winter::random::uuid());

        PreparedStatement(const StatementType         &statement_type,
                          std::string                  statement_template,
                          std::vector<StatementValues> columns_,
                          std::string                  id = winter::random::uuid());

        PreparedStatement(
            const StatementType                                         &statement_type,
            std::string                                                  query,
            std::vector<std::shared_ptr<AbstractPreparedStatementField>> values,
            std::string                                                  id = winter::random::uuid());

        PreparedStatement(
            const StatementType                                   &statement_type,
            std::string                                            statement_template,
            const std::shared_ptr<AbstractPreparedStatementField> &value,
            std::string                                            id = winter::random::uuid());

        const std::string &id() const;

        void set_id(const std::string &id);

        const std::vector<std::shared_ptr<AbstractPreparedStatementField>>
            &values() const;

        void set_values(
            const std::vector<std::shared_ptr<AbstractPreparedStatementField>>
                &values);

        PreparedStatement &AddValue(AbstractPreparedStatementField *field);

        PreparedStatement &AddValue(
            const std::shared_ptr<AbstractPreparedStatementField> &field);

        template<typename T>
        void AddAll(const T &fields) {
            values_.insert(values_.end(), fields.begin(), fields.end());
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

        const AbstractPreparedStatementField &FindByName(
            const std::string &name);

        std::shared_ptr<AbstractPreparedStatementField> FindByField(
            const std::string &name);

        bool FieldIsPresent(const std::string &name);

        int SearchFieldIndex(const std::string &name);

        const std::vector<StatementValues> &columns() const;

        void columns(std::vector<StatementValues> columns);

        PreparedStatement &AddColumn(const StatementValues &column);

        PreparedStatement &AddColumn(const std::vector<StatementValues> &columns);

        virtual ~PreparedStatement() = default;

       private:
        std::string   id_ {};
        StatementType type_ {};
        // std::shared_ptr<AbstractPreparedStatementField> _entityId;
        std::string                                                  statement_template_;
        std::vector<StatementValues>                                 columns_;
        std::vector<std::shared_ptr<AbstractPreparedStatementField>> values_;
        std::vector<std::shared_ptr<AbstractPreparedStatementField>>::iterator
        FindValue(const std::string &name);
    };
}  // namespace winter::data::sql_impl

#endif  // WINTERCPP_WINTER_DATA_SQL_PREPARED_STATEMENT_H
