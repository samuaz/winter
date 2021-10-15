/**
 * @author AZCONA VARGAS, SAMUEL EDUARDO -
 * samuel@theopencompany.tech/samuaz@gmail.com
 * @YEAR 2019
 */

#ifndef WINTER_AUTH_INTERCEPTOR_H
#define WINTER_AUTH_INTERCEPTOR_H

#include <grpcpp/impl/codegen/interceptor.h>
#include <grpcpp/impl/codegen/server_interceptor.h>

#include <memory>

namespace winter::security {

/**
   * grpc interceptor i need to implement this to secure the services without
   * need to call the security namespace
   */
class AuthInterceptor : public grpc::experimental::Interceptor {
 public:
  grpc::experimental::ServerRpcInfo *info;

  AuthInterceptor(grpc::experimental::ServerRpcInfo *info) :
      info(info) {}

  ~AuthInterceptor() {}

  void Intercept(
      grpc::experimental::InterceptorBatchMethods *methods) override;
};
}  // namespace winter::security

#endif	// WINTER_AUTH_INTERCEPTOR_H
