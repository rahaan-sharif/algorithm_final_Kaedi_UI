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

class linked_list
{
private:
    int l1, l2;
    linked_list* next;

public:
    linked_list(int l1_in=0, int l2_in=0)
    {
        l1=l1_in;
        l2=l2_in;
        next=NULL;
    }

    void make_list(linked_list*& start, int l1_in, int l2_in)
    {
        if(start==NULL)
        {
            start=new linked_list(l1_in, l2_in);
            return;
        }
        else
        {
            linked_list* tmp_ll=start;
            while(tmp_ll->next!=NULL)
            {
                tmp_ll=tmp_ll->next;
            }
            tmp_ll->next=new linked_list(l1_in, l2_in);
            return;
        }
    }

    void concat_2_lists(linked_list*& start1, linked_list*& start2)
    {
        if(start2==NULL)
        {
            return;
        }
        else if(start1==NULL)
        {
            start1=start2;
        }
        else
        {
            linked_list* tmp_ll=start1;
            while(tmp_ll->next!=NULL)
            {
                tmp_ll=tmp_ll->next;
            }
            tmp_ll->next=start2;
        }
    }

    void show(linked_list* start)
    {
        while(start!=NULL)
        {
            cout<<"("<<start->l1<<", "<<start->l2<<") -> ";
            start=start->next;
        }
    }
};

class element
{
private:
    d* matrix;
    linked_list* path;
    int value;

public:
    element()
    {
        path=NULL;
        value=0;
        matrix=NULL;
    }

    void set_element(element*& start1, element*& start2, element*& start3)
    {
        d* tmp_d=tmp_d->mul(start2->matrix, start3->matrix);
        int tmp_l1=start2->matrix->get_l1(start2->matrix);
        int tmp_l2=start2->matrix->get_l2(start2->matrix);
        int tmp_l3=start3->matrix->get_l2(start3->matrix);
        int tmp_value=tmp_l1*tmp_l2*tmp_l3;
        linked_list* tmp_path=;
    }

    void add_path(element*& start, d* node_in)
    {
        start->path->make_list(start->path, node_in);  // باید یک ساختتار درختی باشد. این اشتباه است.
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

    element** table=NULL;



    return 0;
}
