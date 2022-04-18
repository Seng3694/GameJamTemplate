cmake_minimum_required(VERSION 3.5)

project(gjt CXX)

set(MAJOR_VERSION 0)
set(MINOR_VERSION 0)

if(WIN32)
	set(SFML_STATIC_LIBRARIES TRUE)
endif()

set(ENGINE_HEADERS
	include/AnimatedSprite.hpp
	include/Animation.hpp
	include/AudioManager.hpp
	include/ContentManager.hpp
	include/CustomMath.hpp
	include/Game.hpp
	include/GameState.hpp
	include/Line.hpp
	include/MessageDispatcher.hpp
	include/MessageSubscriber.hpp
	include/ServiceLocator.hpp
	include/Tileset.hpp
	include/Version.hpp
)

set(ENGINE_SOURCES
	src/Animation.cpp
	src/Game.cpp
	src/Line.cpp
	src/Tileset.cpp
)

add_library(${PROJECT_NAME} STATIC ${ENGINE_HEADERS} ${ENGINE_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC include)

find_package(SFML 2.5 COMPONENTS system main graphics window audio REQUIRED)

if(SFML_FOUND)
	target_include_directories(${PROJECT_NAME} PUBLIC ${SFML_DIR}/../../../include)
	target_link_libraries(${PROJECT_NAME} sfml-system sfml-main sfml-graphics sfml-window sfml-audio)
endif()

add_custom_command(
    TARGET ${PROJECT_NAME}
    PRE_BUILD
    COMMAND ${CMAKE_COMMAND}
        -DMAJOR_VERSION=${MAJOR_VERSION} -DMINOR_VERSION=${MINOR_VERSION} -P "cmake/SetVersion.cmake"
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
