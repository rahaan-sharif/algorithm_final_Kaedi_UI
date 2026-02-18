#include <iostream>
#include <limits>
using namespace std;
#define mat_count 5
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
        int index[3]={0};
        index[0]=(i*count)+k;
        index[1]=((k+1)*count)+j;
        index[2]=(i*count)+j;

        int tmp_multiplications=0;

        if(start[index[0]]->get_multiplications(start[index[0]])!=max_int)
        {
            tmp_multiplications+=start[index[0]]->get_multiplications(start[index[0]]);
        }
        if(start[index[1]]->get_multiplications(start[index[1]])!=max_int)
        {
            tmp_multiplications+=start[index[1]]->get_multiplications(start[index[1]]);
        }

        int tmp_int=0;
        tmp_int  =start[index[0]]->matrix->get_l1(start[index[0]]->matrix);
        tmp_int *=start[index[0]]->matrix->get_l2(start[index[0]]->matrix);
        tmp_int *=start[index[1]]->matrix->get_l2(start[index[1]]->matrix);

        tmp_multiplications+=tmp_int;

        if(start[index[2]]->get_multiplications(start[index[2]]) >= tmp_multiplications)
        {
            start[index[2]]->set_element(start[index[2]],
                                         start[index[0]],
                                         start[index[1]] );
        }

    }

    void show(element* start)
    {
        cout<<"\n---------\n";
        cout<<"total multiplications: "<<start->get_multiplications(start)<<"\n\n";
        start->matrix->show(start->matrix);
        cout<<"show path:\n\t";
        start->bst_path->show(start->bst_path);
        cout<<"\n---------\n\n";
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

     for(int i=0; i<mat_count; i++)
     {
         cout<<"marix_"<<i<<": \n";
         matrices[i]->show(matrices[i]);
     }

     return matrices;
}

element* mcm(d**& matrices, int count)      //matrix chain multiplication
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

int main(void)
{
    d** matrices=set_matrices();
    element* output=mcm(matrices, mat_count);

    cout<<"\n\n\nmultiplication result:\n";
    output->show(output);

    return 0;
}

*/


int main(void)
{

    data** d_start=new data*[4];
    d_start[0]=new data(0, 3.0/8);
    d_start[1]=new data(1, 3.0/8);
    d_start[2]=new data(2, 1.0/8);
    d_start[3]=new data(3, 1.0/8);

    bst** start=new bst*[5];

    start[3]->set(start[3], NULL, NULL, d_start[3]);
    start[2]->set(start[2], NULL, start[3], d_start[2]);
    start[1]->set(start[1], NULL, NULL, d_start[1]);
    start[0]->set(start[0], start[1], start[2], d_start[0]);

    start[0]->show(start[0]);
    cout<<endl;





    return 0;
}
