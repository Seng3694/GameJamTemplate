
set(ENGINE_HEADERS
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
)

set(ENGINE_SOURCES
	src/Game.cpp
)

add_library(gjt_engine ${ENGINE_HEADERS} ${ENGINE_SOURCES})
target_include_directories(gjt_engine PUBLIC include)

find_package(SFML 2.5 COMPONENTS main graphics audio REQUIRED)

if(SFML_FOUND)
	target_include_directories(gjt_engine PUBLIC ${SFML_DIR}/include)
	target_link_libraries(gjt_engine sfml-main sfml-graphics sfml-audio)
	add_custom_command(
		TARGET gjt_engine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${SFML_DIR}/../../../bin/openal32.dll"
                $<TARGET_FILE_DIR:gjt_engine>)
endif()

target_link_libraries(gjt_engine imgui)
