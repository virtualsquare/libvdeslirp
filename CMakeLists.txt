cmake_minimum_required(VERSION 3.13)
project("vdeslirp"
    DESCRIPTION "libslirp for Linux made easy peasy"
    HOMEPAGE_URL "https://github.com/rd235/libvdeslirp"
    VERSION 0.1.0
    LANGUAGES C)

include(GNUInstallDirs)
include(CheckIncludeFile)
include(CheckSymbolExists)

set(LIBS_REQUIRED slirp vdeplug_mod pthread)
set(HEADERS_REQUIRED libvdeplug.h slirp/libslirp.h)
set(CMAKE_REQUIRED_QUIET TRUE)
set(CMAKE_REQUIRED_LIBRARIES slirp)

check_symbol_exists("slirp_add_exec" "slirp/libslirp.h" HAS_ADD_EXEC)
check_symbol_exists("slirp_add_unix" "slirp/libslirp.h" HAS_ADD_UNIX)
check_symbol_exists("slirp_remove_guestfwd" "slirp/libslirp.h" HAS_REMOVE_GUESTFWD)

foreach(THISLIB IN LISTS LIBS_REQUIRED)
  find_library(LIB${THISLIB}_OK ${THISLIB})
  if(NOT LIB${THISLIB}_OK)
    message(FATAL_ERROR "library lib${THISLIB} not found")
  endif()
endforeach(THISLIB)

foreach(HEADER IN LISTS HEADERS_REQUIRED)
  check_include_file(${HEADER} ${HEADER}_OK)
  if(NOT ${HEADER}_OK)
    message(FATAL_ERROR "header file ${HEADER} not found")
  endif()
endforeach(HEADER)

add_definitions(-D_GNU_SOURCE)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_library(vdeslirp SHARED libvdeslirp.c)
target_link_libraries(vdeslirp -lslirp -lpthread -lvdeplug_mod)

set_target_properties(vdeslirp PROPERTIES VERSION ${PROJECT_VERSION}
		SOVERSION ${PROJECT_VERSION_MAJOR})

configure_file(vdeslirp.pc.in vdeslirp.pc @ONLY)
configure_file(config.h.in config.h)

install(TARGETS vdeslirp DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES libvdeslirp.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/slirp)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/vdeslirp.pc
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)

add_subdirectory(man)

add_custom_target(uninstall
  "${CMAKE_COMMAND}" -P "${PROJECT_SOURCE_DIR}/Uninstall.cmake")
