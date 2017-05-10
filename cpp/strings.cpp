#include<string.h>
#include<iostream>
using namespace std;

bool isPalindrome(const char *s, int n){
    
    if(NULL==s || n<1){
        return false;
    }

    const char* front, *back;

    front = s;
    back = s+n-1;

    while(front<back){
        if(*front!=*back) return false;

        ++front;
        --back;
    }


    return true;
}

bool strBInA(const char* a, const char* b){
    long hash = 0;

    while(*a){
        hash |= 1<< (*a-'A');
        ++a;
    }

    while(*b){
        if(!(hash&(1<<(*b-'A')))) return false;
        ++b;
    }

    return true;
}

char* reverseWord(char* s, char* delim){







    char str[strlen(s)];

    strcpy(str, s);

    cout << "strlen:" << strlen(s) << " length:"   << endl;

    char *str02 = NULL;
    str02 = strtok(str, delim); 

    cout << "str:" << str << endl;

    char rst[10][];

    int i=0;
    while(str02!=NULL){
        cout << "str:" <<  " s:" << str02 << endl;
        str02 = strtok(NULL, delim);

        rst[i] = str02;

        i++;

        cout << "rst:" << rst[i] << endl;
    }



   //
   return s;
}

int main(){

    cout << "isPalindrome--------------------" << isPalindrome("madam", 5) << endl;
    cout << "strBInA-------------------------" << strBInA("abcdef","efa") << endl;

    reverseWord("hello#you are best#now ok.", " ");
    return 0;
}

