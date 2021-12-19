#include <stdio.h>
#include <stdlib.h>

// print array of size n
void print_array(int a[], int n) {
    int i = 0;
    while(i < n - 1 && a[i] == 0)i++;
    while(i < n) {
        printf("%d",a[i]);
        i++;
    }
    printf("\n");
}

// scans a single integer into array with size n
void scan_array(int a[], int n) {
    for(int i = 0; i < n; i++) {
        scanf("%1d", &a[i]);
    }
}

// the multiplication operation
// it is better to split the logic on several other functions
// then make multiply function call them.


void array_all_zeros (int array[], int z){
    for(int i = 0; i < z; i++){array[i] = 0;}
}

void multiply(int x[], int n, int y[], int m, int ans[], int* t) {


    array_all_zeros(ans, *t);// answer array all zeros
    
    if(!x[0] || !y[0]){
        *t = 1;
        return ;
    }

    // multiplication of arrays
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            ans[i+j] += x[i] * y[j];
        }
    }

    if(!ans[*t-1]){(*t)--;} // separate if it's a multiply of 10 or not

    int temp = 0;
    for(int i = n+m-1; i > 0; i--){
        temp = ans[i] / 10;
        ans[i] = ans[i] % 10;
        ans[i-1] += temp; 
    }
    
}

// don't change any thing in the main
int main() {
    
    int n;
    scanf("%d", &n);
    int x[n];
    scan_array(x, n);

    int m;
    scanf("%d", &m);
    int y[m];
    scan_array(y, m);

    int t = n + m;
    int ans[t];
    
    multiply(x, n, y, m, ans, &t);
    print_array(ans, t);

    return 0;
}
