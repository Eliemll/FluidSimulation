cmake_minimum_required(VERSION 3.15)
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
project(FluidSimulation)

find_package(SFML 3 COMPONENTS Graphics Window System CONFIG REQUIRED)

# Assurez-vous que ces chemins correspondent EXACTEMENT à vos dossiers
set(SOURCES 
    "main.cpp"
    "src/Physics/PhysicsEngine.cpp"
    "src/Render/Renderer.cpp"
)

add_executable(FluidSimulation ${SOURCES})

# Pour les headers, vous avez bien un dossier "Render" dans "include"
target_include_directories(FluidSimulation PRIVATE "include")

target_link_libraries(FluidSimulation PRIVATE SFML::Graphics SFML::Window SFML::System)

set(VCPKG_APPLOCAL_DEPS ON)