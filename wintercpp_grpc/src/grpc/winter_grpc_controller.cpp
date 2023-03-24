//
// Created by AZCONA VARGAS, SAMUEL EDUARDO [AG-Contractor/5000] on 2019-11-04.
//

#include <wintercpp/exception/database/winter_database_exception.h>
#include <wintercpp/exception/generic/winter_exception.h>
#include <wintercpp/exception/generic/winter_internal_exception.h>
#include <wintercpp/exception/security/winter_security_exception.h>
#include <wintercpp/exception/sql/winter_sql_exception.h>
#include <wintercpp/grpc/winter_grpc_controller.h>

using namespace winter::exception;

grpc::Status winter::GrpcController::responseEntity(
    const std::function<void()> &execute) {
    grpc::Status status = grpc::Status::OK;
    try {
        execute();
    } catch (const SecurityException &e) {
        std::cout << e.what() << std::endl;
        status = grpc::Status(grpc::StatusCode::UNAUTHENTICATED, e.what());
    } catch (const SqlException &e) {
        std::cout << e.what() << std::endl;
        status = grpc::Status(grpc::StatusCode::INTERNAL, e.what());
    } catch (const WinterException &e) {
        std::cout << e.what() << std::endl;
        status = grpc::Status(grpc::StatusCode::INTERNAL, e.what());
    } catch (const std::runtime_error &e) {
        std::cout << e.what() << std::endl;
        status = grpc::Status(grpc::StatusCode::INTERNAL, e.what());
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        status = grpc::Status(grpc::StatusCode::UNKNOWN, e.what());
    }
    return status;
}