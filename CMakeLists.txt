cmake_minimum_required(VERSION 3.14)
project(QRestaurant VERSION 0.1 LANGUAGES CXX)

#====== Global Configurations ==================#

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set additional project information
set(COPYRIGHT "GPLv3")
set(IDENTIFIER "Qt Restaurant-Demo")
option(TESTING "Enable Test" OFF)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(TESTING "Enable Test" ON)
endif()

#============== Dependences ======================#

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Gui Quick Test)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Quick Test)

include(FetchContent)
FetchContent_Declare(
  qtcsv
  GIT_REPOSITORY "https://github.com/iamantony/qtcsv"
  GIT_TAG        v1.6 # qt4_qt5 branch
)
set(QTCSV_PATH ${qtcsv_SOURCE_DIR})
include_directories(${QTCSV_PATH}/include)
link_directories(${qtcsv_BINARY_DIR})
FetchContent_MakeAvailable(qtcsv)

#=============== Target Configurations ============#
set(Restaurant_INCLUDE_DIR
  "include"
)
include_directories(${Restaurant_INCLUDE_DIR})
set(SRC "src/main.cpp" "src/restaurant.cpp")
set(TEST_SRC "test/test.cpp" "src/restaurant.cpp")

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(${PROJECT_NAME})
    qt_finalize_executable(${PROJECT_NAME})
else()
    qt5_add_resources(qml_QRC "data/qml.qrc")
    qt5_wrap_cpp(MOC_Files "${Restaurant_INCLUDE_DIR}/restaurant.hpp")
endif()

# --------------------------------------------------#
if(NOT TESTING)
  add_executable( ${PROJECT_NAME} ${MOC_Files} ${SRC} ${Restaurant_INCLUDE_DIR} ${qml_QRC} ${Restaurant_INCLUDE_DIR})
  target_link_libraries( ${PROJECT_NAME} PUBLIC qtcsv PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::Quick)
else()
  enable_testing(true)
  add_executable( ${PROJECT_NAME} ${MOC_Files} ${TEST_SRC} ${Restaurant_INCLUDE_DIR} ${qml_QRC} ${Restaurant_INCLUDE_DIR})
  target_link_libraries( ${PROJECT_NAME} PUBLIC qtcsv PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt${QT_VERSION_MAJOR}::Test)
  add_test(${PROJECT_NAME} ${PROJECT_NAME})
endif()
