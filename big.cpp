#include "big.h"

using namespace BigErrors;

/*
head - указатель на начало числа
tail - указатель на конец числа
alloc - количество выделенной памяти
length - мощность - количество блоков
capacity - емкость, количество выделенной памяти
*/
unsigned int nlz(base x)
{
    unsigned int result = sizeof(base) * 8, sdwig = sizeof(base) * 8 / 2, add = sdwig;
    while (add > 0)
    {
        if((x>>sdwig) == 0)
        {
            result -= add; x <<= add;
//            std::cout << "x >>" << sdwig << " = 0  " << "  result = " << result;
        }
        add /= 2;
        sdwig += add;

//        std::cout << "   add = " << add << "   sdwig = " << sdwig << std::endl;
    }
//    std::cout << std::endl << "result = " << result;
    return result;
}

Big::Big()
{
    head = new base[100];
    tail = head;
    alloc= head + 100 - 1;
}

Big::~Big()
{
    if(head) {
        delete[] head;
        head = nullptr;
    }
}

Big::Big(int capacity)
{
    head = new base[capacity];
    tail = head;
    alloc= head + capacity - 1;
}

Big::Big(const Big &rhs)
{
    int capacity = rhs.alloc - rhs.head +1;
    int length = rhs.tail - rhs.head +1;

    head = new base[capacity];
    alloc = head + capacity -1;
    tail = head;
    for (int i = 0; i < length; i++) {
        head[i] = rhs.head[i];
        tail++;
    }
    tail--;
}

void Big::resize(int newCapacity)
{
    if(getCapacity() < newCapacity)
    {
        if(head)
        {
            delete[] head;
        }
        head = new base[newCapacity];
        tail = head;
        alloc = head + newCapacity - 1;
    }
}

int Big::getCapacity() const
{
    return alloc - head +1;
}

int Big::getLength() const
{
    return tail - head +1;
}

void Big::rand(int bound)
{
    if(getCapacity() <  bound)
    {
        resize(bound + 1);
    }
    tail = head;
    alloc = head + getCapacity() -1;
    for (int i = 0; i < bound; i++)
    {
        head[i] = std::rand();
        tail++;
    }
    tail--;
}

void Big::compress()
{
    for(int i = getLength() - 1; 0 <= i; i--)
    {
        if (head[i] != 0)
        {
            return;
        }
        tail--;
    }
}

/*1 - больше
 * -1 меньше
 * 0 - равно*/
int compare(const Big &lhs, const Big &rhs)
{
    if(lhs.getLength() > rhs.getLength())
    {
        return 1;
    }
    else
        if(lhs.getLength() < rhs.getLength())
        {
            return -1;
        }
    for(int i = rhs.getLength() - 1; 0 <= i; i--)
    {
        if(lhs.head[i] > rhs.head[i])
            return 1;
        else
            if (lhs.head[i] < rhs.head[i])
            {
                return -1;
            }
    }
    return 0;
}

int compareWithZero(const Big &rhs)
{
    for (int i = rhs.getLength() - 1; 0 <= i; i--)
    {
        if (rhs.head[i] != 0)
        {
            return false;
        }
    }
    return true;
}

bool operator>(Big &lhs, Big &rhs)
{
    if (compare(lhs, rhs) == 1) {
        return true;
    }
    return false;
}

bool operator<(Big &lhs, Big &rhs)
{
    if (compare(lhs, rhs) == -1) {
        return true;
    }
    return false;
}

bool operator>=(Big &lhs, Big &rhs)
{
    int result = compare(lhs, rhs);
    if ((result == 1) || (result == 0)) {
        return true;
    }
    return false;
}

bool operator<=(Big &lhs, Big &rhs)
{
    int result = compare(lhs, rhs);
    if ((result == -1) || (result) == 0) {
        return true;
    }
    return false;
}

bool operator==(Big &lhs, Big &rhs)
{
    if(compare(lhs, rhs) == 0)
    {
        return true;
    }
    return false;
}

bool operator!=(Big &lhs, Big &rhs)
{
    if(compare(lhs, rhs) != 0)
    {
        return true;
    }
    return false;
}

Big Big::mulBase(base rhs)
{
    Big result;

    if(0 == rhs)
    {
        result.head[0] = 0;
        result.tail = result.head;
        return result;
    }
    d_base mask = static_cast<d_base>(1) << (sizeof(base) * 8);

    if (result.getCapacity() < getLength() + 1) {
        result.resize(getLength() + 1);
    }

    d_base tmp;
    d_base carry = 0;
    result.tail = result.head;

    int i;
    for (i = 0; i < getLength(); i++)
    {
        tmp = static_cast<d_base>(head[i]) * static_cast<base>(rhs) + carry;
        carry = tmp / mask;
        result.head[i] = static_cast<base>(tmp % mask);
        result.tail++;
    }

    result.head[i] = carry;
    result.compress();
    return result;
}

Big Big::divBase(base rhs, base &remainder)
{
    Big result;
    if (0 == rhs) {
        throw DIV_ZERO;
    }

    if (getLength() <= 1 && 0 == head[0])  // comparison with zero
    {
        result.tail = result.head;
        result.head[0] = 0;
        remainder = rhs;
        return result;
    }

    result.resize(getCapacity());

    d_base t = 0;
    d_base mask = static_cast<d_base>(1) << (sizeof(base) * 8);
    remainder = 0;

    result.tail = result.head + getLength() -1;
    for(int i = 0; i < result.getLength(); i++)
    {
        result.head[i] = 0;
    }

    for (int i = getLength() - 1; 0 <= i; i--)
    {
        t = static_cast<d_base>(head[i]) + static_cast<d_base>(remainder) * mask;
        result.head[i] = static_cast<base>(t / rhs);
        remainder = static_cast<base>(t % static_cast<d_base>(rhs));
    }

    result.compress();
    return result;

}

// e/c
Big div(Big &e, Big &c, Big &remainder)
{
    Big a, b, result;
    a.resize(e.getLength() + 1);

    a = e;
    b = c;

    int j = 0, n = b.getLength(), m = a.getLength() - n, flag;

    if(compareWithZero(e))
    {
        result.tail = result.head + 1;
        result.head[0] = 0;
        remainder.tail = remainder.head + 1;
        remainder.head[0] = 0;
        return result;
    }

    if (-1 == compare(e, c))
    {
        result.tail = result.head;
        result.head[0] = 0;
        remainder = e;
        return result;
    }

    //if base divBase
    if (b.getLength() <= 1)
    {
        base r;
        result = a.divBase(b.head[0], r);
        remainder.head[0] = r;
        remainder.tail = remainder.head;
        return result;
    }

    d_base d, mask;
    mask = static_cast<d_base>(1) << (sizeof(base) * 8);
    d = mask / static_cast<d_base>(b.head[b.getLength() - 1] + 1);

    a = a.mulBase(static_cast<base>(d));
    if(a.getLength() == e.getLength())
    {
        a.tail++;
        a.head[a.getLength() - 1] = 0;
    }
    b = b.mulBase(static_cast<base>(d));

    d_base roof, left_part, right_part;
    Big glass, new_num, q;

    new_num.resize(a.getLength());
    q.resize(a.getLength());
    q.tail = q.head + m + 1;

    for(int i = 0; i < q.getLength(); i++)
    {
        q.head[i] = 0;
    }

    base b1 = b.head[b.getLength() - 1];
    base b2 = b.head[b.getLength() - 2];
    base aj, aj1, aj2;
    for(j = 0; j <= m; j++)
    {
        aj = a.head[a.getLength() - j - 1];
        aj1 = a.head[a.getLength() - j - 2];
        aj2 = a.head[a.getLength() - j - 3];

        if (aj == b1)
        {
            roof = mask - 1;
        }
        else
        {
            roof = (static_cast<d_base>(aj) * static_cast<d_base>(mask)
                    + static_cast<d_base>(aj1)) /
                static_cast<d_base>(b1);
        }

        //check uneq
        while (1)
        {
            left_part = static_cast<d_base>(b2) * roof;

            right_part = static_cast<d_base>(aj) * mask + static_cast<d_base>(aj1)
                    - roof * static_cast<d_base>(b1);
            /*дальнейшее умножение приведет к переполнению,
         * а left_part переполнится никогда не может =>
         * нервенство не выполнено*/
            if (right_part >> sizeof(base) * 8)
            {
                break;
            }
            right_part = right_part * mask + static_cast<d_base>(aj2);
            if (left_part > right_part)
            {
                roof--;
            } else
                break;
        }
        //mulBase and sub

        new_num.tail = new_num.head;

        for (int i = 0; i <= n; i++)
        {
            new_num.head[n - i] = a.head[a.getLength() - j - 1 - i];
            new_num.tail++;
        }
        new_num.tail--;

        flag = 0;
        glass = b.mulBase(static_cast<base>(roof));
        while (-1 == compare(new_num, glass))
        {
            roof--;
            flag = 1;
            glass = b.mulBase(static_cast<base>(roof));
            exit(0);
        }

        int stored_length_new_num = new_num.getLength();
        new_num = new_num - glass;

        if (stored_length_new_num > new_num.getLength())
        {
            for (int i = new_num.getLength(); i < stored_length_new_num; i++)
            {
                new_num.head[i] = 0;
                new_num.tail++;
            }
        }

        for (int i = 0; i <= n; i++)
        {
            a.head[a.getLength() - j - 1 - i] = new_num.head[n - i];
        }

        if (flag)
        {
            roof--;
            a = a + b;
        }
        q.head[m - j] = static_cast<base>(roof);
    }
    base r;
    remainder = a.divBase(d, r);
    q.compress();
    return q;
}

void Big::pow(Big &degree, Big &modulo)
{
//    Big z{(degree.head[0] & 1)? (*this) : (static_cast<base>(1))};
    Big q{*this};
    Big z;
    if (degree.head[0] & 1) {
        z = *this;
    } else {
        z = static_cast<base>(1);
    };

    int bits = sizeof(base) * 8;

    auto degreeLen = degree.getLength();
    int j = 1;
    for(int i = 0; i < degreeLen; ++i) {
        for(; j < bits; ++j) {
            q = q * q;
            q = q % modulo;
            if (degree.head[i] & (1 << j)) {
                z = z * q;
                z = z % modulo;
            }
        }
        j = 0;
    }
    *this = z;
}

Big operator+(Big &lhs, Big &rhs)
{
    d_base tmp;
    d_base mask = static_cast<d_base>(1) << (sizeof(base) * 8);
    int carry = 0;
    int BLength = rhs.getLength();
    int ALength = lhs.getLength();
    int LessLength;
    int rcapacity,i;
    Big result{ALength + BLength + 1};

    if(ALength <= BLength)
        LessLength = ALength;
    else
        LessLength = BLength;

    if(lhs.getCapacity() <= rhs.getCapacity())
    {
        rcapacity = rhs.getCapacity();
    }
    else
    {
        rcapacity = lhs.getCapacity();
    }

    if(rcapacity + 1 > result.getCapacity())
    {
        result.resize(rcapacity + 1);
    }

    result.tail = result.head;

    for (i = 0; i < LessLength; i++)
    {
        tmp = static_cast<d_base>(rhs.head[i]) +
                static_cast<d_base>(lhs.head[i]) + carry;
        result.head[i] = tmp % mask;
        carry = !!(tmp / mask);
        result.tail++;
    }

    if(i < ALength)
    {
        for(; i < ALength; i++)
        {
            tmp = lhs.head[i] + carry;
            result.head[i] = tmp % mask;
            result.tail++;
            carry = !!(tmp / mask);
        }
    }
    else
        if(i < BLength)
        {
            for(; i < BLength; i++)
            {
                tmp = rhs.head[i] + carry;
                result.head[i] = tmp % mask;
                result.tail++;
                carry = !!(tmp / mask);
            }
        }
    if (carry)
    {
        result.head[i] = carry;
        result.tail++;
    }
    result.tail--;
    result.compress();
    return result;
}

Big operator-(Big& lhs, Big& rhs)
{
    int flag = compare(lhs, rhs);
    if(-1 == flag)
    {
        std::cout << "invalid operation" << std::endl;
        throw INCOMPATIBLE_OPERANDS;
    }

    Big result;
    result.resize(lhs.getCapacity());
    result.tail = result.head;

    if(0 == flag)
    {
        result.head[0]=0;
        return result;
    }
    int carry = 0, given = 0;
    d_base mask = static_cast<d_base>(1) << (sizeof(base) * 8);
    d_base tmp0 = 0;
    d_base tmp1;

    int i;
    for (i = 0; i < rhs.getLength(); i++)
    {
        result.tail++;
        tmp0 = static_cast<d_base>(rhs.head[i]) + static_cast<d_base>(carry);
        carry = 0;

        if (static_cast<d_base>(lhs.head[i]) < tmp0)
        {
            given = 1;
        }

        if (given) {
            tmp1 = static_cast<d_base>(lhs.head[i]) + mask - tmp0;
            result.head[i] = static_cast<base>(tmp1);
            carry = 1;
            given = 0;
        }

        else {
            result.head[i] = lhs.head[i] - static_cast<base>(tmp0);
        }
    }

    for (i; i < lhs.getLength(); i++)
    {
        result.tail++;
        tmp0 = carry;
        carry = 0;
        if (static_cast<d_base>(lhs.head[i]) < tmp0)
        {
            given = 1;
        }

        if (given) {
            tmp1 = static_cast<d_base>(lhs.head[i]) + mask - static_cast<d_base>(tmp0);
            result.head[i] = tmp1;
            carry = 1;
            given = 0;
        }
        else {
            result.head[i] = static_cast<d_base>(lhs.head[i]) - static_cast<d_base>(tmp0);
        }
    }
    result.tail--;
    result.compress();
    return result;
}

Big operator*(Big& lhs, Big& rhs)
{
    Big result;
    if (rhs.getLength() <= 1) {
        result = lhs.mulBase(rhs.head[0]);
        return result;
    }

    result.resize(lhs.getLength() + rhs.getLength());

    d_base mask = static_cast<d_base>(1) << (sizeof(base) * 8);
    d_base tmp, carry = 0;

    for(int i = 0; i < result.getCapacity(); i++)
    {
        result.head[i] = 0;
        result.tail++;
    }
    result.tail--;

    int i, j;
    for (j = 0; j < rhs.getLength(); j++)
    {
        if (0 == rhs.head[j])
        {
            continue;
        }

        for (i = 0; i < lhs.getLength(); i++)
        {
            tmp = static_cast<d_base>(lhs.head[i]) * static_cast<d_base>(rhs.head[j]) +
                static_cast<d_base>(result.head[i + j]) + carry;
            result.head[i + j] = static_cast<base>(tmp);
            carry = tmp >> sizeof(base) * 8;
        }
        result.head[i + j] = carry;
        carry = 0;
    }
    result.compress();
    return result;
}

Big operator/(Big &lhs, Big &rhs)
{
    Big remainder;
    return div(lhs, rhs, remainder);
}

Big operator%(Big &lhs, Big &rhs)
{
    Big remainder;

    div(lhs, rhs, remainder);
    return remainder;
}

Big& Big::operator=(const Big &rhs)
{
    if (getCapacity() < rhs.getCapacity()) {
        resize(rhs.getCapacity());
    }

    tail = head;
    int length = rhs.getLength();

    for (int i = 0; i < length; i++)
    {
        head[i] = rhs.head[i];
        tail++;
    }
    tail--;
    return *this;
}

Big& Big::operator=(int rhs)
{
    if (getCapacity() < 1)
    {
        resize(1);
    }

    tail = head;
    head[0] = rhs;

    return *this;
}

std::istream &operator>>(std::istream &in, Big &rhs)
{
    int block = sizeof(base) * 2;//количество цифр F в числе
    base tmp0, tmp1;
    int index;
    std::string string_for_num;
    in >> string_for_num;
    int string_length = string_for_num.length();
    int n = (string_length) / block + !!((string_length) % (block));
    if(n> rhs.getCapacity())
    {
        rhs.resize(n);
    }

    for(int k = 0; k < n; k++)
    {
        tmp0 = 0;
        tmp1 = 0;
        for(int i = 0; i< block; i++)
        {
            index = string_length - k * block - i -1;
            if(index < 0)
                break;
            char symbol = string_for_num[index];
            if (symbol >= '0' && symbol <= '9')
            {
                tmp1 = symbol - 48;
            } else if (symbol >= 'a' && symbol <= 'f')
            {
                tmp1 = symbol - 87;  // 10 + symbol - 97;
            } else if (symbol >= 'A' && symbol <= 'F')
            {
                tmp1 = symbol - 55;  // symbol + 10 - 65
            } else
            {
                throw INCORRECT_SYMBOL;
            }
            tmp0 = tmp0 | (tmp1 << 4 * i);
        }
        rhs.head[k] = tmp0;
        rhs.tail++;
    }
    rhs.tail--;
    return in;
}

std::ostream &operator<<(std::ostream &out, Big &rhs)
{
    int block = sizeof(base) * 2;  // *8/4 how many numbers in the "base"
    //int length = rhs.getLength();
    int mask = 0xF;
    char tmp;
    unsigned int flag = 1;

    for (int i = rhs.getLength() - 1; 0 <= i; i--)  // starting from the older
    {
        for (int l = (block - 1) * 4; l >= 0; l -= 4)
        {
            tmp = (rhs.head[i] & (mask << l)) >> l;  // get an each number from the block(one number - four bytes)
            if (tmp >= 0 && tmp <= 9)
            {
                if (flag && 0 == tmp)
                {
                    continue;
                }
                flag = 0;
                tmp = tmp + '0';
                out << tmp;
            }
            else
                if (tmp >= 0xA && tmp <= 0xF)
                {
                    tmp = tmp + 87;
                    out << tmp;
                    flag = 0;
                }
            else
                {
                    throw INCORRECT_SYMBOL;
                }
            }
    }

    if(flag)
    {
        out << "0";
    }
    return out;
}

Big mulByKaratsuba(Big &lhs, Big &rhs)
{
    int lhsLen = lhs.getLength();
    int rhsLen = rhs.getLength();

    int range = 70; // как его найти?
    if (lhsLen < range || rhsLen < range) {
        return lhs * rhs;
    }

    int maxLen = std::max(lhsLen, rhsLen);
    int sliceLen = (maxLen + 1) / 2;
//    if(maxLen % 2 == 0) {
//        ++sliceLen;
//    }

    Big lhsLow, lhsHigh, rhsLow, rhsHigh;

    auto makeSlices = [sliceLen](const Big &num, Big &numLow, Big &numHigh, int &numLen) {
        if(sliceLen < numLen) {
            numLow.head = num.head;
            numLow.tail = &num.head[sliceLen - 1];

            numHigh.head = &num.head[sliceLen];
            numHigh.tail = num.tail;
        } else {
            numLow.head = num.head;
            numLow.tail = num.tail;

            numHigh = (Big)0;
        }
    };

    makeSlices(lhs, lhsLow, lhsHigh, lhsLen);
    makeSlices(rhs, rhsLow, rhsHigh, rhsLen);

    Big resLow{sliceLen * 2}; // B
    Big resMiddle{sliceLen * 4};
    Big resHigh{sliceLen * 4}; //A
    Big res{sliceLen * 4};


    resLow = mulByKaratsuba(lhsLow, rhsLow);
    resHigh = mulByKaratsuba(lhsHigh,rhsHigh);
//    resLow = lhsLow * rhsLow;
//    resHigh = lhsHigh * rhsHigh;

//    resMiddle = mulByKaratsuba(lhsLow + rhsHigh, lhsHigh + rhsLow);
//  костыль, тк нормально не складывает
    Big tmp1{sliceLen + 1};
    Big tmp2{sliceLen + 1};
    tmp1 = lhsLow + lhsHigh;
    tmp2 = rhsHigh + rhsLow;

    resMiddle = mulByKaratsuba(tmp1, tmp2);
//    resMiddle = tmp1 * tmp2;


    resMiddle = resMiddle - resLow;
    resMiddle = resMiddle - resHigh;

    resHigh.shiftLeft(sliceLen * 2);
    resMiddle.shiftLeft(sliceLen);
//    res = resHigh + resMiddle + resLow;
//  костыль, тк нормально не складывает
    res = resHigh + resLow;
    res = res + resMiddle;

    //Очищение, тк ссылались на одну память
    lhsLow.head = nullptr;
    lhsHigh.head = nullptr;
    rhsLow.head = nullptr;
    rhsHigh.head = nullptr;

    return res;
}

void Big::shiftLeft(int amount)
{
    if(this->getCapacity() < this->getLength() + amount)
    {
        std::cout << "error";
    }

    for(int i = this->getLength(); i > 0; i--)
    {
        this->head[i + amount -1] = this->head[i - 1];
    }

    for(int i = amount-1; i >= 0; i--)
    {
        this->head[i] = 0;
        this->tail++;
    }
}

