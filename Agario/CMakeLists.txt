add_executable(Agario
        src/main.cpp
        src/Game.cpp
        include/Agario/GameTags.h
)

target_include_directories(Agario PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(Agario PRIVATE
        Engine
)