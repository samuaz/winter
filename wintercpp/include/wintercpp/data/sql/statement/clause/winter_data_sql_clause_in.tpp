namespace winter::data::sql_impl {

    template<typename T>
    In<T>::In(std::vector<T> values) :
        Clause("IN ($IN_VALUE)", "$IN_VALUE"), values_(std::move(values)) {}

    template<typename T>
    In<T>::In(const Select &select) :
        select_(select), has_clause_(true) {}

    template<typename T>
    PreparedStatement In<T>::Prepare() {
        if (has_clause_) {
            return Prepare(
                StatementType::kClause,
                winter::util::string::replace_value(
                    statement_template(),
                    param(),
                    select_.prepared_statement().statement_template()),
                select_.prepared_statement().values());
        } else {
            std::vector<std::shared_ptr<AbstractPreparedStatementField> > fields;
            for (const auto &value : values_) {
                fields.push_back(
                    std::make_shared<PreparedStatementField<T> >(value));
            }
            return Prepare(StatementType::kClause,
                           winter::util::string::replace_value(
                               statement_template(),
                               param(),
                               CommaSeparatedPlaceHolder(values_.size())),
                           fields);
        }
    }
}  // namespace winter::data::sql_impl