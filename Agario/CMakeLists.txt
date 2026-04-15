add_executable(Agario
        src/main.cpp
        src/Game.cpp
        src/World/PlayerActor.cpp
        src/World/CenterMarkerActor.cpp
        include/Agario/World/PlayerActor.h
        include/Agario/World/CenterMarkerActor.h
        include/Agario/GameplayTags/GameTags.h
)

target_include_directories(Agario PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(Agario PRIVATE
        Engine
)
