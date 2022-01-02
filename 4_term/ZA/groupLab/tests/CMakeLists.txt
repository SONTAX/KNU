set(TARGET LabGA_Tests)

add_subdirectory(external/doctest)

file(GLOB SOURCE_FILES ./*.cpp)

add_executable(${TARGET} ${SOURCE_FILES})

target_link_libraries(${TARGET} PRIVATE doctest_with_main GeneralAlgebraLib)