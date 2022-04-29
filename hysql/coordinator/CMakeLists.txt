add_library(coordinator STATIC
    coordinator.cpp
)
target_include_directories(coordinator PUBLIC
    "${PROJECT_SOURCE_DIR}"
)
target_link_libraries(coordinator PUBLIC
    csv
    util
    planner
    runtime
    metadata
)
