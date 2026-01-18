#include <iostream>
using namespace std;
#define max_int 999

class ll   //link-list
{
private:
    int id;
    ll* next;
public:
    ll(int id_in)
    {
        id=id_in;
        next=NULL;
    }

    void make_list(ll*& start, int id_in)
    {
        if(start==NULL)
        {
            start=new ll(id_in);
        }
        else
        {
            ll* tmp_ll=start;
            while(tmp_ll->next!=NULL)
                tmp_ll=tmp_ll->next;
            if(tmp_ll->id!=id_in)
                tmp_ll->next=new ll(id_in);

        }
    }

    void join_two_lls(ll*& start, ll* start_1, ll* start_2)
    {
        start=NULL;
        while(start_1!=NULL)
        {
            start->make_list(start, start_1->id);
            start_1=start_1->next;
        }
        while(start_2!=NULL)
        {
            start->make_list(start, start_2->id);
            start_2=start_2->next;
        }
    }

    void show(ll* start)
    {
        if(start!=NULL)
        {
            while(start->next!=NULL)
            {
                cout<<start->id<<"  ->  ";
                start=start->next;
            }
            cout<<start->id;
        }

        cout<<endl;
    }
};

class node
{
private:
    ll* path;
    int distance;
public:
    node()
    {
        path=NULL;
        distance=INT32_MAX;
    }
    void set(node* start, int distance_in)
    {
        start->distance=distance_in;
        start->path=NULL;
    }
    void set(node* start, node* start_1, node* start_2, int distance_in)
    {
        start->distance=distance_in;
        start->path->join_two_lls(start->path, start_1->path, start_2->path);
    }
    void reset()
    {
        path=NULL;
        distance=INT32_MAX;
    }
    void show()
    {
        cout<<"graph show:\n";
        cout<<"distance: "<<distance<<endl;
        cout<<"path: ";
        path->show(path);
    }
    int get_distance()
    {
        return distance;
    }
    void show_path(node* start)
    {
        start->path->show(start->path);
    }
    void set_path(node*& start, int* arr, int length)
    {
        for(int i=0; i<length; i++)
        {
            start->path->make_list(start->path, arr[i]);
        }
    }
};

void set_node_array(node**& start, int* arr, int vc)
{
    for(int i=0; i<vc; i++)
    {
        for(int j=0; j<vc; j++)
        {
            start[(i*vc)+j]=new node;
            start[(i*vc)+j]->set(start[(i*vc)+j], arr[(i*vc)+j]);

            if(arr[(i*vc)+j]!=max_int)
            {
                int* tmp_arr=new int[2];
                tmp_arr[0]=i;
                tmp_arr[1]=j;
                start[(i*vc)+j]->set_path(start[(i*vc)+j], tmp_arr, 2);
            }

        }

    }
}

void show_node_array(node** start, int length)
{
    cout<<"array_show:\n\n";
    for(int i=0; i<length; i++)
    {
        cout<<"\t"<<i;
    }
    cout<<"\n-------------";
    cout<<"---------------";
    cout<<"---------------\n";

    for(int i=0; i<length; i++)
    {
        cout<<i<<"|\t";

        for(int j=0; j<length; j++)
        {
            cout<<start[(i*length)+j]->get_distance()<<"\t";
        }

        cout<<endl;
    }
    cout<<endl<<endl;
}

void set_example_edges(int*& arr)  //this function provides the matrix of the pamphlet.
{
        arr[0]= 0;
        arr[1]= 1;
        arr[2]= max_int;
        arr[3]= 1;
        arr[4]= 5;

        arr[5]= 9;
        arr[6]= 0;
        arr[7]= 3;
        arr[8]= 2;
        arr[9]= max_int;

        arr[10]= max_int;
        arr[11]= max_int;
        arr[12]= 0;
        arr[13]= 4;
        arr[14]= max_int;

        arr[15]= max_int;
        arr[16]= max_int;
        arr[17]= 2;
        arr[18]= 0;
        arr[19]= 3;

        arr[20]= 3;
        arr[21]= max_int;
        arr[22]= max_int;
        arr[23]= max_int;
        arr[24]= 0;
}

void show_array(int* arr, int length)
{
    cout<<"array_show:\n\n";
    for(int i=0; i<length; i++)
    {
        cout<<"\t"<<i;
    }
    cout<<"\n-------------";
    cout<<"---------------";
    cout<<"---------------\n";

    for(int i=0; i<length; i++)
    {
        cout<<i<<"|\t";

        for(int j=0; j<length; j++)
        {
            cout<<arr[(i*length)+j]<<"\t";
        }

        cout<<endl;
    }
    cout<<endl<<endl;
}

void floid_algorithm(node** start, int vc)
{
    int direct_distance=-1;
    int indirect_distance=-1;

    for(int k=0; k<vc; k++)
    {
        for(int j=0; j<vc; j++)
        {
            for(int i=0; i<vc; i++)
            {
                indirect_distance=start[(i*vc)+k]->get_distance()
                                  + start[(k*vc)+j]->get_distance();
                direct_distance= start[(i*vc)+j]->get_distance();

                if(direct_distance>indirect_distance)
                {
                    start[(i*vc)+j]->set(start[(i*vc)+j],
                                         start[(i*vc)+k],
                                         start[(k*vc)+j],
                                         indirect_distance);
                }
            }
        }
    }
}

int main(void)
{
    int vc=5;   //vertices_count
    int *edges=new int[vc*vc];
    set_example_edges(edges);
    node** start=new node*[vc*vc];

    set_node_array(start, edges, vc);

    cout<<"W matrix:\n";
    show_node_array(start, vc);
    cout<<endl<<endl<<endl<<endl;

    floid_algorithm(start, vc);
    cout<<"D matrix:\n";
    show_node_array(start, vc);
    cout<<endl<<endl<<endl<<endl;

    cout<<"paths:\n";
    for(int i=0; i<vc; i++)
    {
        for(int j=0; j<vc; j++)
        {
            cout<<"\tpath from "<<i<<" to "<<j<<":\t";
            start[(i*vc)+j]->show_path(start[(i*vc)+j]);
        }
    }
    cout<<endl;



    return 0;
}
