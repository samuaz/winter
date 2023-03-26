//
// Created by Samuel Azcona on 16/06/2020.
//

#ifndef WINTERCPP_WINTER_DATA_SQL_CLAUSE_JOIN_H
#define WINTERCPP_WINTER_DATA_SQL_CLAUSE_JOIN_H

#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause.h>
#include <wintercpp/data/sql/table/winter_data_sql_table.h>

namespace winter::data::sql_impl {

    enum class JoinType : int { DEFAULT = 0,
                                INNER,
                                LEFT,
                                RIGHT,
                                CROSS };

    class Join : public virtual Clause {
       public:
        explicit Join(std::shared_ptr<Table> table, JoinType type);
        explicit Join(std::shared_ptr<Table> table);
        PreparedStatement Prepare() override;

        std::string name() const override;

       private:
        std::shared_ptr<Table> table_;
        JoinType               type_;
        void                   GenerateStatement();
        std::string            GenerateType();
    };

}  // namespace winter::data::sql_impl

#endif  // WINTERCPP_WINTER_DATA_SQL_CLAUSE_JOIN_H
