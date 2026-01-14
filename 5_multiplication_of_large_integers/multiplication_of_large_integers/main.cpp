#include <iostream>
using namespace std;
#define lli  long long int

class long_integer
{
private:
    int length;
    int pow;
    int* v;

public:
    long_integer()
    {
        v=NULL;
        length=0;
        pow=0;
    }

    void set_length(int length_in)
    {
        length=length_in;
    }

    void set_pow(int pow_in)
    {
        pow=pow_in;
    }

    void set_v(int* v_in)
    {
        v=v_in;
    }

    void set(int* v_in, int length_in, int pow_in)
    {
        length=length_in;
        pow=pow_in;
        v=v_in;
    }

    int get_length()
    {
        return length;
    }

    int* get_v()
    {
        return v;
    }

    int get_pow()
    {
        return pow;
    }
};

long_integer* mul(long_integer* v1, long_integer* v2)
{
    int n1=v1->get_length();
    int* v1_arr=v1->get_v();
    int n2=v2->get_length();
    int* v2_arr=v2->get_v();

    int n=n1+n2;
    int* output_arr=new int[n];

    for(int i=0; i<n; i++)
    {
        output_arr[i]=0;
    }

    int value_c=1;
    for(int i=n1-1; i>=0; i--)
    {
        for(int j=0; j<n2; j++)
        {
            output_arr[n1+j]+=v2_arr[i]*v1_arr[j]*value_c;
        }

        for(int j=n-1; j>0; j--)
        {
            if(output_arr[j]>10)
            {
                output_arr[j-1]+=output_arr[j]/10;
                output_arr[j]=output_arr[j]%10;
            }
        }

        value_c*=10;

    }

    long_integer* output=new long_integer;
    output->set_length(n);
    output->set_v(output_arr);
    output->set_pow(v1->get_pow()+v2->get_pow());

    return output;
}

//not completed;
long_integer* sum(long_integer* v1, long_integer* v2)
{
    long_integer* output=new long_integer;

    int n1=v1->get_length()+v1->get_pow();
    int n2=v2->get_length()+v2->get_pow();
    int n=max(n1, n2);

    int* tmp_array=v1->get_v();
    int* tmp_v1=new int[n];
    int* tmp_v2=new int[n];
    int* tmp_v3=new int[n+1];
    for(int i=0; i<n; i++)
    {
        tmp_v1[i]=0;
        tmp_v2[i]=0;
        tmp_v3[i]=0;
    }
    for(int i=(n-n1); i<v1->get_length()+(n-n1); i++)
    {
        tmp_v1[i]=tmp_array[i-(n-n1)];
    }
    tmp_array=v2->get_v();
    for(int i=(n-n2); i<v2->get_length()+(n-n2); i++)
    {
        tmp_v2[i]=tmp_array[i-(n-n2)];
    }

    for(int i=0; i<n; i++)
    {
        tmp_v3[i+1]=tmp_v1[i]+tmp_v2[i];
    }

    for(int i=n; i>0; i--)
    {
        if(tmp_v3[i]>10)
        {
            tmp_v3[i-1]+=tmp_v3[i]/10;
            tmp_v3[i]=tmp_v3[i]%10;
        }
    }


    int tmp_pow=0;

}

long_integer* lim(long_integer* v1, long_integer* v2)    //large integer multiplication
{
    long_integer* output=new long_integer;

    if(v1->get_length()==0 || v2->get_length()==0)
    {
        return output;
    }

    int n1=v1->get_length();
    int n2=v2->get_length();
    int n=max(n1, n2);

    if(n<=2)
    {
        output=mul(v1, v2);
        return output;
    }
    else
    {
        int m=n/2;

        long_integer* x=new long_integer;
        x->set(v1->get_v(),(n-m) , m);

        long_integer* y=new long_integer;
        y->set(v1->get_v()+(n-m), m, 0);

        long_integer* w=new long_integer;
        w->set(v2->get_v(), (n-m), m);

        long_integer* z=new long_integer;
        z->set(v2->get_v()+(n-m), m, 0);

        long_integer* tmp_output1=NULL;
        long_integer* tmp_output2=NULL;
        long_integer* tmp_output3=NULL;
        long_integer* tmp_output4=NULL;
        tmp_output1=lim(x, w);
        tmp_output2=lim(x, z);
        tmp_output3=lim(y, w);
        tmp_output4=lim(y, z);

        output=sum(tmp_output1, tmp_output2);
        output=sum(output, tmp_output3);
        output=sum(output, tmp_output4);

        return output;

    }

}


int main(void)
{
    long_integer* v1=new long_integer;
    int* v1_arr=new int[5];
    for(int i=1; i<6; i++)
    {
        v1_arr[i-1]=i;
    }
    cout<<"v1_array: ";
    for(int i=0; i<5; i++)
    {
        cout<<v1_arr[i];
    }
    cout<<endl;
    v1->set_length(5);
    v1->set_v(v1_arr);

    long_integer* v2=new long_integer;
    int* v2_arr=new int[5];
    for(int i=5, j=0; i>0; i--, j++)
    {
        v2_arr[j]=i;
    }
    cout<<"v2_array: ";
    for(int i=0; i<5; i++)
    {
        cout<<v2_arr[i];
    }
    cout<<endl;
    v2->set_length(5);
    v2->set_v(v2_arr);

    long_integer* v3=mul(v1, v2);
    int* v3_arr=v3->get_v();
    for(int i=0; i<v3->get_length(); i++)
    {
        cout<<v3_arr[i];
    }
    cout<<endl;



    return 0;
}


