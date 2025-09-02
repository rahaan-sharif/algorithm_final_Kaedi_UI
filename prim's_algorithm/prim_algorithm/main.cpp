#include <iostream>
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

    void prim(node* start1, node*& start2)
    {

    }
};

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

int linked_list::exist(linked_list* start, int id_in)
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




int main(void)
{
    node* start=NULL;
    start->make_graph(start, 1, 5, 1);
    start->make_graph(start, 1, 3, 2);
    start->make_graph(start, 1, 2, 3);

    start->make_graph(start, 2, 5, 4);
    start->make_graph(start, 2, 4, 5);

    start->make_graph(start, 3, 5, 6);
    start->make_graph(start, 3, 4, 7);

    start->make_graph(start, 4, 5, 8);

    start->show(start);

    return 0;
}
