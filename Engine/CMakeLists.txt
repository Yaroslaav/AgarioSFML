add_library(Engine STATIC
        src/Core/Application.cpp
        include/Engine/Input/InputManager.h
        include/Engine/Input/BindKey.h
        src/Input/BindKey.cpp
        src/Input/InputManager.cpp
        include/Engine/GameplayTags/GameplayTag.h
        include/Engine/GameplayTags/GameplayTagContainer.h
        src/GameplayTags/GameplayTagContainer.cpp
        include/Engine/Components/ActorComponent.h
        include/Engine/Components/MovementComponent.h
        include/Engine/Components/TransformComponent.h
        src/Components/MovementComponent.cpp
        include/Engine/World/Actor.h
        include/Engine/World/Controller/Controller.h
        include/Engine/World/Controller/PlayerController.h
        src/World/Actor.cpp
        src/World/Controller/PlayerController.cpp
        include/Engine/View/Window.h
        include/Engine/View/Camera.h
        include/Engine/View/RenderHandle.h
        include/Engine/View/RenderComponent.h
        include/Engine/View/RenderSystem.h
        src/View/Camera.cpp
        src/View/RenderComponent.cpp
        src/View/RenderSystem.cpp
        src/View/Window.cpp
        include/Engine/GameplayTags/GameTags.h
        include/Engine/World/World.h
        src/World/World.cpp
)

target_include_directories(Engine PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(Engine PUBLIC
        SFML::Graphics
        SFML::Window
        SFML::System
)
