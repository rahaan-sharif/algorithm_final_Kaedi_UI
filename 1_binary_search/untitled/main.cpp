#include <iostream>
using namespace std;

int binary_search(int* array, int low, int high, int item)
//low is lower index and hig is higher index
{
    while(low<=high)
    {
        if(array[(low+high)/2] == item)
        {
            return ((low+high)/2);
        }
        else if(array[(low+high)/2] > item)
        {
            high=(low+high)/2;
        }
        else
        {
            low=(low+high)/2;
        }
    }

    return -1;
}

int main(void)
{
    int *array= new int[10];
    for(int i=0; i<10; i++)
        array[i]=i+2;
    int index=binary_search(array, 0, 9, 5);

    cout<<"index: "<<index<<endl;
    return 0;
}
