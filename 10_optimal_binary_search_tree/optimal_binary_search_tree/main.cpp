#include <iostream>
#include <limits>
using namespace std;
#define min_int  numeric_limits<int>::min()


class bst    //binary search tree
{
private:
    static int counter;

    int key;
    int data;
    bst* left;
    bst* right;



    void merge(int*& array, int low, int middle_index, int high)
    {
        int i=low, j=middle_index+1, index=0;
        int* tmp_array=new int[high-low+1];
        while(index<=(high-low))
        {

            if(i>middle_index)
            {
                tmp_array[index]=array[j++];
            }
            else if(j>high)
            {
                tmp_array[index]=array[i++];
            }
            else if(array[i]<=array[j])
            {
                tmp_array[index]=array[i++];
            }
            else if(array[j]<array[i])
            {
                tmp_array[index]=array[j++];
            }
            else
            {
                cout<<"unexpected error in merge function."<<endl;
            }

            index++;
        }

        for(int k=0; k<(high-low+1); k++)
        {
            array[low+k]=tmp_array[k];
        }
    }

    void merge_sort(int* array, int low, int high)
    {
        if(low<high)
        {
            int middle_index= (low+high)/2;
            merge_sort(array, low , middle_index);
            merge_sort(array, middle_index + 1, high);

            merge(array, low, middle_index, high);
        }
    }




public:
    bst(int key_in=min_int, int data_in=min_int)
    {
        counter++;

        key=key_in;
        data=data_in;
        right=NULL;
        left=NULL;
    }

    void make_tree(bst*& start, int key_in, int data_in=0)
    {
        int* array=new int[counter+1];
        int pivot=(counter-1)/2;
        array[pivot]=start->key;
        bst_to_array(start->left, array, );
        bst_to_array(start->right, array, );

    }

    void bst_to_array(bst*& start, int* arr_p, int& pivot)
    {}






    void show(bst*& start)
    {
        if(start==NULL)
        {
            return;
        }
        else
        {
            start->left->show(start->left);
            cout<<start->key<<"\t";
            start->right->show(start->right);
        }
    }
};

int bst::counter=0;


int main(void)
{
    bst* start=NULL;
    start->make_tree(start, 7);
    start->make_tree(start, 3);
    start->make_tree(start, 2);
    start->make_tree(start, 5);
    start->make_tree(start, 10);
    start->make_tree(start, 8);
    start->make_tree(start, 4);

    start->show(start);


    return 0;
}
