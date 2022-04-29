add_subdirectory("${PROJECT_SOURCE_DIR}/thirdparts/googletest"
    "thirdparts/googletests")

mark_as_advanced(
    BUILD_GMOCK BUILD_GTEST BUILD_SHARED_LIBS
    gmock_build_tests gtest_build_samples gtest_build_tests
    gtest_disable_pthreads gtest_force_shared_crt gtest_hide_internal_symbols
)

set_target_properties(gtest PROPERTIES FOLDER thirdparts)
set_target_properties(gtest_main PROPERTIES FOLDER thirdparts)
set_target_properties(gmock PROPERTIES FOLDER thirdparts)
set_target_properties(gmock_main PROPERTIES FOLDER thirdparts)

macro(package_add_test TESTNAME)
    add_executable(${TESTNAME} ${ARGN})
    target_link_libraries(${TESTNAME}
        gtest gmock gtest_main
        sqlparser
    )
    target_include_directories(${TESTNAME} PUBLIC
        "${PROJECT_SOURCE_DIR}"
        "${PROJECT_SOURCE_DIR}/thirdparts/googletest/googletest/include"
    )
    gtest_discover_tests(${TESTNAME}
        WORKING_DIRECTORY ${PROJECT_DIR}
        PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_DIR}"
    )
    set_target_properties(${TESTNAME} PROPERTIES FOLDER tests)
endmacro()

package_add_test(topn_test topn_test.cpp)
package_add_test(parser_test parser_test.cpp)
