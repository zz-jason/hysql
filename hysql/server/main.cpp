#include <hysql/server/session.h>
#include <hysql/util/row_batch.h>

#include <iostream>
#include <sstream>
#include <string>

int main(int argc, char** argv) {
    std::string prompt = "HySQL> ";
    std::string query;
    hysql::server::Session session;

    while (true) {
        std::cout << prompt;
        std::getline(std::cin, query);
        std::cout << "input: " << query << std::endl;

        try {
            session.Query(query);
        } catch (const hysql::util::Error* err) {
            std::cout << err->ToString() << std::endl;
        }
    }
    return 0;
}
