# Copyright (C) - Jean-S�bastien Fauteux 2017
# This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. 
# To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to 
# Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.

cmake_minimum_required(VERSION 3.0)

project(TFWR)

if(UNIX)
	include(CheckCXXCompilerFlag)
	check_cxx_compiler_flag("-std=c++14" COMPILER_SUPPORTS_CXX14)
	check_cxx_compiler_flag("-std=c++11" COMPILER_SUPPORTS_CXX11)
	check_cxx_compiler_flag("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
	if(COMPILER_SUPPORTS_CXX14)
		set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++14")
	elseif(COMPILER_SUPPORTS_CXX11)
		set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11")
	elseif(COMPILER_SUPPORTS_CXX0X)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
	else()
		MESSAGE(STATUS "The Compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use one that supports C++11.")
	endif()
endif()

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/Modules/;${CMAKE_MODULE_PATH}")

if(WIN32)
    find_package(SFML 2 COMPONENTS graphics window system main)
else()
    find_package(SFML 2 COMPONENTS graphics window system)
endif()
find_package(THOR 2)
find_package(OpenGL)

include_directories("include")
include_directories("include/external/imgui")
include_directories("include/external/imgui-sfml")
include_directories("include/external/rsm_utils/include")

if(SFML_FOUND)
	include_directories(${SFML_INCLUDE_DIR})
else()
	set(SFML_ROOT "" CACHE PATH "SFML top-level directory")
endif(SFML_FOUND)

if(THOR_FOUND)
	include_directories(${THOR_INCLUDE_DIR})
	include_directories(./include/external/aurora/include)
else()
	set(THOR_ROOT "" CACHE PATH "Thor top-level directory")
endif(THOR_FOUND)

set(ImGui_Src
	./include/external/imgui/imgui.cpp
	./include/external/imgui/imgui_draw.cpp
	./include/external/imgui/imconfig.h
	./include/external/imgui/imgui.h
	./include/external/imgui/imgui_internal.h
	./include/external/imgui/stb_rect_pack.h
	./include/external/imgui/stb_textedit.h
	./include/external/imgui/stb_truetype.h
	)

source_group("ImGui" FILES ${ImGui_Src})

set(ImGui_sfml_Src
	./include/external/imgui-sfml/imgui-SFML.cpp
	./include/external/imgui-sfml/imgui-SFML.h
	./include/external/imgui-sfml/imconfig-SFML.h
)

source_group("ImGui SFML" FILES ${ImGui_sfml_Src})


set(Game_State_Inc
	./include/state.hpp
	./include/app_loading_state.hpp
	./include/main_menu_state.hpp
	./include/state_stack.hpp
	./include/stateids.hpp
	)

source_group("Header Files\\States" FILES ${Game_State_Inc})

set(Game_Gui_Inc
	./include/animatedtext.hpp
	./include/guicomponent.hpp
	./include/selectabletext.hpp
	./include/text.hpp
	)

source_group("Header Files\\Gui" FILES ${Game_Gui_Inc})

set(Game_Inc
	./include/message_handler.hpp
	./include/message_dispatcher.hpp
	./include/message.hpp
	./include/application.hpp
	./include/resourceids.hpp
	${Game_State_Inc}
	${Game_Gui_Inc}
	)

set(Game_State_Src
	./src/state.cpp
	./src/app_loading_state.cpp
	./src/main_menu_state.cpp
	./src/state_stack.cpp
	./src/text.cpp
	)

source_group("Source Files\\States" FILES ${Game_State_Src})

set(Game_Gui_Src
	./src/animatedtext.cpp
	./src/guicomponent.cpp
	./src/selectabletext.cpp
	)

source_group("Source Files\\Gui" FILES ${Game_Gui_Src})

set(Game_Src
	./src/main.cpp
	./src/message_dispatcher.cpp
	./src/application.cpp
	${Game_State_Src}
	${Game_Gui_Src}
	)

add_executable(TFWR
    MACOSX_BUNDLE
	${Game_Src}
	${Game_Inc}
	${ImGui_Src}
	${ImGui_sfml_Src}
	)

target_link_libraries(TFWR ${THOR_LIBRARY} ${SFML_LIBRARIES} ${OPENGL_gl_LIBRARY})

if(WIN32)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX")
	set_target_properties(TFWR PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall")
endif()

add_custom_command(TARGET TFWR
		POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:TFWR>
		)
