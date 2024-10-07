cmake_minimum_required(VERSION 3.14)

project(Tetris_56065_56117 LANGUAGES CXX)


set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "-Wall -pedantic-errors")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

add_executable(Tetris_56065_56117
  main.cpp
  Board.h
  Board.cpp
  brick.h
  position.h
  position.cpp
  brick.cpp
  brickFactory.cpp
  brickFactory.h
  Controler.h
  Controler.cpp
  view.h
  view.cpp
  game.h
  game.cpp
  dimensiondialog.h
  dimensiondialog.cpp
  mainwindow.h mainwindow.cpp mainwindow.ui




)
target_link_libraries(Tetris_56065_56117 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)


include(GNUInstallDirs)
install(TARGETS Tetris_56065_56117
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
