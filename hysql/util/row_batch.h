#ifndef NANGA_UTIL_ROW_BATCH_H
#define NANGA_UTIL_ROW_BATCH_H

#include <hysql/util/column.h>

#include <cstdint>
#include <memory>
#include <vector>

namespace hysql {
namespace util {

class RowBatch {
private:
    std::vector<std::unique_ptr<Column>> columns_;

public:
    RowBatch() {}
    ~RowBatch() { columns_.clear(); }
    size_t Size() { return columns_.empty() ? 0 : columns_[0]->Size(); }
};

}  // namespace util
}  // namespace hysql

#endif
