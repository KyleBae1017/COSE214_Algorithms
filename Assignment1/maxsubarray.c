#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct ret_val{ //define struct to return 3 values together

    int l; //low
    int h; //high
    int s; //sum

};

typedef struct ret_val ret_val;

ret_val find_max_crossing_subarray(int *a, int low, int mid, int high){

    int left_sum = INT_MIN;
    int sum = 0;
    int max_left;

    for (int i=mid;i>=low;i--){
        sum += a[i];
        if(sum > left_sum){
            left_sum = sum;
            max_left = i;
        }
    }

    int right_sum = INT_MIN;
    sum = 0;
    int max_right;

    for (int i=mid+1;i<=high;i++){
        sum += a[i];
        if(sum > right_sum){
            right_sum = sum;
            max_right = i;
        }
    }

    ret_val r = {max_left, max_right, left_sum + right_sum};

    return r;

}

ret_val find_maximum_subarray(int *a, int low, int high){


    if(low == high){

        ret_val r = {low, high, a[low]};
        return r;

    }
    
    else{

        int mid = (low + high) / 2;

        ret_val tmp_left = find_maximum_subarray(a, low, mid);
        ret_val tmp_right = find_maximum_subarray(a, mid + 1, high);
        ret_val tmp_cross = find_max_crossing_subarray(a, low, mid, high);

        int left_sum = tmp_left.s;
        int right_sum = tmp_right.s;
        int cross_sum = tmp_cross.s;

        if(left_sum >= right_sum && left_sum >= cross_sum) return tmp_left;
        else if(right_sum >= left_sum && right_sum >= cross_sum) return tmp_right;
        else return tmp_cross;

    }


}

int main(){

    int n;
    scanf("%d", &n);

    int *arr = malloc(sizeof(int) * n);

    for(int i=0;i<n;i++){
        scanf("%d", &arr[i]);
    }

    ret_val ans = find_maximum_subarray(arr, 0, n-1);

    printf("%d\n%d\n%d\n", ans.l, ans.h, ans.s);

    free(arr);

    return 0;

}