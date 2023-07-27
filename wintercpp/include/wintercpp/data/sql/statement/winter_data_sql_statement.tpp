//
// Created by Samuel Azcona on 14/03/2020.
//

//#include "wintercpp/data/sql/statement/winter_data_sql_statement.h"
#include "wintercpp/data/sql/field/winter_data_sql_data_type.h"
namespace winter::data::sql_impl {

    template<typename Children>
    Statement<Children>::Statement(std::string query) :
        statement_template_(std::move(query)), type_(StatementType::kNative) {}

    template<typename Children>
    Statement<Children>::Statement(std::string          statement_template,
                                   const StatementType &statement_type) :
        statement_template_(std::move(statement_template)),
        type_(statement_type) {
        prepared_statement_ = std::make_unique<PreparedStatement>(type_, "", transaction_id_);
    }

    template<typename Children>
    Statement<Children>::Statement(const Statement &statement) :
        statement_template_(statement.statement_template_),
        prepared_statement_(
            new PreparedStatement(*statement.prepared_statement_)),
        type_(statement.type_), transaction_id_(statement.transaction_id_) {}

    template<typename Children>
    StatementType Statement<Children>::type() {
        return type_;
    }

    template<typename Children>
    std::string Statement<Children>::transaction_id() {
        return transaction_id_;
    }

    /* template <typename Children>
    void Statement<Children>::set_transaction_id(const std::string
    &transaction_id) { transaction_id_ = transaction_id;
      prepared_statement_->set_id(transaction_id);
    };

    template <typename Children>
    Children &
    Statement<Children>::set_statement_template(const std::string
    &statement_template) {
      prepared_statement_->set_statement_template(statement_template);
      return This();
    }; */

    template<typename Children>
    Children &Statement<Children>::Value(const DataType &value) {
        prepared_statement_->AddValue(new PreparedStatementField(value));
        return This();
    };

    template<typename Children>
    Children &Statement<Children>::Value(const Column &row, const DataType &value) {
        prepared_statement_->AddValue(
            new PreparedStatementField(row->name(), value));
        return This();
    };

    template<typename Children>
    Children &Statement<Children>::Value(const Column      &row,
                                         const DataType    &value,
                                         const std::string &custom_value) {
        prepared_statement_->AddValue(
            new PreparedStatementField(row->name(), value, custom_value));
        return This();
    };

    template<typename Children>
    const PreparedStatement &Statement<Children>::prepared_statement() {
        BuildStatement();
        return *prepared_statement_;
    };

    template<typename Children>
    template<typename TRANSACTION>
    auto Statement<Children>::Execute(TRANSACTION &transaction) {
        return transaction.Execute(This());
    }

    template<typename Children>
    template<typename TRANSACTION>
    auto Statement<Children>::Execute(
        std::shared_ptr<TRANSACTION> &transaction) {
        return transaction->Execute(This());
    }

    template<typename Children>
    template<typename TRANSACTION>
    auto Statement<Children>::Execute(TRANSACTION *transaction) {
        return transaction->Execute(This());
    }

    template<typename Children>
    template<typename TRANSACTION>
    auto Statement<Children>::operator>>(TRANSACTION &transaction) {
        return Execute(transaction);
    }

    template<typename Children>
    template<typename TRANSACTION>
    auto Statement<Children>::operator>>(TRANSACTION *transaction) {
        return Execute(transaction);
    }

    template<typename Children>
    template<typename TRANSACTION>
    auto Statement<Children>::operator>>(
        std::shared_ptr<TRANSACTION> &transaction) {
        return Execute(transaction);
    }

    template<typename Children>
    template<typename CLAUSE>
    Children &Statement<Children>::AddClause(CLAUSE clause) {
        statement_template_.append(" ").append(clause.Query());
        prepared_statement_->AddAll(clause.Fields());
        if (prepared_statement_->statementValues().empty()) {
            // FIXME
            // prepared_statement_->AddStatementValue(preparedStatement.columns());
        }
        return This();
    }

    template<typename Children>
    template<typename CLAUSE>
    auto &Statement<Children>::operator<<(CLAUSE clause) {
        return AddClause(clause);
    }

    template<typename Children>
    Children &Statement<Children>::This() {
        return dynamic_cast<Children &>(*this);
    }

}  // namespace winter::data::sql_impl