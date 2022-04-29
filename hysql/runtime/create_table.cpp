#include <hysql/metadata/metadata.h>
#include <hysql/runtime/create_table.h>
#include <hysql/runtime/runtime.h>
#include <hysql/util/row_batch.h>

#include <memory>

namespace hysql {
namespace runtime {

std::shared_ptr<hysql::util::RowBatch> CreateTable::Next() {
    auto mm = hysql::metadata::MetaManager::GetInstance();
    mm->CreateTable(schema_name_, table_);
    return std::make_shared<hysql::util::RowBatch>();
}

}  // namespace runtime
}  // namespace hysql
