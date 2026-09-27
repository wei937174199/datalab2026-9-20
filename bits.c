/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~(~x | ~y);
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return (~(x & y)) & (~(~x & ~y));
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    /* 先排除两种特殊情况，即有一个是0，另外一个不是0 */
    if (!x && y){return 0;}
    if (x && !y){return 0;}
    /* 右移31位后，剩下的就是符号位 */
    if ((x>>31)^(y>>31)){return 0;}
    return 1;
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    /*思路和bitCount一致，依次检查前16/8/4/2/1位置是否全为0*/

    int s1 = ((v >> 16)>0) << 4;
    v >>= s1;

    int s2 = ((v >> 8)>0) << 3;
    v >>= s2;

    int s3 = ((v >> 4)>0) << 2;
    v >>= s3;

    int s4 = ((v >> 2)>0) << 1;
    v >>= s4;

    int s5 = (v >> 1)>0;
    v >>= s5;

    return s1|s2|s3|s4|s5;
    /*由于这五个数字本身就在不同数位，可以直接用｜拼接*/
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    n = n << 3;
    m = m << 3;
    /*左移3相当于乘以8*/
    int mask = 0xFF;
    int num1 = (x >> n) & mask;
    int num2 = (x >> m) & mask;
    int mask1 = 0xFF << n;
    int mask2 = 0xFF << m;
    x = x & ~(mask1 | mask2);
    num2 = num2 << n;
    num1 = num1 << m;
    x = x | num1;
    x = x | num2;
    return x;
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    unsigned int res = 0;
    int i = 32;
    while(i){
        res = res << 1;
        unsigned int mask = 1;
        res += mask & v;
        v = v >> 1;
        i--;
    }
    return res;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    x = x >> n;
    int mask = 0xFFFFFFFF >> n;
    x = x & mask;
    return x;
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    /*可以换个角度考虑，取反之后，检查前导0最多有多少个*/
    /*由于以上运算符只能支持2的指数倍运算，而且32恰好是2的五次方，可以考虑用类似二分查找的方式
    来解决问题*/
    /*即，取反之后，先检查前16位是否为0
    如果为0，则把count+16，然后把原数字左移16位，再检查前8位是否为0*/
    /*由此，用等比数列求和，可以检查前31位是否为0（原数字即是否为1），因此还要额外检查此时的最后一位是否为0*/
    /*如果前16位不全为0，则答案必然小于16，因此不对数字作移动，检查前8位是否为0*/
    x = ~x;
    int count = 0;
    int s;

    s = !(x >> 16) << 4;/*
    如果x左移16位是0，则原来的x最左边16位必然是0*/
    count += s;
    /*只有在最左边16位都是0的情况下才把s左移16位*/
    x <<= s;

    s = !(x >> 24) << 3;
    count += s;
    x <<= s;

    s = !(x >> 28) << 2;
    count += s;
    x <<= s;

    s = !(x >> 30) << 1;
    count += s;
    x <<= s;

    s = !(x >> 31);
    count += s;
    x <<= s;

    return count + !(x >> 31);


}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    if(x == 0) return 0;

    unsigned sign = x < 0;
    unsigned mag = x;
    if (sign) mag = -mag;  /* 无符号运算，可处理 INT_MIN */

    unsigned num = mag;
    int mask = (0xFFFFFFFF >> 9);

    int count = 0;
    int i = 16;
    while (i){ 
        unsigned int sig = num >> i;
        if (sig){
            count += i;
            num >>= i;
        }
        i >>= 1;
    }

    int e = count + 127;

    if(count > 23){
        int drop = count - 23;
        unsigned int retained = mag >> drop;/*得到剩下的部分*/
        unsigned int discarded = mag << (32 - drop); /*得到被舍去的数字部分*/

        if ((discarded > 0x80000000u) | ((discarded == 0x80000000u) & (retained & 0x1u))){
            retained += 1;
        }
        if (retained >> 24){
            retained >>= 1;
            e += 1;
        }
        mag = retained;
    }
    else{
        mag <<= (23-count);
    }
    int m = mask & mag;

    return (sign << 31) + (e << 23) + m;
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    int s = (1 << 31) & uf;
    int E = ((uf >> 23) & 0x000000FF);
    int M = uf & (0xFFFFFFFF >> 9);
    if (E == 0x000000FF) return uf;
    /*如果指数部分全1，该数字要么是无穷大要么是NAN，如果是NAN，那么直接返回uf，如果是无穷大
    则返回同符号的无穷大，同样是uf，因此直接返回uf即可*/
    if (E){
        if (E + 1 == 0x000000FF){
            /*此时返回同符号的无穷大*/
            return s + (0x000000FF << 23);
        } 
        /*如果无溢出，直接返回指数+1的结果即可*/
        return uf + (1 << 23);
    }
    /*如果是非规格化小数，则分别考虑溢出和不溢出，先考虑溢出，即非规格化小数->规格化小数
    如果溢出，那么必然是因为M的最高位为1，此时转化为规格化小数后，指数部分为1
    尾数往前进1，相当于舍去M的最高位*/
    if (M & (1 << 22)){
        return s + (1 << 23) + (((0xFFFFFFFF >> 10) & M) << 1);
    }
    /*若非特殊情况，则直接把M往前挪一位即可*/
    return s + (((0xFFFFFFFF >> 10) & M) << 1);
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */

int float64_f2i(unsigned uf1, unsigned uf2) {
    unsigned exp = (uf2 >> 20) & 0x7FF;
    unsigned sign = uf2 >> 31;
    unsigned high = (uf2 & 0xFFFFF) | 0x100000;
    int magnitude;
    int E = exp - 1023;

    if (E < 0)
        return 0;

    if (E > 30)
        return 0x80000000u;

    if (E <= 20) {
        magnitude = high >> (20 - E);
    } else {
        magnitude = (high << (E - 20))
                  | (uf1 >> (52 - E));
    }

    if (sign)
        return -magnitude;
    return magnitude;
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    /*先考虑正溢出情况，规格化float32能表示的最大整数是2^127, 如果x大于127则直接返回正无穷*/
    if (x > 127) return (0xFF000000 >> 1);
    /*再考虑规格化float32能表示的最小数，为2^-126*/
    if (x >= -126){
        int n = x + 127;
        return n << 23;
    }
    /*接下来是非规格化小数，考虑最小的非规格化小数：2^-149*/
    if (x >= -149){
        return 0x1 << (x + 149);
    }
    return 0;

}
