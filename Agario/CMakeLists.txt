file(GLOB_RECURSE AGARIO_SOURCES CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

file(GLOB_RECURSE AGARIO_HEADERS CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
)

add_executable(Agario
        ${AGARIO_SOURCES}
        ${AGARIO_HEADERS}
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES
        ${AGARIO_SOURCES}
        ${AGARIO_HEADERS}
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
