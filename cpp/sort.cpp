#include<iostream>
using namespace std;

#define random(x) (rand()%x)
// #define ARRAY_LEN(a,len) {len=sizeof(a)/sizeof(a[0]);}

void insertSort(int *a, int n){
    for(int i=1;i<n;i++){

        if(a[i-1]>a[i]){

            int j=i-1,x;
            x=a[i];

            while(x<a[j]){
                a[j+1] = a[j];
                j--;
            }

            a[j+1] = x;
        }
    }
}

void quickSort(int *arr, int low, int high)  
{
    if (low < high)
    {
        int i = low, j = high, pivot = arr[low];
        while (i < j)
        {
            while(i < j && arr[j] >= pivot) j--;
            if(i < j) arr[i++] = arr[j];

            while(i < j && arr[i] <= pivot) i++;
            if(i < j) arr[j--] = arr[i];
        }

        arr[i] = pivot;

        quickSort(arr, low, i - 1);
        quickSort(arr, i + 1, high);
    }
}

int main(){


    srand(time(0));

    int arr[10];
    for(int i=0;i<10;i++) arr[i] = random(100);
    for(int i=0;i<10;i++) cout << arr[i] << ", ";
    cout << endl;
    cout << "----------------" << endl;
    //quickSort(arr, 0, 9);
    insertSort(arr,10);

    cout << "after sort:--------------" << endl;
     for(int i=0;i<10;i++) cout << arr[i] << ", ";
    cout << endl;


}

