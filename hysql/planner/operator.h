#ifndef HYSQL_PLANNER_OPERATOR_H
#define HYSQL_PLANNER_OPERATOR_H

#include <hysql/metadata/metadata.h>
#include <thirdparts/sql-parser/src/sql/CreateStatement.h>

#include <memory>
#include <vector>

namespace hysql {
namespace planner {

class Operator {
public:
    enum Type {
        kUnknown = 0,
        kCreateTable,
    };

    Type type_;
    std::vector<std::shared_ptr<Operator>> children_;

public:
    Operator(Operator::Type type) : type_(type) {}
    virtual ~Operator() { children_.clear(); }
};

class OpCreateTable : public Operator {
public:
    std::string schema_name_;
    std::shared_ptr<hysql::metadata::Table> table_;

public:
    OpCreateTable() : Operator(Operator::kCreateTable) {}
};

}  // namespace planner
}  // namespace hysql

#endif
