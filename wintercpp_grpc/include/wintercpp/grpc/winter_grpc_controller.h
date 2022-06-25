//
// Created by AZCONA VARGAS, SAMUEL EDUARDO [AG-Contractor/5000] on 2019-10-04.
//

#ifndef WINTER_GRPC_CONTROLLER_TEMPLATE_H
#define WINTER_GRPC_CONTROLLER_TEMPLATE_H

#include <grpcpp/grpcpp.h>
#include <wintercpp/data/response/winter_data_response.h>

namespace winter {

// CREATE GRPC CONTROLLER
#define GRPC_CONTROLLER(_GRPC_SERVICE_) \
 public                                 \
  winter::GrpcController, public _GRPC_SERVICE_

// RESPONSE MACRO FOR GRPC
#define RESPONSE_ENTITY(...)                   \
  std::function<void()> service_call = [&]() { \
    __VA_ARGS__                                \
  };                                           \
  return responseEntity(service_call)

class GrpcController {
 public:
  virtual ~GrpcController() = default;

 protected:
  /**
       * auto Generate response for the grpc client also this is exception safe
       * @param execute
       * @return
       */
  grpc::Status responseEntity(const std::function<void()> &execute);
};

}  // namespace winter

#endif	// WINTER_GRPC_CONTROLLER_TEMPLATE_H