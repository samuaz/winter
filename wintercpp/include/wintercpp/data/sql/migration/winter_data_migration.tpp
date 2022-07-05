
//
// Created by samuaz on 5/30/21.

#include <memory>

#include "wintercpp/data/response/winter_data_response_status.h"

template<typename TConnectionType, typename TTransactionType>
void DataBaseMigration<TConnectionType, TTransactionType>::execute() {
    TTransactionType transaction(read_write_db_());
    transaction.template Execute<void>([&](TTransactionType
                                           & transaction) -> auto {
        Query(StatementType::kCreate, CreateMigrationTable().script)
            >> transaction;
        for (const auto &migration : Migrations()) {
            auto response = Select() << From(migration_table_)
                                     << Where(Where::make_predicate(
                                            migration_table_->hash,
                                            Condition::EQ,
                                            std::to_string(migration.Hash())))
                            >> transaction;
            if (! response) {
                auto migrationResponse = (Query(StatementType::kCreate, migration.script)
                                          >> transaction);
                migrationResponse.template Then<void>(
                    [&](void) -> void {
                        Insert(migration_table_) << Values(
                            {Values::Add(migration_table_->name,
                                         migration.name),
                             Values::Add(migration_table_->script,
                                         migration.script),
                             Values::Add(migration_table_->hash,
                                         std::to_string(migration.Hash()))})
                            >> transaction;
                    },
                    [&](void) -> void {
                        std::cerr
                            << "EXITING,DB MIGRATION FAIL: " << migration.name
                            << std::endl;
                        exit(EXIT_FAILURE);
                    });
            }
        }
    });
}

template<typename TConnectionType, typename TTransactionType>
std::vector<fs::directory_entry>
DataBaseMigration<TConnectionType, TTransactionType>::MigrationsFiles() const {
    auto                             dir = fs::directory_iterator(path_.value());
    std::vector<fs::directory_entry> paths;
    if (dir->exists()) {
        for (const auto &entry : fs::directory_iterator(path_.value())) {
            paths.push_back(entry);
        }
    }

    std::sort(paths.begin(),
              paths.end(),
              [&](const fs::directory_entry &lhs,
                  const fs::directory_entry &rhs) -> bool {
                  return fs::path(lhs).filename() < fs::path(rhs).filename();
              });
    return paths;
}

template<typename TConnectionType, typename TTransactionType>
std::vector<Migration>
DataBaseMigration<TConnectionType, TTransactionType>::Migrations() const {
    if (path_) {
        std::vector<Migration> migrations;
        for (const auto &entry : MigrationsFiles()) {
            std::ifstream ifs(entry.path());
            std::string   name(fs::path(entry).filename());
            std::string   content((std::istreambuf_iterator<char>(ifs)),
                                (std::istreambuf_iterator<char>()));
            migrations.emplace_back(name, content);
        }
        return migrations;
    }

    return migrations_sql_;
}

template<typename TConnectionType, typename TTransactionType>
Migration DataBaseMigration<TConnectionType,
                            TTransactionType>::CreateMigrationTable() const {
    return Migration("db_migrations",
                     R"(
CREATE table IF NOT exists db_migrations
(
    id bigint NOT NULL AUTO_INCREMENT,
    name        varchar(255)                   not null unique,
    script      text                           not null,
    hash        varchar(255)                   not null unique,
    createdAt   timestamp         DEFAULT CURRENT_TIMESTAMP,
    updatedAt    timestamp DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    PRIMARY KEY (id)
);
)");
}
