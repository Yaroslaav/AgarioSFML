add_executable(Agario
        src/main.cpp
        src/Game.cpp
        src/World/CircleActor.cpp
        src/World/Cell.cpp
        include/Agario/World/CircleActor.h
        include/Agario/World/Cell.h
        include/Agario/GameplayTags/GameTags.h
        include/Agario/World/Food.h
        src/World/Food.cpp
)

target_include_directories(Agario PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(Agario PRIVATE
        Engine
)
