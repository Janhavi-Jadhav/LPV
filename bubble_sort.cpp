#include <iostream>
#include <omp.h>

using namespace std;
// int n = 10;

// function to perform sequential bubble sort
void bubbleSort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

// function to perform parallel bubble sort using OpenMP
void parallelBubbleSort(int arr[], int n) {
    int i, j, temp;
    #pragma omp parallel for private(i, j, temp) num_threads(16)
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}
int main() {
    int *a,n;
    cout<<"\n Enter total no of elements=>";
    cin>>n;
    a=new int[n];
    cout<<"\n Enter elements=>";
    for(int i=0;i<n;i++)
    {
   	 cin>>a[i];
    }
    
    // copy array for parallel sorting
    int arr_copy[n];
    for (int i = 0; i < n; i++) {
        arr_copy[i] = a[i];
    }
    cout << "\nOriginal Array: ";
    for(int i = 0; i<n; i++){
        cout<<a[i]<<" ";
    }
    // measure time for sequential bubble sort
    double start_time = omp_get_wtime();
    bubbleSort(a, n);
    double end_time = omp_get_wtime();
    double sequential_bubble_time = end_time - start_time;
    cout << "\n\nSequential Bubble Sorted array: ";
    for (int i = 0; i < n; i++) {
        cout << a[i] <<" ";
    }

    // measure time for parallel bubble sort
    start_time = omp_get_wtime();
    parallelBubbleSort(a, n);
    end_time = omp_get_wtime();
    double parallel_bubble_time = end_time - start_time;
    cout << "\nParallel Bubble Sorted Array: ";
    for (int i = 0; i < n; i++) {
        cout << a[i] <<" ";
    }
    // output results for bubble sort
    
    cout << "\n\nBubble Sort Results:" << endl;
    cout << "Sequential Time: " << sequential_bubble_time << " seconds" << endl;
    cout << "Parallel Time: " << parallel_bubble_time << " seconds" << endl;
}    