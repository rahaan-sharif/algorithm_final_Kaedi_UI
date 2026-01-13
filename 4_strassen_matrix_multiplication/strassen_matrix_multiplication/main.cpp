#include <iostream>
#include <math.h>
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

int* mat_sub(int* array1, int* array2, int length)
{
    int* array3=new int[length*length];
    for(int i=0; i<length*length; i++)
    {
        array3[i]=-1;
    }

    for(int i=0; i<length*length; i++)
    {
        array3[i]=array1[i]-array2[i];
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
    sq_matrix *parts=new sq_matrix[4];

    //first part:
    parts[(0*2)+0].set_length(length/2);
    int* tmp_11=new int[(length*length)/4];
    for(int i=0; i<length/2; i++)
    {
        for(int j=0; j<length/2; j++)
        {
            tmp_11[(i*(length/2)+j)]=a1[(i*length)+j];
        }
    }
    parts[(0*2)+0].set_matrix(tmp_11);

    //second part:
    parts[(0*2)+1].set_length(length/2);
    int* tmp_12=new int[(length*length)/4];
    for(int i=0; i<length/2; i++)
    {
        for(int j=0; j<length/2; j++)
        {
            tmp_12[(i*length/2)+j]=a1[(i*length)+j+(length/2)];
        }
    }
    parts[(0*2)+1].set_matrix(tmp_12);

    //third part:
    parts[(1*2)+0].set_length(length/2);
    int* tmp_21=new int[(length*length)/4];
    for(int i=0; i<length/2; i++)
    {
        for(int j=0; j<length/2; j++)
        {
            tmp_21[(i*length/2)+j]=a1[((i+length/2)*length)+j];
        }
    }
    parts[(1*2)+0].set_matrix(tmp_21);

    //4'th part:
    parts[(1*2)+1].set_length(length/2);
    int* tmp_22=new int[(length*length)/4];
    for(int i=0; i<length/2; i++)
    {
        for(int j=0; j<length/2; j++)
        {
            tmp_22[(i*length/2)+j]=a1[((i+(length/2))*length)+j+(length/2)];
        }
    }
    parts[(1*2)+1].set_matrix(tmp_22);


    return parts;
}

int* merge_arrays(int** p_arr, int length)
{
    int* output=new int[length];
    for(int i=0; i<length; i++)
    {
        output[i]=-1;
    }

    //part 0:
    for(int i=0; i<(length/2); i++)
    {
        for(int j=0; j<(length/2); j++)
        {
            output[(i*length)+j]=p_arr[0][(i*(length/2))+j];
        }
    }

    //part 1:
    for(int i=0; i<(length/2); i++)
    {
        for(int j=0; j<(length/2); j++)
        {
            output[(i*length)+j+(length/2)]=p_arr[1][(i*(length/2))+j];
        }
    }

    //part 2:
    for(int i=0; i<(length/2); i++)
    {
        for(int j=0; j<(length/2); j++)
        {
            output[(i+(length/2))*length+j]=p_arr[2][(i*(length/2))+j];
        }
    }

    //part 3:
    for(int i=0; i<(length/2); i++)
    {
        for(int j=0; j<(length/2); j++)
        {
            output[((i+(length/2))*length)+j+(length/2)]=p_arr[3][(i*(length/2))+j];
        }
    }

    return output;
}

sq_matrix* strassen_matrix_multiplication(
        int* a, int* b, int length)  //a and b are the matrices.
{
    if(length!=2)
    {
        cout<<"first array:\n";
        print_array(a, length);

        cout<<"second array:\n";
        print_array(b, length);
    }


    if(length<2)
    {
        cout<<"error! length is smaller than 2.\n";
        return NULL;
    }
    else if(length==2)
    {

        int *output_array=new int[2*2];
        for(int i=0; i<4; i++)
        {
            output_array[i]=-1;
        }

        int tmp_int_1=-1;
        int tmp_int_2=-1;
        int m[8]={0};


        //m1:
        tmp_int_1=a[(0*2)+0] + a[(1*2)+1];
        tmp_int_2=b[(0*2)+0] + b[(1*2)+1];
        m[1]=tmp_int_1  *  tmp_int_2;


        //m2:
        tmp_int_1=a[(1*2)+0] + a[(1*2)+1];
        tmp_int_2=b[(0*2)+0];
        m[2]=tmp_int_1  *  tmp_int_2;

        //m3:
        tmp_int_1=a[(0*2)+0];
        tmp_int_2=b[(0*2)+1] - b[(1*2)+1];
        m[3]=tmp_int_1  *  tmp_int_2;

        //m4:
        tmp_int_1=a[(1*2)+1];
        tmp_int_2=b[(1*2)+0] - b[(0*2)+0];
        m[4]=tmp_int_1  *  tmp_int_2;

        //m5:
        tmp_int_1=a[(0*2)+0] + a[(0*2)+1];
        tmp_int_2=b[(1*2)+1];
        m[5]=tmp_int_1  *  tmp_int_2;

        //m6:
        tmp_int_1=a[(1*2)+0] - a[(0*2)+0];
        tmp_int_2=b[(0*2)+0] + b[(0*2)+1];
        m[6]=tmp_int_1  *  tmp_int_2;

        //m7:
        tmp_int_1=a[(0*2)+1] - a[(1*2)+1];
        tmp_int_2=b[(1*2)+0] + b[(1*2)+1];
        m[7]=tmp_int_1  *  tmp_int_2;


        output_array[(0*2)+0] = m[1]+m[4]-m[5]+m[7];
        output_array[(0*2)+1] = m[3]+m[5];
        output_array[(1*2)+0] = m[2]+m[4];
        output_array[(1*2)+1] = m[1]+m[3]-m[2]+m[6];
        sq_matrix* output=new sq_matrix;

        output->set_matrix(output_array);
        output->set_length(4);


        return output;
    }

    else
    {

        sq_matrix* tmp_a=partitioning(a, length);
        sq_matrix* tmp_b=partitioning(b, length);

        int* tmp_int_1=NULL;
        int* tmp_int_2=NULL;

        int** m=new int*[8];

        //m1:
        tmp_int_1 = mat_adding(tmp_a[(0*2)+0].get_matrix(), tmp_a[(1*2)+1].get_matrix(), length/2);
        tmp_int_2 = mat_adding(tmp_b[(0*2)+0].get_matrix(), tmp_b[(1*2)+1].get_matrix(), length/2);
        m[1]=strassen_matrix_multiplication(tmp_int_1, tmp_int_2, length/2)->get_matrix();


        //m2:
        tmp_int_1 = mat_adding(tmp_a[(1*2)+0].get_matrix(), tmp_a[(1*2)+1].get_matrix(), length/2);
        tmp_int_2 = tmp_b[(0*2)+0].get_matrix();
        m[2]=strassen_matrix_multiplication(tmp_int_1, tmp_int_2, length/2)->get_matrix();


        //m3:
        tmp_int_1 = tmp_a[(0*2)+0].get_matrix();
        tmp_int_2 = mat_sub(tmp_b[(0*2)+1].get_matrix(), tmp_b[(1*2)+1].get_matrix(), length/2);
        m[3]=strassen_matrix_multiplication(tmp_int_1, tmp_int_2, length/2)->get_matrix();


        //m4:
        tmp_int_1 = tmp_a[(1*2)+1].get_matrix();
        tmp_int_2 = mat_sub(tmp_b[(1*2)+0].get_matrix(), tmp_b[(0*2)+0].get_matrix(), length/2);
        m[4]=strassen_matrix_multiplication(tmp_int_1, tmp_int_2, length/2)->get_matrix();


        //m5:
        tmp_int_1 = mat_adding(tmp_a[(0*2)+0].get_matrix(), tmp_a[(0*2)+1].get_matrix(), length/2);
        tmp_int_2 = tmp_b[(1*2)+1].get_matrix();
        m[5]=strassen_matrix_multiplication(tmp_int_1, tmp_int_2, length/2)->get_matrix();


        //m6:
        tmp_int_1 = mat_sub(tmp_a[(1*2)+0].get_matrix(), tmp_a[(0*2)+0].get_matrix(), length/2);
        tmp_int_2 = mat_adding(tmp_b[(0*2)+0].get_matrix(), tmp_b[(0*2)+1].get_matrix(), length/2);
        m[6]=strassen_matrix_multiplication(tmp_int_1, tmp_int_2, length/2)->get_matrix();


        //m7:
        tmp_int_1 = mat_sub(tmp_a[(0*2)+1].get_matrix(), tmp_a[(1*2)+1].get_matrix(), length/2);
        tmp_int_2 = mat_adding(tmp_b[(1*2)+0].get_matrix(), tmp_b[(1*2)+1].get_matrix(), length/2);
        m[7]=strassen_matrix_multiplication(tmp_int_1, tmp_int_2, length/2)->get_matrix();



        int* tmp_output=NULL;
        int** output_array= new int*[4];
        //I have to define an array to merge this array in the end before returning.

        tmp_output =mat_adding(m[1], m[4], length/2);
        tmp_output =mat_sub(tmp_output, m[5], length/2);
        output_array[(0*2)+0] =mat_adding(tmp_output, m[7], length/2);


        output_array[(0*2)+1] =mat_adding(m[3], m[5], length/2);


        output_array[(1*2)+0] =mat_adding(m[2], m[4], length/2);


        tmp_output =mat_adding(m[1], m[3], length/2);
        tmp_output =mat_sub(tmp_output, m[2], length/2);
        output_array[(1*2)+1] =mat_adding(tmp_output, m[6], length/2);

        sq_matrix* output=new sq_matrix;
        output->set_length(length);
        output->set_matrix(merge_arrays(output_array, length));

        return output;
    }

}

int main(void)
{
    int* array1=new int[4*4];
    array1[0]=1;
    array1[1]=2;
    array1[2]=3;
    array1[3]=4;
    array1[4]=5;
    array1[5]=6;
    array1[6]=7;
    array1[7]=8;
    array1[8]=9;
    array1[9]=1;
    array1[10]=2;
    array1[11]=3;
    array1[12]=4;
    array1[13]=5;
    array1[14]=6;
    array1[15]=7;

    int* array2=new int[4*4];
    array2[0]=8;
    array2[1]=9;
    array2[2]=1;
    array2[3]=2;
    array2[4]=3;
    array2[5]=4;
    array2[6]=5;
    array2[7]=6;
    array2[8]=7;
    array2[9]=8;
    array2[10]=9;
    array2[11]=1;
    array2[12]=2;
    array2[13]=3;
    array2[14]=4;
    array2[15]=5;


    sq_matrix* tmp_output=preparing_matrices_for_mul(array1, 4, 4,
                                                     array2, 4, 4);

    sq_matrix* strassen_output=strassen_matrix_multiplication(
                                   tmp_output[0].get_matrix(),
                                   tmp_output[1].get_matrix(), tmp_output[1].get_length());


    cout<<"strassen output:\n";
    print_array(strassen_output->get_matrix(), 4);



    return 0;
}
