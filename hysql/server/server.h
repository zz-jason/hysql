#ifndef HYSQL_SERVER_SERVER_H
#define HYSQL_SERVER_SERVER_H

#include <cstdint>
#include <string>

namespace hysql {
namespace server {

class Server {
private:
    const std::string address_;
    const uint16_t port_;

public:
    Server(const std::string& address = "0.0.0.0", const uint16_t port = 5000)
        : address_(address), port_(port) {}

    void Run();
};

}  // namespace server
}  // namespace hysql

#endif
