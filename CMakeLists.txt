cmake_minimum_required(VERSION 3.23)

set(_PROJECT_NAME GaugeDesigner)
set(_PROJECT_VERSION 0.1)


project(${_PROJECT_NAME} VERSION ${_PROJECT_VERSION} LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include(src/source_files.txt)

#include(qml/qml_files.txt)

include(qt_modules.txt)


find_package(Qt5 COMPONENTS ${QT_MODULES} REQUIRED)

add_executable(
    ${_PROJECT_NAME}
    ${PROJECT_HEADERS}
    ${PROJECT_SOURCES}
    resources/resources.qrc
    qml/qml.qrc
)

#qt_add_qml_module(${_PROJECT_NAME}
#    URI qml
#    VERSION 1.0
#    QML_FILES
#        ${QML_FILES}
#)

target_include_directories(${_PROJECT_NAME} PUBLIC
    src
)

set_target_properties(${_PROJECT_NAME} PROPERTIES
    WIN32_EXECUTABLE TRUE
)

target_compile_definitions(${_PROJECT_NAME}
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

list(TRANSFORM QT_MODULES PREPEND Qt5::)
target_link_libraries(${_PROJECT_NAME} PRIVATE
        ${QT_MODULES}
)
