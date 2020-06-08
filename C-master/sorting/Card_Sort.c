#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    char *arr1, *arr2, *temp1, *temp2, *temp3, *temp4;
    int *num, *temp5;
    int N, index, tmp;
    
    scanf("%d", &N); //입력할 카드 개수
    
    arr1 = (char*)malloc(sizeof(char)*N);
    arr2 = (char*)malloc(sizeof(char)*N);
    temp1 = (char*)malloc(sizeof(char)*N);
    temp2 = (char*)malloc(sizeof(char)*N);
    temp3 = (char*)malloc(sizeof(char)*N);
    temp4 = (char*)malloc(sizeof(char)*N);
    temp5 = (int*)malloc(sizeof(int)*N);
    num = (int*)malloc(sizeof(int)*N);
    for( int i = 0 ; i < N ; i ++ ){
        scanf("%c", &arr1[i]); //카드의 suit
        getchar();
        scanf("%c", &arr2[i]); //카드의 rank
        getchar();
    }
    
    for( int i = 0 ; i < N-1 ; i ++ ){
        index = i;
        for( int j = i + 1 ; j < N ; j ++ ){
            if(arr1[index] > arr1[j])
                index == j;
        }
        temp1[i] = arr1[i];
        arr1[i] = arr1[index];
        arr1[index] = temp1[i];
        temp2[i] = arr2[i];
        arr2[i] = arr2[index];
        arr2[index] = temp2[i];
    }
    
    for( int i = 0 ; i < N ; i ++ ){
        switch(arr2[i]){
        case 65: 
            num[i] = 14;
            break;
        case 75:
            num[i] = 13;
            break;
        case 81:
            num[i] = 12;
            break;
        case 74:
            num[i] = 11;
            break;
        case 50:
            num[i] = 2;
            break;
        case 51:
            num[i] = 3;
            break;
        case 52:
            num[i] = 4;
            break;
        case 53:
            num[i] = 5;
            break;
        case 54:
            num[i] = 6;
            break;
        case 55:
            num[i] = 7;
            break;
        case 56:
            num[i] = 8;
            break;
        case 57:
            num[i] = 9;
            break; 
        default:
            num[i] = 10;
            break;
        }
    }
    
    for( int i = 0 ; i < N-1 ; i ++ ){
        tmp = i;
        for( int j = i + 1 ; j < N ; j ++ ){
            if(arr1[i] == arr1[j]){
                if(num[i] > num[j]){
                    tmp = j;
                }
                temp3[i] = arr1[i];
                arr1[i] = arr1[tmp];
                arr1[tmp] = temp3[i];
                temp4[i] = arr2[i];
                arr2[i] = arr2[tmp];
                arr2[tmp] = temp4[i];
            }
        }
    }
    
    for( int i = 0 ; i < N ; i ++ ){
        printf("%c %c\n", arr1[i], arr2[i]);
    }
}
