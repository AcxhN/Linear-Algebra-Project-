#ifndef QBMATRIX2_H
#define QBMATRIX_H

template <class T>
class qbMatrix2 {
    public: 
    // defining some constructors 
    qbMatrix2();
    qbMatrix2(int nRows, int nCols);
    qbMatrix2(int nRows, int nCols, const T *inputData);
    qbMatrix2(const qbMatrix2<T>& inputMatrix);

    // destructor 
    ~qbMatrix2();

    // config. methods
    bool resize(int numRows, int numCols);

    // Element access methods
    T GetElement(int row, int col);
    bool SetElement(int row, int col, T elementValue);
    int GetNumRows();
    int GetNumCols();

    // Overload == operator 
    bool operator== (const qbMatrix2<T>& rhs);

    // Overload +, -, * operators (friends)
    template <class U> friend qbMatrix2<U> operator+ (const qbMatrix2<U>& lhs, const qbMatrix2<U>& rhs);
    template <class U> friend qbMatrix2<U> operator+ (const U& lhs, const qbMatrix2<U>& rhs);
    template <class U> friend qbMatrix2<U> operator+ (const qbMatrix2<U>& lhs, const U& rhs);

    template <class U> friend qbMatrix2<U> operator- (const qbMatrix2<U>& lhs, const qbMatrix2<U>& rhs);
    template <class U> friend qbMatrix2<U> operator- (const U& lhs, const qbMatrix2<U>& rhs);
    template <class U> friend qbMatrix2<U> operator- (const qbMatrix2<U>& lhs, const U& rhs);

    template <class U> friend qbMatrix2<U> operator* (const qbMatrix2<U>& lhs, const qbMatrix2<U>& rhs);
    template <class U> friend qbMatrix2<U> operator* (const U& lhs, const qbMatrix2<U>& rhs);
    template <class U> friend qbMatrix2<U> operator* (const qbMatrix2<U>& lhs, const U& rhs);

    private:
    int Sub2Ind(int row, int col);

    private:
    T *m_matrixData;
    int m_nRows, m_nCols, m_nElements;
};

/* 
        Constructor and destructor functions 
*/
// default constructor 
template <class T>
qbMatrix2<T>::qbMatrix2() {
    m_nRows = 1;
    m_nCols = 1;
    m_nElements = 1;
    m_matrixData = new T[m_nElements];
    m_matrixData[0] = 0.0;
}

// Construct empty matrix (all elemenets == 0)
template <class T>
qbMatrix2<T>::qbMatrix2(int nRows, int nCols) {
    m_nRows = nRows;
    m_nCols = nCols;
    m_nElements = m_nRows * m_nCols;
    m_matrixData = new T[m_nElements];
    for (int i = 0; i < m_nElements; i++) {
        m_matrixData[i] = 0.0;
    }
}

// Construct from const linear array 
template <class T>
qbMatrix2<T>::qbMatrix2(int nRows, int nCols, const T *inputData) {
    m_nRows = nRows;
    m_nCols = nCols;
    m_nElements = m_nRows * m_nCols;
    m_matrixData = new T[m_nElements];
    for (int i = 0; i < m_nElements; i++) {
        m_matrixData[i] = inputData[i];
    }
}

template <class T>
qbMatrix2<T>::~qbMatrix2() { // destructor 
    if(m_matrixData != nullptr) {
        delete[] m_matrixData;
    }
}

/*
        Configuration functions 
*/

template <class T>
bool qbMatrix2<T>::resize(int numRows, int numCols) {
    m_nRows = numRows;
    m_nCols = numCols;
    m_nElements = m_nRows * m_nCols; 
    delete[] m_matrixData;
    m_matrixData = new T[m_nElements];
    if (m_matrixData != nullptr) {
        for (int i = 0;i < m_nElements ; i++) {
            m_matrixData[i] = 0.0;
        }
        return true;
    }
    else {
        return false;
    }
}

/*
        Element functions 
*/
template <class T> 
T qbMatrix2<T>::GetElement(int row, int col) {
    int linearIndex = Sub2Ind(row, col);
    if (linearIndex >= 0) {
        return m_matrixData[linearIndex];
    }
    else {
        return 0.0;
    }
}

template <class T>
bool qbMatrix2<T>::SetElement(int row, int col, T elementValue) {
    int linearIndex = Sub2Ind(row, col);
    if (linearIndex >= 0) {
        m_matrixData[linearIndex] = elementValue;
        return true;
    }
    else {
        return false;
    }
}

template <class T>
int qbMatrix2<T>::GetNumRows() {
    return m_nRows;
}

template <class T>
int qbMatrix2<T>::GetNumCols() {
    return m_nCols;
}

/*
        Overloaded operator functions 
        The + operator 
*/
// matrix + matrix 
template <class T>
qbMatrix2<T> operator+ (const qbMatrix2<T>& lhs, const qbMatrix2<T> & rhs) {
    int numRows = lhs.m_nRows;
    int numCols = lhs.m_nCols;
    int numElements = numRows * numCols;
    T * tempResult = new T[numElements];
    for(int i = 0; i < numElements; i++) {
        tempResult[i] = lhs.m_matrixData[i] + rhs.m_matrixData[i];
    }
    qbMatrix2<T> result(numRows, numCols, tempResult);
    delete[] tempResult;
    return result;
}

// scalar + matrix 
template <class T>
qbMatrix2<T> operator+ (const T& lhs, const qbMatrix2<T>& rhs) {
    int numRows = rhs.m_nRows;
    int numCols = rhs.m_nCols;
    int numElements = numRows * numCols;
    T *tempResult = new T[numElements];
    for (int i = 0; i < numElements; ++i) {
        tempResult[i] = lhs + rhs.m_matrixData[i];
    }
    qbMatrix2<T> result(numRows, numCols, tempResult);
    delete[] tempResult;
    return result;
}

// matrix + scalar 
template <class T>
qbMatrix2<T> operator+ (const qbMatrix2<T>& lhs, const T& rhs) {
    int numRows = lhs.m_nRows;
    int numCols = lhs.m_nCols;
    int numElements = numRows * numCols;
    T *tempResult = new T[numElements];
    for (int i = 0; i < numElements; ++i) {
        tempResult[i] = lhs.m_matrixData[i] + rhs;
    }
    qbMatrix2<T> result(numRows, numCols, tempResult);
    delete[] tempResult;
    return result;
}

/*
        The - operator 
*/
// matrix - matrix 
template <class T>
qbMatrix2<T> operator- (const qbMatrix2<T>& lhs, const qbMatrix2<T> & rhs) {
    int numRows = lhs.m_nRows;
    int numCols = lhs.m_nCols;
    int numElements = numRows * numCols;
    T * tempResult = new T[numElements];
    for(int i = 0; i < numElements; i++) {
        tempResult[i] = lhs.m_matrixData[i] - rhs.m_matrixData[i];
    }
    qbMatrix2<T> result(numRows, numCols, tempResult);
    delete[] tempResult;
    return result;
}

// scalar - matrix 
template <class T>
qbMatrix2<T> operator- (const T& lhs, const qbMatrix2<T>& rhs) {
    int numRows = rhs.m_nRows;
    int numCols = rhs.m_nCols;
    int numElements = numRows * numCols;
    T *tempResult = new T[numElements];
    for (int i = 0; i < numElements; ++i) {
        tempResult[i] = lhs - rhs.m_matrixData[i];
    }
    qbMatrix2<T> result(numRows, numCols, tempResult);
    delete[] tempResult;
    return result;
}

// matrix - scalar 
template <class T>
qbMatrix2<T> operator- (const qbMatrix2<T>& lhs, const T& rhs) {
    int numRows = lhs.m_nRows;
    int numCols = lhs.m_nCols;
    int numElements = numRows * numCols;
    T *tempResult = new T[numElements];
    for (int i = 0; i < numElements; ++i) {
        tempResult[i] = lhs.m_matrixData[i] - rhs;
    }
    qbMatrix2<T> result(numRows, numCols, tempResult);
    delete[] tempResult;
    return result;
}

/*
        The * operator 
*/
// scalar * matrix 
template <class T>
qbMatrix2<T> operator* (const T& lhs, const qbMatrix2<T>& rhs) {
    int numRows = rhs.m_nRows;
    int numCols = rhs.m_nRows; 
    int numElements = numRows * numCols;
    T *tempResult = new T[numElements];
    for(int i = 0; i < numElements; ++i) {
        tempResult[i] = lhs * rhs.m_matrixData[i];
    }
    qbMatrix2<T> result(numRows, numCols, tempResult);
    delete[] tempResult;
    return result;
}

// matrix * scalar 
template <class T>
qbMatrix2<T> operator* ( const qbMatrix2<T>& lhs, const T& rhs) {
    int numRows = lhs.m_nRows;
    int numCols = lhs.m_nRows; 
    int numElements = numRows * numCols;
    T *tempResult = new T[numElements];
    for(int i = 0; i < numElements; ++i) {
        tempResult[i] = lhs.m_matrixData[i] * rhs;
    }
    qbMatrix2<T> result(numRows, numCols, tempResult);
    delete[] tempResult;
    return result;
}

// matrix * matrix 
template <class T>
qbMatrix2<T> operator* (const qbMatrix2<T>& lhs, const qbMatrix2<T>& rhs) {
    int r_numRows = rhs.m_nRows;
    int r_numCols = lhs.m_nCols;
    int l_numRows = lhs.m_nRows;
    int l_numCols = rhs.m_nCols;

    if(l_numRows == r_numCols) {
        // to perform matrix multiplication the lhs matrix must have the same number of rows as the rhs matrix' coloumns
        // output will be the same size as the rhs matrix 
        T *tempResult = new T[lhs.m_nRows * rhs.m_nCols];

        // for loop through each row of LHS
        for(int lhsRow = 0; lhsRow < l_numRows; lhsRow++) {
            // loop through each coloum on the RHS 
            for(int rhsCol = 0; rhsCol < r_numCols; rhsCol++) {
                T elementResult = 0.0;
                // loop through each element of the LHS row
                for (int lhsCol = 0; lhsCol < l_numCols; lhsCol++) {
                    // compute the LHS linear index 
                    int lhsLinearIndex = (lhsRow * l_numCols) + lhsCol;

                    // compute the RHS linear index (based on the LHS col) 
                    // rhs row % == lsh coloumn #
                    int rhsLinearIndex = (lhsCol * r_numCols) + rhsCol;

                    // perfom the multiplication on these elements 
                    elementResult += (lhs.m_matrixData[lhsLinearIndex] * rhs.m_matrixData[rhsLinearIndex]);
                }

                // store the result 
                int resultLinearIndex = (lhsRow * r_numCols) + rhsCol;
                tempResult[resultLinearIndex] = elementResult;
            }
        }
        qbMatrix2<T> result(l_numRows,r_numCols, tempResult);
        delete[] tempResult;
        return result;
    }
    else {
        qbMatrix2<T> result(1,1);
        return result;
    }
}

/*
        The == operator 
*/
template <class T>
bool qbMatrix2<T>::operator== (const qbMatrix2<T>& rhs) {
    // Check if the matrices are the same size, if not return false
    if ((this -> m_nRows != rhs.m_nRows) && (this->m_nCols != rhs.m_nCols)) {
        return false;
    }

    // Check if the elements are equal 
    bool flag = true;
    for(int i = 0; i <this -> m_nElements; ++i) {
        if(this -> m_matrixData[i] != rhs.m_matrixData[i]) {
            flag = false;
        }
        return flag; 
    }
}

/*
        Private functions 
*/
template <class T>
int qbMatrix2<T>::Sub2Ind(int row, int col) {
    if((row < m_nRows) && (row >= 0) && (col < m_nCols) && (col >= 0)) {
        return (row * m_nCols) + col;
    }
    else {
        return -1;
    }
}

#endif
