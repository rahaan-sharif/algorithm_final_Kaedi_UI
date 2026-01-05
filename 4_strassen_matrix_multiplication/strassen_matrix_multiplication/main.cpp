#include <iostream>
using namespace std;


int get_near_upper_power2(int tmp_input)
{
    if(tmp_input<=0)
    {
        return 0;
    }
    else
    {
        int tmp_output=1;
        while(tmp_output<tmp_input)
        {
            tmp_output*=2;
        }

        return tmp_output;
    }
}

int* zero_padding(int array[], int length1, int length2, int length)
{
    int* new_array=new int[length*length];

    for(int i=0; i<length; i++)
    {
        for(int j=0; j<length; j++)
        {
            if(i<length1 && j<length2)
            {
                new_array[i*length+j]=array[i*length1+j];
            }
            else
            {
                new_array[i*length+j]=0;
            }
        }
    }

    return new_array;
}

int* strassen_matrix_multiplication(int* array, int length1, int length2)
{
    int tmp_length=-1;
    if(length1>length2)
    {
        tmp_length=length1;
    }
    else
    {
        tmp_length=length2;
    }

    int tmp_length2=get_near_upper_power2(tmp_length);


}

int main(void)
{



    return 0;
}
