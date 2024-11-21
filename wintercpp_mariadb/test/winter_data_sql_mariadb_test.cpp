//
// Created by samuaz on 3/10/21.
//

#include <gtest/gtest.h>
#include <unistd.h>
#include <wintercpp/winter.h>
#include <wintercpp/winter_mariadb_impl.h>
#include <wintercpp/winter_test_util.h>

#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include <thread>

#include "wintercpp/data/sql/statement/clause/winter_data_sql_clause_where.h"
#include "wintercpp/data/sql/statement/winter_data_sql_insert.h"
#include "wintercpp/data/sql/statement/winter_data_sql_select.h"

using MysqlPool = winter::data::mariadb::connection::Pool;
using MysqlConfig = winter::data::mariadb::connection::Config;
using MysqlConn = winter::data::mariadb::connection::Connection;
using MysqlTransaction = winter::data::mariadb::Transaction;
using namespace winter::test::docker::mariadb;
using namespace winter::data::sql_impl;
using namespace winter::data::mariadb;

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
    ASSERT_FALSE(conn->id().empty());
}

TEST_F(WithMariaDBDatabase, canQueryAndResultSet) {
    auto config = MysqlConfig("localhost",
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

    struct QueryTestTable : public UUIDTable {
        QueryTestTable() :
            UUIDTable("QueryTestTable", true, DatabaseType::kMysql) {}
        const Column col1 = String("col1");
    };

    Migration migration("QueryTestTable", "CREATE TABLE QueryTestTable (col1 VARCHAR(255))");

    DataBaseMigration<MysqlConn, MysqlTransaction> databaseMigration({migration}, MysqlPool::Connection);
    databaseMigration.execute();

    MysqlTransaction transaction(MysqlPool::Connection());

    QueryTestTable testTable;

    Insert() << Into(testTable) << Values({Values::Add(testTable.col1, "hola")}) >> transaction;

    auto result = Select() << From(testTable) << Where(Predicate::Make(testTable.col1, winter::data::sql_impl::Condition::EQ, "hola")) >> transaction;

    ASSERT_EQ(result.FirstOrNullopt()->Value<std::string>(testTable.col1), "hola");
}