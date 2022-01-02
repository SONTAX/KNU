namespace GeneralAlgebra {
    
    template <EllipticCurveNumberConcept T>
    EllipticCurve<T>::EllipticCurve(const T& m_A, const T& m_B, const T& primeNumber)
        : m_Field(primeNumber)
        , m_A(m_A)
        , m_B(m_B) {}

    template <EllipticCurveNumberConcept T>
    void EllipticCurve<T>::SetPrimeNumber(const T& primeNumber) {
        m_Field.SetPrimeNumber(primeNumber);
    }

    template <EllipticCurveNumberConcept T>
    void EllipticCurve<T>::SetA(const T& a) {
        m_A = a;
    }

    template <EllipticCurveNumberConcept T>
    void EllipticCurve<T>::SetB(const T& b) {
        m_B = b;
    }

    template <EllipticCurveNumberConcept T>
    Point<T> EllipticCurve<T>::GetInverse(const Point& point) {
        Point result;
        
        T y1_2 = m_Field.Pow(point.Y, T(2));
        T x1   = m_Field.Add(m_Field.Add(LongArithmetic::FastPow(point.X, T(3)), LongArithmetic::NaiveMul(m_A, point.X)), m_B);
        
        if (y1_2 == x1) {
            if (point.Y != T(0)) {
                result.X = point.X;
                result.Y = m_Field.Sub(T(0), point.Y);
            } else if (point.Y == T(0)) {
                result.X = point.X;
                result.Y = point.Y;
            } else {
                result.X = -1;
                result.Y = -1;
            }
        } else{
            result.X = -1;
            result.Y = -1;
        }

        return  result;
    }
        
    template <EllipticCurveNumberConcept T>
    Point<T> EllipticCurve<T>::Add(const Point& lhs, const Point& rhs) {
        Point result;
        
        T y1_2 = m_Field.Pow(lhs.Y, T(2));
        T y2_2 = m_Field.Pow(rhs.Y, T(2));
        
        T x1   = m_Field.Add(m_Field.Add(LongArithmetic::FastPow(lhs.X, T(3)), LongArithmetic::NaiveMul(m_A, lhs.X)), m_B);
        T x2   = m_Field.Add(m_Field.Add(LongArithmetic::FastPow(rhs.X, T(3)), LongArithmetic::NaiveMul(m_A, rhs.X)), m_B);
        
        if (y1_2 == x1 && y2_2 == x2) {
            if (lhs.X != rhs.X) {
                T s     = m_Field.Div(m_Field.Sub(rhs.Y, lhs.Y), m_Field.Sub(rhs.X, lhs.X));
                T x_sum = m_Field.Sub(m_Field.Sub(m_Field.Pow(s, T(2)), lhs.X), rhs.X);

                result.X = x_sum;

                T sum1  = m_Field.Mul(s, m_Field.Sub(lhs.X, x_sum));
                T y_sum = m_Field.Sub(sum1, lhs.Y);

                result.Y = y_sum;
            } else {
                if (lhs.Y == rhs.Y && lhs.Y != T(0)) {
                    T s     = m_Field.Div(m_Field.Add(m_Field.Mul(T(3), m_Field.Pow(lhs.X, T(2))), m_A), m_Field.Mul(T(2), lhs.X));
                    T x_sum = m_Field.Sub(m_Field.Pow(s, T(2)), m_Field.Mul(T(2), lhs.X));

                    result.X = x_sum;

                    T sum1  = m_Field.Mul(s, m_Field.Sub(lhs.X, x_sum));
                    T y_sum = m_Field.Sub(sum1, lhs.Y);

                    result.Y = y_sum;
                } else {
                    result.X = -1;
                    result.Y = -1;
                }
            }
        } else{
            result.X = -1;
            result.Y = -1;
        }
        
        return result;
    }
    
} // namespace GeneralAlgebra