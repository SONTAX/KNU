set(TARGET Sandbox)

add_subdirectory(external/libfort)
add_subdirectory(external/Ziben)

file(GLOB HEADER_FILES src/*.hpp)
file(GLOB SOURCE_FILES src/*.cpp)

include_directories(src)

add_executable(${TARGET} ${HEADER_FILES} ${SOURCE_FILES})

target_link_libraries(${TARGET} PRIVATE GeneralAlgebraLib libfort::fort ZibenEngine)

file(COPY
        ${CMAKE_CURRENT_SOURCE_DIR}/external/Ziben/Ziben/Assets
    DESTINATION
        ${CMAKE_CURRENT_BINARY_DIR}
)