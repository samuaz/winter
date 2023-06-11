//
// Created by Samuel Azcona on 16/06/2020.
//

#ifndef WINTER_DATA_SQL_CLAUSE_SET
#define WINTER_DATA_SQL_CLAUSE_SET

#include <wintercpp/data/sql/column/winter_data_sql_column.h>
#include <wintercpp/data/sql/preparedstatement/winter_data_sql_prepared_statement_field.h>
#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause.h>

#include <queue>

namespace winter::data::sql_impl {

    class Set : public virtual Clause {
       public:
        explicit Set(const std::vector<std::shared_ptr<winter::data::sql_impl::AbstractPreparedStatementField>> &fields);

        std::string                                                                          Query() const override;
        std::vector<std::shared_ptr<winter::data::sql_impl::AbstractPreparedStatementField>> Fields() const override;

        template<typename T>
        static std::shared_ptr<PreparedStatementField<T>> Add(const Column &column, T value) {
            return std::make_shared<PreparedStatementField<T>>(column->name(),
                                                               value);
        }

        template<typename T>
        static std::shared_ptr<PreparedStatementField<T>> Add(
            const Column &column, T value, const std::string &custom_value_) {
            return std::make_shared<PreparedStatementField<T>>(
                column->name(), value, custom_value_);
        }

       private:
        std::vector<std::shared_ptr<AbstractPreparedStatementField>> fields_;
        const std::string                                            query_template_ = "SET $fields";
        const std::string                                            query_param_ = "$fields";
    };
}  // namespace winter::data::sql_impl

#endif /* WINTER_DATA_SQL_CLAUSE_SET */
