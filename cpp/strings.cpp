#include<string.h>
#include<limits.h>
#include<stack>
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

void reverseWord(char* s, char* delim){

    char str[strlen(s)];

    strcpy(str, s);


    char *str02 = NULL;
    str02 = strtok(str, delim); 
    
    stack<char*> rst;
    rst.push(str02);

    while(str02!=NULL){
        str02 = strtok(NULL, delim);

        if(NULL != str02) rst.push(str02);
    }

    int n=rst.size();
    for(int i=0;i<n;i++){
        cout << rst.top() << ", ";
        rst.pop();
    }
    cout << endl;
}

int atoi_01(char* s){

    if(NULL == s) return 0;
    while(isspace(*s)) ++s;

    int sign = 1;
    if(s[0]=='+' || s[0] == '-'){
        if(s[0] == '-') sign=-1;
        ++s;
    }

    int n=0,c=0;
    while(*s!=0){
        if(!isdigit(*s)) return 0;
        c=*s-'0';

        if(sign==1 && (n>=INT_MAX/10 || (n==INT_MAX/10 && c>INT_MAX%10))){
            n=INT_MAX;
            break;
        }else if(sign==-1 && (n>=INT_MAX/10 || (n==INT_MAX/10 && c-1>INT_MAX%10))){
            n=INT_MIN;
            break;
        }

       n=n*10+c;
        ++s;
    }

    return sign*n;
}

int main(){

    cout << "isPalindrome--------------------" << isPalindrome("madam", 5) << endl;
    cout << "strBInA-------------------------" << strBInA("abcdef","efa") << endl;

    // reverseWord("hello world.", " ");
    cout << "atoi_01--" << ((atoi_01("   +12345") == 12345) &&  (atoi_01("     -12345") == -12345)) << endl;
    cout << "INT_MAX:" << atoi_01("  1233424235345344") << " INT_MIN:" << atoi_01("   -347289489398549");
    return 0;
}

