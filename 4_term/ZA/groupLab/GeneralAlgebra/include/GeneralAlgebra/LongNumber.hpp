#pragma once

#include "IntegralInfo.hpp"
#include "LongNumberCell.hpp"

namespace GeneralAlgebra {

    template <int CellLength>
    class LongNumber {
    public:
        friend class LongArithmetic;

    public:
        using CellType = typename CellType<CellLength>::Value;

    public:
        static const LongNumber Null;
        static const LongNumber One;

    public:
        [[nodiscard]] static inline constexpr int GetCellLength() { return CellLength; }

    public:
        LongNumber();

        template <UnsignedConcept T>
        LongNumber(T number, int size = 0);

        template <SignedConcept T>
        LongNumber(T number, int size = 0);

        LongNumber(const std::string& string, int size = 0);
        LongNumber(std::string&& string, int size = 0);
        LongNumber(const LongNumber& other) = default;
        LongNumber(LongNumber&& other) noexcept;
        ~LongNumber() noexcept = default;

    public:
        [[nodiscard]] inline int GetLength() const { return m_Length; }
        [[nodiscard]] inline int GetActualSize() const { return m_Data.empty() ? 0 : m_Length / CellLength + (m_Length % CellLength == 0 ? 0 : 1); }
        [[nodiscard]] inline int GetMaxSize() const { return m_Data.size(); }
        [[nodiscard]] inline int GetCellLimit() const { return m_CellLimit; }
        [[nodiscard]] inline bool IsPositive() const { return m_Sign == Sign::Plus; }
        [[nodiscard]] inline bool IsNegative() const { return m_Sign == Sign::Minus; }

        [[nodiscard]] bool CanConvertToInt() const;
        [[nodiscard]] bool CanConvertToInt32() const;
        [[nodiscard]] bool CanConvertToInt64() const;

        [[nodiscard]] inline const std::string& ToString() const { return m_String; }
        [[nodiscard]] int ToInt() const;
        [[nodiscard]] std::int32_t ToInt32() const;
        [[nodiscard]] std::int64_t ToInt64() const;

        template <SignedConcept T>
        void
        SetNumber(T number, int size = 0);

        template <UnsignedConcept T>
        void SetNumber(T number, int size = 0);

        void SetString(const std::string& string, int size = 0);

        void Clear();
        void Resize(int size);
        void ShrinkToFit();

        LongNumber& ShiftLeft(int offset);
        LongNumber& ShiftRight(int offset);

        [[nodiscard]] LongNumber Pow(const LongNumber& power) const;

    public:
        template <IntegralConcept T>
        LongNumber& operator =(T number);
        LongNumber& operator =(const std::string& string);
        LongNumber& operator =(const LongNumber& other) = default;
        LongNumber& operator =(LongNumber&& other) noexcept;

        LongNumber operator +(const LongNumber& other) const;
        LongNumber& operator +=(const LongNumber& other);

        LongNumber& operator ++();
        LongNumber operator ++(int) const &;

        LongNumber& operator -();
        LongNumber operator -(const LongNumber& other) const;
        LongNumber& operator -=(const LongNumber& other);

        LongNumber& operator --();
        LongNumber operator --(int) const &;

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

        explicit operator bool() const { return m_String != "0"; }
        explicit operator const char*() const { return m_String.c_str(); }
        explicit operator std::string() const { return m_String; }

    private:
        using DataContainer     = std::vector<CellType>;
        using DataIterator      = typename DataContainer::iterator;
        using DataConstIterator = typename DataContainer::const_iterator;

    private:
        LongNumber(DataIterator begin, DataIterator end);
        LongNumber(DataConstIterator begin, DataConstIterator end);

    private:
        void UpdateLength();
        void UpdateString();
        void Update();

    private:
        DataContainer m_Data;
        Sign          m_Sign;
        int           m_Length;
        int           m_CellLimit;
        std::string   m_String;

    }; // class LongNumber

    using LongNumber1 = LongNumber<1>;
    using LongNumber2 = LongNumber<2>;
    using LongNumber3 = LongNumber<3>;
    using LongNumber4 = LongNumber<4>;
    using LongNumber5 = LongNumber<5>;
    using LongNumber6 = LongNumber<6>;
    using LongNumber7 = LongNumber<7>;
    using LongNumber8 = LongNumber<8>;
    using LongNumber9 = LongNumber<9>;

    template <int CellLength>
    std::istream& operator >>(std::istream& istream, LongNumber<CellLength>& number);

    template <int CellLength>
    std::ostream& operator <<(std::ostream& ostream, const LongNumber<CellLength>& number);
    
} // namespace GeneralAlgebra

#include "LongNumber.inl"