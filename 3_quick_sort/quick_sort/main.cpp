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

void partitioning(int array[], int length)
{
    if(length<=1)
    {
        return;
    }
    else
    {
        int pivot_item=array[0];

        int tmp=0;
        for(int i=1; i<length; i++)
        {
            if(array[i]>=pivot_item)
            {
                tmp++;
            }
        }

        int *lower_array=new int[length-tmp-1];
        int *grater_array=new int[tmp];

        int i=0, j=0;
        for(int k=1; k<length; k++)
        {
            if(array[k]>pivot_item)
            {
                grater_array[i++]=array[k];
            }
            else
            {
                lower_array[j++]=array[k];
            }
        }

        partitioning(lower_array, length-tmp-1);
        partitioning(grater_array, tmp);

        for(int i=0; i<(length-tmp-1); i++)
        {
            array[i]=lower_array[i];
        }

        array[length-tmp-1]=pivot_item;

        for(int i=length-tmp; i<length; i++)
        {
            array[i]=grater_array[i-(length-tmp)];
        }




    }
}

void quick_sort(int tmp_array[], int length)
{
    partitioning(tmp_array, length);
}

int main(void)
{
    int tmp_array[10]={0, 4, 2, 1, 3, 5, 9, 6, 7, 8};

    print_array(tmp_array, 10);

    quick_sort(tmp_array, 10);

    print_array(tmp_array, 10);


    return 0;
}
