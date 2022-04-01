cmake_minimum_required(VERSION 3.5)

project(GameJamTemplate)
set(SFML_STATIC_LIBRARIES TRUE)

add_subdirectory(ext)
add_subdirectory(engine)
add_subdirectory(game)
