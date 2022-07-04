//
// Created by samuaz on 5/31/21.
//

using namespace winter::data::sql_impl::mysql::connection;

template<typename TDriver>
Config<TDriver>::Config(std::function<TDriver()> driver,
                        std::string              host,
                        int                      port,
                        std::string              user_name,
                        std::string              password,
                        std::string              schema,
                        bool                     opt_reconnect,
                        int                      opt_connect_timeout,
                        ConnectionProperties     other_properties) :
    _driver(driver()),
    _host(std::move(host)), _port(port), _user_name(std::move(user_name)),
    _password(std::move(password)), _schema(std::move(schema)),
    _opt_reconnect(opt_reconnect), _opt_connect_timeout(opt_connect_timeout),
    _other_properties(std::move(other_properties)) {}

template<typename TDriver>
const std::string& Config<TDriver>::host() const {
    return _host;
}

template<typename TDriver>
int Config<TDriver>::port() const {
    return _port;
}

template<typename TDriver>
const std::string& Config<TDriver>::user_name() const {
    return _user_name;
}

template<typename TDriver>
const std::string& Config<TDriver>::password() const {
    return _password;
}

template<typename TDriver>
const std::string& Config<TDriver>::schema() const {
    return _schema;
}

template<typename TDriver>
bool Config<TDriver>::is_opt_reconnect() const {
    return _opt_reconnect;
}

template<typename TDriver>
int Config<TDriver>::opt_connect_timeout() const {
    return _opt_connect_timeout;
}

template<typename TDriver>
const ConnectionProperties& Config<TDriver>::properties() const {
    return _other_properties;
}

template<typename TDriver>
const TDriver& Config<TDriver>::driver() const {
    return _driver;
}