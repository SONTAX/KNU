#pragma once

namespace GeneralAlgebra {

#define CELL_IMPLEMENTATION(CellLength, Type) template <> struct CellType<CellLength> { using Value = Type; }

    template <int CellLength>
    struct CellType { using Value = bool; };

    CELL_IMPLEMENTATION(1, std::int8_t );
    CELL_IMPLEMENTATION(2, std::int16_t);
    CELL_IMPLEMENTATION(3, std::int32_t);
    CELL_IMPLEMENTATION(4, std::int32_t);
    CELL_IMPLEMENTATION(5, std::int64_t);
    CELL_IMPLEMENTATION(6, std::int64_t);
    CELL_IMPLEMENTATION(7, std::int64_t);
    CELL_IMPLEMENTATION(8, std::int64_t);
    CELL_IMPLEMENTATION(9, std::int64_t);

} // namespace GeneralAlgebra