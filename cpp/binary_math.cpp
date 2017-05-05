#include<map>
#include<iostream>

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
    return 0;
}

