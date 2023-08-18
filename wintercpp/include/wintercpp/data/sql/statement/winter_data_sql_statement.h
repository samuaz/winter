//
// Created by Samuel Azcona on 14/03/2020.
//

#ifndef WINTER_DATA_SQL_STATEMENT
#define WINTER_DATA_SQL_STATEMENT

#include <wintercpp/data/sql/preparedstatement/winter_data_sql_prepared_statement.h>
#include <wintercpp/data/sql/preparedstatement/winter_data_sql_prepared_statement_field.h>

#include <string>
#include <utility>

#include "wintercpp/data/sql/field/winter_data_sql_data_type.h"

namespace winter::data::sql_impl {

    class IStatement {
       public:
        virtual StatementType type() = 0;

        virtual const PreparedStatement &prepared_statement() = 0;

        virtual std::string transaction_id() = 0;

        // virtual void set_transaction_id(const std::string &id) = 0;

       protected:
        virtual void BuildStatement() = 0;
    };

    template<typename Children>
    class Statement : public virtual IStatement {
       public:
        explicit Statement(const std::string &query, const std::string &transaction_id = winter::random::uuid());
        Statement(const std::string &statement_template, const StatementType &statement_type, const std::string &transaction_id = winter::random::uuid());
        Statement(const Statement &statement);

        Statement    &operator=(const Statement &) = default;
        StatementType type() override;

        std::string transaction_id() override;
        /*
        void set_transaction_id(const std::string &transaction_id) override;

        Children &set_statement_template(const std::string &statement_template);
      */

        Children &Value(const DataType &value);

        Children &Value(const Column &row, const DataType &value);

        Children &Value(const Column      &row,
                        const DataType    &value,
                        const std::string &custom_value);

        const PreparedStatement &prepared_statement() override;

        template<typename TRANSACTION>
        auto Execute(TRANSACTION &transaction);

        template<typename TRANSACTION>
        auto Execute(std::shared_ptr<TRANSACTION> &transaction);

        template<typename TRANSACTION>
        auto Execute(TRANSACTION *transaction);

        template<typename TRANSACTION>
        auto operator>>(TRANSACTION &transaction);

        template<typename TRANSACTION>
        auto operator>>(TRANSACTION *transaction);

        template<typename TRANSACTION>
        auto operator>>(std::shared_ptr<TRANSACTION> &transaction);

        template<typename CLAUSE>
        Children &AddClause(CLAUSE clause);

        template<typename CLAUSE>
        auto &operator<<(CLAUSE clause);

        virtual ~Statement();

       protected:
        std::string         statement_template_;
        PreparedStatement   prepared_statement_;
        const StatementType type_ {};

       private:
        const std::string transaction_id_;
        Children         &This();
    };

    template<typename Children>
    Statement<Children>::~Statement() = default;

}  // namespace winter::data::sql_impl

#include "winter_data_sql_statement.tpp"

#endif /* WINTER_DATA_SQL_STATEMENT */
