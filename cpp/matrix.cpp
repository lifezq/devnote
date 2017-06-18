#include<iostream>
using namespace std;

void mulMatrix(int **matrixA, int **matrixB, int **matrixC, int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            matrixC[i][j]=0;
            for(int k=0;k<n;k++){
                matrixC[i][j]+=matrixA[i][k]*matrixB[k][j];
            }
        }
    }
}

bool YangMatrixLocateSearch(int **matrix, int n, int value){
    int i=0,j=n-1;
    int val=matrix[i][j];
    while(true){
        if(val>value && j>0){
           val=matrix[i][--j]; 
        }else if(val<value && i<n-1){
            val=matrix[++i][j];
        }else if(val==value){
            return true;
        }else{
            return false;
        }
    }
}

bool YangMatrixBinarySearch(int **matrix, int n, int value){
    int left=0,right=n-1;
    while(left<=right){
        int mid=left+((right-left)>>1);
        if(matrix[mid][mid]>value){
            right=mid-1;
        }else if(matrix[mid][mid]<value){
            left=mid+1;
        }else {
            return true;
        }
    }

    return false;
}

