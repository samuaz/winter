//
// Created by samuaz on 5/30/21.
//

#ifndef WINTERCPP_WINTER_DATA_MIGRATION_H
#define WINTERCPP_WINTER_DATA_MIGRATION_H

#include <openssl/sha.h>
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
#include <string>
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
        const Column script_name = String("name");
        const Column script = String("script");
        const Column hash = String("hash");
    };

    struct Migration {
        std::string name;
        std::string script;

        Migration(std::string name, std::string script) :
            name(std::move(name)), script(std::move(script)) {}

        std::string HASH_256() const {
            unsigned char hash[SHA256_DIGEST_LENGTH];
            SHA256_CTX    sha256;
            SHA256_Init(&sha256);
            SHA256_Update(&sha256, script.c_str(), script.size());
            SHA256_Final(hash, &sha256);
            stringstream ss;
            for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
                ss << hex << setw(2) << setfill('0') << (int) hash[i];
            }
            return ss.str();
        };

        /*         [[nodiscard]] std::string Hash() const {
                    const unsigned char *str = reinterpret_cast<unsigned char *>(const_cast<char *>(script.c_str()));
                    unsigned char        hash[SHA_DIGEST_LENGTH];  // == 20
                    SHA1(str, sizeof(str) - 1, hash);
                    std::ostringstream s;

                    s << std::hex;

                    for (int i = 0; i < SHA_DIGEST_LENGTH; i++) {
                        s << std::hex << std::setfill('0') << std::setw(2) << (unsigned int) hash[i];
                    }
                    // return h1 ^ (h2 << 1);
                    // return std::hash<std::string>()(script);
                    return s.str();
                    ;
                } */
    };

    template<typename TConnectionType, typename TTransactionType>
    class DataBaseMigration {
       public:
        explicit DataBaseMigration(
            std::vector<Migration>                            migrations_sql,
            std::function<std::shared_ptr<TConnectionType>()> readWriteDb) :
            path_(std::nullopt),
            migrations_sql_(std::move(migrations_sql)),
            read_write_db_(std::move(readWriteDb)) {}
        DataBaseMigration(
            std::string                                       path,
            std::function<std::shared_ptr<TConnectionType>()> readWriteDb) :
            path_(std::move(path)),
            read_write_db_(std::move(readWriteDb)) {}

        void execute();

       private:
        const std::optional<std::string> path_;
        const std::vector<Migration>     migrations_sql_;

        std::function<std::shared_ptr<TConnectionType>()> read_write_db_;
        std::shared_ptr<MigrationTable>                   migration_table_ = std::make_shared<MigrationTable>();
        std::vector<fs::directory_entry>                  MigrationsFiles() const;
        std::vector<Migration>                            Migrations() const;

        Migration CreateMigrationTable() const;
    };

#include "winter_data_migration.tpp"

}  // namespace winter::data::sql_impl
#endif  // WINTERCPP_WINTER_DATA_MIGRATION_H
