#ifndef HYSQL_SERVER_SESSION_H
#define HYSQL_SERVER_SESSION_H

#include <hysql/coordinator/coordinator.h>
#include <hysql/planner/planner.h>
#include <hysql/planner/resolver.h>
#include <thirdparts/sql-parser/src/SQLParser.h>

#include <memory>
#include <string>

namespace hysql {
namespace server {

class Session {
private:
    std::unique_ptr<hysql::planner::Planner> planner_;
    std::unique_ptr<hysql::coordinator::Coordinator> coordinator_;

public:
    Session()
        : planner_(std::make_unique<hysql::planner::Planner>()),
          coordinator_(std::make_unique<hysql::coordinator::Coordinator>()) {}
    void Query(const std::string& query);
};

void Session::Query(const std::string& query) {
    hsql::SQLParserResult result;
    bool ok = hsql::SQLParser::parse(query, &result);
    if (!result.isValid()) {
        throw hysql::util::Error::NewInvalidSyntaxError(
            std::string(result.errorMsg()));
    }
    for (size_t i = 0; i < result.size(); ++i) {
        auto stmt = result.getStatement(i);
        auto logical = hysql::planner::Resolver::Resolve(stmt);
        auto physical = planner_->Optimize(logical);
        coordinator_->Execute(physical);
    }
}

}  // namespace server
}  // namespace hysql

#endif
