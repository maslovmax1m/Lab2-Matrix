
#ifndef __TMATRIX_H__
#define __TMATRIX_H__

#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// ������ �������
template <class ValType>
class TVector
{
protected:
    ValType* pVector;
    int Size;       // ������ �������
    int StartIndex; // ������ ������� �������� �������
public:
    TVector(int s = 10, int si = 0);
    TVector(const TVector& v);                // ����������� �����������
    ~TVector();
    int GetSize() { return Size; } // ������ �������
    int GetStartIndex() { return StartIndex; } // ������ ������� ��������
    ValType& operator[](int pos);             // ������
    bool operator==(const TVector& v) const;  // ���������
    bool operator!=(const TVector& v) const;  // ���������
    TVector& operator=(const TVector& v);     // ������������
    // ��������� ��������
    TVector  operator+(const ValType& val);   // ��������� ������
    TVector  operator-(const ValType& val);   // ������� ������
    TVector  operator*(const ValType& val);   // �������� �� ������

    // ��������� ��������
    TVector  operator+(const TVector& v);     // ��������
    TVector  operator-(const TVector& v);     // ���������
    ValType  operator*(const TVector& v);     // ��������� ������������

    // ����-�����
    friend istream& operator>>(istream& in, TVector& v)
    {
        for (int i = 0; i < v.Size; i++)
            in >> v.pVector[i];
        return in;
    }
    friend ostream& operator<<(ostream& out, const TVector& v)
    {
        for (int i = 0; i < v.StartIndex; i++)
            out << setw(5) << setprecision(2) << 0 << ' ';
        for (int i = 0; i < v.Size; i++)
            out << setw(5) << setprecision(2) << v.pVector[i] << ' ';
        return out;
    }
};

template <class ValType>
TVector<ValType>::TVector(int s, int si) : Size(s), StartIndex(si)
{
    if (Size > MAX_VECTOR_SIZE || Size < 0 || StartIndex < 0)
        throw - 1;
    pVector = new ValType[Size];
    for (int i = 0; i < Size; i++)
        pVector[i] = 0;
} /*-------------------------------------------------------------------------*/

template <class ValType> //����������� �����������
TVector<ValType>::TVector(const TVector<ValType>& v) : Size(v.Size), StartIndex(v.StartIndex)
{
    pVector = new ValType[Size];
    for (int i = 0; i < Size; i++)
    {
        pVector[i] = v.pVector[i];
    }
} /*-------------------------------------------------------------------------*/

template <class ValType>
TVector<ValType>::~TVector()
{
    delete[] pVector;
} /*-------------------------------------------------------------------------*/

template <class ValType> // ������
ValType& TVector<ValType>::operator[](int pos)
{
    if (pos - StartIndex < 0 || pos - StartIndex >= Size)
        throw - 1;
    return pVector[pos - StartIndex];
} /*-------------------------------------------------------------------------*/

template <class ValType> // ���������
bool TVector<ValType>::operator==(const TVector& v) const
{
    if (StartIndex != v.StartIndex || Size != v.Size)
        return 0;
    for (int i = 0; i < Size; i++)
    {
        if (pVector[i] != v.pVector[i])
            return 0;
    }
    return 1;
} /*-------------------------------------------------------------------------*/

template <class ValType> // ���������
bool TVector<ValType>::operator!=(const TVector& v) const
{
    return !(*this == v);
} /*-------------------------------------------------------------------------*/

template <class ValType> // ������������
TVector<ValType>& TVector<ValType>::operator=(const TVector& v)
{
    if (this != &v)
    {
        Size = v.Size;
        StartIndex = v.StartIndex;
        delete[]pVector;
        pVector = new ValType[Size];
        for (int i = 0; i < Size; i++)
            pVector[i] = v.pVector[i];
    }
    return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // ��������� ������
TVector<ValType> TVector<ValType>::operator+(const ValType& val)
{
    TVector<ValType> tmp = *this;
    for (int i = 0; i < Size; i++)
    {
        tmp.pVector[i] = tmp.pVector[i] + val;
    }
    return tmp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // ������� ������
TVector<ValType> TVector<ValType>::operator-(const ValType& val)
{
    TVector<ValType> tmp = *this;
    for (int i = 0; i < Size; i++)
    {
        tmp.pVector[i] = tmp.pVector[i] - val;
    }
    return tmp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // �������� �� ������
TVector<ValType> TVector<ValType>::operator*(const ValType& val)
{
    TVector<ValType> tmp(Size, StartIndex);
    for (int i = 0; i < Size; i++)
    {
        tmp.pVector[i] = pVector[i] * val;
    }
    return tmp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // ��������
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType>& v)
{
    if (Size != v.Size)
        throw - 1;
    TVector<ValType> tmp(Size, StartIndex);
    for (int i = 0; i < Size; i++)
    {
        tmp.pVector[i] = pVector[i] + v.pVector[i];
    }
    return tmp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // ���������
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType>& v)
{
    if (Size != v.Size)
        throw - 1;
    TVector<ValType> tmp(Size, StartIndex);
    for (int i = 0; i < Size; i++)
    {
        tmp.pVector[i] = pVector[i] - v.pVector[i];
    }
    return tmp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // ��������� ������������
ValType TVector<ValType>::operator*(const TVector<ValType>& v)
{
    if (Size != v.Size)
        throw - 1;
    ValType tmp = 0;
    for (int i = 0; i < Size; i++)
    {
        tmp = tmp + (pVector[i] * v.pVector[i]);
    }
    return tmp;
} /*-------------------------------------------------------------------------*/


// ����������������� �������
template <class ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
    TMatrix(int s = 10);
    TMatrix(const TMatrix& mt);                    // �����������
    TMatrix(const TVector<TVector<ValType> >& mt); // �������������� ����
    bool operator==(const TMatrix& mt) const;      // ���������
    bool operator!=(const TMatrix& mt) const;      // ���������
    TMatrix& operator= (const TMatrix& mt);        // ������������
    TMatrix  operator+ (const TMatrix& mt);        // ��������
    TMatrix  operator- (const TMatrix& mt);        // ���������

    // ���� / �����
    friend istream& operator>>(istream& in, TMatrix& mt)
    {
        for (int i = 0; i < mt.Size; i++)
            in >> mt.pVector[i];
        return in;
    }
    friend ostream& operator<<(ostream& out, const TMatrix& mt)
    {
        for (int i = 0; i < mt.Size; i++)
            out << mt.pVector[i] << endl;
        return out;
    }
};

template <class ValType>
TMatrix<ValType>::TMatrix(int s) : TVector<TVector<ValType> >(s)
{
    if (this->Size<0 || this->Size > MAX_MATRIX_SIZE)
        throw - 1;
    int StInd = 0;
    for (int i = 0; i < this->Size; i++)
    {
        this->pVector[i] = TVector<ValType>(this->Size - StInd, StInd);
        StInd++;
    }
} /*-------------------------------------------------------------------------*/

template <class ValType> // ����������� �����������
TMatrix<ValType>::TMatrix(const TMatrix<ValType>& mt) : TVector<TVector<ValType> >(mt)
{
    for (int i = 0; i < this->Size; i++)
        this->pVector[i] = TVector<ValType>(mt.pVector[i]);;
}

template <class ValType> // ����������� �������������� ����
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> >& mt) : TVector<TVector<ValType> >(mt)
{ }

template <class ValType> // ���������
bool TMatrix<ValType>::operator==(const TMatrix<ValType>& mt) const
{
    return TVector<TVector<ValType> >::operator==(mt);
} /*-------------------------------------------------------------------------*/

template <class ValType> // ���������
bool TMatrix<ValType>::operator!=(const TMatrix<ValType>& mt) const
{
    return !(*this == mt);
} /*-------------------------------------------------------------------------*/

template <class ValType> // ������������
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType>& mt)
{
    if (this != &mt)
    {
        this->Size = mt.Size;
        delete[] this->pVector;
        this->pVector = new TVector<ValType>[this->Size];
        for (int i = 0; i < this->Size; i++)
            this->pVector[i] = mt.pVector[i];
    }
    return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // ��������
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType>& mt)
{
    if (this->Size != mt.Size)
        throw - 1;
    return TVector<TVector<ValType> >::operator+(mt);
} /*-------------------------------------------------------------------------*/

template <class ValType> // ���������
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType>& mt)
{
    if (this->Size != mt.Size)
        throw - 1;
    return TVector<TVector<ValType> >::operator-(mt);
} /*-------------------------------------------------------------------------*/

// TVector �3 �2 �4 �6
// TMatrix �2 �2 �3 �3
#endif
