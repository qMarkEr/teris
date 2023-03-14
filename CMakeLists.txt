cmake_minimum_required(VERSION 3.22)
project(tetris C)

set(CMAKE_C_STANDARD 11)
set(CURSES_NEED_NCURSES TRUE)
find_package(Curses REQUIRED)

add_executable(tetris main.c controls.c render.c render.h figures.c figures.h)
target_link_libraries(tetris m ncurses)
target_link_libraries(${PROJECT_NAME} ncurses)
#if (CURSES_FOUND AND CURSES_HAVE_NCURSES_H)
#    include_directories(${CURSES_INCLUDE_DIR})
#    target_link_libraries (tetris ${CURSES_LIBRARIES})
#endif()