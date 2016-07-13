#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <cstring>
#include <cstdlib>
#include <sstream>

using namespace std;

// The least significant "digit" is placed in data[0]
struct BigInteger {
    public:
        // Represent a large positive integer in base 1000000000
        static const int base = 1000000000;
        static const int decimalShift = 9;
        // Maximum length of digit array is 3000
        static const int initialSize = 3000;

        BigInteger(const char *numString);
        string toString();
        friend BigInteger multiply(const BigInteger& num1, const BigInteger& num2);
        friend BigInteger add(const BigInteger& num1, const BigInteger& num2);
        friend BigInteger substract(const BigInteger& num1, const BigInteger& num2);
        friend BigInteger splitAndGetLowerPart(const BigInteger &num1, int middle);
        friend BigInteger splitAndGetHigherPart(const BigInteger &num1, int middle);
    private:
        BigInteger():digitsLength(0) { }
        int digitsLength;
        unsigned int data[initialSize];
};


BigInteger::BigInteger(const char* numString):digitsLength(0) {
    // assume that the numString is always valid
    int size = strlen(numString);

    char tmpArray[decimalShift+1];
    while (size > 0) {
        size -= decimalShift;
        if (size >= 0) {
            strncpy(tmpArray, numString + size, decimalShift);
        } else {
            strncpy(tmpArray, numString, size + decimalShift);
            tmpArray[size + decimalShift] = '\0';
        }
        data[digitsLength++] = atoi(tmpArray);
    }
    
    // remove leading zero
    while (digitsLength > 1 && data[digitsLength-1] == 0) {
        digitsLength--;
    }
}

string BigInteger::toString() {
    string numString;
    
    int size = digitsLength;
    
    ostringstream ostream;
    bool firstDigit = true;

    // Notice that the least significant "digit" is placed in tmpData[0]
    while(size>0) {
        if (firstDigit) {
            firstDigit = false;
            ostream << data[size-1];
        } else
            ostream << setw(decimalShift) << setfill('0') << data[size-1];
        numString += ostream.str();
        ostream.str("");
        size--;
    }
    
    return numString;
}

BigInteger splitAndGetLowerPart(const BigInteger &num, int middle) {
    BigInteger low;
    if (num.digitsLength >= middle) {
        copy(num.data, num.data + middle, low.data);
        low.digitsLength = middle;
    } else {
        copy(num.data, num.data + num.digitsLength, low.data);
        low.digitsLength = num.digitsLength;
    }
    return low;
}

BigInteger splitAndGetHigherPart(const BigInteger &num, int middle) {
    BigInteger high;
    if (num.digitsLength > middle) {
        copy(num.data + middle, num.data + num.digitsLength, high.data);
        high.digitsLength = num.digitsLength - middle;
    } else {
        high.data[high.digitsLength++] = 0;
    }

    return high;
}

BigInteger multiply(const BigInteger& num1, const BigInteger& num2)
{
    // Karatsuba algorithm
    // https://en.wikipedia.org/wiki/Karatsuba_algorithm
    // 大数除法：http://blog.csdn.net/sunmenggmail/article/details/7532522
    
    if (num1.digitsLength == 1 && num2.digitsLength == 1) {
        BigInteger product;
        unsigned long long tmp = static_cast<unsigned long long>(num1.data[0]) * num2.data[0];
        product.data[product.digitsLength++] = tmp % BigInteger::base;
        tmp = tmp / BigInteger::base;
        if (tmp)
            product.data[product.digitsLength++] = tmp;

        return product;
    }

    int maxSize = max(num1.digitsLength, num2.digitsLength); 
    int middle = maxSize / 2;

    // x0 is num1.data[0...middle)
    // x1 is num1.data[middle...maxSize)
    BigInteger x0 = splitAndGetLowerPart(num1, middle);
    BigInteger x1 = splitAndGetHigherPart(num1, middle);

    BigInteger y0 = splitAndGetLowerPart(num2, middle);
    BigInteger y1 = splitAndGetHigherPart(num2, middle);

    BigInteger z0 = multiply(x0, y0);
    BigInteger z2 = multiply(x1, y1);
    BigInteger z1 = multiply(add(x1,x0), add(y1,y0));
    z1 = substract(z1, z2);
    z1 = substract(z1, z0);

    memmove(z2.data + middle * 2, z2.data, sizeof(unsigned int) * z2.digitsLength);
    memset(z2.data, 0, sizeof(unsigned int) * middle * 2);
    z2.digitsLength += middle * 2;
    // remove leading zero
    while (z2.digitsLength > 1 && z2.data[z2.digitsLength-1] == 0) {
        z2.digitsLength--;
    }

    memmove(z1.data + middle, z1.data, sizeof(unsigned int) * z1.digitsLength);
    memset(z1.data, 0, sizeof(unsigned int) * middle);
    z1.digitsLength += middle;
    while (z1.digitsLength > 1 && z1.data[z1.digitsLength-1] == 0) {
        z1.digitsLength--;
    }

    return add(add(z2, z1), z0);
}

BigInteger add(const BigInteger& num1, const BigInteger& num2)
{
    BigInteger tmpInteger;

    int maxLength = num1.digitsLength > num2.digitsLength ? num1.digitsLength : num2.digitsLength;
    const unsigned int* maxData = (num1.digitsLength > num2.digitsLength) ? num1.data: num2.data;

    int minLength = num1.digitsLength > num2.digitsLength ? num2.digitsLength : num1.digitsLength;
    const unsigned int* minData = num1.digitsLength > num2.digitsLength ? num2.data: num1.data;

    unsigned int carry = 0;
    int i;
    for( i = 0; i<minLength; i++) {
        unsigned long long tmp = static_cast<unsigned long long>(minData[i]) + maxData[i] + carry;
        carry = tmp / BigInteger::base;
        tmpInteger.data[tmpInteger.digitsLength++] = tmp % BigInteger::base;
    }

    for (; i < maxLength; ++i) {
        unsigned long long tmp = static_cast<unsigned long long>(maxData[i]) + carry;
        carry = tmp / BigInteger::base;
        tmpInteger.data[tmpInteger.digitsLength++] = tmp % BigInteger::base;
    }

    if(carry > 0)
        tmpInteger.data[tmpInteger.digitsLength++] = 1;

    return tmpInteger;
}

BigInteger substract(const BigInteger& num1, const BigInteger& num2)
{
    // assume that num1 is great than or equal to num2
    BigInteger tmpInteger;
    
    unsigned int borrow = 0;

    int i = 0;
    for (i=0; i<num2.digitsLength; i++) {
        long long tmp = static_cast<long long>(num1.data[i]) - borrow;
        if (tmp < num2.data[i]) {
            borrow = 1;
            tmp += BigInteger::base;
        } else 
            borrow = 0;
        tmp -= num2.data[i];
        tmpInteger.data[tmpInteger.digitsLength++] = tmp;
    }

    for (; i<num1.digitsLength; i++) {
        long long tmp = static_cast<long long>(num1.data[i]) - borrow;
        if (tmp < 0)
            tmp += BigInteger::base;
        else
            borrow = 0;
        tmpInteger.data[tmpInteger.digitsLength++] = tmp;
    }

    // remove leading zero
    while (tmpInteger.digitsLength > 1 && tmpInteger.data[tmpInteger.digitsLength-1] == 0) {
        tmpInteger.digitsLength--;
    }

    return tmpInteger;
}

int main(int argc, char *argv[])
{
    int N = 0;
    while (cin >> N) {
        BigInteger aNMinus1("2");
        cout << aNMinus1.toString() << endl;
        BigInteger one("1");
        for (int i=2; i<=N; i++) {
            BigInteger aN = add(multiply(substract(aNMinus1, one), aNMinus1), one);
            cout << aN.toString() << endl;
            aNMinus1 = aN;
        }
    }
    return 0;
}
