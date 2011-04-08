#include <iostream>

template <typename T>
class Array {
    private:
        int m_nLength;
        T *m_ptData;

    public:
        Array()
        {
            m_nLength = 0;
            m_ptData = 0;
        }

        Array(int nLength)
        {
            m_ptData = new T[nLength];
            m_nLength = nLength;
        }

        ~Array()
        {
            delete[] m_ptData;
        }

        void Erase()
        {
            delete[] m_ptData;
            m_ptData = 0;
            m_nLength = 0;
        }

        T& operator[](int nIndex)
        {
            return m_ptData[nIndex];
        }

        int GetLength();
};

template <typename T>
int Array<T>::GetLength() { return m_nLength; }

int main()
{
    Array<int> anArray(12);
    Array<double> adArray(12);

    for(int nCount = 0; nCount < 12; nCount++) {
    int anArray[12];
        anArray[nCount] = nCount;
        adArray[nCount] = nCount + 0.5;
    }

    for(int nCount = 11; nCount >= 0; nCount--) {
        std::cout << anArray[nCount] << "\t" << adArray[nCount] << std::endl;
    }

    return 0;
}
