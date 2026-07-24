cmake_minimum_required(VERSION 3.25 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 23)
project(espeon VERSION 1.0.0 LANGUAGES C CXX)

option(ESPEON_BUILD_TESTS "Build espeon Tests" ON)
option(ESPEON_TESTS_INCLUDE_ASSETS "Include assets for espeon tests" OFF)

set(ESPEON_USING_SDL3 OFF)
set(EXPEON_USING_DX OFF)

if(NOT TARGET SDL3::SDL3 AND NOT TARGET SDL3::SDL3-static)
    find_package(SDL3 CONFIG QUIET)
endif()

add_library(espeon STATIC 
    src/backend/BackendRenderer.cpp
)
add_library(espeon::espeon ALIAS espeon)

if(TARGET SDL3::SDL3 OR TARGET SDL3::SDL3-static)
    target_link_libraries(espeon PRIVATE 
        SDL3::SDL3
    )
    target_sources(espeon PUBLIC src/backend/SDL3Backend.cpp)
endif()

if (WIN32)
    find_library(DX12_LIBRARY d3d12)
    find_library(DXGI_LIBRARY dxgi)
    find_path(DX12_INCLUDE_DIR d3d12.h)

    if(DX12_LIBRARY AND DXGI_LIBRARY AND DX12_INCLUDE_DIR)
        target_link_libraries(espeon PRIVATE
            d3d12.lib 
            dxgi.lib 
            d3dcompiler.lib 
            dxguid.lib
        )
        target_sources(espeon PUBLIC src/backend/DX12Backend.cpp)
    endif()
endif()

target_include_directories(espeon PUBLIC ${PROJECT_SOURCE_DIR}/include)

install(TARGETS espeon
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)
install(DIRECTORY include/ DESTINATION include)

if (ESPEON_BUILD_TESTS)
    project(espeon_test_sdl3)
    add_executable(espeon_test_sdl3 test/sdl3.cpp)
    find_package(SDL3 CONFIG REQUIRED)
    target_link_libraries(espeon_test_sdl3 PUBLIC SDL3::SDL3 espeon::espeon)

    project(espeon_test_dx12)
    add_executable(espeon_test_dx12 WIN32 test/dx12.cpp)
    target_link_libraries(espeon_test_sdl3 PUBLIC d3d12.lib dxgi.lib d3dcompiler.lib dxguid.lib espeon::espeon)
endif()