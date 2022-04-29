#ifndef NANGA_UTIL_COLUMN_H
#define NANGA_UTIL_COLUMN_H

#include <cstdint>
#include <memory>

namespace hysql {
namespace util {

class Column {
private:
    char* data_;
    size_t size_;

public:
    size_t Size() { return size_; }
};

}  // namespace util
}  // namespace hysql

#endif
