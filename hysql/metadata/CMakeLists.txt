add_library(metadata STATIC
    metadata.cpp
)
target_include_directories(metadata PUBLIC
    "${PROJECT_SOURCE_DIR}"
)
target_link_libraries(metadata PUBLIC
    util
)
