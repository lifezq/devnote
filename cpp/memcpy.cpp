#include<iostream>
#include<assert.h>
using namespace std;

void* memcpy(void *dst, const void *src, size_t count){

    assert((dst != NULL && (src != NULL)));

    unsigned char *pdst = (unsigned char *)dst;
    const unsigned char *psrc = (const unsigned char *)src;

    assert(!(psrc <= pdst && pdst<psrc+count));
    assert(!(psrc >= pdst && psrc<pdst+count));

    while(count--)
    {
        *pdst = *psrc;

        pdst++;
        psrc++;
    }

    return dst;
}

/*  
void* memmove(void* dest, void* source, size_t count){
    void* ret = dest;
    if(dest <= source || dest >= (source + count)){
        // copy from lower addresses to higher addresses
        while(count--)
            *dest++ = *source++;
    }else{
        // copy from higher addresses to lower addresses
        dest += count-1;
        source += count -1;
        while(count--)
            *dest-- = *source--;
    }

    return ret;
}
*/

int main(){

    
    cout << "running..." << endl;

    int a=8888;

    cout << "sizeof a:" << sizeof(a) << endl;
    int b;


    memcpy(&b, &a, sizeof(a));

    cout << "b:" << b << " size a:" << sizeof(a) << " sizeofb :" << sizeof(b) <<endl;
    return 0;
}
