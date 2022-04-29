#include <hysql/metadata/metadata.h>
#include <hysql/planner/operator.h>
#include <hysql/planner/resolver.h>
#include <hysql/util/error.h>
#include <thirdparts/sql-parser/src/SQLParser.h>
#include <thirdparts/sql-parser/src/sql/CreateStatement.h>

#include <memory>

namespace hysql {
namespace planner {

std::shared_ptr<Operator> Resolver::Resolve(const hsql::SQLStatement* stmt) {
    switch (stmt->type()) {
        case hsql::kStmtCreate: {
            return ResolveCreateStatement((hsql::CreateStatement*)stmt);
        }
        case hsql::kStmtDrop: {
            return ResolveDropStatement((hsql::DropStatement*)stmt);
        }
        case hsql::kStmtSelect: {
            return ResolveSelectStatement((hsql::SelectStatement*)stmt);
        }
        case hsql::kStmtError: {
            throw hysql::util::Error::NewUnsupportedError(
                "unsupported statement: Error");
        }
        case hsql::kStmtImport: {
            throw hysql::util::Error::NewUnsupportedError(
                "unsupported statement: Import");
        }
        case hsql::kStmtInsert: {
            throw hysql::util::Error::NewUnsupportedError(
                "unsupported statement: Insert");
        }
        case hsql::kStmtUpdate: {
            throw hysql::util::Error::NewUnsupportedError(
                "unsupported statement: Update");
        }
        case hsql::kStmtDelete: {
            throw hysql::util::Error::NewUnsupportedError(
                "unsupported statement: Delete");
        }
        case hsql::kStmtPrepare: {
            throw hysql::util::Error::NewUnsupportedError(
                "unsupported statement: Prepare");
        }
        case hsql::kStmtExecute: {
            throw hysql::util::Error::NewUnsupportedError(
                "unsupported statement: Execute");
        }
        case hsql::kStmtExport: {
            throw hysql::util::Error::NewUnsupportedError(
                "unsupported statement: Export");
        }
        case hsql::kStmtRename: {
            throw hysql::util::Error::NewUnsupportedError(
                "unsupported statement: Rename");
        }
        case hsql::kStmtAlter: {
            throw hysql::util::Error::NewUnsupportedError(
                "unsupported statement: Alter");
        }
        case hsql::kStmtShow: {
            throw hysql::util::Error::NewUnsupportedError(
                "unsupported statement: Show");
        }
        case hsql::kStmtTransaction: {
            throw hysql::util::Error::NewUnsupportedError(
                "unsupported statement: Transaction");
        }
        default: {
            throw hysql::util::Error::NewUnsupportedError("unknown statement");
        }
    }
    return nullptr;
}

std::shared_ptr<Operator> Resolver::ResolveCreateStatement(
    const hsql::CreateStatement* stmt) {
    switch (stmt->type) {
        case hsql::kCreateTable: {
            return HandleCreateTable(stmt);
        }
        case hsql::kCreateTableFromTbl: {
            throw hysql::util::Error::NewUnsupportedError(
                "Create Table From Table is unsupported");
            break;
        }
        case hsql::kCreateView: {
            throw hysql::util::Error::NewUnsupportedError(
                "Create View is unsupported");
            break;
        }
        case hsql::kCreateIndex: {
            throw hysql::util::Error::NewUnsupportedError(
                "Create Index is unsupported");
            break;
        }
    }
}

std::shared_ptr<Operator> Resolver::HandleCreateTable(
    const hsql::CreateStatement* stmt) {
    std::shared_ptr<OpCreateTable> result(new OpCreateTable());
    result->schema_name_ =
        std::string(stmt->schema == nullptr ? "" : stmt->schema);
    result->table_ = std::make_shared<hysql::metadata::Table>();
    result->table_->table_name_ = std::string(stmt->tableName);
    for (const hsql::ColumnDefinition* def : *stmt->columns) {
        result->table_->columns_.push_back(ToColumn(def));
    }
    return result;
}

std::shared_ptr<hysql::metadata::Column> Resolver::ToColumn(
    const hsql::ColumnDefinition* def) {
    const char* column_name = def->name;
    std::shared_ptr<hysql::metadata::ColumnType> column_type = nullptr;
    switch (def->type.data_type) {
        case hsql::DataType::REAL:
        case hsql::DataType::DOUBLE: {
            column_type = std::make_shared<hysql::metadata::ColumnType>(
                hysql::metadata::ColumnType::kDouble, def->type.length,
                def->type.precision, def->type.scale);
            break;
        }
        case hsql::DataType::SMALLINT:
        case hsql::DataType::INT:
        case hsql::DataType::LONG: {
            column_type = std::make_shared<hysql::metadata::ColumnType>(
                hysql::metadata::ColumnType::kInt64, def->type.length,
                def->type.precision, def->type.scale);
            break;
        }
        default: {
            throw hysql::util::Error::NewUnsupportedError("unsupported type");
        }
    }
    return std::make_shared<hysql::metadata::Column>(column_name, column_type);
}

}  // namespace planner
}  // namespace hysql
