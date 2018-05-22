cmake_minimum_required(VERSION 3.2)

if ($ENV{TRAVIS_BUILD_NUMBER})
	set(VERSION_BUILD $ENV{TRAVIS_BUILD_NUMBER})
else()
	set(VERSION_BUILD 0)
endif()

project(allocator VERSION 1.1.${VERSION_BUILD}) 


add_executable(allocator main.cpp allocator.h forward_list.h )

add_executable(alloc_test alloc_test.cpp debug.h debug.cpp allocator.h)
add_executable(list_test list_test.cpp forward_list.h)


set_target_properties(allocator alloc_test list_test PROPERTIES 
	CXX_STANDARD 14
	CXX_STANDARD_REQUIRED ON
)
set_target_properties(alloc_test list_test
	PROPERTIES
	COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
	INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(alloc_test ${Boost_LIBRARIES})
target_link_libraries(list_test ${Boost_LIBRARIES})
install(TARGETS allocator RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT n.gaivoronskiy@innopolis.ru)

include(CPack)

enable_testing()

add_test(alloc_test alloc_test)
add_test(list_test list_test)

