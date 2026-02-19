#include <iostream>
#include <limits>
#include <time.h>
#include <random>

using namespace std;
#define nodes_count 4
#define max_float  numeric_limits<float>::max()


//checked.
class data
{
private:
    int key;
    float probability;
    int value;

public:
    data(int key_in=-1, float probability_in=0, int value_in=0)
    {
        key=key_in;
        probability=probability_in;
        value=value_in;
    }

    void show(data* start)
    {
        cout<<"show data:"<<endl;
        if(start==NULL)
        {
            cout<<"\t NULL pointer"<<endl;
            return;
        }

        cout<<"\tkey: "<<start->key<<endl;
        cout<<"\tprobability: "<<start->probability<<endl;
        cout<<"\tvalue: "<<start->value<<endl;
        cout<<"\n";

    }

    int get_key(data* start)
    {
        return start->key;
    }

    float get_probability(data* start)
    {
        return start->probability;
    }

    int get_value(data* start)
    {
        return start->value;
    }
};

//checked.
class bst              //binary search tree
{
private:
    data* dp; //data pointe
    bst* left, *right;

    float sum_probabilities(bst*& start, int i)
    {
        if(start==NULL)
        {
            return 0;
        }
        else
        {
            float sum = 0;
            sum += i*start->dp->get_probability(start->dp);
            sum += start->right->sum_probabilities(start->right, i+1);
            sum += start->left->sum_probabilities(start->left, i+1);

            return sum;
        }
    }

public:
    bst(data* dpi=NULL ) //dpi=data pointer in
    {
        dp=dpi;
        right=NULL;
        left=NULL;
    }

    void set(bst*& start1, bst* start2, bst* start3, data*& dpi)
    {
        start1=new bst(dpi);

        start1->left=start2;
        start1->right=start3;
    }

    float get_sc(bst*& start)  //sc=search count
    {
        float output=0;
        output += start->left->sum_probabilities(start->left, 2);
        output += start->right->sum_probabilities(start->right, 2);
        output += start->dp->get_probability(start->dp);
        return output;
    }

    void show(bst*& start)
    {
        if(start==NULL)
        {
            return;
        }
        else
        {
            cout<<"( ";
            if(start->left!=NULL)
            {
                start->left->show(start->left);
            }

            cout<<"[k= ";
            cout<<start->dp->get_key(start->dp)<<" ";
            cout<<", sc= "<<start->get_sc(start)<<"] ";


            if(start->right!=NULL)
            {
                start->right->show(start->right);
            }
            cout<<" ) ";

        }
    }

};



/*
//redefine this function, and make a function to give initial values.
bst* make_optimal_bst(bst** start, int n_count)      //matrix chain multiplication
{
    element** table=new element*[count*count];
    for(int i=0; i<count*count; i++)
    {
        table[i]=new element;
    }

    for(int i=0; i<count; i++)
    {
        int tmp_int=(i*count)+i;
        table[tmp_int]=new element(matrices[i]);
    }

    for(int diagonal=0; diagonal<count; diagonal++)
    {
        for(int i=0; i+diagonal<count; i++)
        {
            int j=i+diagonal;
            for(int k=i; k<j; k++)
            {
                table[0]->get_relation(table, count, i, j, k);
            }
        }
    }

    return table[(0*count) + count-1];
}
*/

void set_initial_values(data**& d_start, int counter)
{
    if(counter==4)  //based on professor's pamphlet.
    {
        d_start=new data*[counter];
        d_start[0]=new data(0, 3.0/8);
        d_start[1]=new data(1, 3.0/8);
        d_start[2]=new data(2, 1.0/8);
        d_start[3]=new data(3, 1.0/8);
        return;
    }
    else
    {
        srand(time(0));

        int* tmp_arr=new int[counter];
        int tmp_sum=0;

        for(int i=0; i<counter; i++)
        {
            tmp_arr[i]=random()%100;
            tmp_sum+=tmp_arr[i];
        }
        float* tmp_arr_float=new float[counter];
        for(int i=0; i<counter; i++)
        {
            tmp_arr_float[i]=(float)tmp_arr[i]/tmp_sum;
        }

        d_start=new data*[counter];
        for(int i=0; i<counter; i++)
        {
            d_start[i]=new data(i, tmp_arr_float[i]);
        }

        return;
    }

}

int main(void)
{

    data** d_start=NULL;
    set_initial_values(d_start, nodes_count);

    for(int i=0; i<nodes_count; i++)
    {
        d_start[i]->show(d_start[i]);
    }


    /*bst** start=new bst*[nodes_count];

    start[3]->set(start[3], NULL, NULL, d_start[3]);
    start[2]->set(start[2], NULL, start[3], d_start[2]);
    start[1]->set(start[1], NULL, NULL, d_start[1]);
    start[0]->set(start[0], start[1], start[2], d_start[0]);

    start[0]->show(start[0]);
    cout<<endl;*/





    return 0;
}
