# for csv-parser
add_subdirectory(csv-parser)

# for sql-parser
set(PARSER_DIR sql-parser)
add_library(sqlparser SHARED
    sql-parser/src/parser/bison_parser.cpp
    sql-parser/src/parser/flex_lexer.cpp
    sql-parser/src/sql/Expr.cpp
    sql-parser/src/sql/PrepareStatement.cpp
    sql-parser/src/sql/SQLStatement.cpp
    sql-parser/src/sql/statements.cpp
    sql-parser/src/SQLParser.cpp
    sql-parser/src/SQLParserResult.cpp
    sql-parser/src/util/sqlhelper.cpp
)
target_include_directories(sqlparser INTERFACE
    sql-parser/src
)
target_compile_options(sqlparser PRIVATE
    -std=c++1z
    -O3 -Wno-sign-compare
    -fPIC
)
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    target_compile_options(sqlparser PRIVATE -Wno-unneeded-internal-declaration -Wno-format)
endif()
