#include "LongArithmetic.hpp"

namespace GeneralAlgebra {

#define CAN_CONVERT(func, value)           \
    try {                                  \
        func(value);                       \
    } catch (const std::exception& e) {    \
        return false;                      \
    }                                      \
    return true;

    template <int CellLength>
    const LongNumber<CellLength> LongNumber<CellLength>::Null = LongNumber<CellLength>(0);

    template <int CellLength>
    const LongNumber<CellLength> LongNumber<CellLength>::One = LongNumber<CellLength>(1);

    template <int CellLength>
    LongNumber<CellLength>::LongNumber()
        : m_Sign(Sign::Plus)
        , m_Length(1)
        , m_CellLimit(static_cast<int>(std::pow(10, CellLength)))
        , m_String("0") {

        static_assert(CellLength > 0 && CellLength < 10);

        Resize(1);
    }

    template <int CellLength>
    template <UnsignedConcept T>
    LongNumber<CellLength>::LongNumber(T number, int size)
        : m_Sign(Sign::Plus)
        , m_Length(1)
        , m_CellLimit(static_cast<int>(std::pow(10, CellLength)))
        , m_String("0") {

        static_assert(CellLength > 0 && CellLength < 10);

        if (number == 0) {
            Resize(1);
            return;
        }

        SetNumber(number, size);
    }

    template <int CellLength>
    template <SignedConcept T>
    LongNumber<CellLength>::LongNumber(T number, int size)
    : m_Sign(Sign::Plus)
    , m_Length(1)
    , m_CellLimit(static_cast<int>(std::pow(10, CellLength)))
    , m_String("0") {

        static_assert(CellLength > 0 && CellLength < 10);

        if (number == 0) {
            Resize(1);
            return;
        }

        SetNumber(number, size);
    }

    template <int CellLength>
    LongNumber<CellLength>::LongNumber(const std::string& string, int size)
        : m_Sign(Sign::Plus)
        , m_Length(1)
        , m_CellLimit(static_cast<int>(std::pow(10, CellLength)))
        , m_String(string) {

        static_assert(CellLength > 0 && CellLength < 10);

        int actualStringSize = m_String.size() / CellLength + (m_String.size() % CellLength == 0 ? 0 : 1);

        SetString(m_String, size >= actualStringSize && !string.empty() ? size : actualStringSize);
    }

    template <int CellLength>
    LongNumber<CellLength>::LongNumber(std::string&& string, int size)
        : m_Sign(Sign::Plus)
        , m_Length(1)
        , m_CellLimit(static_cast<int>(std::pow(10, CellLength)))
        , m_String(string) {

        static_assert(CellLength > 0 && CellLength < 10);

        int actualStringSize = m_String.size() / CellLength + (m_String.size() % CellLength == 0 ? 0 : 1);

        Resize(size >= actualStringSize && !m_String.empty() ? size : actualStringSize);
        SetString(m_String);
    }

    template <int CellLength>
    LongNumber<CellLength>::LongNumber(LongNumber&& other) noexcept
        : m_Data(std::exchange(other.m_Data, {}))
        , m_Sign(std::exchange(other.m_Sign, Sign::Plus))
        , m_Length(std::exchange(other.m_Length, 1))
        , m_CellLimit(other.m_CellLimit)
        , m_String(std::exchange(other.m_String, "0")) {}

    template <int CellLength>
    bool LongNumber<CellLength>::CanConvertToInt() const {
        CAN_CONVERT(std::stoi, ToString())
    }

    template <int CellLength>
    bool LongNumber<CellLength>::CanConvertToInt32() const  {
        CAN_CONVERT(std::stol, ToString())
    }

    template <int CellLength>
    bool LongNumber<CellLength>::CanConvertToInt64() const {
        CAN_CONVERT(std::stoll, ToString())
    }

    template <int CellLength>
    int LongNumber<CellLength>::ToInt() const {
        if (CanConvertToInt())
            return std::stoi(ToString());

        throw std::range_error("GeneralAlgebra::LongNumber::ToInt: Can't fit into int type");
    }

    template <int CellLength>
    std::int32_t LongNumber<CellLength>::ToInt32() const {
        if (CanConvertToInt32())
            return std::stol(ToString());

        throw std::range_error("GeneralAlgebra::LongNumber::ToInt32: Can't fit into int32_t type");
    }

    template <int CellLength>
    std::int64_t LongNumber<CellLength>::ToInt64() const {
        if (CanConvertToInt64())
            return std::stoll(ToString());

        throw std::range_error("GeneralAlgebra::LongNumber::ToInt32: Can't fit into int64_t type");
    }

    template <int CellLength>
    template <SignedConcept T>
    void LongNumber<CellLength>::SetNumber(T number, int size) {
        auto numberSize = IntegralInfo::GetSize<CellLength>(std::abs(number));
        Resize(size != 0 && size > numberSize ? size : numberSize);

        auto cell = m_Data.begin();

        m_Sign = IntegralInfo::GetSign(number);
        number = std::abs(number);

        while (true) {
            if (number == 0)
                return Update();

            *(cell++)  = number % m_CellLimit;
            number    /= m_CellLimit;
        }
    }

    template <int CellLength>
    template <UnsignedConcept T>
    void LongNumber<CellLength>::SetNumber(T number, int size) {
        auto numberSize = IntegralInfo::GetSize<CellLength>(number);
        Resize(size != 0 && size > numberSize ? size : numberSize);

        auto cell = m_Data.begin();

        m_Sign = IntegralInfo::GetSign(number);

        while (true) {
            if (number == 0)
                return Update();

            *(cell++)  = number % m_CellLimit;
            number    /= m_CellLimit;
        }
    }

    template <int CellLength>
    void LongNumber<CellLength>::SetString(const std::string& string, int size) {
        if (std::find_if(string.begin() + (!string.empty() && string.front() == '-' ? 1 : 0), string.end(), [](char ch) {
            return ch < '0' || ch > '9';
        }) != string.end()) {
            throw std::invalid_argument(
                "GeneralAlgebra::LongNumber::LongNumber: Digit has unacceptable code"
            );
        }

        auto stringSize = string.size() / CellLength + (string.size() % CellLength == 0 ? 0 : 1);
        Resize(size != 0 && size > stringSize ? size : stringSize);

        m_Sign = !string.empty() && string.front() == '-' ? Sign::Minus : Sign::Plus;

        auto cell = m_Data.begin();
        auto ch   = string.rbegin();
        auto end  = m_Sign == Sign::Plus ? string.rend() : --string.rend();

        while (true) {
            for (int i = 0; i < CellLength; ++i, ++ch) {
                if (ch == end)
                    return Update();

                *cell += static_cast<int>(std::pow(10, i)) * (*ch - '0');
            }

            ++cell;
        }
    }

    template <int CellLength>
    void LongNumber<CellLength>::Clear() {
        m_Data.clear();
        m_String = "0";

        m_Sign   = Sign::Plus;
        m_Length = 1;
    }

    template <int CellLength>
    void LongNumber<CellLength>::Resize(int size) {
        m_Data.resize(size);
        std::fill_n(m_Data.begin(), m_Data.size(), 0);
    }

    template <int CellLength>
    void LongNumber<CellLength>::ShrinkToFit() {
        m_Data.shrink_to_fit();
    }

    template <int CellLength>
    LongNumber<CellLength>& LongNumber<CellLength>::ShiftLeft(int offset) {
        if (GetActualSize() < GetMaxSize() + offset / CellLength + offset % CellLength)
            Resize(GetMaxSize() + offset / CellLength + offset % CellLength);

        auto split = static_cast<CellType>(std::pow(10, CellLength - offset % CellLength));

        for (int i = GetActualSize() - 1; i >= 0; --i) {
            auto high = m_Data[i] / split;
            auto low  = m_Data[i] % split;

            m_Data[i + offset / CellLength + 1] += high;
            m_Data[i + offset / CellLength]      = low * static_cast<CellType>(std::pow(10, offset % CellLength));

            if (offset / CellLength != 0)
                m_Data[i] = 0;
        }

        Update();

        return *this;
    }

    template <int CellLength>
    LongNumber<CellLength>& LongNumber<CellLength>::ShiftRight(int offset) {
        auto split = static_cast<CellType>(std::pow(10, offset % CellLength));

        for (int i = 0; i < GetActualSize(); ++i) {
            int highIndex = i + offset / CellLength;
            int lowIndex  = i + offset / CellLength + 1;

            auto high = highIndex < GetActualSize() ? m_Data[highIndex] / split : 0;
            auto low  = lowIndex < GetActualSize()  ? m_Data[lowIndex]  % split : 0;

            m_Data[i] = low * static_cast<CellType>(std::pow(10, CellLength - offset % CellLength)) + high;
        }

        Update();

        return *this;
    }

    template<int CellLength>
    LongNumber<CellLength> LongNumber<CellLength>::Pow(const LongNumber& power) const {
        return LongArithmetic::FastPow(*this, power);
    }

    template <int CellLength>
    template <IntegralConcept T>
    LongNumber<CellLength>& LongNumber<CellLength>::operator =(T number) {
        SetNumber(number);
        return *this;
    }

    template <int CellLength>
    LongNumber<CellLength>& LongNumber<CellLength>::operator =(const std::string& string) {
        SetString(string);
        return *this;
    }

    template <int CellLength>
    LongNumber<CellLength>& LongNumber<CellLength>::operator =(LongNumber&& other) noexcept {
        if (this != &other) {
            m_Data      = std::exchange(other.m_Data, {});
            m_Sign      = std::exchange(other.m_Sign, Sign::Plus);
            m_Length    = std::exchange(other.m_Length, 1);
            m_CellLimit = other.m_CellLimit;
            m_String    = std::exchange(other.m_String, "0");
        }

        return *this;
    }

    template <int CellLength>
    LongNumber<CellLength> LongNumber<CellLength>::operator +(const LongNumber& other) const {
        return LongArithmetic::Add(*this, other);
    }

    template <int CellLength>
    LongNumber<CellLength>& LongNumber<CellLength>::operator +=(const LongNumber& other) {
        return (*this = *this + other);
    }

    template <int CellLength>
    LongNumber<CellLength>& LongNumber<CellLength>::operator ++() {
        return (*this = *this + LongNumber(1));
    }

    template <int CellLength>
    LongNumber<CellLength> LongNumber<CellLength>::operator ++(int) const & {
        LongNumber temp = std::move(*this);
        ++temp;
        return temp;
    }

    template <int CellLength>
    LongNumber<CellLength>& LongNumber<CellLength>::operator -() {
        m_Sign = m_Sign == Sign::Plus ? Sign::Minus : Sign::Plus;
        return *this;
    }

    template <int CellLength>
    LongNumber<CellLength> LongNumber<CellLength>::operator -(const LongNumber& other) const {
        return LongArithmetic::Sub(*this, other);
    }

    template <int CellLength>
    LongNumber<CellLength>& LongNumber<CellLength>::operator -=(const LongNumber& other) {
        return (*this = *this - other);
    }

    template <int CellLength>
    LongNumber<CellLength>& LongNumber<CellLength>::operator --() {
        return (*this = *this - LongNumber(1));
    }

    template <int CellLength>
    LongNumber<CellLength> LongNumber<CellLength>::operator --(int) const & {
        LongNumber temp = std::move(*this);
        --temp;
        return temp;
    }

    template <int CellLength>
    LongNumber<CellLength> LongNumber<CellLength>::operator *(const LongNumber& other) const {
        return LongArithmetic::KaratsubaMul(*this, other);
    }

    template <int CellLength>
    LongNumber<CellLength>& LongNumber<CellLength>::operator *=(const LongNumber& other) {
        return (*this = *this * other);
    }

    template <int CellLength>
    LongNumber<CellLength> LongNumber<CellLength>::operator /(const LongNumber& other) const {
        return LongArithmetic::LogDiv(*this, other);
    }

    template <int CellLength>
    LongNumber<CellLength>& LongNumber<CellLength>::operator /=(const LongNumber& other) {
        return (*this = *this / other);
    }

    template <int CellLength>
    LongNumber<CellLength> LongNumber<CellLength>::operator %(const LongNumber& other) const {
        return LongArithmetic::LogRem(*this, other);
    }

    template <int CellLength>
    LongNumber<CellLength>& LongNumber<CellLength>::operator %=(const LongNumber& other) {
        return (*this = *this % other);
    }

    template <int CellLength>
    bool LongNumber<CellLength>::operator <(const LongNumber& other) const {
        if (m_Sign < other.m_Sign)
            return true;

        if (m_Sign > other.m_Sign)
            return false;

        if (m_Length < other.m_Length)
            return m_Sign == Sign::Plus;

        if (m_Length > other.m_Length)
            return m_Sign == Sign::Minus;

        for (int i = GetActualSize() - 1; i >= 0; --i) {
            if (m_Data[i] < other.m_Data[i])
                return true;

            if (m_Data[i] > other.m_Data[i])
                return false;
        }

        return false;
    }

    template <int CellLength>
    bool LongNumber<CellLength>::operator <=(const LongNumber& other) const {
        if (m_Sign < other.m_Sign)
            return true;

        if (m_Sign > other.m_Sign)
            return false;

        if (m_Length < other.m_Length)
            return m_Sign == Sign::Plus;

        if (m_Length > other.m_Length)
            return m_Sign == Sign::Minus;

        for (int i = GetActualSize() - 1; i >= 0; --i) {
            if (m_Data[i] < other.m_Data[i])
                return true;

            if (m_Data[i] > other.m_Data[i])
                return false;
        }

        return true;
    }

    template <int CellLength>
    bool LongNumber<CellLength>::operator >(const LongNumber& other) const {
        if (m_Sign < other.m_Sign)
            return false;

        if (m_Sign > other.m_Sign)
            return true;

        if (m_Length < other.m_Length)
            return m_Sign == Sign::Minus;

        if (m_Length > other.m_Length)
            return m_Sign == Sign::Plus;

        for (int i = GetActualSize() - 1; i >= 0; --i) {
            if (m_Data[i] < other.m_Data[i])
                return false;

            if (m_Data[i] > other.m_Data[i])
                return true;
        }

        return false;
    }

    template <int CellLength>
    bool LongNumber<CellLength>::operator >=(const LongNumber& other) const {
        if (m_Sign < other.m_Sign)
            return false;

        if (m_Sign > other.m_Sign)
            return true;

        if (m_Length < other.m_Length)
            return m_Sign == Sign::Minus;

        if (m_Length > other.m_Length)
            return m_Sign == Sign::Plus;

        for (int i = GetActualSize() - 1; i >= 0; --i) {
            if (m_Data[i] < other.m_Data[i])
                return false;

            if (m_Data[i] > other.m_Data[i])
                return true;
        }

        return true;
    }

    template <int CellLength>
    bool LongNumber<CellLength>::operator !=(const LongNumber& other) const {
        if (m_Sign != other.m_Sign)
            return true;

        return m_String != other.m_String;
    }

    template <int CellLength>
    bool LongNumber<CellLength>::operator ==(const LongNumber& other) const {
        if (m_Sign != other.m_Sign)
            return false;

        if (m_Length != other.m_Length)
            return false;

        return m_String == other.m_String;
    }

    template <int CellLength>
    LongNumber<CellLength>::LongNumber(DataIterator begin, DataIterator end)
        : m_Data(begin, end)
        , m_Sign(Sign::Plus)
        , m_Length(1)
        , m_CellLimit(static_cast<int>(std::pow(10, CellLength)))
        , m_String("0") {

        Update();
    }

    template <int CellLength>
    LongNumber<CellLength>::LongNumber(DataConstIterator begin, DataConstIterator end)
        : m_Data(begin, end)
        , m_Sign(Sign::Plus)
        , m_Length(1)
        , m_CellLimit(static_cast<int>(std::pow(10, CellLength)))
        , m_String("0") {

        Update();
    }

    template <int CellLength>
    void LongNumber<CellLength>::UpdateLength() {
        auto first  = std::find_if(m_Data.rbegin(), m_Data.rend(), [](int cell) { return cell != 0; });
        int  length = m_Data.rend() - first;

        m_Length = length == 0 ? 1 : (length - 1) * CellLength + IntegralInfo::GetLength(*first);
    }

    template <int CellLength>
    void LongNumber<CellLength>::UpdateString() {
        if (m_Length == 1 && (m_Data.empty() || m_Data.front() == 0)) {
            m_String = "0";
            return;
        }

        std::stringstream ss;

        if (m_Sign == Sign::Minus)
            ss << "-";

        for (int i = GetActualSize() - 1; i >= 0; --i) {
            if (i != GetActualSize() - 1)
                ss << std::setw(CellLength) << std::setfill('0');

            ss << +m_Data[i];
        }

        m_String = std::move(ss.str());
    }

    template <int CellLength>
    void LongNumber<CellLength>::Update() {
        UpdateLength();
        UpdateString();
    }
    
    template <int CellLength>
    std::istream& operator >>(std::istream& istream, LongNumber<CellLength>& number) {
        std::string string;

        istream >> string;
        number.SetString(string);

        return istream;
    }

    template <int CellLength>
    std::ostream& operator <<(std::ostream& ostream, const LongNumber<CellLength>& number) {
        return ostream << number.ToString();
    }

} // namespace GeneralAlgebra