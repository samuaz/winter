//
// Created by samuaz on 3/10/21.
//

#include <gtest/gtest.h>
#include <wintercpp/winter.h>
#include <wintercpp/winter_mariadb_impl.h>
#include <wintercpp/winter_test_util.h>

#include <iostream>
#include <memory>
#include <optional>

#include "gmock/gmock-matchers.h"
#include "gmock/gmock-more-matchers.h"
#include "wintercpp/data/sql/column/winter_data_sql_column.h"
#include "wintercpp/data/sql/field/winter_data_sql_field_type.h"
#include "wintercpp/data/sql/mariadb/connection/winter_data_sql_mariadb_impl_connection_config.h"
#include "wintercpp/data/sql/preparedstatement/winter_data_sql_prepared_statement.h"
#include "wintercpp/data/sql/statement/clause/winter_data_sql_clause_or.h"
#include "wintercpp/data/sql/statement/clause/winter_data_sql_clause_where.h"
#include "wintercpp/data/sql/table/winter_data_sql_table.h"

using MysqlPool = winter::data::mariadb::connection::Pool;
using MysqlConfig = winter::data::mariadb::connection::Config;
using namespace winter::test::docker::mariadb;

TEST_F(WithMariaDBDatabase, canConnectToMariaDB) {
    auto config = winter::data::mariadb::connection::Config("localhost",
                                                            portNumber,
                                                            MARIA_DB_USER,
                                                            MARIA_DB_PASSWORD,
                                                            MARIA_DB_SCHEMA_NAME,
                                                            false,
                                                            3600,
                                                            false,
                                                            {});

    MysqlPool::Init(
        winter::descriptor::PoolDescriptor(
            "mysql",
            1,
            10,
            5000,
            10,
            true),
        config);

    auto conn = MysqlPool::Connection();
    ASSERT_FALSE(conn->id().empty());  // asegura que el string no esté vacío
}

/*
    using namespace winter::data::sql_impl;

    auto table = Table("db_migrations", TableType::kTable, DatabaseType::kMysql);

    auto statement = PreparedStatement(StatementType::kNative, "SELECT * FROM db_migrations")
                         .AddColumn(Column(table, "name", FieldType::kString))
                         .AddColumn(Column(table, "name", FieldType::kString));

    auto response = conn->Execute(statement);

    std::cout << "el status de la query es"
              << response.message()
              << response.message()
              << "el status de la query es"
              << "el status de la query es"
              << "el status de la query es"
              << std::endl;

    auto results = response.result();

    response.ReturnOrThrow();

    if (results.has_value()) {
        std::cout << "el result tiene un valor" << std::endl;
        const auto &value = results.value();
        for (auto &r : value) {
            std::cout << r["name"].as<std::string>() << std::endl;
        }
    }

    delete conn;

*/