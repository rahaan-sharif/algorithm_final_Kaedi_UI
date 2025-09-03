#include <iostream>
#include <climits>
using namespace std;

class node;

class linked_list
{
private:
    node* node_item;
    int length;
    linked_list* next;
public:
    linked_list(int length_in, node* node_item_in=NULL)
    {
        node_item=node_item_in;
        length=length_in;
        next=NULL;
    }

    void make_list(linked_list*& start, node* node_item_in, int length_in)
    {
        if(start==NULL)
        {
            start=new linked_list(length_in, node_item_in);
            return;
        }
        else
        {
            linked_list* tmp=start;
            while(tmp->next != NULL)
            {
                tmp=tmp->next;
            }
            tmp->next=new linked_list(length_in, node_item_in);
        }
    }

    void show(linked_list* start);

    int exist(linked_list* start, int id_in);

    void get_smallest_edge(node* start_node, linked_list* start_ll, int*& output);

};

//////////////////////////
class node
{
private:
    linked_list* related;
    node* next, *prev;
    int id;
public:
    node(int id_in=-1)
    {
        id=id_in;
        related=NULL;

        next=NULL;
        prev=NULL;
    }

    void make_node(node*& start, int id_in)
    {
        if(start==NULL)
        {
            start=new node(id_in);
            return;
        }
        else
        {
            node* tmp_node=start;
            while(tmp_node->next!=NULL)
            {
                tmp_node=tmp_node->next;
            }
            tmp_node->next=new node(id_in);
            tmp_node->next->prev=tmp_node;
            return;
        }
    }

    int exist(node* start, int id_in)
    {
        while(start!=NULL)
        {
            if(start->id==id_in)
            {
                return 1;
            }
            start=start->next;
        }
        return 0;
    }

    node* get_node(node*& start, int id_in)
    {
        node* tmp_node=start;
        while(tmp_node!=NULL)
        {
            if(tmp_node->id==id_in)
                return tmp_node;
            tmp_node=tmp_node->next;
        }
        return NULL;
    }

    void make_graph(node*& start, int id_1, int id_2, int length_in)
    {
        if(!exist(start, id_1))
        {
            start->make_node(start, id_1);
        }
        if(!exist(start, id_2))
        {
            start->make_node(start, id_2);
        }

        node* tmp_node=start;
        node* tmp_node1=NULL;
        node* tmp_node2=NULL;
        while(tmp_node!=NULL)
        {
            if(tmp_node->id==id_1)
                tmp_node1=tmp_node;
            if(tmp_node->id==id_2)
                tmp_node2=tmp_node;
            tmp_node=tmp_node->next;
        }
        tmp_node1->related->make_list(tmp_node1->related, tmp_node2, length_in);
        tmp_node2->related->make_list(tmp_node2->related, tmp_node1, length_in);

    }

    int get_id(node* start)
    {
        return start->id;
    }

    void show(node* start)
    {
        if(start==NULL)
            return;
        cout<<"\n\n====="<<endl;
        cout<<"node_ID: "<<start->id<<endl;
        cout<<"\tneighbors: "<<endl;
        start->related->show(start->related);
        start=start->next;
        start->show(start);
    }

    void get_smallest_edge(node* start1, node* start2, int*& output)
    {
        node* tmp_node=start1;
        while(tmp_node!=NULL)
        {
            if(start2->exist(start2, tmp_node->id))
            {
                output[0]=tmp_node->id;
                tmp_node->related->get_smallest_edge(start2, tmp_node->related, output);
            }

            tmp_node=tmp_node->next;
        }
    }

    //in this function we check if all verteces of start 1 is in start2:
    int compare_verteces(node* start1, node*start2)
    {
        while(start1!=NULL)
        {
            if(!start2->exist(start2, start1->id))
            {
                return 0;
            }
            start1=start1->next;
        }

        return 1;
    }

    void prim(node* start1, node*& start2)
    {
        if (start2==NULL)
        {
            start2->make_node(start2, start1->id);

        }
        while(!start2->compare_verteces(start1, start2))
        {
            int* output=new int[3];
            output[0]=-1;
            output[1]=-1;
            output[2]=INT_MAX;

            start2->get_smallest_edge(start1, start2, output);

            start2->make_graph(start2, output[0], output[1], output[2]);
        }
    }
};


void linked_list::show(linked_list* start)
{
    if(start==NULL)
    {
        cout<<"NULL\n";
        return;
    }
    while(start!=NULL)
    {
        cout<<"\t"<<start->node_item->get_id(start->node_item)
            <<" -> length -> "<<start->length<<endl;
        start=start->next;
    }
}

int  linked_list::exist(linked_list* start, int id_in)
{
    if(start==NULL)
    {
        return 0;
    }
    while(start!=NULL)
    {
        if(start->node_item->get_id(start->node_item)==id_in)
            return 1;
        start=start->next;
    }
    return 0;
}

void linked_list::get_smallest_edge(node* start_node, linked_list* start_ll, int*& output)
{
    while(start_ll!=NULL)
    {
        if(start_ll->length<output[1])
        {
            if(!start_node->exist(start_node,
                                  start_ll->node_item->get_id(
                                      start_ll->node_item)))
            {
                output[1]=start_ll->node_item->get_id(start_ll->node_item);
                output[2]=start_ll->length;
            }
        }

        start_ll=start_ll->next;
    }
}

void make_test_graph(node*& start)
{
     start->make_graph(start, 1, 5, 1);
     start->make_graph(start, 1, 3, 2);
     start->make_graph(start, 1, 2, 3);

     start->make_graph(start, 2, 5, 4);
     start->make_graph(start, 2, 4, 5);

     start->make_graph(start, 3, 5, 6);
     start->make_graph(start, 3, 4, 7);

     start->make_graph(start, 4, 5, 8);

     //start->show(start);

}


int main(void)
{
    node* start1=NULL;
    make_test_graph(start1);

    node* start2=NULL;
    cout<<"test: before prim:\n";
    start2->prim(start1, start2);

    start2->show(start2);


    return 0;
}
