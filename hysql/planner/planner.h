#ifndef HYSQL_PLANNER_PLANNER_H
#define HYSQL_PLANNER_PLANNER_H

#include <hysql/planner/operator.h>
#include <hysql/planner/resolver.h>
#include <hysql/util/error.h>
#include <thirdparts/sql-parser/src/SQLParser.h>

#include <memory>

namespace hysql {
namespace planner {

class Planner {
public:
    std::shared_ptr<Operator> Optimize(const std::shared_ptr<Operator> logical);

private:
    // helper functions
};

}  // namespace planner
}  // namespace hysql

#endif
