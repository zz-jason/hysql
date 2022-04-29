#ifndef HYSQL_METADATA_METADATA_H
#define HYSQL_METADATA_METADATA_H

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace hysql {
namespace metadata {

struct ColumnType {
    enum Type {
        kUnknown = 0,
        kInt64,
        kDouble,
    };

    Type type_;
    size_t length_;
    size_t precision_;
    size_t scale_;

    ColumnType(Type type, size_t length, size_t precision, size_t scale)
        : type_(type), length_(length), precision_(precision), scale_(scale) {}
};

struct Column {
    std::string column_name_;
    std::shared_ptr<ColumnType> type_;

    Column(const char* column_name, std::shared_ptr<ColumnType> type)
        : column_name_(column_name), type_(type) {}
};

struct Table {
    uint64_t table_id_;
    std::string table_name_;
    std::vector<std::shared_ptr<Column>> columns_;
};

struct Schema {
    std::string schema_name_;

    // the order of tables doesn't matter, so we use a map to store tables.
    std::map<std::string, std::shared_ptr<Table>> tables_;

    Schema(const std::string& name) : schema_name_(name) {}
};

class MetaManager {
private:
    // TODO: make this map thread-safe.
    std::map<std::string, std::shared_ptr<Schema>> schemas_;

private:
    MetaManager() {
        std::string default_schema = "";
        schemas_[default_schema] = std::make_shared<Schema>(default_schema);
    }

public:
    static MetaManager* GetInstance() {
        static MetaManager instance;
        return &instance;
    }

public:
    // disallow copy construct and assignment
    MetaManager(MetaManager const&) = delete;
    void operator=(const MetaManager&) = delete;

    void CreateSchema(const std::string& schema_name);
    void DropSchema(const std::string& schema_name);
    std::shared_ptr<Schema> GetSchema(const std::string& schema_name);

    void CreateTable(const std::string& schema_name,
                     std::shared_ptr<Table> table);
    void DropTable(const std::string& schema_name,
                   const std::string& table_name);
    std::shared_ptr<Table> GetTable(const std::string& schema_name,
                                    const std::string& table_name);
};

}  // namespace metadata
}  // namespace hysql

#endif
