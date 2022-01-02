#pragma once

namespace GeneralAlgebra::Literals {

#define LONG_NUMBER_LITERAL(CellLength)                                                         \
    inline LongNumber<CellLength> operator ""_ln##CellLength(const char* string) {              \
        return LongNumber<CellLength>(string);                                                  \
    }

    LONG_NUMBER_LITERAL(1)
    LONG_NUMBER_LITERAL(2)
    LONG_NUMBER_LITERAL(3)
    LONG_NUMBER_LITERAL(4)
    LONG_NUMBER_LITERAL(5)
    LONG_NUMBER_LITERAL(6)
    LONG_NUMBER_LITERAL(7)
    LONG_NUMBER_LITERAL(8)
    LONG_NUMBER_LITERAL(9)

} // namespace GeneralAlgebra::Literals