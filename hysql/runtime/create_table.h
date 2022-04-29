#ifndef HYSQL_RUNTIME_CREATE_TABLE_H
#define HYSQL_RUNTIME_CREATE_TABLE_H

#include <hysql/metadata/metadata.h>
#include <hysql/runtime/runtime.h>

#include <algorithm>
#include <memory>

namespace hysql {
namespace runtime {

class CreateTable : public Operator {
private:
    std::string schema_name_;
    std::shared_ptr<hysql::metadata::Table> table_;

public:
    CreateTable(const std::string& schema_name,
                std::shared_ptr<hysql::metadata::Table> table)
        : Operator(std::make_shared<hysql::util::Schema>()),
          schema_name_(schema_name),
          table_(table) {}

    virtual std::shared_ptr<hysql::util::RowBatch> Next();
};

}  // namespace runtime
}  // namespace hysql

#endif
