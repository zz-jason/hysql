#ifndef NANGA_RUNTIME_SCAN_CSV_H
#define NANGA_RUNTIME_SCAN_CSV_H

#include <hysql/runtime/runtime.h>
#include <hysql/util/row_batch.h>

#include <csv.hpp>
#include <iostream>

namespace hysql {
namespace runtime {

class TableScanCSV : public Operator {
private:
    csv::CSVReader reader_;

public:
    TableScanCSV(const char* filename,
                 std::shared_ptr<hysql::util::Schema> schema)
        : reader_(filename), Operator(schema) {}
    virtual std::shared_ptr<hysql::util::RowBatch> Next() {
        for (csv::CSVRow& row : reader_) {
            for (csv::CSVField& field : row) {
                std::cout << field.get<>() << " ";
            }
            std::cout << std::endl;
        }
        return nullptr;
    }
};

}  // namespace runtime
}  // namespace hysql

#endif
