project(qucslib CXX C)
cmake_minimum_required(VERSION 3.1.0)

# use top VERSION file
file(STRINGS ${PROJECT_SOURCE_DIR}/../VERSION QUCS_VERSION)
message(STATUS "Configuring ${PROJECT_NAME} (GUI): VERSION ${QUCS_VERSION}")

set(PROJECT_VERSION "${QUCS_VERSION}")

set(PROJECT_VENDOR "Qucs team. This program is licensed under the GNU GPL")
set(PROJECT_COPYRIGHT_YEAR "2014")
set(PROJECT_DOMAIN_FIRST "qucs")
set(PROJECT_DOMAIN_SECOND "org")

set(CMAKE_BUILD_TYPE Debug)

add_definitions(-DHAVE_CONFIG_H)

# configure the header config.h
configure_file("${PROJECT_SOURCE_DIR}/../config.h.cmake"
               "${PROJECT_BINARY_DIR}/config.h")

include_directories(${PROJECT_BINARY_DIR} "../qucs")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall ") # enable warning level
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x ") # enable C++11

# flag not available in mingw 4.8.2, MSVC10
if(NOT WIN32)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-register ")
endif()

find_package(Qt5 COMPONENTS Gui REQUIRED)

add_definitions(${QT_DEFINITIONS})

set(QUCSLIB_SRCS main.cpp qucslib.cpp displaydialog.cpp symbolwidget.cpp
                 librarydialog.cpp)

set(QUCSLIB_MOC_HDRS qucslib.h displaydialog.h symbolwidget.h librarydialog.h)

qt5_wrap_cpp(QUCSLIB_MOC_SRCS ${QUCSLIB_MOC_HDRS})

set(RESOURCES qucslib_.qrc)
qt5_add_resources(RESOURCES_SRCS ${RESOURCES})

if(APPLE)
  # set information on Info.plist file
  set(MACOSX_BUNDLE_INFO_STRING "${PROJECT_NAME} ${PROJECT_VERSION}")
  set(MACOSX_BUNDLE_BUNDLE_VERSION "${PROJECT_NAME} ${PROJECT_VERSION}")
  set(MACOSX_BUNDLE_LONG_VERSION_STRING "${PROJECT_NAME} ${PROJECT_VERSION}")
  set(MACOSX_BUNDLE_SHORT_VERSION_STRING "${PROJECT_VERSION}")
  set(MACOSX_BUNDLE_COPYRIGHT "${PROJECT_COPYRIGHT_YEAR} ${PROJECT_VENDOR}")
  set(MACOSX_BUNDLE_GUI_IDENTIFIER
      "${PROJECT_DOMAIN_SECOND}.${PROJECT_DOMAIN_FIRST}")
  set(MACOSX_BUNDLE_BUNDLE_NAME "${PROJECT_NAME}")
  set(MACOSX_BUNDLE_ICON_FILE qucslib.icns)

  # set where in the bundle to put the icns file
  set_source_files_properties(
    ${CMAKE_CURRENT_SOURCE_DIR}/../qucs/bitmaps/qucslib.icns
    PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
  # include the icns file in the target
  set(QUCSLIB_SRCS ${QUCSLIB_SRCS}
                   ${CMAKE_CURRENT_SOURCE_DIR}/../qucs/bitmaps/qucslib.icns)

endif(APPLE)

add_executable(qucslib MACOSX_BUNDLE WIN32 ${QUCSLIB_SRCS} ${QUCSLIB_MOC_SRCS}
                                           ${RESOURCES_SRCS})

target_link_libraries(qucslib Qt::Core Qt::Gui Qt::Widgets)

install(
  TARGETS qucslib
  BUNDLE DESTINATION bin COMPONENT Runtime
  RUNTIME DESTINATION bin COMPONENT Runtime)

add_subdirectory(library)

# man pages
install(FILES qucslib.1 DESTINATION share/man/man1)
