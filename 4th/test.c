#include <stdio.h>
#include <string.h>

int main(){

    int i;
    printf("숫자를 입력하세요 :");
    scanf("%d", &i);

    int arr[i];

    memset(arr, -1, sizeof(arr));

    for(int j = 0; j<i; j++){
        printf("%d ", arr[j]);
    }


}