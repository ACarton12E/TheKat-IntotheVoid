# Created by and for Qt Creator This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

cmake_minimum_required(VERSION 3.5)
project(TheKatITV)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

include_directories(
    src
    src/assets/download
    src/code/Collectoon
    src/code/Enemies/Fishoder
    src/code/Enemies/Shadowner
    src/code/Enemies/Spikader
    src/code/Platform
    src/code/Player
    src/code/UI
    src/code/Water
    src/include/SDL2
    src/scenes/arcade
)

set (SRCS
    src/assets/download/assets.cpp
    src/assets/download/assets.h
    src/code/Collectoon/collectoon.cpp
    src/code/Collectoon/collectoon.h
    src/code/Enemies/Fishoder/fishoder.cpp
    src/code/Enemies/Fishoder/fishoder.h
    src/code/Enemies/Shadowner/shadowner.cpp
    src/code/Enemies/Shadowner/shadowner.h
    src/code/Enemies/Spikader/spikader.cpp
    src/code/Enemies/Spikader/spikader.h
    src/code/Platform/platform.cpp
    src/code/Platform/platform.h
    src/code/Player/player.cpp
    src/code/Player/player.h
    src/code/UI/UI.cpp
    src/code/UI/UI.h
    src/code/Water/water.cpp
    src/code/Water/water.h
    src/include/SDL2/begin_code.h
    src/include/SDL2/close_code.h
    src/include/SDL2/SDL.h
    src/include/SDL2/SDL_assert.h
    src/include/SDL2/SDL_atomic.h
    src/include/SDL2/SDL_audio.h
    src/include/SDL2/SDL_bits.h
    src/include/SDL2/SDL_blendmode.h
    src/include/SDL2/SDL_clipboard.h
    src/include/SDL2/SDL_config.h
    src/include/SDL2/SDL_config_android.h
    src/include/SDL2/SDL_config_emscripten.h
    src/include/SDL2/SDL_config_iphoneos.h
    src/include/SDL2/SDL_config_macosx.h
    src/include/SDL2/SDL_config_minimal.h
    src/include/SDL2/SDL_config_ngage.h
    src/include/SDL2/SDL_config_os2.h
    src/include/SDL2/SDL_config_pandora.h
    src/include/SDL2/SDL_config_windows.h
    src/include/SDL2/SDL_config_wingdk.h
    src/include/SDL2/SDL_config_winrt.h
    src/include/SDL2/SDL_config_xbox.h
    src/include/SDL2/SDL_copying.h
    src/include/SDL2/SDL_cpuinfo.h
    src/include/SDL2/SDL_egl.h
    src/include/SDL2/SDL_endian.h
    src/include/SDL2/SDL_error.h
    src/include/SDL2/SDL_events.h
    src/include/SDL2/SDL_filesystem.h
    src/include/SDL2/SDL_gamecontroller.h
    src/include/SDL2/SDL_gesture.h
    src/include/SDL2/SDL_guid.h
    src/include/SDL2/SDL_haptic.h
    src/include/SDL2/SDL_hidapi.h
    src/include/SDL2/SDL_hints.h
    src/include/SDL2/SDL_image.h
    src/include/SDL2/SDL_joystick.h
    src/include/SDL2/SDL_keyboard.h
    src/include/SDL2/SDL_keycode.h
    src/include/SDL2/SDL_loadso.h
    src/include/SDL2/SDL_locale.h
    src/include/SDL2/SDL_log.h
    src/include/SDL2/SDL_main.h
    src/include/SDL2/SDL_messagebox.h
    src/include/SDL2/SDL_metal.h
    src/include/SDL2/SDL_misc.h
    src/include/SDL2/SDL_mixer.h
    src/include/SDL2/SDL_mouse.h
    src/include/SDL2/SDL_mutex.h
    src/include/SDL2/SDL_name.h
    src/include/SDL2/SDL_opengl.h
    src/include/SDL2/SDL_opengl_glext.h
    src/include/SDL2/SDL_opengles.h
    src/include/SDL2/SDL_opengles2.h
    src/include/SDL2/SDL_opengles2_gl2.h
    src/include/SDL2/SDL_opengles2_gl2ext.h
    src/include/SDL2/SDL_opengles2_gl2platform.h
    src/include/SDL2/SDL_opengles2_khrplatform.h
    src/include/SDL2/SDL_pixels.h
    src/include/SDL2/SDL_platform.h
    src/include/SDL2/SDL_power.h
    src/include/SDL2/SDL_quit.h
    src/include/SDL2/SDL_rect.h
    src/include/SDL2/SDL_render.h
    src/include/SDL2/SDL_revision.h
    src/include/SDL2/SDL_rwops.h
    src/include/SDL2/SDL_scancode.h
    src/include/SDL2/SDL_sensor.h
    src/include/SDL2/SDL_shape.h
    src/include/SDL2/SDL_stdinc.h
    src/include/SDL2/SDL_surface.h
    src/include/SDL2/SDL_system.h
    src/include/SDL2/SDL_syswm.h
    src/include/SDL2/SDL_test.h
    src/include/SDL2/SDL_test_assert.h
    src/include/SDL2/SDL_test_common.h
    src/include/SDL2/SDL_test_compare.h
    src/include/SDL2/SDL_test_crc32.h
    src/include/SDL2/SDL_test_font.h
    src/include/SDL2/SDL_test_fuzzer.h
    src/include/SDL2/SDL_test_harness.h
    src/include/SDL2/SDL_test_images.h
    src/include/SDL2/SDL_test_log.h
    src/include/SDL2/SDL_test_md5.h
    src/include/SDL2/SDL_test_memory.h
    src/include/SDL2/SDL_test_random.h
    src/include/SDL2/SDL_thread.h
    src/include/SDL2/SDL_timer.h
    src/include/SDL2/SDL_touch.h
    src/include/SDL2/SDL_ttf.h
    src/include/SDL2/SDL_types.h
    src/include/SDL2/SDL_version.h
    src/include/SDL2/SDL_video.h
    src/include/SDL2/SDL_vulkan.h
    src/plugins/betterInit/betterInit.hpp
    src/plugins/betterInput/betterInput.hpp
    src/plugins/camera/camera.h
    src/plugins/JSON/json.hpp
    src/assets/json/players/thekat.json
    src/plugins/particles/particle.cpp
    src/plugins/particles/particle.h
    src/scenes/arcade/arcade.cpp
    src/scenes/arcade/arcade.h
    src/Global.h
    src/main.cpp
    Wii/Makefile.wii
)


add_executable(${CMAKE_PROJECT_NAME} ${SRCS})

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE )
