#include <iostream>
//#include <vector>
#include <string>
//#include <iomanip>

using namespace std;

class Item
{
public:
    int id;
    string name;
    Item(int id, string name) : name{name}, id{id} {}
};

class Inventory
{
public:
    Item*** tab;
    int rows;
    int cols;
    Inventory(int rows = 4, int cols =9) : rows{rows}, cols{cols}
    {
        tab = new Item**[rows];
        int a = 0;
        for(int i = 0; i < rows; i++)
        {
            tab[i] = new Item*[cols];
        }

        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < cols; j++)
            {
                tab[i][j] = new Item(a, "NAN");
                a++;
            }
        }
    }
    ~Inventory()
    {
        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < cols; j++)
            {
                delete tab[i][j];
            }
        }
        for(int i = 0; i < rows; i++)
        {
            delete[] tab[i];
        }
        delete[] tab;

    }
    void display_name()
    {
        cout << "-----------------" << endl;
        for(int i = 0; i < rows; i++)
        {
            for(int y = 0; y < cols; y++)
            {

            }
            for(int j = 0; j < cols; j++)
            {
                if(tab[i][j]->name == "NAN")
                {
                    cout << "[]   ";
                }
                else
                {
                    cout << "[" << tab[i][j]->name << "]  ";
                }
            }
            cout << endl;
        }
    }
    void display_id()
    {
        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < cols; j++)
            {
                cout << "[" << tab[i][j]->id << "]  ";
            }
            cout << endl;
        }
    }

    void add_item(int row_cords, int col_cords)
    {
        tab[row_cords - 1][col_cords - 1] = new Item(11, "!");
    }
    void swap_item(int row_cords1, int col_cords1, int row_cords2, int col_cords2)
    {
        swap(tab[row_cords1 - 1][col_cords1 - 1], tab[row_cords2 - 1][col_cords2 - 1]);
    }
};


int main()
{
    //auto sth = new Inventory();
    //sth->display_name();
    Inventory something(4, 9);
    something.add_item(2, 6);
    something.display_name();
    something.swap_item(2, 6, 3, 6);
    something.display_name();

    return 0;
}
