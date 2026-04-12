add_library(Engine STATIC
        src/Core/Application.cpp
        include/Engine/Input/InputManager.h
        include/Engine/Input/BindKey.h
        src/Input/BindKey.cpp
        src/Input/InputManager.cpp
        include/Engine/GameplayTags/GameplayTag.h
        include/Engine/GameplayTags/GameplayTagContainer.h
        src/GameplayTags/GameplayTagContainer.cpp
        include/Engine/View/Window.h
        include/Engine/View/Camera.h
        src/View/Camera.cpp
        src/View/Window.cpp
        include/Engine/GameplayTags/GameTags.h
)

target_include_directories(Engine PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(Engine PUBLIC
        SFML::Graphics
        SFML::Window
        SFML::System
)
