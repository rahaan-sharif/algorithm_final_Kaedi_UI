#include <iostream>
using namespace std;

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

    void set(int* v_in, int length_in, int pow_in=0)
    {
        length=length_in;
        pow=pow_in;
        v=v_in;

        int j=0;
        for(int i=0; i<length; i++)
        {
            if(v[i]==0)
            {
                j++;
            }
            else
            {
                break;
            }
        }
        length-=j;
        v+=j;

        if(length<=0)
        {
            length=1;
            pow=0;
            v=new int[1];
            v[0]=0;
        }
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

    void show()
    {
        for(int i=0; i<length; i++)
        {
            cout<<v[i];
        }
        cout<<" ";
        for(int i=0; i<pow; i++)
        {
            cout<<0;
        }
    }

    void zero_padding(int new_length)
    {
        if(new_length<=length)
        {
            return;
        }
        int* tmp_v=new int[new_length];
        for(int i=0; i<new_length; i++)
        {
            tmp_v[i]=0;
        }

        for(int i=0; i<length; i++)
        {
            tmp_v[i+(new_length - length)]=v[i];
        }

        v=tmp_v;
        length=new_length;
    }
};

void show_array(int* arr, int length)
{
    for(int i=0; i<length; i++)
    {
        cout<<arr[i];
    }
    cout<<endl;
}

long_integer* mul(long_integer* v1, long_integer* v2)
{
    int n1=v1->get_length();
    int* v1_arr=v1->get_v();

    int n2=v2->get_length();
    int* v2_arr=v2->get_v();

    int n=n1+n2;

    long_integer* output=new long_integer;

    int* output_arr=new int[n];

    if((v1->get_length()==1 && v1->get_v()[0]==0) ||
       (v2->get_length()==1 && v2->get_v()[0]==0))
    {
        int* tmp_v=new int[1];
        tmp_v[0]=0;
        int tmp_length=1;
        output->set(tmp_v, tmp_length);

        return output;
    }

    for(int i=0; i<n; i++)
    {
        output_arr[i]=0;
    }

    int value_c=1;
    for(int i=n2-1; i>=0; i--)
    {
        for(int j=0; j<n1; j++)
        {
            output_arr[n2+j]+=v2_arr[i]*v1_arr[j]*value_c;
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

    int output_length=n;

    int j=0;
    for(int i=0; i<n; i++)
    {
        if(output_arr[i]==0)
        {
            output_length--;
            j++;

        }
        else
        {
            break;
        }
    }
    output_arr+=j;

    int output_pow=v1->get_pow()+v2->get_pow();

    output->set(output_arr, output_length, output_pow);

    return output;
}

long_integer* sum(long_integer* v1, long_integer* v2)
{
    long_integer* output=new long_integer;

    int pow1=v1->get_pow();
    int pow2=v2->get_pow();
    int output_pow=min(pow1, pow2);
    int n1=v1->get_length() + v1->get_pow() - output_pow;
    int n2=v2->get_length() + v2->get_pow() - output_pow;
    int output_length=max(n1, n2)+1;

    int* tmp_v1=new int[output_length-1];
    int* tmp_v2=new int[output_length-1];
    int* tmp_v3=new int[output_length];
    for(int i=0; i<output_length-1; i++)
    {
        tmp_v1[i]=0;
        tmp_v2[i]=0;
        tmp_v3[i]=0;
    }
    tmp_v3[output_length-1]=0;

    int* tmp_array=v1->get_v();

    int j=output_length-2-(v1->get_pow()-output_pow);
    for(int i=v1->get_length()-1; i>=0; i--)
    {
        tmp_v1[j]=tmp_array[i];
        j--;
    }

    tmp_array=v2->get_v();

    j=output_length-2-(v2->get_pow()-output_pow);
    for(int i=v2->get_length()-1; i>=0; i--)
    {
        tmp_v2[j]=tmp_array[i];
        j--;
    }

    for(int i=0; i<output_length-1; i++)
    {
        tmp_v3[i+1]=tmp_v1[i]+tmp_v2[i];
    }

    for(int i=output_length-1; i>0; i--)
    {
        if(tmp_v3[i]>9)
        {
            tmp_v3[i-1]+=tmp_v3[i]/10;
            tmp_v3[i]=tmp_v3[i]%10;
        }
    }

    int tmp_counter=0;
    for(int i=output_length-1; i>=0; i--)
    {
        if(tmp_v3[i]==0)
        {
            tmp_counter++;
        }
        else
        {
            break;
        }
    }

    output_length-=tmp_counter;
    output_pow   +=tmp_counter;

    if(tmp_v3[0]==0)
    {
        tmp_v3++;
        output_length--;
    }

    output->set(tmp_v3, output_length, output_pow);

    return output;
}

long_integer* lim(long_integer* v1, long_integer* v2)    //large integer multiplication
{
    long_integer* output=new long_integer;

    if(v1->get_length()==0 || v2->get_length()==0)
    {
        cout<<"error! one input is equal with zero.\n";
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

        if(n==n1)
        {
            v2->zero_padding(n);
        }
        else
        {
            v1->zero_padding(n);
        }

        long_integer* x=new long_integer;
        long_integer* y=new long_integer;
        long_integer* w=new long_integer;
        long_integer* z=new long_integer;
        x->set(v1->get_v(),(v1->get_length()-m) , m+v1->get_pow());
        y->set(v1->get_v()+(v1->get_length()-m), m, 0+v1->get_pow());
        w->set(v2->get_v(), (v2->get_length()-m), m+v2->get_pow());
        z->set(v2->get_v()+(v2->get_length()-m), m, 0+v2->get_pow());

        long_integer* tmp_output1=NULL;
        long_integer* tmp_output2=NULL;
        long_integer* tmp_output3=NULL;
        long_integer* tmp_output4=NULL;
        tmp_output1=lim(x, w);
        tmp_output2=lim(x, z);
        tmp_output3=lim(y, w);
        tmp_output4=lim(y, z);

        long_integer* output1=sum(tmp_output1, tmp_output2);
        long_integer* output2=output=sum(output1, tmp_output3);
        output=sum(output2, tmp_output4);

        return output;
    }
}

int main(void)
{

    int tmp_length1=7;
    int tmp_length2=9;

    long_integer* v1=new long_integer;
    int* v1_arr=new int[tmp_length1];
    for(int i=0; i<tmp_length1; i++)
    {
        v1_arr[i]=(i*2-3/4*6+1)%10;
    }
    v1->set(v1_arr, tmp_length1);

    long_integer* v2=new long_integer;
    int* v2_arr=new int[tmp_length2];
    for(int i=0; i<tmp_length2; i++)
    {
        v2_arr[i]=(i+1)%10;
    }
    v2->set(v2_arr, tmp_length2);

    long_integer* v3=lim(v1, v2);

    v1->show();
    cout<<" * ";
    v2->show();
    cout<<" = ";
    v3->show();
    cout<<endl<<endl;



    return 0;
}
