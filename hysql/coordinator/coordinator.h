#ifndef NANGA_COORDINATOR_COORDINATOR_H
#define NANGA_COORDINATOR_COORDINATOR_H

#include <hysql/planner/planner.h>
#include <hysql/runtime/runtime.h>

#include <memory>
#include <vector>

namespace hysql {
namespace coordinator {

class Coordinator {
public:
    void Execute(const std::shared_ptr<hysql::planner::Operator> physical);

private:
    std::shared_ptr<hysql::runtime::Stage> ToStage(
        const std::shared_ptr<hysql::planner::Operator> physical);

    std::shared_ptr<hysql::runtime::Operator> NewOperator(
        const std::shared_ptr<hysql::planner::Operator> physical);
};

}  // namespace coordinator
}  // namespace hysql

#endif
