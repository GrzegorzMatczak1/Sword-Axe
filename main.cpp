#include <iostream>
//#include <vector>
#include <string>

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
    Inventory(int rows = 5, int cols = 5) : rows{rows}, cols{cols}
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
        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < cols; j++)
            {
                if(tab[i][j]->name == "NAN")
                {
                    cout << "[]\t";
                }
                else
                {
                    cout << "[" << tab[i][j]->name << "]\t";
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
                cout << "[" << tab[i][j]->id << "]\t";
            }
            cout << endl;
        }
    }

};


int main()
{
    //auto sth = new Inventory();
    //sth->display_name();
    Inventory something(4, 9);
    something.display_name();
    return 0;
}
