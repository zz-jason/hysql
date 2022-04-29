#include <hysql/planner/planner.h>
#include <thirdparts/sql-parser/src/SQLParser.h>
#include <thirdparts/sql-parser/src/sql/CreateStatement.h>

#include <iostream>
#include <memory>

namespace hysql {
namespace planner {

std::shared_ptr<Operator> Planner::Optimize(
    const std::shared_ptr<Operator> logical) {
    switch (logical->type_) {
        case Operator::kCreateTable: {
            return logical;
        }
        default: {
            throw hysql::util::Error::NewUnsupportedError(
                "operator is not supported for optimize");
        }
    }
    return nullptr;
};

}  // namespace planner
}  // namespace hysql
