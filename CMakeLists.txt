cmake_mininum_required(VERSION 3.10)

project(book-manager VERSION 1.0.0 LANGUAGES C)
set(CMAKE_BUILD_TYPE Release)

add_executable(book-manager-server main.c)


TARGET_LINK_LIBRARIES(${PROJECT_NAME} libmysqlclient.so)
