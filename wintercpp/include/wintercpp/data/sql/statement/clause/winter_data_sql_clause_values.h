//
// Created by Samuel Azcona on 07/06/2020.
//

#ifndef WINTER_DATA_SQL_CLAUSE_VALUES
#define WINTER_DATA_SQL_CLAUSE_VALUES

#include <wintercpp/data/sql/column/winter_data_sql_column.h>
#include <wintercpp/data/sql/preparedstatement/winter_data_sql_prepared_statement_field.h>
#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause.h>

#include <utility>
#include <vector>

namespace winter::data::sql_impl {

    class Values : public virtual Clause {
       public:
        explicit Values(
            std::vector<std::shared_ptr<AbstractPreparedStatementField> >
                fields);

        PreparedStatement Prepare() override;
        std::string       name() const override;

        template<typename T>
        static std::shared_ptr<PreparedStatementField<T> > Add(
            const Column &column, T value) {
            return std::make_shared<PreparedStatementField<T> >(column->name(),
                                                                value);
        }

        template<typename T>
        static std::shared_ptr<PreparedStatementField<T> > Add(
            const Column &column, T value, const std::string &custom_value) {
            return std::make_shared<PreparedStatementField<T> >(
                column->name(), value, custom_value);
        }

       private:
        std::vector<std::shared_ptr<AbstractPreparedStatementField> > _fields;
    };

}  // namespace winter::data::sql_impl

#endif /* WINTER_DATA_SQL_CLAUSE_VALUES */
