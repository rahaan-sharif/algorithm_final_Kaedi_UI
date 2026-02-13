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
        if(start==NULL)
        {
            cout<<"\t NULL pointer"<<endl;
            return;
        }

        cout<<"\tl1: "<<start->l1<<endl;
        cout<<"\tl2: "<<start->l2<<endl;

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

    void add_right(bst*& start1, bst*& start2)
    {
        start1->right=start2;
    }

    void add_left(bst*& start1, bst*& start2)
    {
        start1->left=start2;
    }


public:
    bst(int mul_in, int l1_in=0, int l2_in=0)
    {
        l1=l1_in;
        l2=l2_in;
        multiplications=mul_in;
        right=NULL;
        left=NULL;
    }

    int get_value(bst*& start)
    {
        if(start==NULL)
        {
            return 0;
        }
        else
        {
            return start->multiplications;
        }
    }

    void set(bst*& start1, bst*& start2, bst*& start3)
    {
        start1->l1=start2->l1;
        start1->l2=start3->l2;

        start1->add_left(start1, start2);
        start1->add_right(start1, start3);

        start1->multiplications  = start2->multiplications;
        start1->multiplications += start3->multiplications;
        start1->multiplications += (start2->l1 * start2->l2 * start3->l2);
    }

    void show(bst*& start)
    {
        cout<<"show bst:\n";
        if(start==NULL)
        {
            cout<<"\t NULL pointer.\n";
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

public:
    element()
    {
        bst_path=NULL;
        matrix=NULL;
    }

    void set(d*& mat_in)
    {
        matrix=mat_in;
    }

    void set_element(element*& start1, element*& start2, element*& start3)
    {
        d* tmp_d=new d;
        tmp_d=tmp_d->mul(start2->matrix, start3->matrix);

        bst* tmp_path=new bst(0, 0, 0);

        tmp_path->set(tmp_path, start2->bst_path, start3->bst_path);

        start1->matrix=tmp_d;
        start1->bst_path=tmp_path;
    }

    int get_value(element*& start)
    {
        return start->bst_path->get_value(start->bst_path);
    }

    void get_relation(element**& start, int count,
                      int i, int j, int k)
    {
        //cout<<"get_relation function:\n";

        int index[3]={0};
        index[0]=(i*count)+k;
        index[1]=((k+1)*count)+j;
        index[2]=(i*count)+j;

        /*cout<<"index[0]: "<<index[0]<<endl;
        cout<<"index[1]: "<<index[1]<<endl;
        cout<<"index[2]: "<<index[2]<<endl;*/

        int tmp_int=-1;
        //cout<<"tmp_int: "<<tmp_int<<endl;
        tmp_int=start[index[0]]->get_value(start[index[0]]);
        //cout<<"tmp_int: "<<tmp_int<<endl;
        tmp_int+=start[index[1]]->get_value(start[index[1]]);
        //cout<<"tmp_int: "<<tmp_int<<endl;

        int tmp_int1=start[index[0]]->matrix->get_l1(start[index[0]]->matrix) ;
        //cout<<"tmp_int1: "<<tmp_int1<<endl;

        int tmp_int2=start[index[0]]->matrix->get_l2(start[index[0]]->matrix) ;
        //cout<<"tmp_int2: "<<tmp_int2<<endl;

        int tmp_int3=start[index[1]]->matrix->get_l2(start[index[1]]->matrix) ;
        //cout<<"tmp_int3: "<<tmp_int3<<endl;

        tmp_int+=(tmp_int1*tmp_int2*tmp_int3);
        //cout<<"tmp_int: "<<tmp_int<<endl;


        // اینجا کمتر بودن باید درست بشه. ایراد داره

        cout<<"\tstart[2]->value: "<<start[index[2]]->get_value(start[index[2]])<<endl;
        cout<<"\ttmp_int: "<<tmp_int<<endl;
        if(start[index[2]]->get_value(start[index[2]]) > tmp_int)
        {
            start[index[2]]->set_element(start[index[2]],
                                            start[index[0]],
                                            start[index[1]]);
        }

    }

    void show_path(element*& start)
    {
        start->bst_path->show(start->bst_path);
    }

    void show_element(element* start)
    {
        cout<<"\n\n---------\n";
        start->matrix->show(start->matrix);
        start->bst_path->show(start->bst_path);
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

element* mcm(int**& arr, int* l, int count)      //matrix chain multiplication
{
    cout<<"mcm funciton\n"<<endl;

    d** matrices=new d*[count];
    for(int i=0; i<count; i++)
    {
        matrices[i]=new d(l[i], l[i+1], arr[i]);
    }

    /*for(int i=0; i<count; i++)
    {
        matrices[i]->show(matrices[i]);
    }*/
    cout<<"matrices are created successfully.\n"<<endl;

    element** table=new element*[count*count];
    for(int i=0; i<count*count; i++)
    {
        table[i]=new element;
    }

    /*for(int i=0; i<count*count; i++)
    {
        table[i]->show_element(table[i]);
    }*/
    cout<<"tabel is created successfully.\n"<<endl;

    for(int i=0; i<count; i++)
    {
        int tmp_int=(i*count)+i;
        table[tmp_int]->set(matrices[i]);
    }

    /*for(int i=0; i<count; i++)
    {
        cout<<"\n\n**************************************\n";
        cout<<"i: "<<i<<endl;
        table[(i*count)+i]->show_element(table[(i*count)+i]);
    }*/
    cout<<"first main diagonal is set successfully.\n"<<endl;


    cout<<"main part:\n";
    for(int diagonal=0; diagonal<count; diagonal++)
    {
        cout<<"diagonal: "<<diagonal<<endl;
        for(int i=0; i+diagonal<count; i++)
        {
            int j=i+diagonal;
            cout<<"\ti: "<<i<<endl;
            cout<<"\tj: "<<j<<endl;
            //cout<<"\t\t\t("<< i<<", "<< i+diagonal<<") -> "<<endl;
            for(int k=i; k<j; k++)
            {
                cout<<"\tk: "<<k<<endl;
                table[0]->get_relation(table, count, i, j, k);
            }
            cout<<endl;
        }
        //cout<<endl<<endl;
    }

    return table[(0*count) + count-1];

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

    cout<<"before mcm"<<endl;

    element* output=mcm(arr, l, mat_count);
    output->show_path(output);


    return 0;
}
