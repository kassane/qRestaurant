cmake_minimum_required(VERSION 3.14)
project(QRestaurant VERSION 0.1 LANGUAGES CXX)

#====== Global Configurations ==================#

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Quick)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick)

include(FetchContent)
FetchContent_Declare(
  qtcsv
  GIT_REPOSITORY "https://github.com/iamantony/qtcsv"
  GIT_TAG        v1.6 # qt4_qt5 branch
)
if(NOT qtcsv_POPULATED)
  FetchContent_Populate(qtcsv)
endif()
set(QTCSV_PATH ${qtcsv_SOURCE_DIR})
include_directories(${QTCSV_PATH}/include)
link_directories(${qtcsv_BINARY_DIR})
FetchContent_MakeAvailable(qtcsv)

find_package(Qt5 COMPONENTS Core QuickControls2 Quick Qml REQUIRED)
#=============== Target Configurations ============#
set(Restaurant_INCLUDE_DIR
  "headers"
)
include_directories(${Restaurant_INCLUDE_DIR})
set(SRC "src/main.cpp" "src/restaurant.cpp")

qt5_add_resources(qml_QRC "data/qml.qrc")
qt5_wrap_cpp(MOC_Files ${Restaurant_INCLUDE_DIR}/restaurant.hpp)

# --------------------------------------------------#
add_executable( ${PROJECT_NAME} ${OS_BUNDLE} ${MOC_Files} ${SRC} ${Restaurant_INCLUDE_DIR} ${qml_QRC} ${Restaurant_INCLUDE_DIR})
target_link_libraries( ${PROJECT_NAME} PUBLIC qtcsv  Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)
