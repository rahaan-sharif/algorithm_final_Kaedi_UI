#include <iostream>
using namespace std;


class sq_matrix{

private:
    int length;
    int* matrix;

public:
    sq_matrix()
    {
        length=-1;
        matrix=NULL;
    }

    void set_length(int length_in)
    {
        length=length_in;
    }

    void set_matrix(int* matrix_in)
    {
        matrix=matrix_in;
    }

    int get_length()
    {
        return length;
    }

    int* get_matrix()
    {
        return matrix;
    }
};

void print_array(int* array, int length1, int length2=0)
{
    if(length2==0)
    {
        cout<<"--------\n";
        for(int i=0; i<length1; i++)
        {
            for(int j=0; j<length1; j++)
            {
                cout<<array[i*length1+j]<<"\t";
            }
            cout<<endl;
        }

        cout<<"\n--------\n";
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

int* mat_adding(int* array1, int* array2, int length)
{
    int* array3=new int[length*length];
    for(int i=0; i<length*length; i++)
    {
        array3[i]=-1;
    }

    for(int i=0; i<length*length; i++)
    {
        array3[i]=array1[i]+array2[i];
    }

    return array3;

}

sq_matrix* preparing_matrices_for_mul(
        int* array1, int length11, int length12,
        int*array2, int length21, int length22)
{

    int tmp_length1=-1, tmp_length2=-1, tmp_length=-1;

    if(length11>length12)
    {
        tmp_length1=length11;
    }
    else
    {
        tmp_length1=length12;
    }

    if(length21>length22)
    {
        tmp_length2=length21;
    }
    else
    {
        tmp_length2=length22;
    }

    if(tmp_length1>tmp_length2)
    {
        tmp_length=tmp_length1;
    }
    else
    {
        tmp_length=tmp_length2;
    }

    tmp_length=get_near_upper_power2(tmp_length);

    array1=zero_padding(array1, length11, length12, tmp_length);
    array2=zero_padding(array2, length21, length22, tmp_length);


    sq_matrix* tmp_sq=new sq_matrix[2];
    tmp_sq[0].set_matrix(array1);
    tmp_sq[0].set_length(tmp_length);
    tmp_sq[1].set_matrix(array2);
    tmp_sq[1].set_length(tmp_length);

    return tmp_sq;
}

sq_matrix* partitioning(int* a1, int length) //a1 is array1
{
    cout<<"partitioning ... \n";
    sq_matrix *parts=new sq_matrix[9];
    cout<<"partitioning second part... \n";

    //first part:
    parts[(1*3)+1].set_length(length/2);
    int* tmp_11=new int[(length*length)/4];
    for(int i=0; i<length/2; i++)
    {
        for(int j=0; j<length/2; j++)
        {
            tmp_11[(i*(length/2)+j)]=a1[(i*length)+j];
        }
    }
    parts[(1*3)+1].set_matrix(tmp_11);

    //second part:
    parts[(1*3)+2].set_length(length/2);
    int* tmp_12=new int[(length*length)/4];
    for(int i=0; i<length/2; i++)
    {
        for(int j=0; j<length/2; j++)
        {
            tmp_12[(i*length/2)+j]=a1[(i*length)+j+(length/2)];
        }
    }
    parts[(1*3)+2].set_matrix(tmp_12);

    //third part:
    parts[(2*3)+1].set_length(length/2);
    int* tmp_21=new int[(length*length)/4];
    for(int i=0; i<length/2; i++)
    {
        for(int j=0; j<length/2; j++)
        {
            tmp_21[(i*length/2)+j]=a1[((i+length/2)*length)+j];
        }
    }
    parts[(2*3)+1].set_matrix(tmp_21);

    //4'th part:
    parts[(2*3)+2].set_length(length/2);
    int* tmp_22=new int[(length*length)/4];
    for(int i=0; i<length/2; i++)
    {
        for(int j=0; j<length/2; j++)
        {
            tmp_22[(i*length/2)+j]=a1[((i+(length/2))*length)+j+(length/2)];
        }
    }
    parts[(2*3)+2].set_matrix(tmp_22);


    return parts;
}

sq_matrix* strassen_matrix_multiplication(
        int* a1, int* a2, int length)
{
    if(length<2)
    {
        cout<<"error! length is smaller than 2.\n";
        return NULL;
    }

    else if(length==2)
    {}

    else
    {
        sq_matrix* tmp_a1=partitioning(a1, length);
        sq_matrix* tmp_a2=partitioning(a2, length);
    }

}

int main(void)
{

    int* array1=new int[5*3];  //it should be 3*5 or other random dimensions.
    for(int i=0; i<15; i++)
    {
        array1[i]=i;
    }

    int* array2=new int[7*4];   //it should be 4*6 or other random dimensions.
    for(int i=0; i<21; i++)
    {
        array2[i]=(i*2-3)>>2;
    }
    cout<<"befor function..."<<endl<<endl;


    sq_matrix* tmp_output=preparing_matrices_for_mul(array1, 5, 3,
                                                     array2, 7, 4);
    //sq_matrix* strassen_output=strassen_matrix_multiplication(
    //                               tmp_output[0].get_matrix(),
    //                               tmp_output[1].get_matrix(), tmp_output[1].get_length());
    //

    print_array(tmp_output[0].get_matrix(), tmp_output[0].get_length());
    cout<<"**********************************\n";
    cout<<"\n";
    sq_matrix* tmp_output_2=partitioning(tmp_output[0].get_matrix(), tmp_output[0].get_length());
    for(int i=0; i<9; i++)
    {
        cout<<"here"<<endl;
        print_array(tmp_output_2[i].get_matrix(), tmp_output_2[i].get_length());
        cout<<"\n\n--------*---------*------\n\n";
    }








    return 0;
}
