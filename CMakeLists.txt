cmake_minimum_required(VERSION 3.5)

project(GameJamTemplate CXX)

set(SFML_STATIC_LIBRARIES TRUE)

add_subdirectory(ext)

set(INCLUDE_DIRS
	include
)

set(HEADERS
	include/AudioManager.hpp
	include/ContentManager.hpp
	include/ContentManager.inl
	include/CustomMath.hpp
	include/CustomMath.inl
	include/Game.hpp
	include/Game.inl
	include/GameState.hpp
	include/ServiceLocator.hpp
	include/ServiceLocator.inl
	include/TestState.hpp
)

set(SOURCES
	src/Game.cpp
	src/Main.cpp
)

include_directories(${INCLUDE_DIRS})
add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})

find_package(SFML 2.5 COMPONENTS main graphics audio REQUIRED)

if(SFML_FOUND)
	target_include_directories(${PROJECT_NAME} PUBLIC ${SFML_DIR}/include)
	target_link_libraries(${PROJECT_NAME} sfml-main sfml-graphics sfml-audio)
	add_custom_command(
		TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${SFML_DIR}/../../../bin/openal32.dll"
                $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif()

target_link_libraries(${PROJECT_NAME} imgui)

if(EXISTS ${CMAKE_SOURCE_DIR}/content)
	add_custom_command(
		TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
				${CMAKE_SOURCE_DIR}/content
				${CMAKE_CURRENT_BINARY_DIR}/content
	)
endif()
