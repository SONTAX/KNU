#pragma once

#include <cmath>

namespace GeneralAlgebra {

    enum class Sign : int { Minus = -1, Plus = 1 };

    template <typename T>
    concept IntegralConcept = std::is_integral_v<T>;

    template <typename T>
    concept SignedConcept = IntegralConcept<T> && std::is_signed_v<T>;

    template <typename T>
    concept UnsignedConcept = IntegralConcept<T> && std::is_unsigned_v<T>;

    namespace IntegralInfo {

        template <UnsignedConcept T>
        constexpr inline Sign GetSign(T number) {
            return Sign::Plus;
        }

        template <SignedConcept T>
        constexpr inline Sign GetSign(T number) {
            return std::is_unsigned<T>::value || number >= 0 ? Sign::Plus : Sign::Minus;
        }

        template <IntegralConcept T>
        constexpr inline int GetLength(T number) {
            return std::trunc(std::log10(number)) + 1;
        }

        template <int CellLength, IntegralConcept T>
        constexpr inline auto GetSize(T number) {
            return GetLength(number) / CellLength + (GetLength(number) % CellLength != 0 ? 1 : 0);
        }

    } // namespace IntegralInfo

} // namespace GeneralAlgebra