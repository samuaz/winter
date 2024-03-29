//
// Created by samuaz on 6/1/22.
//

#ifndef WINTERCPP_WINTER_DATA_SQL_MYSQL_IMPL_CONNECTION_CONFIG_H
#define WINTERCPP_WINTER_DATA_SQL_MYSQL_IMPL_CONNECTION_CONFIG_H
#include <mysql/jdbc.h>
#include <wintercpp/winter_mysql_core.h>

namespace winter::data::mysql::connection {

    class Config :
        public virtual winter::data::sql_impl::mysql::connection::Config<
            ::sql::Driver*> {
       public:
        Config(const string&               host,
               int                         port,
               const string&               userName,
               const string&               password,
               const string&               schema,
               bool                        optReconnect,
               int                         optConnectTimeout,
               const ConnectionProperties& otherProperties) :
            winter::data::sql_impl::mysql::connection::Config<::sql::Driver*>(
                []() -> ::sql::Driver* {
                    return ::sql::mysql::get_driver_instance();
                },
                host,
                port,
                userName,
                password,
                schema,
                optReconnect,
                optConnectTimeout,
                true,
                otherProperties) {}
    };
}  // namespace winter::data::mysql::connection
#endif  // WINTERCPP_WINTER_DATA_SQL_MYSQL_IMPL_CONNECTION_CONFIG_H
