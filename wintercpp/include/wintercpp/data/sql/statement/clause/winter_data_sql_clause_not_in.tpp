namespace winter::data::sql_impl {

    template<typename T>
    NotIn<T>::NotIn(const std::vector<T> &values) :
        values_(values) {}

    template<typename T>
    NotIn<T>::NotIn(const StatementValue &statement_value) :
        statement_value_(statement_value), has_clause_(true) {}

    template<typename T>
    std::vector<std::shared_ptr<winter::data::sql_impl::AbstractPreparedStatementField>> NotIn<T>::Fields() const {
        std::vector<std::shared_ptr<AbstractPreparedStatementField>> fields;
        for (const auto &value : values_) {
            fields.push_back(
                std::make_shared<PreparedStatementField<T>>(value));
        }
        return fields;
    };

    template<typename T>
    std::string NotIn<T>::Query() const {
        if (has_clause_) {
            std::string subQuery;
            auto       &statement_value = statement_value_;
            auto        clause_ptr = std::get_if<std::shared_ptr<Clause>>(&statement_value);
            if (clause_ptr) {
                subQuery = clause_ptr->get()->Query();
            } else {
                std::string       typeName = StatementValueType(statement_value.index());
                std::stringstream ss;
                ss << "invalid statement_value " << typeName << " not supported";
                throw ::winter::exception::WinterInternalException::Create(
                    __FILE__,
                    __FUNCTION__,
                    __LINE__,
                    ss.str());
            }
            return winter::util::string::replace_value(
                query_template_,
                query_param_,
                std::move(subQuery));
        }
        return winter::util::string::replace_value(
            query_template_,
            query_param_,
            CommaSeparatedPlaceHolder(values_.size()));
    }
}  // namespace winter::data::sql_impl