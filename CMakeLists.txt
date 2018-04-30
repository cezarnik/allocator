cmake_minimum_required(VERSION 3.2)

if ($ENV{TRAVIS_BUILD_NUMBER})
	set(VERSION_BUILD $ENV{TRAVIS_BUILD_NUMBER})
else()
	set(VERSION_BUILD 0)
endif()

project(allocator VERSION 1.1.${VERSION_BUILD}) 


add_executable(allocator main.cpp allocator.h forward_list.h )

set_target_properties(allocator PROPERTIES 
	CXX_STANDARD 14
	CXX_STANDARD_REQUIRED ON
)
install(TARGETS allocator RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT n.gaivoronskiy@innopolis.ru)

include(CPack)


