
using namespace winter::data::sql_impl;
using namespace winter::data::sql_impl::mysql;

template<typename TResultRow>
winter::data::sql_impl::mysql::Response<TResultRow>
winter::data::sql_impl::mysql::Response<TResultRow>::Error(
    const std::string &transactionId,
    StatementType type,
    const std::string &message) {
    return {transactionId, type, ResponseStatus::kError, message};
}

template<typename TResultRow>
winter::data::sql_impl::mysql::Response<TResultRow>
winter::data::sql_impl::mysql::Response<TResultRow>::Success(
    const std::string &transactionId,
    StatementType type,
    const std::vector<TResultRow> &result,
    int row_affected,
    const std::string &message) {
    return {transactionId,
            type,
            result,
            ResponseStatus::kSuccess,
            message,
            row_affected};
}

template<typename TResultRow>
winter::data::sql_impl::mysql::Response<TResultRow>::~Response() = default;
