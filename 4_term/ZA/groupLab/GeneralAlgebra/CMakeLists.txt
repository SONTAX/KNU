set(TARGET GeneralAlgebraLib)

add_subdirectory(external/Random)

file(GLOB HEADER_FILES
    include/GeneralAlgebra/*.hpp
    include/GeneralAlgebra/*.inl

    src/*.hpp
)

add_library(${TARGET} STATIC ${HEADER_FILES} include/GeneralAlgebra/EulerAndCarmichael/EulerFunction.hpp include/GeneralAlgebra/EulerAndCarmichael/CarmichaelFunction.hpp)

target_include_directories(GeneralAlgebraLib PUBLIC include)

target_link_libraries(${TARGET} PUBLIC NgRandom)

set_target_properties(${TARGET} PROPERTIES LINKER_LANGUAGE CXX)

target_precompile_headers(${TARGET} PUBLIC src/Precompiled.hpp)