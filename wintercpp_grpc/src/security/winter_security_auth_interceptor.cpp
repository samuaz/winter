/**
 * @author AZCONA VARGAS, SAMUEL EDUARDO -
 * samuel@theopencompany.tech/samuaz@gmail.com
 * @YEAR 2019
 */

#include <wintercpp/security/winter_security_auth_interceptor.h>
#include <wintercpp/security/winter_security_jwt_grpc.h>
#include <wintercpp/security/winter_security_token_status.h>

using namespace winter::security;

// todo: check if im using this shit
void AuthInterceptor::Intercept(
    grpc::experimental::InterceptorBatchMethods *methods) {
    if (methods->QueryInterceptionHookPoint(
            grpc::experimental::InterceptionHookPoints::
                POST_RECV_INITIAL_METADATA)) {
        auto map = methods->GetRecvInitialMetadata();

        std::multimap<grpc::string_ref, grpc::string_ref>::iterator itr;

        for (itr = map->begin(); itr != map->end(); ++itr) {
            if (itr->first == "authorization") {
                std::string erase = "Bearer ";
                std::size_t pos = itr->second.find(erase);
                std::string value = itr->second.data();
                std::string token = value.erase(pos, erase.length());

                TokenStatus tokenStatus = security::GrpcJwt::instance().ValidateToken(token);

                if (tokenStatus.isValid()) {
                    methods->Proceed();
                } else {
                    methods->ModifySendStatus(
                        grpc::Status(grpc::StatusCode::UNAUTHENTICATED,
                                     tokenStatus.message()));
                    methods->FailHijackedRecvMessage();
                }
            } else {
                methods->ModifySendStatus(grpc::Status(
                    grpc::StatusCode::INTERNAL, "UNAUTHENTICATED"));
            }
        }
    }
}
