#ifndef HYSQL_PLANNER_RESOLVER_H
#define HYSQL_PLANNER_RESOLVER_H

#include <hysql/metadata/metadata.h>
#include <hysql/planner/operator.h>
#include <thirdparts/sql-parser/src/SQLParser.h>
#include <thirdparts/sql-parser/src/sql/CreateStatement.h>

#include <memory>

namespace hysql {
namespace planner {

class Resolver {
public:
    static std::shared_ptr<Operator> Resolve(const hsql::SQLStatement* stmt);
    static std::shared_ptr<Operator> ResolveCreateStatement(
        const hsql::CreateStatement* stmt);

    static std::shared_ptr<Operator> ResolveDropStatement(
        const hsql::DropStatement* stmt) {
        return nullptr;
    }
    static std::shared_ptr<Operator> ResolveSelectStatement(
        const hsql::SelectStatement* stmt) {
        return nullptr;
    }

private:
    static std::shared_ptr<Operator> HandleCreateTable(
        const hsql::CreateStatement* stmt);

    static std::shared_ptr<hysql::metadata::Column> ToColumn(
        const hsql::ColumnDefinition* def);
};

}  // namespace planner
}  // namespace hysql

#endif
