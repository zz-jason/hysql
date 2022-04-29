add_library(planner STATIC
    resolver.cpp
    planner.cpp
)
target_include_directories(planner PUBLIC
    "${PROJECT_SOURCE_DIR}"
)
target_link_libraries(planner PUBLIC
    util
    sqlparser
    metadata
)
