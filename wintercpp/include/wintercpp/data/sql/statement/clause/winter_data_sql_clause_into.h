//
// Created by Samuel Azcona on 07/06/2020.
//

#ifndef WINTERCPP_WINTER_DATA_SQL_CLAUSE_INTO_H
#define WINTERCPP_WINTER_DATA_SQL_CLAUSE_INTO_H

#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause.h>
#include <wintercpp/data/sql/table/winter_data_sql_table.h>

namespace winter::data::sql_impl {
    class Into : public virtual Clause {
       public:
        explicit Into(std::shared_ptr<Table> table);
        PreparedStatement Prepare() override;

        std::string name() const override;

       private:
        std::shared_ptr<Table> table_;
        void                   GenerateStatement();
    };
}  // namespace winter::data::sql_impl

#endif  // WINTERCPP_WINTER_DATA_SQL_CLAUSE_INTO_H
