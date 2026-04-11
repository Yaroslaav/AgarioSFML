add_library(Engine STATIC
        src/core/Application.cpp
        include/Engine/input/InputManager.h
        include/Engine/input/BindKey.h
        src/input/BindKey.cpp
        src/Input/InputManager.cpp
)

target_include_directories(Engine PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(Engine PUBLIC
        SFML::Graphics
        SFML::Window
        SFML::System
)