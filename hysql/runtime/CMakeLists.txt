add_library(runtime STATIC
    table_scan_csv.cpp
    create_table.cpp
)
target_include_directories(runtime PUBLIC
    "${PROJECT_SOURCE_DIR}"
    "${PROJECT_SOURCE_DIR}/thirdparts/csv-parser/include"
)
target_link_libraries(runtime PUBLIC
    csv
    util
    metadata
)
