namespace winter::data::sql {

template <typename T>
NotIn<T>::NotIn(std::vector<T> values) : Clause("NOT IN ($NOT_IN_VALUE)", "$NOT_IN_VALUE"),
					 values_(std::move(values)) {}

template <typename T>
NotIn<T>::NotIn(const Select &select) : select_(select), has_clause(true) {}

template <typename T>
PreparedStatement
NotIn<T>::Prepare() {
  if (has_clause) {
    return Prepare(
	StatementType::kClause,
	winter::util::string::replace_value(
	    statement_template(),
	    param(),
	    select_.prepared_statement().statement_template()),
	select_.prepared_statement().values());
  } else {
    std::deque<std::shared_ptr<AbstractPreparedStatementField> > fields;
    for (const auto &value : values_) {
      fields.push_back(std::make_shared<PreparedStatementField<T> >(value));
    }
    return Prepare(
	StatementType::kClause,
	winter::util::string::replace_value(
	    statement_template(),
	    param(),
	    winter::data::sql::CommaSeparatedPlaceHolder(values_.size())),
	fields);
  }
}
}  // namespace winter::data::sql