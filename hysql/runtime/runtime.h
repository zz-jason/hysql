#ifndef HYSQL_RUNTIME_RUNTIME_H
#define HYSQL_RUNTIME_RUNTIME_H

#include <hysql/util/row_batch.h>
#include <hysql/util/schema.h>

#include <memory>
#include <vector>

namespace hysql {
namespace runtime {

// The execution plan is split into Stages for better perforamnce and resource
// utilization:
//
// Plan (Stage DAG): Stage (Pipeline DAG): Pipeline (Operator chain):
//
//    Stage             Pipeline           Operator
//     /  \              /  \                 |
//    /    \            /    \             Operator
//   /      \          /      \               |
// Stage   Stage     Pipeline  Pipeline    Operator
//
// Operator is almost the same with the plan nodes with some difference:
// HashAggregate is split into 2 operations:
//  1. HashAggBuild
//  2. HashAggProbe
//
// HashJoin is split into 2 operations:
//  1. HashJoinBuild
//  2. HashJoinProbe

// Operators are chained together to form an execution pipeline.
class Operator {
protected:
    std::shared_ptr<hysql::util::Schema> schema_;
    std::shared_ptr<Operator> input_;

public:
    Operator(std::shared_ptr<hysql::util::Schema> schema) : schema_(schema) {}

    std::shared_ptr<hysql::util::Schema> GetSchema() { return schema_; }
    void SetInput(std::shared_ptr<Operator> op) { input_ = op; }

    virtual std::shared_ptr<hysql::util::RowBatch> Next() = 0;
};

// the root operator of a pipeline usually returns nothing, it should be of of
// the following things:
// 1. DDL statements
// 2. Sink to remote client
// 3. Sink to local/remote storage
class Pipeline {
private:
    std::shared_ptr<Operator> operator_;
    bool finished_;
    std::vector<std::shared_ptr<Pipeline>> inputs_;

public:
    Pipeline(std::shared_ptr<Operator> op)
        : operator_(op), finished_(false), inputs_() {}

    void SetHeadOperator(std::shared_ptr<Operator> op) { operator_ = op; }
    std::shared_ptr<Operator> GetHeadOperator() const { return operator_; }

    void Execute() {
        // execute inputs firstly
        for (auto input : inputs_) {
            input->Execute();
        }

        // execute the current pipeline
        while (true) {
            const auto rb = operator_->Next();
            if (rb->Size() == 0) break;  // no more data
        }
    }
};

class Stage {
private:
    std::shared_ptr<Pipeline> pipeline_;
    bool finished_;
    std::vector<std::shared_ptr<Stage>> inputs_;

public:
    Stage(std::shared_ptr<Pipeline> pipeline)
        : pipeline_(pipeline), finished_(false), inputs_() {}

    void SetRootPipeline(std::shared_ptr<Pipeline> pipeline) {
        pipeline_ = pipeline;
    }

    std::shared_ptr<Pipeline> GetRootPipeline() const { return pipeline_; }

    void Execute() {
        // TODO: execute a pipeline with multi-threads
        // TODO: execute avaiable pipelines concurrently
        pipeline_->Execute();
    }

private:
    void TopologicalSort();
};

}  // namespace runtime
}  // namespace hysql

#endif
