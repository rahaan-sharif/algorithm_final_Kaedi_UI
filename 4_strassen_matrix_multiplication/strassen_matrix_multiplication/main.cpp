#include <iostream>
using namespace std;

void print_array(int* array, int length1, int length2=0)
{
    if(length2==0)
    {
        cout<<"--------\n";
        for(int i=0; i<length1-1; i++)
        {
            cout<<array[i]<<", ";
        }
        cout<<array[length1-1]<<endl;

        cout<<"--------\n";
    }
    else
    {
        cout<<"--------\n";
        for(int i=0; i<length1; i++)
        {
            for(int j=0; j<length2; j++)
            {
                cout<<array[i*length2+j]<<"\t";
            }
            cout<<endl;
        }

        cout<<"\n--------\n";
    }
}

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
                new_array[i*length+j]=array[i*length2+j];
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

    int* array2=zero_padding(array, length1, length2, tmp_length2);



}

int main(void)
{

    int* array=new int[3*5];
    for(int i=0; i<15; i++)
    {
        array[i]=i;
        cout<<array[i]<<", ";
    }
    cout<<endl<<endl;


    print_array(array, 3, 5);

    int tmp1=0;
    cout<<"enter a number: ";
    cin>>tmp1;

    int tmp=get_near_upper_power2(5);
    array=zero_padding(array, 3, 5, tmp);

    print_array(array, tmp, tmp);




    return 0;
}
