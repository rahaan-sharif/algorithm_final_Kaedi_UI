#include <iostream>
using namespace std;


class linked_list
{
private:
    int item;
    linked_list* next;
    linked_list* prev;
public:
    linked_list(int item_in)
    {
        item=item_in;
        next=NULL;
        prev=NULL;
    }

    void make_ll(linked_list*& start, int item_in, int direction=1)
    {
        if(start==NULL)
        {
            start=new linked_list(item_in);
            return;
        }

        else
        {
            if(direction>=0)
            {
                linked_list* tmp_ll=start;
                while(tmp_ll->next!=NULL)
                    tmp_ll=tmp_ll->next;
                tmp_ll->next=new linked_list(item_in);
                tmp_ll->next->prev=tmp_ll;
            }
            else
            {
                linked_list* tmp_ll=start;
                while(tmp_ll->prev!=NULL)
                    tmp_ll=tmp_ll->prev;
                tmp_ll->prev=new linked_list(item_in);
                tmp_ll->prev->next=tmp_ll;
            }
        }

    }

    void show(linked_list* start, int direction=1)
    {
        if(direction>=0)
        {
            while(start!=NULL)
            {
                cout<<start->item<<" -> ";
                start=start->next;
            }
        }
        else
        {
            while(start->prev!=NULL)
            {
                start=start->prev;
            }
            while(start!=NULL)
            {
                cout<<start->item<<" <- ";
                start=start->next;
            }
        }
        cout<<endl<<endl;
    }

    void show2(linked_list* start)
    {
        cout<<start->item<<" ";
        start=start->prev;

        cout<<start->item<<" ";
        start=start->prev;

        cout<<start->item<<" ";
        start=start->prev;

        cout<<start->item<<" ";
        start=start->prev;

        cout<<start->item<<" ";
        start=start->prev;

        cout<<start->item<<" ";
        start=start->prev;

        cout<<start->item<<" -> ";
        start=start->next;


    }

    void quick_sort_right(linked_list*& start)
    {
        if(start==NULL)
        {
            return;
        }
        else
        {
            linked_list* new_start=NULL;
            new_start->make_ll(new_start, start->item);
            start=start->next;

            while(start!=NULL)
            {
                cout<<start->item<<endl;
                if(new_start->item <= start->item)
                {
                    new_start->make_ll(new_start, start->item, 1);
                }
                else
                {
                    new_start->make_ll(new_start, start->item, -1);
                }
                start=start->next;
            }

            new_start->next->quick_sort_right(new_start->next);
            new_start->prev->quick_sort_left(new_start->prev);

            start=new_start;
        }
    }

    void quick_sort_left(linked_list*& start)
    {
        if(start==NULL)
        {
            return;
        }
        else
        {
            linked_list* new_start=NULL;
            new_start->make_ll(new_start, start->item);
            start=start->prev;

            while(start!=NULL)
            {
                if(new_start->item <= start->item)
                {
                    new_start->make_ll(new_start, start->item, 1);
                }
                else
                {
                    new_start->make_ll(new_start, start->item, -1);
                }
                start=start->prev;
            }

            new_start->next->quick_sort_right(new_start->next);
            new_start->prev->quick_sort_left(new_start->prev);

            start=new_start;
        }
    }

};



int main(void)
{
    linked_list* start=NULL;
    for(int i=10; i>-1; i--)
    {
        start->make_ll(start, i);
    }

    start->quick_sort_right(start);

    cout<<"now"<<endl;
    start->show2(start);


    return 0;
}
