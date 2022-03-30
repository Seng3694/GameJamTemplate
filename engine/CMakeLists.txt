set(ENGINE_HEADERS
	include/AudioManager.hpp
	include/ContentManager.hpp
	include/CustomMath.hpp
	include/Game.hpp
	include/GameState.hpp
	include/ParticleSystem.hpp
	include/ServiceLocator.hpp
)

set(ENGINE_SOURCES
	src/Game.cpp
	src/ParticleSystem.cpp
)
add_library(gjt_engine STATIC ${ENGINE_HEADERS} ${ENGINE_SOURCES})
target_include_directories(gjt_engine PUBLIC include)

target_link_libraries(gjt_engine sfml-main sfml-system sfml-graphics sfml-window sfml-audio)

#if(CMAKE_SIZEOF_VOID_P EQUAL 8)
#	set(PLATFORM_CONFIG x64)
#elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
#	set(PLATFORM_CONFIG x86)
#endif()

#add_custom_command(
#	TARGET gjt_engine POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy_if_different
#            ${CMAKE_SOURCE_DIR}/ext/SFML/extlibs/bin/${PLATFORM_CONFIG}/openal32.dll
#            $<TARGET_FILE_DIR:gjt_engine>)

target_link_libraries(gjt_engine imgui)
