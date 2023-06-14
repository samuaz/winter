//
// Created by Samuel Azcona on 14/04/2020.
//

#ifndef WINTER_DATA_SQL_REPOSITORY_UTILS
#define WINTER_DATA_SQL_REPOSITORY_UTILS

//#include <mysql/jdbc.h>
#include <wintercpp/data/repository/winter_data_repository.h>
#include <wintercpp/data/response/winter_data_response.h>
#include <wintercpp/data/sql/preparedstatement/winter_data_sql_prepared_statement.h>
#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_from.h>
#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_where.h>
#include <wintercpp/data/sql/statement/winter_data_sql_select.h>
#include <wintercpp/data/sql/table/winter_data_sql_table.h>
#include <wintercpp/data/sql/table/winter_data_sql_uuid_table.h>
#include <wintercpp/data/winter_data_pageable.h>
#include <wintercpp/exception/generic/winter_internal_exception.h>

#include <functional>
#include <memory>

#include "wintercpp/data/sql/statement/clause/winter_data_sql_clause_predicate.h"

namespace winter::data::sql_impl {

    using namespace winter::exception;

    template<typename TEntityClass,
             typename TIDType,
             typename TTransaction,
             typename TResultRow>
    inline TEntityClass FindById(
        const std::shared_ptr<Table>                        &table,
        TIDType                                              id,
        TTransaction                                        &transaction,
        std::function<TEntityClass(std::vector<TResultRow>)> entityGenerator) {
        if (table->tableType() == TableType::kTable) {
            auto message = "TABLE " + table->name() + " IS NOT ID BASE TABLE";
            return winter::data::Response<TEntityClass>(
                nullopt, ResponseStatus::kError, message);
        }
        return entityGenerator(SelectById(id).Execute(transaction));
    }

    template<typename TEntityClass,
             typename TIDType,
             typename TTransaction,
             typename TResultRow>
    std::vector<TEntityClass> FindAll(
        const std::shared_ptr<Table> &table,
        TTransaction                 &transaction,
        std::function<std::vector<TEntityClass>(std::vector<TResultRow>)>
            entityGenerator) {
        return entityGenerator(Select() << From(table) >> transaction);
    }

    template<typename TTransaction>
    inline int Count(const std::shared_ptr<Table> &table,
                     TTransaction                 &transaction) {
        auto res = Select("SELECT COUNT(*) AS Count FROM " + table->name())
                   >> transaction;
        if (res) {
            auto resultRow = res().front();
            return resultRow["Count"].template as<int>().Value();
        }
        return 0;
    }

    template<typename TEntityClass,
             typename TIDType,
             typename TTransaction,
             typename TResultRow>
    inline winter::data::Pageable<TEntityClass> Page(
        const std::shared_ptr<Table> &table,
        int                           page_size,
        int                           page_number,
        const std::string            &order_by,
        TTransaction                 &transaction,
        std::function<std::vector<TEntityClass>(std::vector<TResultRow>)>
            entityGenerator) {
        return winter::data::Pageable<TEntityClass>(
            page_size,
            page_number,
            Count(table, transaction),
            entityGenerator(Select {"SELECT * FROM " + table->name()
                                    + " ORDER BY " + order_by
                                    + " LIMIT ? OFFSET ?"}
                                .Value(page_size)
                                .Value(page_number)
                            >> transaction));
    }

    template<typename TEntityClass, typename TIDType>
    inline winter::data::sql_impl::Select SelectById(
        const std::shared_ptr<Table> &table, TIDType id) {
        if (table->tableType() == TableType::kTable) {
            throw WinterInternalException::Create(
                __FILE__,
                __FUNCTION__,
                __LINE__,
                "TABLE " + table->name() + " IS NOT ID BASE TABLE");
        }

        Select select;
        select << From(table);
        // todo: add suport for hex and unhex ond postgresql
        switch (table->tableType()) {
            case TableType::kUUID: {
                auto uuidTable = std::dynamic_pointer_cast<
                    winter::data::sql_impl::UUIDTable>(table);
                if (uuidTable->binary()) {
                    select << Where(Predicate::MakePredicate(
                        uuidTable->id(), Condition::EQ, id, "unhex(?)"));
                } else {
                    select << Where(Predicate::MakePredicate(
                        uuidTable->id(), Condition::EQ, id));
                }
                break;
            }
            default:
                throw WinterInternalException::Create(
                    __FILE__,
                    __FUNCTION__,
                    __LINE__,
                    "not yet support for different tables types than UUID");
        }

        return select;
    }

}  // namespace winter::data::sql_impl

#endif /* WINTER_DATA_SQL_REPOSITORY_UTILS */
