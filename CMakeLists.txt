cmake_minimum_required(VERSION 3.10)

if (${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.11")
    cmake_policy(SET CMP0072 NEW)
endif ()
if (${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.12")
    cmake_policy(SET CMP0074 NEW)
endif ()

project(qwtplot3d VERSION 0.3.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(OpenGL REQUIRED)

if (${PREFER_QT})
    if (${PREFER_QT} EQUAL 6)
        find_package(Qt6 COMPONENTS Core OpenGLWidgets Widgets REQUIRED)
        set(V 6)
    elseif (${PREFER_QT} EQUAL 5)
        find_package(Qt5 COMPONENTS Core OpenGL Widgets REQUIRED)
        set(V 5)
    endif ()
else ()
    find_package(Qt6 COMPONENTS Core OpenGLWidgets Widgets QUIET)
    if (${Qt6_FOUND})
        set(V 6)
    else ()
        find_package(Qt5 COMPONENTS Core OpenGL Widgets REQUIRED)
        set(V 5)
    endif ()
endif ()
get_target_property(QT_LIB_PATH Qt${V}::Core LOCATION)
message(STATUS "Found Qt${V}Core: ${QT_LIB_PATH}")

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/3rdparty/gl2ps
    ${OPENGL_INCLUDE_DIRS})

set(SOURCES
    src/qwt3d_autoscaler.cpp
    src/qwt3d_axis.cpp
    src/qwt3d_color.cpp
    src/qwt3d_colorlegend.cpp
    src/qwt3d_coordsys.cpp
    src/qwt3d_curve.cpp
    src/qwt3d_dataviews.cpp
    src/qwt3d_drawable.cpp
    src/qwt3d_enrichment_std.cpp
    src/qwt3d_extglwidget.cpp
    src/qwt3d_function.cpp
    src/qwt3d_gridmapping.cpp
    src/qwt3d_gridplot.cpp
    src/qwt3d_io_gl2ps.cpp
    src/qwt3d_io_reader.cpp
    src/qwt3d_io.cpp
    src/qwt3d_label.cpp
    src/qwt3d_lighting.cpp
    src/qwt3d_meshplot.cpp
    src/qwt3d_mousekeyboard.cpp
    src/qwt3d_movements.cpp
    src/qwt3d_parametricsurface.cpp
    src/qwt3d_plot.cpp
    src/qwt3d_scale.cpp
#    src/qwt3d_surfaceplot.cpp
    src/qwt3d_types.cpp
    3rdparty/gl2ps/gl2ps.c)

set(HEADERS
    include/qwt3d_autoptr.h
    include/qwt3d_autoscaler.h
    include/qwt3d_axis.h
    include/qwt3d_color.h
    include/qwt3d_colorlegend.h
    include/qwt3d_coordsys.h
    include/qwt3d_curve.h
    include/qwt3d_drawable.h
    include/qwt3d_enrichment_std.h
    include/qwt3d_enrichment.h
    include/qwt3d_extglwidget.h
    include/qwt3d_function.h
    include/qwt3d_global.h
    include/qwt3d_graphplot.h
    include/qwt3d_gridmapping.h
    include/qwt3d_helper.h
    include/qwt3d_io_gl2ps.h
    include/qwt3d_io_reader.h
    include/qwt3d_io.h
    include/qwt3d_label.h
    include/qwt3d_mapping.h
    include/qwt3d_multiplot.h
    include/qwt3d_openglhelper.h
    include/qwt3d_parametricsurface.h
    include/qwt3d_plot.h
    include/qwt3d_portability.h
    include/qwt3d_scale.h
#    include/qwt3d_surfaceplot.h
    include/qwt3d_types.h
    include/qwt3d_volumeplot.h
    3rdparty/gl2ps/gl2ps.h)

if (APPLE)
    add_definitions(-DGL_SILENCE_DEPRECATION=1)
endif ()

add_library(qwtplot3d_static STATIC ${SOURCES} ${HEADERS})
set_target_properties(qwtplot3d_static PROPERTIES
    OUTPUT_NAME "qwtplot3d")
target_link_libraries(qwtplot3d_static PUBLIC
    Qt${V}::Core Qt${V}::Widgets OpenGL::GLU)
if (V EQUAL 6)
    target_link_libraries(qwtplot3d_static PUBLIC Qt6::OpenGLWidgets)
else ()
    target_link_libraries(qwtplot3d_static PUBLIC Qt${V}::OpenGL)
endif ()

if (BUILD_SHARED_LIBS)
    add_library(qwtplot3d_shared SHARED $<TARGET_OBJECTS:qwtplot3d_static>)
    set_target_properties(qwtplot3d_shared PROPERTIES
        VERSION ${qwtplot3d_VERSION}
        SOVERSION ${qwtplot3d_VERSION_MAJOR}
        OUTPUT_NAME "qwtplot3d")
    target_link_libraries(qwtplot3d_shared PUBLIC
        Qt${V}::Core Qt${V}::Widgets OpenGL::GLU)
    if (V EQUAL 6)
        target_link_libraries(qwtplot3d_shared PUBLIC Qt6::OpenGLWidgets)
    else ()
        target_link_libraries(qwtplot3d_shared PUBLIC Qt${V}::OpenGL)
    endif ()
endif ()

include(GNUInstallDirs)
install(TARGETS qwtplot3d_static
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
if (BUILD_SHARED_LIBS)
    install(TARGETS qwtplot3d_shared
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
endif ()
install(FILES ${HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/qwtplot3d)
