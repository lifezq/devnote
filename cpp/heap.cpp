#include<iostream>  
using namespace std;

int parent(int i){
    return i/2;  
}

int left(int i){
    return 2*i;
}

int right(int i){
    return 2*i+1;
}

void maxHeap(int *a,int i,int len){
    int l=left(i),r=right(i);  
    int largest=i;  
    if(l<=len&&a[largest]<a[l]) largest=l;  

    if(r<=len&&a[largest]<a[r]) largest=r;

    if(largest!=i)  
    {  
        int temp=a[largest];  
        a[largest]=a[i];  
        a[i]=temp;  
        maxHeap(a,largest,len);  
    }
}

void buildMaxHeap(int *a,int len){
    for(int i=len/2;i>=1;i--) maxHeap(a,i,len);
}

void heapSort(int *a,int len){
    len=len-1;
    buildMaxHeap(a,len);  

    cout << "builded heap:";
    for(int i=0;i<=len;i++) cout << a[i] << " " ;
    cout << endl;

    for(int i=len;i>1;)
    {
        int temp;
        temp=a[i];
        a[i]=a[1];
        a[1]=temp;

        i--;

        maxHeap(a,1,i);
    }
}

int main(){
    int a[11]={0,4,1,3,2,16,9,10,14,8,7};  
    heapSort(a,11);  
    for(int i=0;i<11;i++) cout<<a[i]<<" ";  
    cout<<endl;  
}  
