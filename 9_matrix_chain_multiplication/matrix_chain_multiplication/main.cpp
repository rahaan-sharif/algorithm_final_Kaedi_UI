i have to replace k with k+1.
I have to change mcm function.











#include <iostream>
using namespace std;
#define mat_count 6

class d
{
private:
    int l1;
    int l2;
    int* array;

public:
    d(int l1_in=-1, int l2_in=-1, int* array_in=NULL)
    {
        l1=l1_in;
        l2=l2_in;
        array=array_in;
    }

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

    void show(d* start)
    {
        cout<<"show d:"<<endl;
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

    int get_l1(d* start)
    {
        return start->l1;
    }

    int get_l2(d* start)
    {
        return start->l2;
    }
};

class bst              //binary search tree
{
private:
    int multiplications;   //number of multiplications till here.
    int l1, l2;
    bst* left, *right;

public:
    bst(int mul_in, int l1_in=0, int l2_in=0)
    {
        l1=l1_in;
        l2=l2_in;
        multiplications=mul_in;
        right=NULL;
        left=NULL;
    }

    void set_value(bst*& start, int mul_in, int l1_in, int l2_in)
    {
        start=new bst(mul_in, l1_in, l2_in);
    }

    int get_value(bst*& start)
    {
        return start->multiplications;
    }

    void add_right(bst*& start1, bst*& start2)
    {
        start1->right=start2;
    }

    void add_left(bst*& start1, bst*& start2)
    {
        start1->left=start2;
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
                cout<<"(( ";
                start->left->show(start->left);
                start->right->show(start->right);
                cout<<") ";
                cout<<" ["<<start->l1<<","<<start->l2<<"] )";
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
    //linked_list* path;
    //int value;           number of multiplications till here.

public:
    element()
    {
        bst_path=NULL;
        value=0;
        matrix=NULL;
    }

    void set_element(element*& start1, element*& start2, element*& start3)
    {
        d* tmp_d=new d;
        tmp_d=tmp_d->mul(start2->matrix, start3->matrix);

        int tmp_l1=start2->matrix->get_l1(start2->matrix);
        int tmp_l2=start2->matrix->get_l1(start2->matrix);
        int tmp_l3=start3->matrix->get_l2(start3->matrix);
        int tmp_value=tmp_l1*tmp_l2*tmp_l3;
        tmp_value+=start2->get_value(start2);
        tmp_value+=start3->get_value(start3);

        bst* tmp_path=new bst(0, 0, 0);
        tmp_path->set_value(tmp_path, tmp_value,
                            start2->matrix->get_l1(start2->matrix),
                            start3->matrix->get_l2(start3->matrix));

        tmp_path->add_left(tmp_path, start2->bst_path);
        tmp_path->add_right(tmp_path, start3->bst_path);

        start1->matrix=tmp_d;
        start1->bst_path=tmp_path;

        //linked_list* tmp_path=new linked_list;
        //tmp_path->concat_2_lists(tmp_path, start2->path, start2->path);
    }

    int get_value(element*& start)
    {
        return start->bst_path->get_value(start->bst_path);
    }

    void get_relation(element**& start, int count,
                      int i, int j, int k)
    {
        int tmp_int=-1;
        tmp_int=start[(i*count)+k]->get_value(start[(i*count)+k]);
        tmp_int+=start[(k*count)+j]->get_value(start[(k*count)+j]);
        int tmp_int1=start[(i*count)+k]->matrix->get_l1(start[(i*count)+k]->matrix) ;
        int tmp_int2=start[(i*count)+k]->matrix->get_l2(start[(i*count)+k]->matrix) ;
        int tmp_int3=start[(k*count)+j]->matrix->get_l2(start[(k*count)+j]->matrix) ;
        tmp_int+=(tmp_int1*tmp_int2*tmp_int3);

        if(start[(i*count)+j]->get_value(start[(i*count)+j]) > tmp_int)
        {
            start[(i*count)+j]->set_element(start[(i*count)+j],
                                            start[(i*count)+k],
                                            start[(k*count)+j]);
        }
    }
};

void set_mat(int*& arr, int l1, int l2)
{
    arr=new int[l1*l2];

    int tmp=(l1*l2)+11;
    for(int i=0; i<l1*l2; i++)
    {
        arr[i]=((((i*17)+((i*37)*43)/(19))<<2)*23*tmp+tmp+7)%10;
        tmp=(tmp*29)%97;
    }
}

void mcm(int**& arr, int* l, int count)      //matrix chain multiplication
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
        for(int j=0; j<count; j++)
        {
            if((j+i)<count)
            {
                int tmp1=j, tmp2=j+i;
                //cout<<"("<<j<<","<<j+i<<") -> ";

            }
        }

        cout<<endl;
    }



}

int main(void)
{
    int* l=new int[mat_count+1];
    l[0]= 5;
    l[1]= 2;
    l[2]= 3;
    l[3]= 4;
    l[4]= 6;
    l[5]= 7;
    l[6]= 8;

    int** arr=new int*[mat_count];
    for(int i=0; i<mat_count; i++)
    {
        set_mat(arr[i], l[i], l[i+1]);
    }

    mcm(arr, l, mat_count);


    return 0;
}
