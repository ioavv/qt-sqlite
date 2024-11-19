cmake_minimum_required(VERSION 3.16)

project(qt-sqlite VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick Sql)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appqt-sqlite
    main.cpp
)

qt_add_qml_module(appqt-sqlite
    URI qt-sqlite
    VERSION 1.0
    QML_FILES
        Main.qml
        SOURCES databasemanager.h databasemanager.cpp
)


set_target_properties(appqt-sqlite PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appqt-sqlite
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appqt-sqlite
    PRIVATE Qt6::Quick
    PRIVATE Qt6::Sql
)

include(GNUInstallDirs)
install(TARGETS appqt-sqlite
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
