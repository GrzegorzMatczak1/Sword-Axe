#include <iostream>
#include <vector>
#include <iomanip>
#include "item.h"

using namespace std;


class Equipment
{
private:
    Item*** grid;
    int rows;
    int cols;
public:

    Equipment(int rows = 5, int cols = 5) : rows{rows}, cols{cols}
    {
        grid = new Item**[rows];
        for (int i = 0; i < rows; i++)
        {
            grid[i] = new Item*[cols];
        }

        int count = 0;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                grid[i][j] = new Item("Item " + to_string((count)));
                count++;
            }
        }
    }

    ~Equipment()
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                delete grid[i][j];
            }
        }
        for (int i = 0; i < rows; i++)
        {
            delete[] grid[i];
        }
        delete[] grid;
    }

    void display()
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if(j == 0)
                {
                    cout << setw(5);
                }
                cout << "[" << grid[i][j]->name << "]" << setw(3);
            }
            cout << endl;
        }
    }

};

int main()
{

    Equipment E(8, 8);
    E.display();

    return 0;

}
