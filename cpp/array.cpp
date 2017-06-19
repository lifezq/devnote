#include<iostream>
#include<algorithm>
#include<stdio.h>
using namespace std;

void twoSum(int *arr, unsigned int len, int sum){
    sort(arr, arr+len);
    int begin = 0, end = len-1;
    while(begin < end){
        long currSum = arr[begin] + arr[end];
        if(currSum==sum){
            cout << "begin val:" << arr[begin] << " end val:" << arr[end] << endl;
            begin++;
            end--;
        }else{
            
            if(currSum<sum)
                begin++;
            else
                end --;
        }
    }
}

void threeSum(int *arr, int len){

    sort(arr, arr+len);

    int second,end,sum;
    for(int first=0;first<len-2;first++){

        second = first+1;
        end=len-1;

        while(second<end){

            sum=arr[first]+arr[second]+arr[end];
            if(sum==0){

                cout << "first val:" << arr[first] << " second val:" << arr[second] << " three val:" << arr[end] << endl;
                second++;
                end--;

                while(second<end && arr[second-1]==arr[second]) second++;
                while(second<end && arr[end]==arr[end+1]) end--;
            }else{

                if(sum>0)
                    end--;
                else
                    second++;
            }
        }
    }
}

void fourSum(int *arr, int len){

    sort(arr, arr+len);

    int sum;
    for(int i=0;i<len-3;i++){
        for(int j=i+1;j<len-2;j++){
            int k=j+1;
            int h=len-1;

            while(k<h){
                sum=arr[i]+arr[j]+arr[k]+arr[h];
                if(sum == 0){
                    printf("i:%d j:%d k:%d h:%d\n",arr[i],arr[j],arr[k],arr[h]);
                    k++;
                    h--;

                    while(k<h && arr[k-1] == arr[k]) k++;
                    while(k<h && arr[h] == arr[h+1]) h--;
                }else{

                    if(sum>0)
                        h--;
                    else
                        k++;
                }
            }
        }
    }
}

int maxSub(int *arr, int len){
    if(len<1) return 0;

    int currSum=0,maxSum=arr[0];

    for(int i=0;i<len;i++){
        currSum=(arr[i]>currSum+arr[i])?arr[i]:currSum+arr[i];
        maxSum=(maxSum>currSum)?maxSum:currSum;
    }

    return maxSum;
}

long long Fibonacci(unsigned int n){
    int result[3] = {0, 1, 2};
    if (n <= 2) return result[n];

    return Fibonacci(n - 1) + Fibonacci(n - 2);
}

//1, 1, 2, 3, 5, 8, 13, 21..
int ClimbStairs(int n){
    int dp[3] = { 1, 1  };
    if (n < 2) return 1;
    
    for (int i = 2; i <= n; i++){
        dp[2] = dp[0] + dp[1];
        dp[0] = dp[1];
        dp[1] = dp[2];
    }
                    
    return dp[2];
}

bool isOddNumber(int n){
    return (n&0x01)==0x01;
}

void oddEvenSort(int *arr, unsigned int len){
    if(arr == NULL || len == 0) return;

    int *begin = arr;
    int *end = arr+len-1;

    while(begin<end){

        while(isOddNumber(*begin)) begin++;
        while(!isOddNumber(*end)) end--;
        if(begin<end){
            *begin^=*end;
            *end^=*begin;
            *begin^=*end;
        }

        begin++;
        end--;
    }
}

void dutchFlag(int *arr, int len){
    int *begin=arr;
    int *cur=arr;
    int *end=arr+len-1;
    while(cur<=end){
        if(*cur==0){
            if(*cur!=*begin){
                *cur^=*begin;
                *begin^=*cur;
                *cur^=*begin;
            }

            cur++;
            begin++;
        }else if(*cur==1){
            cur++;
        }else{
            if(*cur!=*end){
                *cur^=*end;
                *end^=*cur;
                *cur^=*end;
            }

            end--;
        }
    }
}

bool isEqual(int a, int b){
    return ((a|b)&b) == a;
}

// 查找出现次数等于或超过数组长度一半的数
int findOneNumber(int *arr, int n){
    int candidate=arr[0], nTimes=1;
    for(int i=1;i<n;i++){
        if(candidate!=arr[i]){
            if(nTimes>0){
                nTimes--;
            }else {
                candidate=arr[i];
                nTimes=1;
            }
        }else{
            nTimes++;
        }
    }

    if(nTimes==0) return arr[--n];
    return candidate;
}

//最大连续乘积子串
//动态规划求解法
int maxProductSubstring(int *arr, int n){
    int maxEnd=arr[0], minEnd=arr[0],maxResult=arr[0];
    for(int i=1;i<n;i++){
        int end1=maxEnd*arr[i],end2=minEnd*arr[i];
        maxEnd=max(max(end1, end2), arr[i]);
        minEnd=min(min(end1, end2), arr[i]);
        maxResult=max(maxResult, maxEnd);
    }

    return maxResult;
}

int main(){
    int arr[10] = {-20,-18,-15,17,10,16,8,13,5,7};

    //    twoSum(arr, 10, 20);
    //threeSum(arr, 10);
    //fourSum(arr, 10);
    //cout << "maxSub:" << maxSub(arr,10) << endl;
    //cout << "Fibonacci(5):" << Fibonacci(5) << endl;
    //cout << "ClimbStairs(5):" << ClimbStairs(5) << endl;

    //oddEvenSort(arr,10);
    
    srand(time(0));
    for(int i=0;i<20;i++){
        for(int j=0;j<10;j++) arr[j]=rand()%3;
        dutchFlag(arr, 10);
        for(int i=0;i<10;i++) cout << arr[i] << " ";
        cout << endl;
    }

    //cout << "====:" << isEqual(10,110) << endl;

    int arr2[4]={0,1,2,1};
    cout << "findOneNumber:" << findOneNumber(arr2, 4) << endl;

    cout << "maxProductSubstring value:" << maxProductSubstring(arr, 10) << endl;
    return 0;
}
