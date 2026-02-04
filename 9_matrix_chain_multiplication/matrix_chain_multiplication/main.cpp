#include <iostream>
using namespace std;

class d
{
private:
    int length;
    int height;
    int* array;

public:
    d(int length_in=-1, int height_in=-1, int* array_in=NULL)
    {
        length=length_in;
        height=height_in;
        array=array_in;
    }

    d* mul(d*& mat1, d*& mat2, int l1, int l2, int l3)
    {
        int* output_arr=new int[l1*l3];
        for(int i=0; i<l1*l3; i++)
        {
            output_arr[i]=0;
        }

        for(int i=0; i<l1; i++)
        {
            for(int j=0; j<l2; j++)
            {
                for(int k=0; k<l3; k++)
                {
                    output_arr[(i*l3)+k] += mat1->array[(i*l2)+j] * mat2->array[(j*l3)+k];
                }
            }
        }


        d* output=new d(l1, l3, output_arr);
        return output;
    }

    void show()
    {
        cout<<"show d:"<<endl;
        for(int i=0; i<length; i++)
        {
            for(int j=0; j<height; j++)
            {
                cout<<array[(i*height)+j]<<"\t";
            }
            cout<<endl;
        }
        cout<<endl<<endl;
    }
};

class linked_list
{
private:
    d* node;
    linked_list* next;

public:
    linked_list(d* node_in=NULL, linked_list* next_in=NULL)
    {
        node=node_in;
        next=next_in;
    }
    void make_list(linked_list*& start, d* node_in)
    {
        if(start==NULL)
        {
            start=new linked_list(node_in, NULL);
            return;
        }
        else
        {
            linked_list* tmp_ll=start;
            while(tmp_ll->next!=NULL)
            {
                tmp_ll=tmp_ll->next;
            }
            tmp_ll->next=new linked_list(node_in, NULL);
            return;
        }
    }
    void show(linked_list* start)
    {
        while(start!=NULL)
        {
            start->node->show();
            start=start->next;
            cout<<endl;
        }
    }
};

class element
{
private:
    linked_list* path;
    int value;

public:
    element(linked_list* path_in, int value_in)
    {
        path=path_in;
        value=value_in;
    }

    void add_path(element*& start, d* node_in)
    {
        start->path->make_list(start->path, node_in);
    }

};

void set_mat(int*& arr, int l1, int l2)
{
    int tmp=(l1*l2)+11;
    for(int i=0; i<l1*l2; i++)
    {
        arr[i]=((((i*17)+((i*37)*43)/(19))<<2)*23*tmp+tmp+7)%10;
        tmp=(tmp*29)%97;
    }
}

int main(void)
{
    int* arr1=new int[3*4];
    int* arr2=new int[4*5];
    set_mat(arr1, 3, 4);
    set_mat(arr2, 4, 5);

    d* tmp1=new d(3, 4, arr1);
    d* tmp2=new d(4, 5, arr2);
    tmp1->show();
    tmp2->show();

    element** table=NULL;



    return 0;
}
