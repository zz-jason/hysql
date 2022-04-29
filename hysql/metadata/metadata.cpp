#include <hysql/metadata/metadata.h>
#include <hysql/util/error.h>

#include <cstdint>
#include <map>
#include <memory>
#include <string>

namespace hysql {
namespace metadata {

void MetaManager::CreateSchema(const std::string& schema) {
    if (schemas_.contains(schema)) {
        throw hysql::util::Error::NewSchemaDuplicatedError(
            "schema duplicated: " + schema);
    }
    schemas_[schema] = std::make_shared<Schema>(schema);
}
void MetaManager::DropSchema(const std::string& schema) {
    if (!schemas_.contains(schema)) {
        throw hysql::util::Error::NewSchemaNotExistError("schema not exist: " +
                                                         schema);
    }
    schemas_.erase(schema);
}

std::shared_ptr<Schema> MetaManager::GetSchema(const std::string& schema) {
    if (!schemas_.contains(schema)) {
        throw hysql::util::Error::NewSchemaNotExistError("schema not exist: " +
                                                         schema);
    }
    return schemas_[schema];
}

void MetaManager::CreateTable(const std::string& schema_name,
                              std::shared_ptr<Table> table) {
    auto schema = GetSchema(schema_name);
    if (schema->tables_.contains(table->table_name_)) {
        throw hysql::util::Error::NewTableDuplicatedError("table duplicated: " +
                                                          table->table_name_);
    }
    schema->tables_[table->table_name_] = table;
}

void MetaManager::DropTable(const std::string& schema_name,
                            const std::string& table_name) {
    auto schema = GetSchema(schema_name);
    if (!schema->tables_.contains(table_name)) {
        throw hysql::util::Error::NewTableNotExistError("table not exist: " +
                                                        table_name);
    }
    schema->tables_.erase(table_name);
}

std::shared_ptr<Table> MetaManager::GetTable(const std::string& schema_name,
                                             const std::string& table_name) {
    auto schema = GetSchema(schema_name);
    if (!schema->tables_.contains(table_name)) {
        throw hysql::util::Error::NewTableNotExistError("table not exist: " +
                                                        table_name);
    }
    return schema->tables_[table_name];
}

}  // namespace metadata
}  // namespace hysql
