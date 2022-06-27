//
// Created by Samuel Azcona on 27/03/2020.
//

#ifndef WINTERCPP_WINTER_DATA_SQL_REPOSITORY_H
#define WINTERCPP_WINTER_DATA_SQL_REPOSITORY_H

#include <wintercpp/data/response/winter_data_response.h>
#include <wintercpp/data/winter_data_pageable.h>

#include <memory>
#include <string>
#include <vector>

namespace winter::data {

    using namespace winter::data::response;

    /**
     * @tparam TEntityClass is the entity class that represents and returns this
     * repository
     * @tparam TIDType is the datatype of id PK of the entity Table, example
     * UUID, Long, Int
     * @tparam TResultSetType is the ResultSetType returned by the mysql
     * database connection and transaction
     */
    template<typename TEntityClass, typename TIDType, typename TResultSetType>
    class Repository {
       public:
        /**
         * @brief Returns the entity by given id
         * @param TIDType
         * @return Response<TEntityClass> returns a winter::reponse of given
         * TEntityClass
         */
        virtual Response<TEntityClass> FindById(TIDType id) = 0;

        /**
         * @brief returns a paginated list of TEntityClass
         * @param page_size how many elements should a page contain
         * @param page_number the name of the page
         * @param order_by criteria to sort the page order
         */
        virtual Pageable<TEntityClass> Page(int page_size,
                                            int page_number,
                                            const std::string &order_by) = 0;

        /**
         * @brief Returns the total count of elements of given repository table
         * @return int
         */
        virtual int Count() = 0;

       protected:
        /**
         * @brief Implements the logic to persist the entity in the database
         * @param TEntityClass
         * @return Response<TEntityClass>
         */
        virtual Response<TEntityClass> Save(const TEntityClass &entity) = 0;

        /**
         * @brief Implements the logic to Generate TEntityClass from
         * TResultSetType, unpack the TResultSetType and call the CreateEntity
         * @param TResultSetType
         * @return Response<TEntityClass>
         */
        virtual Response<TEntityClass> Generate(const TResultSetType &) = 0;

        /**
         * @brief Implements the logic to Create TEntityClass from
         * TResultSetType
         * @param TEntityClass
         * @return Response<TEntityClass>
         */
        virtual std::optional<TEntityClass> CreateEntity(
            const TResultSetType &) = 0;

        /**
         * @brief Returns a single TEntityClass from TResultSetType, if there is
         * a list return the first one
         * @param TResultSetType
         * @return Response<TEntityClass>
         */
        virtual Response<TEntityClass> Single(const TResultSetType &) = 0;

        /**
         * @brief Returns a vector of TEntityClass from TResultSetType, if there
         * is not results will return empty vector
         * @param TResultSetType
         * @return Response<TEntityClass>
         */
        virtual std::vector<TEntityClass> All(const TResultSetType &) = 0;
    };

}  // namespace winter::data

#endif  // WINTERCPP_WINTER_DATA_SQL_REPOSITORY_H
