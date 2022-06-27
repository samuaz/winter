#include "wintercpp/data/response/winter_data_response_status.h"
namespace winter::data::response {

    template<typename T>
    Response<T> Response<T>::Error(const std::string &message) {
        return Response<T>(ResponseStatus::kError, message);
    }

    template<typename T>
    Response<T> Response<T>::Success(const std::optional<T> &entity,
                                     const std::string &message) {
        return Response<T>(entity, ResponseStatus::kSuccess, message);
    }

    template<typename T>
    bool Response<T>::IsSuccess() const {
        if (status_ == ResponseStatus::kError) { return false; }
        return true;
    }

    template<typename T>
    bool Response<T>::IsError() const {
        return ! IsSuccess();
    }
}  // namespace winter::data::response

// namespace winter::data