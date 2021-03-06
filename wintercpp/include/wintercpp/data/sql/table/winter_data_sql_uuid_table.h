//
// Created by Samuel Azcona on 14/03/2020.
//

#ifndef WINTER_DATA_SQL_UUID_TABLE
#define WINTER_DATA_SQL_UUID_TABLE

#include <wintercpp/data/sql/table/winter_data_sql_table.h>

namespace winter::data::sql_impl {

    class UUIDTable :
        public Table,
        public virtual AutoGeneratedTable<std::string> {
       public:
        UUIDTable(const std::string &name,
                  bool               binary,
                  DatabaseType       database_type);

        std::string GenerateId() const override;

        bool binary() const;

        const Column &id() const;

        ~UUIDTable() override = default;

       private:
        const Column id_;
        const bool   binary_;
    };

}  // namespace winter::data::sql_impl

#endif /* WINTER_DATA_SQL_UUID_TABLE */
