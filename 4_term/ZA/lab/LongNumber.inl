#include <limits>

namespace GeneralAlgebra {

    namespace Internal {

        template <typename T>
        inline typename std::enable_if<std::is_integral<T>::value, Sign>::type GetSign(T number) {
            return std::is_unsigned<T>::value || number >= 0 ? Sign::Plus : Sign::Minus;
        }

        template <typename T>
        inline typename std::enable_if<std::is_integral<T>::value, int>::type GetLength(T number) {
            return static_cast<int>(std::log10(number)) + 1;
        }

    } // namespace Internal

#define CAN_CONVERT(func, value)           \
    try {                                  \
        func(value);                       \
    } catch (const std::exception& e) {    \
        return false;                      \
    }                                      \
    return true;

    template <int Size, int CellSize>
    LongNumber<Size, CellSize>::LongNumber()
            : m_Sign(Sign::Plus)
            , m_Length(1)
            , m_MaxCellValue(static_cast<int>(std::pow(10, CellSize)))
            , m_String("0") {

        m_Data.resize(Size);
    }

    template <int Size, int CellSize>
    LongNumber<Size, CellSize>::LongNumber(int number)
            : m_Sign(Sign::Plus)
            , m_Length(1)
            , m_MaxCellValue(static_cast<int>(std::pow(10, CellSize)))
            , m_String("0") {

        m_Data.resize(Size);
        SetInt(number);
    }

    template <int Size, int CellSize>
    LongNumber<Size, CellSize>::LongNumber(const std::string& string)
            : m_Sign(Sign::Plus)
            , m_Length(1)
            , m_MaxCellValue(static_cast<int>(std::pow(10, CellSize)))
            , m_String("0") {

        m_Data.resize(Size);
        SetString(string);
    }

    template <int Size, int CellSize>
    LongNumber<Size, CellSize>::LongNumber(LongNumber&& other) noexcept
            : m_Data(std::exchange(other.m_Data, {}))
            , m_Sign(std::exchange(other.m_Sign, Sign::Plus))
            , m_Length(std::exchange(other.m_Length, 1))
            , m_MaxCellValue(other.m_MaxCellValue)
            , m_String(std::exchange(other.m_String, "0")) {}

    template <int Size, int CellSize>
    bool LongNumber<Size, CellSize>::CanConvertToInt() const {
        CAN_CONVERT(std::stoi, ToString())
    }

    template <int Size, int CellSize>
    bool LongNumber<Size, CellSize>::CanConvertToInt32() const  {
        CAN_CONVERT(std::stol, ToString());
    }

    template <int Size, int CellSize>
    bool LongNumber<Size, CellSize>::CanConvertToInt64() const {
        CAN_CONVERT(std::stoll, ToString());
    }

    template <int Size, int CellSize>
    int LongNumber<Size, CellSize>::ToInt() const {
        if (CanConvertToInt())
            return std::stoi(ToString());

        throw std::range_error("GeneralAlgebra::LongNumber::ToInt: Can't fit into int type");
    }

    template <int Size, int CellSize>
    int32_t LongNumber<Size, CellSize>::ToInt32() const {
        if (CanConvertToInt32())
            return std::stol(ToString());

        throw std::range_error("GeneralAlgebra::LongNumber::ToInt32: Can't fit into int32_t type");
    }

    template <int Size, int CellSize>
    int64_t LongNumber<Size, CellSize>::ToInt64() const {
        if (CanConvertToInt64())
            return std::stoll(ToString());

        throw std::range_error("GeneralAlgebra::LongNumber::ToInt32: Can't fit into int64_t type");
    }

    template <int Size, int CellSize>
    void LongNumber<Size, CellSize>::SetInt(int number) {
        SetString(std::to_string(number));
    }

    template <int Size, int CellSize>
    void LongNumber<Size, CellSize>::SetString(const std::string& string) {
        m_Sign = !string.empty() && string[0] == '-' ? Sign::Minus : Sign::Plus;

        auto cell = m_Data.rbegin();
        auto ch   = string.rbegin();
        auto end  = m_Sign == Sign::Plus ? string.rend() : --string.rend();

        while (true) {
            for (int j = 0; j < CellSize; ++j, ++ch) {
                if (ch == end)
                    return Update();

                if (*ch < '0' || *ch > '9') {
                    throw std::invalid_argument(
                            "GeneralAlgebra::LongNumber::LongNumber: Digit has unacceptable code"
                    );
                }

                *cell += static_cast<int>(std::pow(10, j)) * (*ch - '0');
            }

            ++cell;
        }
    }

    template <int Size, int CellSize>
    void LongNumber<Size, CellSize>::Clear() {
        m_Data.clear();
        m_String.clear();

        m_Sign   = Sign::Plus;
        m_Length = 1;
    }

    template <int Size, int CellSize>
    LongNumber<Size, CellSize>& LongNumber<Size, CellSize>::operator =(LongNumber&& other) noexcept {
        if (this != &other) {
            m_Data         = std::exchange(other.m_Data, {});
            m_Sign         = std::exchange(other.m_Sign, Sign::Plus);
            m_Length       = std::exchange(other.m_Length, 1);
            m_MaxCellValue = other.m_MaxCellValue;
            m_String       = std::exchange(other.m_String, "0");
        }

        return *this;
    }

    template <int Size, int CellSize>
    LongNumber<Size, CellSize> LongNumber<Size, CellSize>::operator +(const LongNumber& other) const {
        if (m_Sign == other.m_Sign)
            return ModuloAdd(other, m_Sign);

        if (m_Sign == Sign::Plus)
            return m_Length > other.m_Length ? ModuloSub(other) : other.ModuloSub(*this, Sign::Minus);

        return m_Length > other.m_Length ? ModuloSub(other, Sign::Minus) : other.ModuloSub(*this);
    }

    template <int Size, int CellSize>
    LongNumber<Size, CellSize>& LongNumber<Size, CellSize>::operator +=(const LongNumber& other) {
        return (*this = *this + other);
    }

    template <int Size, int CellSize>
    LongNumber<Size, CellSize>& LongNumber<Size, CellSize>::operator ++() {
        return *this;
    }

    template <int Size, int CellSize>
    const LongNumber<Size, CellSize> LongNumber<Size, CellSize>::operator ++(int) const {
        return {};
    }

    template <int Size, int CellSize>
    LongNumber<Size, CellSize>& LongNumber<Size, CellSize>::operator -() {
        m_Sign = m_Sign == Sign::Plus ? Sign::Minus : Sign::Plus;
        return *this;
    }

    template <int Size, int CellSize>
    LongNumber<Size, CellSize> LongNumber<Size, CellSize>::operator -(const LongNumber& other) const {
        if (m_Sign == other.m_Sign){
            if (m_Sign == Sign::Plus)
                return *this >= other ? ModuloSub(other, Sign::Plus) : other.ModuloSub(*this, Sign::Minus);

            return *this >= other ? other.ModuloSub(*this, Sign::Plus) : ModuloSub(other, Sign::Minus);
        }

        return ModuloAdd(other, m_Sign);
    }

    template <int Size, int CellSize>
    LongNumber<Size, CellSize>& LongNumber<Size, CellSize>::operator -=(const LongNumber& other) {
        return (*this = *this - other);
    }

    template <int Size, int CellSize>
    LongNumber<Size, CellSize>& LongNumber<Size, CellSize>::operator --() {
        return *this;
    }

    template <int Size, int CellSize>
    const LongNumber<Size, CellSize> LongNumber<Size, CellSize>::operator --(int) const {
        return {};
    }

    template <int Size, int CellSize>
    LongNumber<Size, CellSize> LongNumber<Size, CellSize>::operator *(const LongNumber& other) const {
        LongNumber result;

        result.m_Sign = m_Sign == other.m_Sign ? Sign::Plus : Sign::Minus;

        for (int i = Size - 1, transfer = 0; i >= Size - other.m_Length; --i) {
            for (int j = Size - 1; j >= Size - m_Length - 1; --j) {
                int& resultCurrentCell = result.m_Data[i + j + 1 - Size];

                resultCurrentCell += other.m_Data[i] * m_Data[j] + transfer;
                transfer           = resultCurrentCell / m_MaxCellValue;
                resultCurrentCell %= m_MaxCellValue;
            }
        }

        result.Update();

        return result;
    }

    template <int Size, int CellSize>
    LongNumber<Size, CellSize>& LongNumber<Size, CellSize>::operator *=(const LongNumber& other) {
        return (*this = *this * other);
    }

    template <int Size, int CellSize>
    LongNumber<Size, CellSize> LongNumber<Size, CellSize>::operator /(const LongNumber& other) const {
        return Division(other);
    }

    template <int Size, int CellSize>
    LongNumber<Size, CellSize>& LongNumber<Size, CellSize>::operator /=(const LongNumber& other) {
        return (*this = *this / other);
    }

    template <int Size, int CellSize>
    LongNumber<Size, CellSize> LongNumber<Size, CellSize>::operator %(const LongNumber& other) const {
        return Division(other, true);
    }

    template <int Size, int CellSize>
    LongNumber<Size, CellSize>& LongNumber<Size, CellSize>::operator %=(const LongNumber& other) {
        return (*this = *this % other);
    }

    template <int Size, int CellSize>
    bool LongNumber<Size, CellSize>::operator <(const LongNumber& other) const {
        if (m_Sign < other.m_Sign)
            return true;

        if (m_Sign > other.m_Sign)
            return false;

        if (m_Length < other.m_Length)
            return m_Sign == Sign::Plus;

        if (m_Length > other.m_Length)
            return m_Sign == Sign::Minus;

        for (int i = Size - m_Length; i < Size; ++i) {
            if (m_Data[i] < other.m_Data[i])
                return true;

            if (m_Data[i] > other.m_Data[i])
                return false;
        }

        return false;
    }

    template <int Size, int CellSize>
    bool LongNumber<Size, CellSize>::operator <=(const LongNumber& other) const {
        if (m_Sign < other.m_Sign)
            return true;

        if (m_Sign > other.m_Sign)
            return false;

        if (m_Length < other.m_Length)
            return m_Sign == Sign::Plus;

        if (m_Length > other.m_Length)
            return m_Sign == Sign::Minus;

        for (int i = Size - m_Length; i < Size; ++i) {
            if (m_Data[i] < other.m_Data[i])
                return true;

            if (m_Data[i] > other.m_Data[i])
                return false;
        }

        return true;
    }

    template <int Size, int CellSize>
    bool LongNumber<Size, CellSize>::operator >(const LongNumber& other) const {
        if (m_Sign < other.m_Sign)
            return false;

        if (m_Sign > other.m_Sign)
            return true;

        if (m_Length < other.m_Length)
            return m_Sign == Sign::Minus;

        if (m_Length > other.m_Length)
            return m_Sign == Sign::Plus;

        for (int i = Size - m_Length; i < Size; ++i) {
            if (m_Data[i] < other.m_Data[i])
                return false;

            if (m_Data[i] > other.m_Data[i])
                return true;
        }

        return false;
    }

    template <int Size, int CellSize>
    bool LongNumber<Size, CellSize>::operator >=(const LongNumber& other) const {
        if (m_Sign < other.m_Sign)
            return false;

        if (m_Sign > other.m_Sign)
            return true;

        if (m_Length < other.m_Length)
            return m_Sign == Sign::Minus;

        if (m_Length > other.m_Length)
            return m_Sign == Sign::Plus;

        for (int i = Size - m_Length; i < Size; ++i) {
            if (m_Data[i] < other.m_Data[i])
                return false;

            if (m_Data[i] > other.m_Data[i])
                return true;
        }

        return true;
    }

    template <int Size, int CellSize>
    bool LongNumber<Size, CellSize>::operator !=(const LongNumber& other) const {
        return std::tie(m_Data, m_Sign) != std::tie(other.m_Data, other.m_Sign);
    }

    template <int Size, int CellSize>
    bool LongNumber<Size, CellSize>::operator ==(const LongNumber& other) const {
        return std::tie(m_Data, m_Sign) == std::tie(other.m_Data, other.m_Sign);
    }

    template <int Size, int CellSize>
    LongNumber<Size, CellSize> LongNumber<Size, CellSize>::ModuloAdd(const LongNumber& other, const Sign& sign) const {
        LongNumber result;

        result.m_Sign = sign;

        for (int i = Size - 1, transfer = 0; i >= 0; --i) {
            auto& currentCell = result.m_Data[i];

            currentCell  = m_Data[i] + other.m_Data[i] + transfer;
            transfer     = currentCell / m_MaxCellValue;
            currentCell %= m_MaxCellValue;

            if (transfer == 0)
                break;
        }

        result.Update();

        return result;
    }

    template <int Size, int CellSize>
    LongNumber<Size, CellSize> LongNumber<Size, CellSize>::ModuloSub(const LongNumber& other, const Sign& sign) const {
        LongNumber result;

        result.m_Sign = sign;

        for (int i = Size - 1, transfer = 0; i >= 0; --i) {
            auto& currentCell = result.m_Data[i];

            currentCell  = (m_Data[i] - transfer) - other.m_Data[i] + m_MaxCellValue;
            transfer     = currentCell < m_MaxCellValue ? 1 : 0;
            currentCell %= m_MaxCellValue;
        }

        result.Update();

        return result;
    }

    template <int Size, int CellSize>
    LongNumber<Size, CellSize> LongNumber<Size, CellSize>::Division(const LongNumber <Size, CellSize> &other,
                                                                    bool returnRemainder) const{
        LongNumber result, remainder;

        LongNumber second = other;
        second.m_Sign = Sign::Plus;

        result.m_Sign = m_Sign == other.m_Sign ? Sign::Plus : Sign::Minus;

        for(int i = Size - m_Length + 1; i < Size; i++){
            for(int j = Size - remainder.m_Length - 1; j < Size - 1; j++)
                remainder.m_Data[j] = remainder.m_Data[j + 1];

            remainder.m_Data[Size - 1] = m_Data[i];
            remainder.UpdateLength();

            int counter = 0;
            while(remainder >= second){
                counter++;
                remainder -= second;
            }

            result.m_Data[i] = counter;
        }

        result.Update();
        remainder.m_Sign = m_Sign;
        remainder.Update();

        if (returnRemainder)
            return remainder;
        return result;
    }

    template <int Size, int CellSize>
    std::istream& operator >>(std::istream& istream, LongNumber<Size, CellSize>& number) {
        std::string string;

        istream >> string;
        number.SetString(string);

        return istream;
    }

    template <int Size, int CellSize>
    void LongNumber<Size, CellSize>::UpdateLength() {
        auto it     = std::find_if(m_Data.begin(), m_Data.end(), [](int cell) { return cell != 0; });
        int  length = m_Data.end() - it;

        m_Length = length == 0 ? 1 : (length - 1) * CellSize + Internal::GetLength(*it);
    }

    template <int Size, int CellSize>
    void LongNumber<Size, CellSize>::UpdateString() {
        m_String.clear();

        if (m_Sign == Sign::Minus)
            m_String.push_back('-');

        auto begin = std::find_if(m_Data.begin(), m_Data.end(), [](int cell) { return cell != 0; });

        for (auto it = begin; it != m_Data.end(); ++it)
            m_String.append(*it != 0 ? std::to_string(*it) : std::string(CellSize, '0'));

        if (m_String.empty())
            m_String = "0";
    }

    template <int Size, int CellSize>
    void LongNumber<Size, CellSize>::Update() {
        UpdateLength();
        UpdateString();
    }

    template <int Size, int CellSize>
    std::ostream& operator <<(std::ostream& ostream, const LongNumber<Size, CellSize>& number) {
        return ostream << number.ToString();
    }

} // namespace GeneralAlgebra