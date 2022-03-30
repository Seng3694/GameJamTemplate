set(SOURCES
	imgui.cpp
	imgui_demo.cpp
	imgui_draw.cpp
	imgui_widgets.cpp
	imgui_tables.cpp
	misc/cpp/imgui_stdlib.cpp
	imgui-sfml/imgui-SFML.cpp
)

add_library(imgui STATIC ${SOURCES})
target_include_directories(imgui PUBLIC . misc/cpp imgui-sfml)
target_link_libraries(imgui sfml-system sfml-graphics)
