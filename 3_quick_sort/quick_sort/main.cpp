#include <iostream>
using namespace std;

void print_array(int array[], int length)
{
    cout<<"--------\n";
    cout<<"print array: \n";
    for(int i=0; i<length-1; i++)
    {
        cout<<array[i]<<", ";
    }
    cout<<array[length-1]<<endl;
    cout<<"--------\n";
}

void partitioning()
{}

void merge()
{}

void quick_sort()
{}

int main(void)
{
    int tmp_array[10]={0, 4, 2, 1, 3, 5, 9, 6, 7, 8};
    print_array(tmp_array, 10);

    return 0;
}
