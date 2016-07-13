#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <vector>

using namespace std;

// The least significant "digit" is placed in data[0]
struct BigInteger {
    public:
        static const int base = 1 << 16;
        static const int initialSize = 7000;

        BigInteger(string num);
        string toString();
        friend BigInteger multiply(const BigInteger& num1, const BigInteger& num2);
        friend BigInteger add(const BigInteger& num1, const BigInteger& num2);
        friend BigInteger substract(const BigInteger& num1, const BigInteger& num2);
        friend BigInteger splitAndGetLowerPart(const BigInteger &num1, int middle);
        friend BigInteger splitAndGetHigherPart(const BigInteger &num1, int middle);
    private:
        BigInteger():digitsLength(0) { }
        int digitsLength;
        unsigned short data[initialSize];
};


BigInteger::BigInteger(string numString):digitsLength(0) {
    // assume that the numString is always valid
    string::iterator iter = numString.begin(); 
    
    while (iter != numString.end()) {
        int dividend = 0;
        int remainder = 0;
        
        // calculate the remainder
        while (iter != numString.end()) {
            dividend = *iter - '0' + remainder * 10;
            remainder = dividend % base;
            *iter++ = dividend / base + '0';
        }
        data[digitsLength++] = remainder;
        
        iter = numString.begin(); 
    
        // skip the leading '0'
        while (iter != numString.end() && *iter == '0') {
            iter++;
        }
    }
}

string BigInteger::toString() {
    string numString;
    
   unsigned short tmpData[initialSize];
   copy(data, data+digitsLength, tmpData);
   int size = digitsLength;

    // Remember that the least significant "digit" is placed in tmpData[0]
    while(size>0) {
        int dividend = 0;
        int remainder = 0;
        int i = size - 1;
        while(i>=0) {
            dividend = tmpData[i] + remainder * base;
            remainder = dividend % 10;
            tmpData[i] = dividend / 10;
            i--;
        }
        numString += remainder + '0';
        while(size>0 && tmpData[size-1] == 0)
            size--;
    }
    
    reverse(numString.begin(), numString.end());
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
        unsigned int tmp = num1.data[0] * num2.data[0]; 
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

    memmove(z2.data + middle * 2, z2.data, sizeof(unsigned short) * z2.digitsLength);
    memset(z2.data, 0, sizeof(unsigned short) * middle * 2);
    z2.digitsLength += middle * 2;
    // remove leading zero
    while (z2.digitsLength > 1 && z2.data[z2.digitsLength-1] == 0) {
        z2.digitsLength--;
    }

    memmove(z1.data + middle, z1.data, sizeof(unsigned short) * z1.digitsLength);
    memset(z1.data, 0, sizeof(unsigned short) * middle);
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
    const unsigned short* maxData = (num1.digitsLength > num2.digitsLength) ? num1.data: num2.data;

    int minLength = num1.digitsLength > num2.digitsLength ? num2.digitsLength : num1.digitsLength;
    const unsigned short* minData = num1.digitsLength > num2.digitsLength ? num2.data: num1.data;

    unsigned short carry = 0;
    int i;
    for( i = 0; i<minLength; i++) {
        unsigned int tmp = minData[i] + maxData[i] + carry;
        carry = tmp / BigInteger::base;
        tmpInteger.data[tmpInteger.digitsLength++] = tmp % BigInteger::base;
    }

    for (; i < maxLength; ++i) {
        unsigned int tmp = maxData[i] + carry;
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
    
    unsigned short borrow = 0;

    int i = 0;
    for (i=0; i<num2.digitsLength; i++) {
        int tmp = num1.data[i] - borrow;
        if (tmp < num2.data[i]) {
            borrow = 1;
            tmp += BigInteger::base;
        } else 
            borrow = 0;
        tmp -= num2.data[i];
        tmpInteger.data[tmpInteger.digitsLength++] = tmp;
    }

    for (; i<num1.digitsLength; i++) {
        int tmp = num1.data[i] - borrow;
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
    if (argc != 3)
        return -1;

    string numString1(argv[1]);
    BigInteger num1(numString1);
    string numString2(argv[2]);
    BigInteger num2(numString2);
    cout << multiply(num1, num2).toString() << endl;

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
