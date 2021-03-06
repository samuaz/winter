//
// Created by samuaz on 3/10/21.
//

#include <gtest/gtest.h>
#include <wintercpp/winter.h>
#include <wintercpp/winter_mariadb_impl.h>

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

TEST(configCreation, canCreateMariaDBConfig) {
    auto props = std::map<std::string, std::string> {};

    auto config = winter::data::mariadb::connection::Config("localhost",
                                                            3305,
                                                            "media_manager",
                                                            "media_manager",
                                                            "media_manager_db",
                                                            3600,
                                                            0,
                                                            props);

    ::sql::ConnectOptionsMap connectionProperties;
    connectionProperties["hostName"] = config.host();
    connectionProperties["user"] = config.user_name();
    connectionProperties["password"] = config.password();
    connectionProperties["schema"] = config.schema();
    connectionProperties["port"] = std::to_string(config.port());
    connectionProperties["OPT_RECONNECT"]
        = std::to_string(config.is_opt_reconnect());
    connectionProperties["OPT_CONNECT_TIMEOUT"]
        = std::to_string(config.opt_connect_timeout());

    std::string url = config.host() + ":" + std::to_string(config.port()) + "/"
                      + config.schema();

    auto conn = new winter::data::mariadb::connection::Connection(
        config.driver()->connect("jdbc:mariadb://" + url,
                                 connectionProperties));

    std::cout << conn->id() << std::endl;

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
}