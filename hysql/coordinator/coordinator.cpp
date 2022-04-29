#include <hysql/coordinator/coordinator.h>
#include <hysql/planner/planner.h>
#include <hysql/runtime/create_table.h>
#include <hysql/runtime/runtime.h>
#include <hysql/util/error.h>

#include <cassert>
#include <memory>

namespace hysql {
namespace coordinator {

void Coordinator::Execute(
    const std::shared_ptr<hysql::planner::Operator> physical) {
    // construct the execution stages.
    auto stage = ToStage(physical);

    // schedule and execute stages. since there is only one stage right now, we
    // just execute it.
    stage->Execute();
}

std::shared_ptr<hysql::runtime::Stage> Coordinator::ToStage(
    const std::shared_ptr<hysql::planner::Operator> physical) {
    switch (physical->children_.size()) {
        case 0: {
            auto op = NewOperator(physical);
            auto pipeline = std::make_shared<hysql::runtime::Pipeline>(op);
            return std::make_shared<hysql::runtime::Stage>(pipeline);
        }
        case 1: {
            auto stage = ToStage(physical->children_[0]);
            auto op = NewOperator(physical);
            auto pipeline = stage->GetRootPipeline();
            op->SetInput(pipeline->GetHeadOperator());
            pipeline->SetHeadOperator(op);
            return stage;
        }
        default: {
            // handle operators have at least 2 children, it might be split into
            // multiple pipelines.
            throw hysql::util::Error::NewUnsupportedError(
                "construct stage for operator have multiple children is "
                "unsupported");
        }
    }
    return nullptr;
}

std::shared_ptr<hysql::runtime::Operator> Coordinator::NewOperator(
    const std::shared_ptr<hysql::planner::Operator> physical) {
    switch (physical->type_) {
        case hysql::planner::Operator::kCreateTable: {
            auto actual = (hysql::planner::OpCreateTable*)physical.get();
            return std::make_shared<hysql::runtime::CreateTable>(
                actual->schema_name_, actual->table_);
        }
        default: {
            throw hysql::util::Error::NewUnsupportedError(
                "operator is not supported for optimize");
        }
    }
    return nullptr;
}

}  // namespace coordinator
}  // namespace hysql
