add_executable(Agario
        src/main.cpp
        src/Game.cpp
        src/Components/MassComponent.cpp
        src/World/CircleActor.cpp
        src/World/Cell.cpp
        include/Agario/Config/Settings.h
        include/Agario/Component/MassComponent.h
        include/Agario/World/CircleActor.h
        include/Agario/World/Cell.h
        include/Agario/GameplayTags/GameTags.h
        include/Agario/World/Food.h
        src/World/Food.cpp
        include/Agario/World/CellAIController.h
        src/World/CellAIController.cpp
        include/Agario/World/ChunkGrid.h
        src/World/ChunkGrid.cpp
)

target_include_directories(Agario PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(Agario PRIVATE
        Engine
)

add_custom_command(TARGET Agario POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:Agario>/assets
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_RUNTIME_DLLS:Agario>
        $<TARGET_FILE_DIR:Agario>
        COMMAND_EXPAND_LISTS
)