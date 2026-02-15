#include <iostream>
#include <limits>
using namespace std;
#define mat_count 6
#define max_int  numeric_limits<int>::max()

//checked.
class d
{
private:
    int l1;
    int l2;
    int* array;

public:
    //checked.
    d(int l1_in=-1, int l2_in=-1, int* array_in=NULL)
    {
        l1=l1_in;
        l2=l2_in;
        array=array_in;
    }

    //checked.
    d* mul(d*& mat1, d*& mat2)
    {
        if(mat1->l2!=mat2->l1)
        {
            cout<<"error! matrices can't be multiplied to each other.\n";
            return NULL;
        }
        else
        {
            int ll1=mat1->l1;
            int ll2=mat1->l2;
            int ll3=mat2->l2;

            int* output_arr=new int[ll1*ll3];
            for(int i=0; i<ll1*ll3; i++)
            {
                output_arr[i]=0;
            }

            for(int i=0; i<ll1; i++)
            {
                for(int j=0; j<ll2; j++)
                {
                    for(int k=0; k<ll3; k++)
                    {
                        output_arr[(i*ll3)+k] += mat1->array[(i*ll2)+j] * mat2->array[(j*ll3)+k];
                    }
                }
            }


            d* output=new d(ll1, ll3, output_arr);
            return output;
        }
    }

    //checked.
    void show(d* start)
    {
        cout<<"show d:"<<endl;
        if(start==NULL)
        {
            cout<<"\t NULL pointer"<<endl;
            return;
        }

        cout<<"\tl1: "<<start->l1<<endl;
        cout<<"\tl2: "<<start->l2<<endl;

        for(int i=0; i<start->l1; i++)
        {
            for(int j=0; j<start->l2; j++)
            {
                cout<<start->array[(i*start->l2)+j]<<"\t";
            }
            cout<<endl;
        }
        cout<<endl<<endl;
    }

    //checked.
    int get_l1(d* start)
    {
        return start->l1;
    }

    //checked.
    int get_l2(d* start)
    {
        return start->l2;
    }
};

//checked.
class bst              //binary search tree
{
private:
    int multiplications;   //number of multiplications till here.
    int l1, l2;
    bst* left, *right;

public:
    bst(int l1_in, int l2_in)
    {
        l1=l1_in;
        l2=l2_in;
        multiplications=max_int;
        right=NULL;
        left=NULL;
    }

    int get_multiplications(bst*& start)
    {
        if(start==NULL)
        {
            return max_int;
        }
        else
        {
            return start->multiplications;
        }
    }

    void set(bst*& start1, bst*& start2, bst*& start3)
    {
        start1=new bst(-1, -1);

        start1->left=start2;
        start1->right=start3;

        start1->l1=start2->l1;
        start1->l2=start3->l2;

        int tmp_int=0;
        if(start2->multiplications!=max_int)
        {
            tmp_int+=start2->multiplications;
        }
        if(start3->multiplications!=max_int)
        {
            tmp_int+=start3->multiplications;
        }
        tmp_int+=start2->l1 * start2->l2 * start3->l2;
        start1->multiplications=tmp_int;

    }

    void show(bst*& start)
    {
        if(start==NULL)
        {
            return;
        }
        else
        {
            if(start->right==NULL  &&  start->left==NULL)
            {
                cout<<" ["<<start->l1<<","<<start->l2<<"] ";
                return;
            }
            else
            {
                cout<<"( ";
                start->left->show(start->left);
                start->right->show(start->right);
                cout<<") ";

                return;
            }
        }
    }

};



class element
{
private:
    d* matrix;
    bst* bst_path;

public:
    element()
    {
        bst_path=new bst(-1, -1);
        matrix  =new d(-1, -1);
    }

    element(d*& mat_in)
    {
        matrix=mat_in;
        int l1=mat_in->get_l1(mat_in);
        int l2=mat_in->get_l2(mat_in);
        bst_path=new bst(l1, l2);
    }

    void set_element(element*& start1, element*& start2, element*& start3)
    {
        start1=new element();

        d* tmp_d=new d;
        tmp_d=tmp_d->mul(start2->matrix, start3->matrix);

        bst* tmp_path=new bst(-1, -1);
        tmp_path->set(tmp_path, start2->bst_path, start3->bst_path);

        start1->matrix=tmp_d;
        start1->bst_path=tmp_path;
    }

    int get_multiplications(element*& start)
    {
        return start->bst_path->get_multiplications(start->bst_path);
    }

    void get_relation(element**& start, int count,
                      int i, int j, int k)
    {
        //cout<<"get_relation function:\n";

        int index[3]={0};
        index[0]=(i*count)+k;
        index[1]=((k+1)*count)+j;
        index[2]=(i*count)+j;

        int tmp_int=0;

        if(start[index[0]]->get_multiplications(start[index[0]])==max_int ||
           start[index[1]]->get_multiplications(start[index[1]])==max_int)
        {
            if(start[index[0]]->matrix!=NULL &&
               start[index[1]]->matrix!=NULL)
            {
                cout<<"\t\ti: "<<i<<"  k: "<<k<<"       k+1: "<<k+1<<"  j: "<<j<<endl;
                int tmp_int1=-1, tmp_int2=-1;
                tmp_int1=start[index[0]]->get_multiplications(start[index[0]]);
                tmp_int2=start[index[1]]->get_multiplications(start[index[1]]);

                if(tmp_int1==max_int)
                {
                    tmp_int1=0;
                }
                if(tmp_int2==max_int)
                {
                    tmp_int2=0;
                }

                int tmp_int11=start[index[0]]->matrix->get_l1(start[index[0]]->matrix) ;
                int tmp_int22=start[index[0]]->matrix->get_l2(start[index[0]]->matrix) ;
                int tmp_int33=start[index[1]]->matrix->get_l2(start[index[1]]->matrix) ;

                tmp_int=(tmp_int11*tmp_int22*tmp_int33);
                tmp_int+=tmp_int1+tmp_int2;
            }
            else
            {
                cout<<"\t\t *** i: "<<i<<"  j: "<<j<<"  k: "<<k<<endl;
                tmp_int=max_int;
            }
        }
        else
        {
            cout<<"\n\t\telse part:\n";
            cout<<"\t\ti: "<<i<<"  k: "<<k<<"       k+1: "<<k+1<<"  j: "<<j<<endl;
            if(start[index[0]]->bst_path==NULL)
            {
                cout<<"\t\t0 IS null.\n";
            }
            else
            {
                cout<<"\n-----------\n";
                start[index[0]]->bst_path->show(start[index[0]]->bst_path);
                cout<<"\n===========\n";
            }
            if(start[index[1]]->bst_path==NULL)
            {
                cout<<"\t\t1 is null.\n";
            }
            if(start[index[2]]->bst_path==NULL)
            {
                cout<<"\t\t2 is null.\n";
            }
            cout<<endl;

            tmp_int=-1;
            tmp_int=start[index[0]]->get_multiplications(start[index[0]]);
            tmp_int+=start[index[1]]->get_multiplications(start[index[1]]);

            int tmp_int1=start[index[0]]->matrix->get_l1(start[index[0]]->matrix) ;
            int tmp_int2=start[index[0]]->matrix->get_l2(start[index[0]]->matrix) ;
            int tmp_int3=start[index[1]]->matrix->get_l2(start[index[1]]->matrix) ;

            tmp_int+=(tmp_int1*tmp_int2*tmp_int3);
        }

        if(start[index[2]]->get_multiplications(start[index[2]]) >= tmp_int)
        {
            start[index[2]]->set_element(start[index[2]],
                                            start[index[0]],
                                            start[index[1]]);
        }

    }

    void show(element* start)
    {
        cout<<"\n\n---------\n";
        start->matrix->show(start->matrix);
        start->bst_path->show(start->bst_path);
    }
};

d** set_matrices()
{
    int* l=new int[mat_count+1];
     l[0]= 5;
     l[1]= 2;
     l[2]= 3;
     l[3]= 4;
     l[4]= 6;
     l[5]= 7;
     l[6]= 8;

     d** matrices=new d*[mat_count];

     for(int i=0; i<mat_count; i++)
     {
         int l1=l[i];
         int l2=l[i+1];
         int* arr=NULL;


         arr=new int[l1*l2];
         int tmp=(l1*l2)+11;
         for(int i=0; i<l1*l2; i++)
         {
             arr[i]=((((i*17)+((i*37)*43)/(19))<<2)*23*tmp+tmp+7)%10;
             tmp=(tmp*29)%97;
         }

         matrices[i]=new d(l1, l2, arr);
     }

     return matrices;
}

/*
element* mcm(int**& arr, int* l, int count)      //matrix chain multiplication
{
    d** matrices=new d*[count];
    for(int i=0; i<count; i++)
    {
        matrices[i]=new d(l[i], l[i+1], arr[i]);
    }

    element** table=new element*[count*count];
    for(int i=0; i<count*count; i++)
    {
        table[i]=new element;
    }

    for(int i=0; i<count; i++)
    {
        int tmp_int=(i*count)+i;
        table[tmp_int]->set(matrices[i]);
    }


    cout<<"main part:\n";
    for(int diagonal=0; diagonal<count; diagonal++)
    {
        cout<<"diagonal: "<<diagonal<<endl;
        for(int i=0; i+diagonal<count; i++)
        {
            int j=i+diagonal;
            cout<<"\ti: "<<i<<endl;
            cout<<"\tj: "<<j<<endl;
            //cout<<"\t\t\t("<< i<<", "<< i+diagonal<<") -> "<<endl;
            for(int k=i; k<j; k++)
            {
                cout<<"\tk: "<<k<<endl;
                table[0]->get_relation(table, count, i, j, k);
            }
            cout<<endl;
        }
        //cout<<endl<<endl;
    }

    table[3]->show_element(table[(0*count)+count-1]);
    cout<<"\n-----------------------------------------------------"<<endl;

    return table[(0*count) + count-1];

}
*/

int main(void)
{
    d** matrices=set_matrices();

    //test part:
    //element class must be tested before anything.
    element** start=new element*[11];

    start[0]=new element(matrices[0]);
    start[1]=new element(matrices[1]);
    start[2]=new element(matrices[2]);
    start[3]=new element(matrices[3]);
    start[4]=new element(matrices[4]);
    start[5]=new element(matrices[5]);

    start[6]->set_element(start[6], start[0], start[1]);
    start[7]->set_element(start[7], start[2], start[3]);
    start[8]->set_element(start[8], start[4], start[5]);
    start[9]->set_element(start[9], start[7], start[8]);
    start[10]->set_element(start[10], start[6], start[9]);

    start[10]->show(start[10]);




    cout<<"\n\nbefore mcm"<<endl;

    /*
    element* output=mcm(arr, l, mat_count);
    output->show_path(output);
    */



    return 0;
}
