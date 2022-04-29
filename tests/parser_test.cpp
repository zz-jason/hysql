#include <thirdparts/googletest/googletest/include/gtest/gtest.h>
#include <thirdparts/sql-parser/src/SQLParser.h>

#include <string>

namespace hysql {
namespace tests {

TEST(SQLParserTest, TestSelect) {
    const std::string query =
        "select * from test where test.a > 10 and test.a < 20 order by test.a, "
        "test.b; select * from test;";

    hsql::SQLParserResult result;
    hsql::SQLParser::parse(query, &result);

    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result.getStatement(0)->isType(hsql::kStmtSelect), true);
    EXPECT_EQ(result.getStatement(1)->isType(hsql::kStmtSelect), true);
}

}  // namespace tests
}  // namespace hysql
