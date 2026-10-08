# Controles del wrapper GS usando el runtime ya parcheado, sin datos del juego ni OpenGL.
# Incluir desde el CMakeLists.txt raíz de PS2Recomp después de definir ps2_runtime.
add_executable(gow_gs_replay_test "${CMAKE_CURRENT_LIST_DIR}/../../tests/gs_replay_test.cpp")
target_link_libraries(gow_gs_replay_test PRIVATE ps2_runtime)
add_executable(gow_gs_replay "${CMAKE_CURRENT_LIST_DIR}/../render/repetir_gs.cpp")
target_link_libraries(gow_gs_replay PRIVATE ps2_runtime)
target_include_directories(gow_gs_replay PRIVATE "${CMAKE_CURRENT_LIST_DIR}/../../src")
add_executable(gow_gs_replay_checkpoints_test "${CMAKE_CURRENT_LIST_DIR}/../../tests/gs_replay_checkpoints_test.cpp")
target_link_libraries(gow_gs_replay_checkpoints_test PRIVATE ps2_runtime)
target_include_directories(gow_gs_replay_checkpoints_test PRIVATE "${CMAKE_CURRENT_LIST_DIR}/../../src")
add_executable(gow_gs_finish_async_test "${CMAKE_CURRENT_LIST_DIR}/../../tests/gs_finish_async_test.cpp")
target_link_libraries(gow_gs_finish_async_test PRIVATE ps2_runtime)
