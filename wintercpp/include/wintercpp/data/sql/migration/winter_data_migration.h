//
// Created by samuaz on 5/30/21.
//

#ifndef WINTERCPP_WINTER_DATA_MIGRATION_H
#define WINTERCPP_WINTER_DATA_MIGRATION_H

#include <wintercpp/data/sql/column/winter_data_sql_column.h>
#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_values.h>
#include <wintercpp/data/sql/statement/winter_data_sql_insert.h>
#include <wintercpp/data/sql/statement/winter_data_sql_query.h>
#include <wintercpp/data/sql/statement/winter_data_sql_select.h>
#include <wintercpp/data/sql/table/winter_data_sql_table.h>
#include <wintercpp/data/sql/transaction/winter_data_sql_transaction.h>

#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <optional>
#include <utility>
#include <vector>

#include "string"

namespace winter::data::sql_impl {
namespace fs = std::filesystem;
using namespace winter;
using namespace winter::data::sql_impl;

struct MigrationTable : public virtual Table {
  MigrationTable() :
      Table("db_migrations", DatabaseType::kGeneric) {}

  const Column id = Long("id");
  const Column name = String("name");
  const Column script = String("script");
  const Column hash = String("hash");
};

struct Migration {
  std::string name;
  std::string script;

  Migration(std::string name, std::string script) :
      name(std::move(name)),
      script(std::move(script)) {}

  [[nodiscard]] std::size_t
  Hash() const {
    // return h1 ^ (h2 << 1);
    return std::hash<std::string>()(script);
    ;
  }
};

template <typename TConnectionType, typename TTransactionType>
class DataBaseMigration {
 public:
  explicit DataBaseMigration(
      std::vector<Migration> migrations_sql,
      std::function<std::shared_ptr<TConnectionType>()> readWriteDb) :
      path_(std::nullopt),
      migrations_sql_(std::move(migrations_sql)),
      read_write_db_(std::move(readWriteDb)) {}
  DataBaseMigration(
      std::string path,
      std::function<std::shared_ptr<TConnectionType>()> readWriteDb) :
      path_(std::move(path)),
      read_write_db_(std::move(readWriteDb)) {}

  void execute();

 private:
  const std::optional<std::string> path_;
  const std::vector<Migration> migrations_sql_;

  std::function<std::shared_ptr<TConnectionType>()> read_write_db_;
  std::shared_ptr<MigrationTable> migration_table_ = std::make_shared<MigrationTable>();
  std::vector<fs::directory_entry> MigrationsFiles() const;
  std::vector<Migration> Migrations() const;

  Migration CreateMigrationTable() const;
};

#include "winter_data_migration.tpp"

}  // namespace winter::data::sql_impl
#endif	// WINTERCPP_WINTER_DATA_MIGRATION_H
