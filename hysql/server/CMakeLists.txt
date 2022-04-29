# hysql is both the name the executable binary and the target.
add_executable(hysql
    main.cpp
)
set_target_properties(hysql PROPERTIES
    CXX_STANDARD 20 # enable c++20
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS OFF
)
target_include_directories(hysql PUBLIC
    "${PROJECT_SOURCE_DIR}"
)
target_link_libraries(hysql PUBLIC
    planner
    coordinator
)
