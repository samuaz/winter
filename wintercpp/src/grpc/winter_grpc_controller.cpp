//
// Created by AZCONA VARGAS, SAMUEL EDUARDO [AG-Contractor/5000] on 2019-11-04.
//

#include <wintercpp/grpc/winter_grpc_controller.h>

using namespace winter::exception;

grpc::Status
winter::GrpcController::responseEntity(
    const std::function<void()> &execute) {
  grpc::Status status = grpc::Status::OK;
  try {
    execute();
  } catch (const SecurityException &e) {
    status = grpc::Status(grpc::StatusCode::UNAUTHENTICATED, e.what());
  } catch (const WinterInternalException &e) {
    status = grpc::Status(grpc::StatusCode::INTERNAL, e.what());
  } catch (const ::sql::SQLException &e) {
    status = grpc::Status(grpc::StatusCode::INTERNAL, e.what());
  } catch (const std::runtime_error &e) {
    status = grpc::Status(grpc::StatusCode::INTERNAL, e.what());
  } catch (...) {
    status = grpc::Status(grpc::StatusCode::UNKNOWN, "UNKNOWN ERROR");
  }
  return status;
}
