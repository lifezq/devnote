#include<iostream>
#include<algorithm>
#include<stdio.h>
using namespace std;

void twoSum(int arr[], unsigned int len, int sum){
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

void threeSum(int arr[], int len){

    sort(arr, arr+len);

    int second,end,sum;
    for(int first;first<len-2;first++){

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

void fourSum(int arr[], int len){

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

int maxSub(int arr[], int len){
    if(len<1) return 0;

    int currSum=0,maxSum=arr[0];

    for(int i=0;i<len;i++){
        currSum=(arr[i]>currSum+arr[i])?arr[i]:currSum+arr[i];
        maxSum=(maxSum>currSum)?maxSum:currSum;
    }

    return maxSum;
}

int main(){
    int arr[10] = {-20,-18,-15,17,10,16,8,13,5,7};
    //    twoSum(arr, 10, 20);
    //threeSum(arr, 10);
    //fourSum(arr, 10);
    cout << "maxSub:" << maxSub(arr,10) << endl;
}
