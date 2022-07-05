//
// Created by Samuel Azcona on 21/05/2020.
//

#ifndef WINTERCPP_WINTER_DATA_SQL_CLAUSE_OPERATOR_H
#define WINTERCPP_WINTER_DATA_SQL_CLAUSE_OPERATOR_H

#include <string>

namespace winter::data::sql_impl {

    enum class Condition : int {
        NONE,
        EQ,
        NOT_EQ,
        LESS,
        LESS_EQ,
        GREATER,
        GREATER_EQ,
        IN,
        NOT,
        NOT_IN,
        BETWEEN,
        IS,
        LIKE,
        EXISTS,
        NOT_NULL,
        IS_NULL,
        IS_NOT_NULL
    };

    template<Condition>
    struct GetCondition {
        static std::string Get();
    };

    template<>
    struct GetCondition<Condition::EQ> {
        static std::string Get();
    };

    template<>
    struct GetCondition<Condition::NOT_EQ> {
        static std::string Get();
    };

    template<>
    struct GetCondition<Condition::LESS> {
        static std::string Get();
    };

    template<>
    struct GetCondition<Condition::LESS_EQ> {
        static std::string Get();
    };

    template<>
    struct GetCondition<Condition::GREATER> {
        static std::string Get();
    };

    template<>
    struct GetCondition<Condition::GREATER_EQ> {
        static std::string Get();
    };

    template<>
    struct GetCondition<Condition::IN> {
        static std::string Get();
    };

    template<>
    struct GetCondition<Condition::NOT> {
        static std::string Get();
    };

    template<>
    struct GetCondition<Condition::NOT_IN> {
        static std::string Get();
    };

    template<>
    struct GetCondition<Condition::BETWEEN> {
        static std::string Get();
    };

    template<>
    struct GetCondition<Condition::IS> {
        static std::string Get();
    };

    template<>
    struct GetCondition<Condition::LIKE> {
        static std::string Get();
    };

    template<>
    struct GetCondition<Condition::EXISTS> {
        static std::string Get();
    };

    template<>
    struct GetCondition<Condition::NONE> {
        static std::string Get();
    };

    template<>
    struct GetCondition<Condition::NOT_NULL> {
        static std::string Get();
    };

    template<>
    struct GetCondition<Condition::IS_NULL> {
        static std::string Get();
    };

    template<>
    struct GetCondition<Condition::IS_NOT_NULL> {
        static std::string Get();
    };

    std::string condition(Condition condition);

}  // namespace winter::data::sql_impl

#endif  // WINTERCPP_WINTER_DATA_SQL_CLAUSE_OPERATOR_H
