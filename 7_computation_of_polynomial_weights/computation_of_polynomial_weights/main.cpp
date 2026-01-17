#include <iostream>
using namespace std;

void reset_array(int*& arr, int n, int pi=INT16_MIN)
{
    for(int i=0; i<n; i++)
    {
        arr[i]=pi;
    }
}

void coppy_array(int*& arr1, int*& arr2, int length)
{
    for(int i=0; i<=length; i++)
    {
        arr1[i]=arr2[i];
    }
}

void show_array(int* arr, int n)
{
    for(int i=0; i<=n; i++)
    {
        cout<<arr[i]<<"\t";
    }
    cout<<endl<<endl;
}

void cpw(int n)  //computation of polynomial weights
{
    int* arr=new int[n+1];
    reset_array(arr, n+1, -1);
    int* tmp_arr=new int[n+1];
    reset_array(tmp_arr, n+1);

    for(int k=0; k<=n; k++)
    {
        tmp_arr[0]=1;
        tmp_arr[k]=1;

        for(int j=1; j<k; j++)
        {
            tmp_arr[j]=arr[j]+arr[j-1];
        }

        show_array(tmp_arr, k);

        coppy_array(arr, tmp_arr, k);
    }

    cout<<"\n\n\n============\n";
    show_array(arr, n);

}

int main(void)
{

    cpw(26);

    return 0;
}
