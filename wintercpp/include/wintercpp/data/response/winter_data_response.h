//
// Created by Samuel Azcona on 24/06/2020.
//

#ifndef WINTER_DATA_RESPONSE
#define WINTER_DATA_RESPONSE

#include <wintercpp/data/response/winter_data_response_status.h>
#include <wintercpp/template/winter_response_template.h>

#include <optional>
#include <string>

namespace winter::data::response {

    /**
     * This class represents a response that can or not contain the wrapper an
     * optional object T, also implements a useful helper Error or Success
     * creator
     *
     * @tparam T Entity wrapper object
     */
    template<typename T>
    class Response final :
        public virtual winter::templates::
            Response<Response<T>, T, ResponseStatus> {
       public:
        using winter::templates::Response<winter::data::response::Response<T>,
                                          T,
                                          ResponseStatus>::Response;

        /**
         * @brief Create an Error Response, wrapper object is empty optional
         * object
         * @param string error message
         * @return Response<T>
         */
        static Response<T> Error(const std::string &message);

        /**
         * @brief Create a SUCCESS Response, wrapper object is mandatory
         * @param string error message
         * @return Response<T>
         */
        static Response<T> Success(const std::optional<T> &entity,
                                   const std::string      &message = "Success");

        /**
         * @brief Boolean that Returns true if object is present
         * @return bool
         */
        bool IsSuccess() const override;

        /**
         * @brief Boolean that Returns true if object is not present
         * @return bool
         */
        bool IsError() const override;

       private:
        using winter::templates::Response<winter::data::response::Response<T>,
                                          T,
                                          ResponseStatus>::status_;
        using winter::templates::Response<winter::data::response::Response<T>,
                                          T,
                                          ResponseStatus>::message_;
        using winter::templates::Response<winter::data::response::Response<T>,
                                          T,
                                          ResponseStatus>::result_;
    };
}  // namespace winter::data::response

#include "winter_data_response.tpp"

#endif /* WINTER_DATA_RESPONSE */
