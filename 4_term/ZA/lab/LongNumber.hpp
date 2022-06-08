#pragma once

#include <vector>
#include <cmath>
#include <string>
#include <stdexcept>
#include <tuple>
#include <cstdint>
#include <functional>

namespace GeneralAlgebra {

    enum class Sign : int { Minus = -1, Plus = 1 };

    template <int Size, int CellSize>
    class LongNumber {
    public:
        using DataContainer = std::vector<int>;

        LongNumber();
        explicit LongNumber(int number);
        explicit LongNumber(const std::string& string);
        LongNumber(const LongNumber& other) = default;
        LongNumber(LongNumber&& other) noexcept;
        virtual ~LongNumber() noexcept = default;

        [[nodiscard]] inline int GetLength() const { return m_Length; }
        [[nodiscard]] inline int GetMaxLength() const { return Size; }
        [[nodiscard]] inline int GetCellSize() const { return CellSize; }
        [[nodiscard]] bool CanConvertToInt() const;
        [[nodiscard]] bool CanConvertToInt32() const;
        [[nodiscard]] bool CanConvertToInt64() const;

        [[nodiscard]] inline const std::string& ToString() const { return m_String; }
        [[nodiscard]] int ToInt() const;
        [[nodiscard]] int32_t ToInt32() const;
        [[nodiscard]] int64_t ToInt64() const;

        void SetInt(int number);
        void SetString(const std::string& string);

        void Clear();

        LongNumber& operator =(const LongNumber& other) = default;
        LongNumber& operator =(LongNumber&& other) noexcept;

        LongNumber operator +(const LongNumber& other) const;
        LongNumber& operator +=(const LongNumber& other);

        LongNumber& operator ++();
        const LongNumber operator ++(int) const;

        LongNumber& operator -();
        LongNumber operator -(const LongNumber& other) const;
        LongNumber& operator -=(const LongNumber& other);

        LongNumber& operator --();
        const LongNumber operator --(int) const;

        LongNumber operator *(const LongNumber& other) const;
        LongNumber& operator *=(const LongNumber& other);

        LongNumber operator /(const LongNumber& other) const;
        LongNumber& operator /=(const LongNumber& other);

        LongNumber operator %(const LongNumber& other) const;
        LongNumber& operator %=(const LongNumber& other);

        bool operator <(const LongNumber& other) const;
        bool operator <=(const LongNumber& other) const;

        bool operator >(const LongNumber& other) const;
        bool operator >=(const LongNumber& other) const;

        bool operator !=(const LongNumber& other) const;
        bool operator ==(const LongNumber& other) const;

    private:
        [[nodiscard]] LongNumber ModuloAdd(const LongNumber& other, const Sign& sign = Sign::Plus) const;
        [[nodiscard]] LongNumber ModuloSub(const LongNumber& other, const Sign& sign = Sign::Plus) const;
        [[nodiscard]] LongNumber Division(const LongNumber& other, bool returnRemainder = false) const;

        void UpdateLength();
        void UpdateString();
        void Update();

    private:
        DataContainer m_Data;
        Sign          m_Sign;
        int           m_Length;
        int           m_MaxCellValue;
        std::string   m_String;

    }; // class LongNumber

    namespace Literals {

#define DECLARE_LONG_NUMBER(Size, CellSize)                                                 \
    LongNumber<Size, CellSize> operator ""_ln##Size##_##CellSize(const char* string) {      \
        return LongNumber<Size, CellSize>(string);                                          \
    }                                                                                       \

        DECLARE_LONG_NUMBER(100, 2)
        DECLARE_LONG_NUMBER(1000, 2)
        DECLARE_LONG_NUMBER(10000, 2)

    } // namespace Literals

    template <int Size, int CellSize>
    std::istream& operator >>(std::istream& istream, LongNumber<Size, CellSize>& number);

    template <int Size, int CellSize>
    std::ostream& operator <<(std::ostream& ostream, const LongNumber<Size, CellSize>& number);

} // namespace GeneralAlgebra

#include "LongNumber.inl"