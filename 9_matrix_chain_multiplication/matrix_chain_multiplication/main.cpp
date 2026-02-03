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

int main(void)
{
    int* array=new int[12];
    for(int i=0; i<12; i++)
    {
        array[i]=i;
    }

    d tmp=d(3, 4, array);
    tmp.show();



    return 0;
}
