#include <map>
#include <iostream>

using namespace std;

/*
3+5=8

0000 0011 = 3

0000 0101 = 5


0000 0110 = 0000 0011 ^ 0000 0101

0000 0010 = 0000 0011 & 0000 0101 << 1


0000 0100 = 0000 0110 ^ 0000 0010

0000 0100 = 0000 0110 & 0000 0010 << 1


0000 0000 = 0000 0100 ^ 0000 0100

0000 1000 = 0000 0100 & 0000 0100 << 1


0000 1000 = 0000 0000 ^ 0000 1000

0000 0000 = 0000 0000 & 0000 1000 << 1

=========
0000 1000
*/

// 异或：
//     1. 任何数异或1，取反。常用于把某位取反
//     2. 任何数异或0,任何数。
//     3. 任何数异或自己，把自己清零。
//     4. (n^-1) == ~n
//     5. -n == ~(n-1) == (~n)+1

// 清除位最右边的1: n = n & (n-1)
// 获取位最右边的1: n = n & (-n) || n = n & (~(n-1))

int binaryPlus(int a,int b){
    int carry,add;

    do{
        add = a ^ b; //该操作得到本位的加法结果 
        carry = (a & b) << 1; //该操作得到该位对高位的进位值  

        a = add;
        b = carry;

        // cout << "add:" << add << " carry:" << carry << endl;

    }while(carry!=0); //循环直到某次运算没有进位，运算结束

   
    return add;
}

int binarySubtract(int a, int b){
    return binaryPlus(a, binaryPlus(~b, 1)); // a + b = a + (-b) = a + (~b + 1)
}

/*
* BinaryMultiply
* 7 * 18 = 0000 0111 * 0001 0010 = 126
               00000111
               00010010
               ---------
               00000000
              00000111
             00000000
            00000000
           00000111
           ------------
               01111110         = 126
               0+2+4+8+16+32+64 = 126
*/
int binaryMultiply(int a,int b){
    map<int, int> bit32_map;

    for(int i = 0; i < 32; i++){
        bit32_map.insert(pair<int, int>(1<<i, i));
    }
        
    // for(map<int, int>::iterator it = bit32_map.begin(); it != bit32_map.end(); it++){
    //     cout << "it->first:" << it->first << "it->second:" << it->second  << endl;
    // }

    int num = 0;

    while(b!=0){
      int move_bit = bit32_map[b&(-b)];
        num += a << move_bit;
        b = b&(b-1);

        // cout << "move_bit:" << move_bit << endl;
    }
  
    // cout << "num:" << num << endl;

    // cout << "bit32_map.size:" << bit32_map.size() << endl;

    return num;
}

int binaryDivide(int a, int b){
    bool is_negative = (a > 0) ^ (b > 0);  
    if(a < 0)  a = -a;  
    if(b < 0)  b = -b;  
    if(a < b)  return 0;  

    int divisor_move_bit = 0;   
    for(divisor_move_bit = 0; divisor_move_bit < 32; divisor_move_bit++) {  
        if((b << divisor_move_bit) >= a)
            break; 
    }  

    int num = 0;  
    for(; divisor_move_bit >= 0; divisor_move_bit--) {  

      if((b << divisor_move_bit)>a) continue;

        num |= (1 << divisor_move_bit);  
        a -= (b << divisor_move_bit);  
    }  

    if(is_negative)  
        return -num;  

    return num;  
}

void swap(int *a, int *b){
    *a^=*b;
    *b^=*a;
    *a^=*b;
}

// (n^-1)==~n
int abs(int n){
    int f = n >> 31;
    return (n^f)-f;
}

int avg(int a, int b){
    return (a&b)+((a^b)>>1);
}

int min(int a, int b){
    return b + ((a-b) & ((a-b)>>31));
}

int max(int a, int b){
    return a - ((a-b) & ((a-b)>>31));
    //return (b&((a-b)>>31)) | (a & (~(a-b)>>31));
}

int minInt(){
    return 1<<31;
}

int maxInt(){
    return ((unsigned) -1) >> 1;
    //return (1<<31)-1;
}

int multiply2M(int n, int m){
    return n<<m;// n=n*(2^m)
}

int isOddNumber(int n){
    return (n&1) == 1;
}

int isEqual(int a, int b){
    return (a^b) == 0;
}

int getBit(int n, int m){
    return (n>>(m-1)) & 1;
}

int main(){

    int a,b;

    cout << "Input int.a:";
    cin >> a;

    cout << "Input int.b:";
    cin >> b;
    cout  << endl;

    cout << a << "+" << b << "=" << binaryPlus(a,b) << endl;

    cout << a << "-" << b << "=" << binarySubtract(a,b) << endl;

    cout << a << "x" << b << "=" << binaryMultiply(a,b) << endl;

    cout << a << "/" << b << "=" << binaryDivide(a,b) << endl;

    swap(&a, &b);
    cout << "after swaped:" << " a:" << a << " b:" << b << endl;
  
    cout << "abs a:" << abs(a) << " b:" << abs(b) << endl;

    cout << "avg ab:" << avg(a, b) << endl;

    cout << "min:" << min(a, b) << " max ab:" << max(a, b) << endl;

    cout << "min int:" << minInt() << " max int:" << maxInt() << endl;

    cout << a << "*(2^3)=" << multiply2M(a, 3) << endl;

    cout << "isOddNumber a:" << isOddNumber(a) << " b:" << isOddNumber(b) << endl;
    return 0;
}

