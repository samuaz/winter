/**
 * @author Samuel Azcona
 * @email samuel@theopencompany.dev
 * @create date 2021-06-26 16:46:51
 * @modify date 2021-06-26 16:46:51
 * @desc winterc++ winterBoot class that initialize the main functions
 */

#ifndef __WINTER_BOOT_H__
#define __WINTER_BOOT_H__

#include <grpcpp/grpcpp.h>
#include <wintercpp/grpc/winter_grpc_controller.h>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

#define WINTER_ADD_CONTROLLER(_SERVICE_) \
    _SERVICE_ controller##_SERVICE_;     \
    winter::WinterBoot::registerController(&controller##_SERVICE_)

namespace winter {

    class WinterBoot {
       public:
        static WinterBoot &getInstance() {
            std::call_once(m_once_, []() {
                instance_.reset(new WinterBoot());
            });
            return *instance_;
        }

        WinterBoot(WinterBoot const &) = delete;

        void operator=(WinterBoot const &) = delete;

        static void init(const std::string &host, const std::string &port);

        static void onInit(const std::string &host,
                           const std::string &port,
                           const std::function<void()> &initFunction);

        static void registerController(grpc::Service *controller);

        ~WinterBoot();

       private:
        WinterBoot();
        static void runServer(const std::string &host, const std::string &port);
        static ServerBuilder builder_;
        static std::unique_ptr<WinterBoot> instance_;
        static std::once_flag m_once_;
    };

}  // namespace winter

#endif  // __WINTER_BOOT_H__