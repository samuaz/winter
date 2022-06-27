//
// Created by Samuel Azcona on 24/05/2020.
//

#ifndef WINTER_DATA_SQL_CLAUSE_FROM
#define WINTER_DATA_SQL_CLAUSE_FROM

#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause.h>
#include <wintercpp/data/sql/table/winter_data_sql_table.h>

#include <memory>
#include <vector>

namespace winter::data::sql_impl {

    class From : public virtual Clause {
       public:
        explicit From(std::vector<std::shared_ptr<Table>> tables);
        explicit From(const std::shared_ptr<Table> &table);
        PreparedStatement Prepare() override;

       private:
        std::vector<std::shared_ptr<Table>> tables_;
        std::vector<Column> columns_;
        void GenerateStatement();
    };

}  // namespace winter::data::sql_impl

#endif /* WINTER_DATA_SQL_CLAUSE_FROM */
