cmake_minimum_required(VERSION 3.20)

project(PS2Runtime VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(PS2X_ENABLE_RUNNER_UNITY_BUILD "Build ps2EntryRunner with CMake unity build" ON)
set(PS2X_RUNNER_UNITY_BUILD_BATCH_SIZE 32 CACHE STRING "Unity build batch size for ps2EntryRunner")
option(PS2X_ENABLE_RUNNER_PCH "Precompile the heavy runtime headers for ps2EntryRunner" ON)
option(PS2X_ENABLE_SCCACHE "Use sccache as compiler launcher when available" ON)

option(PS2X_ENABLE_RUNTIME_LOGS "Enable PS2 runtime logs" ON)
option(PS2X_ENABLE_AGRESSIVE_LOGS "Enable very verbose/agressive PS2 runtime logs" ON)
option(PS2X_ENABLE_IOP_RPC_TRACE "Log unhandled IOP/SIF RPC trace suggestions" ON)
option(PS2X_STRICT_RETURN_DIAGNOSTICS "Route generated JR $ra returns through runtime branch diagnostics" OFF)
option(PS2X_SHOW_WINDOWS_CONSOLE "Show a console window for ps2EntryRunner on Windows release builds" ON)
option(PS2X_ENABLE_DEBUG_UI "Build the desktop runtime debug UI" ON)

if(PS2X_ENABLE_SCCACHE)
    find_program(PS2X_SCCACHE_PROGRAM sccache)

    if(PS2X_SCCACHE_PROGRAM)
        if(CMAKE_C_COMPILER)
            set(CMAKE_C_COMPILER_LAUNCHER "${PS2X_SCCACHE_PROGRAM}")
        endif()

        set(CMAKE_CXX_COMPILER_LAUNCHER "${PS2X_SCCACHE_PROGRAM}")
        message(STATUS "Using sccache: ${PS2X_SCCACHE_PROGRAM}")
    else()
        message(STATUS "sccache not found; continuing without compiler launcher")
    endif()
endif()

include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/ReleaseMode.cmake")

set(PS2X_IS_VITA OFF)

if((CMAKE_C_COMPILER MATCHES "arm-vita-eabi") OR
    (CMAKE_CXX_COMPILER MATCHES "arm-vita-eabi"))
    set(PS2X_IS_VITA ON)
endif()

set(PS2X_IS_ANDROID OFF)

if(ANDROID)
    set(PS2X_IS_ANDROID ON)
endif()

option(PS2X_VITA_CREATE_PACKAGE "Create Vita eboot/vpk targets" ON)
set(PS2X_VITA_APP_NAME "PS2 Retro X" CACHE STRING "Display name for the Vita bubble")
set(PS2X_VITA_TITLEID "RANJ00001" CACHE STRING "9-character Vita title id")
set(PS2X_VITA_VERSION "01.00" CACHE STRING "Vita app version")
set(PS2X_DEFAULT_BOOT_ELF "" CACHE STRING "Guest ELF path passed directly to main() when argv is unavailable")

if(PS2X_IS_VITA)
    if(NOT DEFINED ENV{VITASDK})
        message(FATAL_ERROR "VITASDK is not defined. Configure inside the VitaSDK environment or pass the Vita toolchain file.")
    endif()

    set(PS2X_VITASDK "$ENV{VITASDK}")

    if(NOT EXISTS "${PS2X_VITASDK}/share/vita.cmake")
        message(FATAL_ERROR "Could not find vita.cmake under ${PS2X_VITASDK}/share.")
    endif()

    include("${PS2X_VITASDK}/share/vita.cmake" REQUIRED)
else()
    include(FetchContent)
    set(FETCHCONTENT_QUIET FALSE)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(BUILD_GAMES OFF CACHE BOOL "" FORCE)

    if(PS2X_IS_ANDROID)
        set(PLATFORM "Android" CACHE STRING "" FORCE)
    endif()

    FetchContent_Declare(
        raylib
        GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
        GIT_TAG "5.5" # we will migrate to 4.2.0 later, trust me it will be better
        GIT_PROGRESS TRUE
    )
    FetchContent_MakeAvailable(raylib)

    if(PS2X_ENABLE_DEBUG_UI AND NOT PS2X_IS_ANDROID)
        FetchContent_Declare(
            imgui
            GIT_REPOSITORY https://github.com/ocornut/imgui.git
            GIT_TAG "v1.92.7-docking"
            GIT_SHALLOW TRUE
        )
        FetchContent_GetProperties(imgui)

        if(NOT imgui_POPULATED)
            FetchContent_Populate(imgui)
        endif()

        set(PS2X_IMGUI_SOURCE_DIR "${imgui_SOURCE_DIR}")

        add_library(imgui STATIC
            "${PS2X_IMGUI_SOURCE_DIR}/imgui.cpp"
            "${PS2X_IMGUI_SOURCE_DIR}/imgui_draw.cpp"
            "${PS2X_IMGUI_SOURCE_DIR}/imgui_tables.cpp"
            "${PS2X_IMGUI_SOURCE_DIR}/imgui_widgets.cpp"
            "${PS2X_IMGUI_SOURCE_DIR}/imgui_demo.cpp"
        )
        target_include_directories(imgui PUBLIC "${PS2X_IMGUI_SOURCE_DIR}")

        FetchContent_Declare(
            rlImGui
            GIT_REPOSITORY https://github.com/raylib-extras/rlImGui.git
            GIT_TAG "Raylib_5_5"
            GIT_SHALLOW TRUE
        )
        FetchContent_GetProperties(rlImGui)

        if(NOT rlimgui_POPULATED)
            FetchContent_Populate(rlImGui)
        endif()

        set(PS2X_RLIMGUI_SOURCE_DIR "${rlimgui_SOURCE_DIR}")

        add_library(rlImGui STATIC
            "${PS2X_RLIMGUI_SOURCE_DIR}/rlImGui.cpp"
        )
        target_include_directories(rlImGui PUBLIC "${PS2X_RLIMGUI_SOURCE_DIR}")
        target_link_libraries(rlImGui PUBLIC raylib imgui)
    endif()
endif()

add_library(ps2_host_backend INTERFACE)

set(PS2X_DEFAULT_BOOT_ELF_DEFINE "")

if(PS2X_DEFAULT_BOOT_ELF)
    set(PS2X_DEFAULT_BOOT_ELF_DEFINE "${PS2X_DEFAULT_BOOT_ELF}")
    string(REPLACE "\\" "\\\\" PS2X_DEFAULT_BOOT_ELF_DEFINE "${PS2X_DEFAULT_BOOT_ELF_DEFINE}")
    string(REPLACE "\"" "\\\"" PS2X_DEFAULT_BOOT_ELF_DEFINE "${PS2X_DEFAULT_BOOT_ELF_DEFINE}")
endif()

if(PS2X_IS_VITA)
    set(PS2X_VITA_PREFIX "${PS2X_VITASDK}/arm-vita-eabi")
    set(PS2X_VITA_EXTRA_INCLUDE_DIRS "" CACHE STRING "Extra include directories for Vita host dependencies")
    set(PS2X_VITA_LIBRARY_DIR "${PS2X_VITA_PREFIX}/lib")
    set(PS2X_VITA_REQUIRED_LIBRARY_NAMES
        raylib
        SDL2
        OpenSLES
        taihen_stub
        SceAppMgr_stub
        SceCtrl_stub
        SceGxm_stub
        SceCommonDialog_stub
        SceLibKernel_stub
        SceAudio_stub
        SceTouch_stub
        SceHid_stub
        SceMotion_stub
        SceSysmodule_stub
        SceIofilemgr_stub
        SceNetCtl_stub
        SceNet_stub
        SceDisplay_stub
        SceAppUtil_stub
        SceAudioIn_stub
        ScePower_stub
        SceProcessmgr_stub
        SceIme_stub
        libIMGEGL_stub_weak
        libgpu_es4_ext_stub_weak
        libGLESv2_stub_weak
        libGL_stub_weak
        libGLESv1_CM_stub_weak
    )

    set(PS2X_VITA_INCLUDE_DIRS
        "${PS2X_VITA_PREFIX}/include"
    )

    foreach(PS2X_VITA_OPTIONAL_INCLUDE_DIR IN ITEMS
        "${PS2X_VITA_PREFIX}/include/raylib"
        "${PS2X_VITA_PREFIX}/include/SDL2")
        if(EXISTS "${PS2X_VITA_OPTIONAL_INCLUDE_DIR}")
            list(APPEND PS2X_VITA_INCLUDE_DIRS "${PS2X_VITA_OPTIONAL_INCLUDE_DIR}")
        endif()
    endforeach()

    if(PS2X_VITA_EXTRA_INCLUDE_DIRS)
        list(APPEND PS2X_VITA_INCLUDE_DIRS ${PS2X_VITA_EXTRA_INCLUDE_DIRS})
    endif()

    if(NOT EXISTS "${PS2X_VITA_PREFIX}/include/SDL2/SDL.h")
        message(FATAL_ERROR
            "Missing SDL2 headers under ${PS2X_VITA_PREFIX}/include/SDL2. "
            "Quenom/raylib-5.5-vita requires SDL2 with PVR support installed into VitaSDK.")
    endif()

    if(NOT EXISTS "${PS2X_VITA_LIBRARY_DIR}")
        message(FATAL_ERROR "Missing Vita library directory: ${PS2X_VITA_LIBRARY_DIR}")
    endif()

    function(ps2x_find_vita_library out_var library_name)
        string(MAKE_C_IDENTIFIER "${library_name}" library_id)
        set(cache_var "PS2X_VITA_LIB_${library_id}")

        find_library(${cache_var}
            NAMES "${library_name}" "${library_name}.a" "lib${library_name}.a"
            PATHS "${PS2X_VITA_LIBRARY_DIR}"
            NO_DEFAULT_PATH
        )

        if(NOT ${cache_var})
            message(FATAL_ERROR
                "Could not find Vita library '${library_name}' under ${PS2X_VITA_LIBRARY_DIR}. "
                "Install Quenom/raylib-5.5-vita and its SDL2/PVR dependencies into VitaSDK first.")
        endif()

        set(${out_var} "${${cache_var}}" PARENT_SCOPE)
    endfunction()

    set(PS2X_VITA_RESOLVED_LIBRARIES "")

    foreach(PS2X_VITA_LIBRARY_NAME IN LISTS PS2X_VITA_REQUIRED_LIBRARY_NAMES)
        ps2x_find_vita_library(PS2X_VITA_LIBRARY_PATH "${PS2X_VITA_LIBRARY_NAME}")
        list(APPEND PS2X_VITA_RESOLVED_LIBRARIES "${PS2X_VITA_LIBRARY_PATH}")
    endforeach()

    target_compile_definitions(ps2_host_backend INTERFACE PLATFORM_VITA)
    target_include_directories(ps2_host_backend INTERFACE ${PS2X_VITA_INCLUDE_DIRS})
    target_link_libraries(ps2_host_backend INTERFACE
        ${PS2X_VITA_RESOLVED_LIBRARIES}
        m
        c
        pthread
    )
else()
    target_link_libraries(ps2_host_backend INTERFACE raylib)

    if(PS2X_IS_ANDROID)
        target_link_libraries(ps2_host_backend INTERFACE log android)
    endif()
endif()

# GOW-Port: MPEG video (FMV) is decoded by the vendored libmpeg2 (third_party/libmpeg2, portable C, also builds for
# the Switch). FFmpeg stays available as an opt-in alternative backend.
add_library(libmpeg2 STATIC
    third_party/libmpeg2/alloc.c
    third_party/libmpeg2/cpu_accel.c
    third_party/libmpeg2/cpu_state.c
    third_party/libmpeg2/decode.c
    third_party/libmpeg2/header.c
    third_party/libmpeg2/idct.c
    third_party/libmpeg2/motion_comp.c
    third_party/libmpeg2/slice.c
)
target_include_directories(libmpeg2 PUBLIC third_party/libmpeg2)
if(MSVC)
    target_compile_options(libmpeg2 PRIVATE /W0)
endif()

option(PS2X_ENABLE_FFMPEG "Decode MPEG video with FFmpeg instead of libmpeg2" OFF)

if(NOT PS2X_ENABLE_FFMPEG)
    add_library(ffmpeg INTERFACE)
elseif(WIN32)
    include(ExternalProject)

    set(FFMPEG_PREBUILT_TAG "n7.1-241205")
    set(FFMPEG_PREBUILT_URL
        "https://github.com/System233/ffmpeg-msvc-prebuilt/releases/download/${FFMPEG_PREBUILT_TAG}/ffmpeg-${FFMPEG_PREBUILT_TAG}-lgpl-amd64-shared.zip")

    set(FFMPEG_PREFIX_DIR "${CMAKE_BINARY_DIR}/ThirdParty/ffmpeg-prefix")
    set(FFMPEG_SOURCE_DIR "${FFMPEG_PREFIX_DIR}/src/ffmpeg_external")
    set(FFMPEG_INCLUDE_DIR "${FFMPEG_SOURCE_DIR}/include")
    set(FFMPEG_LIB_DIR "${FFMPEG_SOURCE_DIR}/bin")
    set(FFMPEG_BIN_DIR "${FFMPEG_SOURCE_DIR}/bin")

    ExternalProject_Add(ffmpeg_external
        URL "${FFMPEG_PREBUILT_URL}"
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
        PREFIX "${FFMPEG_PREFIX_DIR}"
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
        BUILD_BYPRODUCTS
        "${FFMPEG_LIB_DIR}/avcodec.lib"
        "${FFMPEG_LIB_DIR}/avformat.lib"
        "${FFMPEG_LIB_DIR}/avutil.lib"
        "${FFMPEG_LIB_DIR}/swresample.lib"
        "${FFMPEG_LIB_DIR}/swscale.lib"
    )

    # Link against the import libraries shipped with the Windows DLLs.
    add_library(ffmpeg_avcodec STATIC IMPORTED GLOBAL)
    set_target_properties(ffmpeg_avcodec PROPERTIES
        IMPORTED_LOCATION "${FFMPEG_LIB_DIR}/avcodec.lib"
        INTERFACE_INCLUDE_DIRECTORIES "${FFMPEG_INCLUDE_DIR}"
    )
    add_dependencies(ffmpeg_avcodec ffmpeg_external)

    add_library(ffmpeg_avformat STATIC IMPORTED GLOBAL)
    set_target_properties(ffmpeg_avformat PROPERTIES
        IMPORTED_LOCATION "${FFMPEG_LIB_DIR}/avformat.lib"
        INTERFACE_INCLUDE_DIRECTORIES "${FFMPEG_INCLUDE_DIR}"
    )
    add_dependencies(ffmpeg_avformat ffmpeg_external)

    add_library(ffmpeg_avutil STATIC IMPORTED GLOBAL)
    set_target_properties(ffmpeg_avutil PROPERTIES
        IMPORTED_LOCATION "${FFMPEG_LIB_DIR}/avutil.lib"
        INTERFACE_INCLUDE_DIRECTORIES "${FFMPEG_INCLUDE_DIR}"
    )
    add_dependencies(ffmpeg_avutil ffmpeg_external)

    add_library(ffmpeg_swresample STATIC IMPORTED GLOBAL)
    set_target_properties(ffmpeg_swresample PROPERTIES
        IMPORTED_LOCATION "${FFMPEG_LIB_DIR}/swresample.lib"
        INTERFACE_INCLUDE_DIRECTORIES "${FFMPEG_INCLUDE_DIR}"
    )
    add_dependencies(ffmpeg_swresample ffmpeg_external)

    add_library(ffmpeg_swscale STATIC IMPORTED GLOBAL)
    set_target_properties(ffmpeg_swscale PROPERTIES
        IMPORTED_LOCATION "${FFMPEG_LIB_DIR}/swscale.lib"
        INTERFACE_INCLUDE_DIRECTORIES "${FFMPEG_INCLUDE_DIR}"
    )
    add_dependencies(ffmpeg_swscale ffmpeg_external)

    add_library(ffmpeg INTERFACE)
    target_link_libraries(ffmpeg INTERFACE
        ffmpeg_avcodec
        ffmpeg_avformat
        ffmpeg_avutil
        ffmpeg_swresample
        ffmpeg_swscale
        bcrypt
        secur32
        ws2_32
        user32
        advapi32
        ole32
        shell32
    )

    set(PS2X_FFMPEG_BIN_DIR "${FFMPEG_BIN_DIR}" CACHE INTERNAL "Directory containing FFmpeg runtime DLLs")
    set(PS2X_COPY_FFMPEG_DLLS_SCRIPT
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/CopyFfmpegDlls.cmake"
        CACHE INTERNAL
        "Script used to stage FFmpeg runtime DLLs beside executables")
else()
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(FFMPEG REQUIRED IMPORTED_TARGET GLOBAL
        libavcodec
        libavformat
        libavutil
        libswresample
        libswscale
    )

    add_library(ffmpeg INTERFACE)
    target_link_libraries(ffmpeg INTERFACE PkgConfig::FFMPEG)
endif()

function(ps2x_stage_ffmpeg_runtime_dlls target_name)
    if(NOT WIN32)
        return()
    endif()

    if(NOT PS2X_FFMPEG_BIN_DIR OR NOT PS2X_COPY_FFMPEG_DLLS_SCRIPT)
        return()
    endif()

    if(TARGET ffmpeg_external)
        add_dependencies(${target_name} ffmpeg_external)
    endif()

    add_custom_command(
        TARGET ${target_name} POST_BUILD
        COMMAND "${CMAKE_COMMAND}"
        "-Dsource_dir=${PS2X_FFMPEG_BIN_DIR}"
        "-Ddest_dir=$<TARGET_FILE_DIR:${target_name}>"
        -P "${PS2X_COPY_FFMPEG_DLLS_SCRIPT}"
        VERBATIM
    )
endfunction()

add_library(ps2_runtime STATIC
    src/lib/game_overrides.cpp
    src/lib/gs/ps2_gif_arbiter.cpp
    src/lib/ps2_audio.cpp
    src/lib/ps2_audio_vag.cpp
    src/lib/gs/ps2_gs_memory.cpp
    src/lib/gs/gs_frontend.cpp
    src/lib/gs/gs_stage.cpp # GOW-Port: GS frontend stage pipelined behind VU1.
    src/lib/gs/gs_display.cpp # GOW-Port: native display state + GS FINISH handshake (no-emulation step 5).
    src/lib/gs/gs_host_present.cpp # GOW-Port: mismo consumidor de textura en juego y controles.
        # GOW-Port: backend OpenGL y cola del fork SotC ac9efa0 (GPL-3.0).
    src/lib/gs/gs_threaded_backend.cpp
    src/lib/gs/gs_swizzle.cpp
    src/lib/gs/gpu/gs_gl.cpp
    src/lib/gs/gpu/gs_hw_backend.cpp

src/lib/gs/gpu/gs_texture_store.cpp
    src/lib/ps2_iop_host.cpp
    src/lib/ps2_memory.cpp
    src/lib/ps2_pad.cpp
    # GOW-Port: funciones de Tobiichi Port sobre el runtime de Waffle (gow_integracion.cpp las conecta).
    src/lib/gow_integracion.cpp
    src/lib/gow_trucos.cpp
    src/lib/gow_video.cpp
    src/lib/gow_fijar.cpp
    src/lib/gow_cancelar.cpp
    src/lib/gow_sondeo.cpp
    src/lib/gow_espera.cpp
    src/lib/ps2_audio_device.cpp # GOW-Port: sound output on a chosen device
    src/lib/ps2_pad_rumble_win.cpp # GOW-Port: Windows gamepad rumble (XInput, DualShock 4 / DualSense)
    src/lib/ps2_rom_device.cpp
    src/lib/ps2_vfs.cpp
    src/lib/ps2_runtime.cpp
    src/lib/ps2_vif1_interpreter.cpp
    src/lib/vu/ps2_vu1_core.cpp
    # GOW-Port: EE differential tester (PS2X_EE_DIFF) with PCSX2's EE interpreter and VU0 ops (GPL-3.0+).
    src/lib/ee_ref/ee_diff.cpp
    src/lib/ee_watch.cpp
    src/lib/ee_ref/eeref.cpp
    src/lib/ee_ref/R5900OpcodeImpl.cpp
    src/lib/ee_ref/R5900OpcodeTables.cpp
    src/lib/ee_ref/MMI.cpp
    src/lib/ee_ref/FPU.cpp
    src/lib/vu_pcsx2/pcsx2_vu0_cop2.cpp
    src/lib/vu_pcsx2/pcsx2_vu1_bridge.cpp
    src/lib/vu_pcsx2/VUops.cpp
    src/lib/vu_pcsx2/VUflags.cpp
    src/lib/vu_pcsx2/VU1microInterp.cpp
    src/lib/vu/ps2_vu1_upper.cpp
    src/lib/vu/ps2_vu1_lower.cpp
    src/lib/games_database.cpp
)

if(PS2X_ENABLE_RUNTIME_LOGS)
    target_compile_definitions(ps2_runtime PUBLIC
        PS2_RUNTIME_LOGS=1
    )
endif()

if(PS2X_ENABLE_AGRESSIVE_LOGS)
    target_compile_definitions(ps2_runtime PUBLIC
        AGRESSIVE_LOGS=1
        PS2_FUNCTION_LOG_TRACKER=1
    )
endif()

if(PS2X_ENABLE_IOP_RPC_TRACE)
    target_compile_definitions(ps2_runtime PUBLIC
        PS2X_ENABLE_IOP_RPC_TRACE=1
    )
else()
    target_compile_definitions(ps2_runtime PUBLIC
        PS2X_ENABLE_IOP_RPC_TRACE=0
    )
endif()

if(PS2X_STRICT_RETURN_DIAGNOSTICS)
    target_compile_definitions(ps2_runtime PUBLIC
        PS2X_STRICT_RETURN_DIAGNOSTICS=1
    )
endif()

target_compile_definitions(ps2_runtime PRIVATE
    PS2X_HAS_FFMPEG=$<BOOL:${PS2X_ENABLE_FFMPEG}>
)

file(GLOB_RECURSE KERNEL_SRC_FILES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/lib/Kernel/*.cpp"
)

target_sources(ps2_runtime PRIVATE
    ${KERNEL_SRC_FILES}
)

file(GLOB RUNNER_SRC_FILES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/runner/*.cpp"
)

set(RUNNER_MAIN_CPP "${CMAKE_CURRENT_SOURCE_DIR}/src/runner/main.cpp")
set(ROOT_MAIN_CPP "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

if(EXISTS "${RUNNER_MAIN_CPP}")
    list(APPEND RUNNER_SRC_FILES "${RUNNER_MAIN_CPP}")
elseif(EXISTS "${ROOT_MAIN_CPP}")
    list(APPEND RUNNER_SRC_FILES "${ROOT_MAIN_CPP}")
endif()

if(PS2X_IS_ANDROID)
    add_library(ps2EntryRunner SHARED
        ${RUNNER_SRC_FILES}
    )

    target_link_options(ps2EntryRunner PRIVATE "-Wl,--undefined=ANativeActivity_onCreate")
else()
    add_executable(ps2EntryRunner
        ${RUNNER_SRC_FILES}
    )
endif()

if(PS2X_ENABLE_RUNNER_UNITY_BUILD)
    set_target_properties(ps2EntryRunner PROPERTIES
        UNITY_BUILD ON
        UNITY_BUILD_BATCH_SIZE "${PS2X_RUNNER_UNITY_BUILD_BATCH_SIZE}"
    )
endif()

if(PS2X_ENABLE_RUNNER_PCH)
    set(PS2X_RUNNER_PCH_HEADERS
        "${CMAKE_CURRENT_SOURCE_DIR}/include/ps2_runtime_macros.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/ps2_runtime.h"
    )

    foreach(PS2X_RUNNER_GENERATED_HEADER IN ITEMS
        "${CMAKE_CURRENT_SOURCE_DIR}/include/ps2_recompiled_functions.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/ps2_recompiled_stubs.h")
        if(EXISTS "${PS2X_RUNNER_GENERATED_HEADER}")
            list(APPEND PS2X_RUNNER_PCH_HEADERS "${PS2X_RUNNER_GENERATED_HEADER}")
        endif()
    endforeach()

    list(APPEND PS2X_RUNNER_PCH_HEADERS
        "${CMAKE_CURRENT_SOURCE_DIR}/include/ps2_syscalls.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/ps2_stubs.h"
    )

    target_precompile_headers(ps2EntryRunner PRIVATE ${PS2X_RUNNER_PCH_HEADERS})
endif()

if(PS2X_DEFAULT_BOOT_ELF_DEFINE)
    target_compile_definitions(ps2EntryRunner PRIVATE
        PS2X_DEFAULT_BOOT_ELF="${PS2X_DEFAULT_BOOT_ELF_DEFINE}"
    )
endif()

if(MSVC)
    target_compile_options(ps2EntryRunner PRIVATE /FS)
endif()

target_include_directories(ps2_runtime PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lib/Kernel
)
# GOW-Port (Linux): ee_ref/common/BitUtils.h incluye "common/Pcsx2Defs.h" relativo a ee_ref/; MSVC lo encuentra por
# la carpeta del archivo que lo incluye, GCC/Clang no. Solo para los fuentes de ee_ref (su R5900.h y Common.h
# no deben tapar los de vu_pcsx2).
set_source_files_properties(
    src/lib/ee_ref/ee_diff.cpp src/lib/ee_ref/eeref.cpp src/lib/ee_ref/R5900OpcodeImpl.cpp
    src/lib/ee_ref/R5900OpcodeTables.cpp src/lib/ee_ref/MMI.cpp src/lib/ee_ref/FPU.cpp
    PROPERTIES INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/src/lib/ee_ref")

target_link_libraries(ps2_runtime PUBLIC ps2_host_backend ffmpeg libmpeg2 ps2_iop)
if(WIN32)
    # GOW-Port: WGL propio del hilo GS.
    target_link_libraries(ps2_runtime PRIVATE opengl32 gdi32)
endif()
target_link_libraries(ps2EntryRunner
    PRIVATE
    ps2_runtime
)

# GOW-Port: microcódigo de VU1 compilado. PS2X_VU1_MICROCODE_DIR es una carpeta local con micromemorias de
# 16 KB capturadas con GOW_VU1_CAPTURA; PS2X_VU1_GENERATOR_SOURCE es tools/vu1/generar_vu1.cpp. El C++
# generado se enlaza en el ejecutable y el despachador lo usa en lugar del intérprete para los pares que
# coinciden. Son datos del juego: se generan en la carpeta de compilación y no se publican.
set(PS2X_VU1_MICROCODE_DIR "" CACHE PATH "Micromemorias de VU1 capturadas (vacío: solo intérprete)")
set(PS2X_VU1_GENERATOR_SOURCE "" CACHE FILEPATH "Generador de C++ para VU1 (tools/vu1/generar_vu1.cpp)")
if(PS2X_VU1_MICROCODE_DIR AND PS2X_VU1_GENERATOR_SOURCE AND NOT PS2X_IS_ANDROID AND NOT PS2X_IS_VITA)
    file(GLOB PS2X_VU1_IMAGES CONFIGURE_DEPENDS "${PS2X_VU1_MICROCODE_DIR}/*.bin")
    if(PS2X_VU1_IMAGES)
        add_executable(ps2x_vu1_generator "${PS2X_VU1_GENERATOR_SOURCE}")
        target_link_libraries(ps2x_vu1_generator PRIVATE ps2_runtime)
        set(PS2X_VU1_GENERATED_DIR "${CMAKE_CURRENT_BINARY_DIR}/vu1_generado")
        set(PS2X_VU1_GENERATED_PARTS)
        foreach(part RANGE 0 12)
            list(APPEND PS2X_VU1_GENERATED_PARTS "${PS2X_VU1_GENERATED_DIR}/programa${part}.cpp")
        endforeach()
        add_custom_command(OUTPUT ${PS2X_VU1_GENERATED_PARTS}
            COMMAND "${CMAKE_COMMAND}" -E make_directory "${PS2X_VU1_GENERATED_DIR}"
            # GOW-Port: la carpeta, no cada archivo: miles de rutas superan la línea de órdenes de Windows.
            COMMAND "$<TARGET_FILE:ps2x_vu1_generator>" "${PS2X_VU1_GENERATED_DIR}" "${PS2X_VU1_MICROCODE_DIR}"
            DEPENDS ps2x_vu1_generator ${PS2X_VU1_IMAGES}
            VERBATIM)
        target_sources(ps2EntryRunner PRIVATE ${PS2X_VU1_GENERATED_PARTS})
        set_source_files_properties(${PS2X_VU1_GENERATED_PARTS} PROPERTIES
            SKIP_UNITY_BUILD_INCLUSION ON
            SKIP_PRECOMPILE_HEADERS ON)
        target_include_directories(ps2EntryRunner PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/lib/vu")
        if(MSVC)
            set_source_files_properties(${PS2X_VU1_GENERATED_PARTS} PROPERTIES COMPILE_OPTIONS "/bigobj")
        endif()
        # GOW-Port: native lean backend (tools/vu1/vu1n_gen.py): straight-line blocks with immediate semantics.
        find_package(Python3 COMPONENTS Interpreter)
        set(PS2X_VU1N_GEN_OVERRIDE "" CACHE FILEPATH "Alternative vu1n_gen.py (empty: tools/vu1/vu1n_gen.py of the root repo)")
        if(PS2X_VU1N_GEN_OVERRIDE)
            set(PS2X_VU1N_GEN "${PS2X_VU1N_GEN_OVERRIDE}")
        else()
            get_filename_component(PS2X_VU1N_GEN "${CMAKE_CURRENT_SOURCE_DIR}/../../../tools/vu1/vu1n_gen.py" ABSOLUTE)
        endif()
        if(Python3_FOUND AND EXISTS "${PS2X_VU1N_GEN}")
            set(PS2X_VU1N_DIR "${CMAKE_CURRENT_BINARY_DIR}/vu1n_generado")
            set(PS2X_VU1N_PARTS)
            foreach(part RANGE 0 5)
                list(APPEND PS2X_VU1N_PARTS "${PS2X_VU1N_DIR}/vu1n_part${part}.cpp")
            endforeach()
            set(PS2X_VU1N_HEADS "${PS2X_VU1_MICROCODE_DIR}/../vu1n_heads.txt")
            get_filename_component(PS2X_VU1N_HEADS "${PS2X_VU1N_HEADS}" ABSOLUTE)
            set(PS2X_VU1N_HEADS_DEP)
            if(EXISTS "${PS2X_VU1N_HEADS}")
                set(PS2X_VU1N_HEADS_DEP "${PS2X_VU1N_HEADS}")
            endif()
            add_custom_command(OUTPUT ${PS2X_VU1N_PARTS}
                COMMAND "${Python3_EXECUTABLE}" -I "${PS2X_VU1N_GEN}" "${PS2X_VU1N_DIR}" "${PS2X_VU1_MICROCODE_DIR}" --heads "${PS2X_VU1N_HEADS}" --parts 6
                DEPENDS "${PS2X_VU1N_GEN}" ${PS2X_VU1_IMAGES} ${PS2X_VU1N_HEADS_DEP}
                VERBATIM)
            target_sources(ps2EntryRunner PRIVATE ${PS2X_VU1N_PARTS})
            set_source_files_properties(${PS2X_VU1N_PARTS} PROPERTIES
                SKIP_UNITY_BUILD_INCLUSION ON
                SKIP_PRECOMPILE_HEADERS ON)
            if(MSVC)
                set_source_files_properties(${PS2X_VU1N_PARTS} PROPERTIES COMPILE_OPTIONS "/bigobj")
            endif()
        endif()
        list(LENGTH PS2X_VU1_IMAGES PS2X_VU1_IMAGE_COUNT)
        message(STATUS "VU1 compilada: ${PS2X_VU1_IMAGE_COUNT} micromemorias en ${PS2X_VU1_MICROCODE_DIR}")
    endif()
endif()

if(PS2X_ENABLE_DEBUG_UI AND NOT PS2X_IS_VITA AND NOT PS2X_IS_ANDROID)
    target_sources(ps2EntryRunner PRIVATE
        src/lib/ps2_debug_panel.cpp
    )
    target_link_libraries(ps2EntryRunner PRIVATE rlImGui imgui)
    target_compile_definitions(ps2EntryRunner PRIVATE PS2X_ENABLE_DEBUG_UI=1)
endif()

ps2x_stage_ffmpeg_runtime_dlls(ps2EntryRunner)

if(PS2X_IS_VITA)
    set(VITA_MKSFOEX_FLAGS "${VITA_MKSFOEX_FLAGS} -d PARENTAL_LEVEL=1") 
    set(VITA_MKSFOEX_FLAGS "${VITA_MKSFOEX_FLAGS} -d ATTRIBUTE2=12")

    if(PS2X_VITA_CREATE_PACKAGE)
        set(PS2X_VITA_VPK_FILES "")

        foreach(PS2X_VITA_MODULE IN ITEMS
            libgpu_es4_ext.suprx
            libIMGEGL.suprx
            libGLESv2.suprx
            libpvrPSP2_WSEGL.suprx
            libGL.suprx)
            set(PS2X_VITA_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/vita/module/${PS2X_VITA_MODULE}")

            if(EXISTS "${PS2X_VITA_MODULE_PATH}")
                list(APPEND PS2X_VITA_VPK_FILES FILE "${PS2X_VITA_MODULE_PATH}" "module/${PS2X_VITA_MODULE}")
            else()
                message(WARNING
                    "Missing ${PS2X_VITA_MODULE_PATH}; the vpk will rely on ur0:data/external/ for it")
            endif()
        endforeach()

        vita_create_self(eboot.bin ps2EntryRunner UNSAFE)
        vita_create_vpk(ps2EntryRunner.vpk ${PS2X_VITA_TITLEID} eboot.bin
            VERSION ${PS2X_VITA_VERSION}
            NAME ${PS2X_VITA_APP_NAME}
            ${PS2X_VITA_VPK_FILES}
        )
    endif()
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    EnableFastReleaseMode(ps2_runtime)
    EnableFastReleaseMode(ps2EntryRunner)

    if(WIN32 AND NOT PS2X_SHOW_WINDOWS_CONSOLE)
        if(MSVC)
            target_link_options(ps2EntryRunner PRIVATE
                $<$<OR:$<CONFIG:Release>,$<CONFIG:RelWithDebInfo>>:/SUBSYSTEM:WINDOWS>
                $<$<OR:$<CONFIG:Release>,$<CONFIG:RelWithDebInfo>>:/ENTRY:mainCRTStartup>
            )
        elseif(MINGW)
            target_link_options(ps2EntryRunner PRIVATE
                $<$<OR:$<CONFIG:Release>,$<CONFIG:RelWithDebInfo>>:-mwindows>
            )
        endif()
    endif()
endif()

# Work around WinAPI vs raylib symbol clash for CloseWindow on x64
if(MSVC)
    target_link_options(ps2EntryRunner PRIVATE "/FORCE:MULTIPLE")
endif()

# Vita: Work around for GCC 10's LTO plugin
if(PS2X_IS_VITA)
    target_link_options(ps2EntryRunner PRIVATE "-Wl,--allow-multiple-definition")
    target_sources(ps2EntryRunner PRIVATE src/lib/ps2_vita_runtime.cpp)
    set_source_files_properties(src/lib/ps2_vita_runtime.cpp PROPERTIES
        SKIP_UNITY_BUILD_INCLUSION TRUE
        COMPILE_OPTIONS "-fno-lto"
    )
endif()

if(PS2X_IS_ANDROID)
    target_sources(ps2EntryRunner PRIVATE src/lib/ps2_android_runtime.cpp)
endif()

install(TARGETS ps2_runtime ps2EntryRunner
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

if(WIN32 AND PS2X_ENABLE_FFMPEG)
    install(DIRECTORY "${FFMPEG_BIN_DIR}/"
        DESTINATION bin
        FILES_MATCHING
        PATTERN "*.dll"
    )
endif()

install(DIRECTORY include/
    DESTINATION include
)

# GOW-Port include
target_include_directories(ps2EntryRunner PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/runner)
