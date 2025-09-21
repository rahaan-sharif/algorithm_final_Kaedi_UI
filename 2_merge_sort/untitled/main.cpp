#include <iostream>
using namespace std;

void show(int* array, int low, int high)
{
    cout<<"show array:  ";
    for(int i=low; i<high; i++)
        cout<<array[i]<<", ";
    cout<<array[high]<<endl<<endl;
}
void merge(int*& array, int low, int middle_index, int high)
{
    int i=low, j=middle_index+1, index=0;
    int* tmp_array=new int[high-low+1];
    while(index<=(high-low))
    {

        if(i>middle_index)
        {
            tmp_array[index]=array[j++];
        }
        else if(j>high)
        {
            tmp_array[index]=array[i++];
        }
        else if(array[i]<=array[j])
        {
            tmp_array[index]=array[i++];
        }
        else if(array[j]<array[i])
        {
            tmp_array[index]=array[j++];
        }
        else
        {
            cout<<"unexpected error in merge function."<<endl;
        }

        index++;
    }

    for(int k=0; k<(high-low+1); k++)
    {
        array[low+k]=tmp_array[k];
    }
}
void merge_sort(int* array, int low, int high)
{
    if(low<high)
    {
        int middle_index= (low+high)/2;
        merge_sort(array, low , middle_index);
        merge_sort(array, middle_index + 1, high);

        merge(array, low, middle_index, high);
    }
}


int main(void)
{
    int array[10]={10, 9, 8, 1, 2, 4, 3, 6, 7, 5};
    merge_sort(array, 0, 9);
    show(array, 0, 9);


    return 0;
}
