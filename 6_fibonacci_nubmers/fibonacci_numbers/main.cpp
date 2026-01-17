#include <iostream>
using namespace std;
#define lli long long int

lli fibonacci_func(lli n)
{
    lli a1=0;
    lli a2=1;
    if(n==0)
    {
        return a1;
    }
    else if(n==1)
    {
        return a2;
    }
    else
    {
        lli i=2;
        while(i<=n)
        {
            lli tmp=a1+a2;
            a1=a2;
            a2=tmp;
            i++;
        }
        return  a2;
    }
}
int main(void)
{
    for(int i=0; i<10; i++)
    {
        cout<<i<<"\t"<<fibonacci_func(i)<<"\n";
    }


    return 0;
}
