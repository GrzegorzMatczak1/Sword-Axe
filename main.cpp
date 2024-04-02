#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <cstdlib>
#include <stdlib.h>
#include <memory>
#include <iomanip>
#include <map>
#include "item.h"

using namespace std;

class Inventory //Inventory Class
{
public:
    Item*** tab;
    Gear** battle_slots;
    int rows;
    int cols;
    string letters;
    map<char, int> row_indexes;
    map<string, int> col_indexes;

    Inventory(int rows = 4, int cols = 9) : rows{rows}, cols{cols} //Inventory Constructor
    {
        letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        tab = new Item**[rows];
        for(int i = 0; i < rows; i++)
        {
            tab[i] = new Item*[cols];
        }
        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < cols; j++)
            {
                tab[i][j] = new Item();
            }
        }
        battle_slots = new Gear*[6];
        battle_slots[0] = new Helmet(); // helmet slot
        battle_slots[1] = new Chestplate(); // chestplate
        battle_slots[2] = new Leggins(); // leggins
        battle_slots[3] = new Boots(); // boots
        battle_slots[4] = new Weapon(); // weapons like sword, trident or whatever
        battle_slots[5] = new Shield(); // shield, obviously
        fill_row_indexes();
    }

    // this one creates a map (dictionary) of letters and their matching indexes
    // depending on amound of rows. example: 'A': 0, 'B': 1 and so on until the amout is equeal to rows
    void fill_row_indexes()
    {
        int numeric_value_of_capital_letter = 65;
        for (int i = 0; i < rows; i++)
        {
            row_indexes[char(numeric_value_of_capital_letter)] = i;
            numeric_value_of_capital_letter++;
        }
    }

    // same but with column numbers. had to be done
    void fill_col_indexes()
    {
        for (int i = 0; i < cols; i++)
        {
            col_indexes[to_string(i + 1)] = i;
        }
    }

    void display()
    {
        cout << " ==============================" << endl;
        cout << setw(4);
        for(int numeration = 0; numeration < cols; numeration++)
        {
            cout << " " << numeration + 1 << " ";
        }
        cout << endl << setw(3);


        for (int i = 0; i < rows; i++)
        {
            cout << letters[i];
            for(int j = 0; j < cols; j++)
            {
                if(tab[i][j]->name == "none")
                {
                    cout << "[ ]";
                }
                else
                {
                    cout <<"[" << tab[i][j]->display_name << "]";
                }
            }
            cout << endl << setw(3);
        }
        cout << "#";
        for(int i = 0; i < 6; i++)
        {
            if(battle_slots[i]->name == "none")
            {
                cout << "{ }";
            }
            else
            {
                cout << "{" << battle_slots[i]->display_name << "}";
            }
        }
        cout << endl;
    }

    void add_item_test(int row_cords, int col_cords, const Item& itemToAdd) //This code adds temprorary items to the inventory
    {
        tab[row_cords - 1][col_cords - 1] = new Item(itemToAdd);
    }

    void add_gear_test(int row_cords, int col_cords, const Gear& gearToAdd, string where)
    {
        if(where == "main")
        {
            tab[row_cords - 1][col_cords - 1] = new Gear(gearToAdd);
        }
        else if(where == "gear")
        {
            battle_slots[row_cords - 1] = new Gear(gearToAdd);
        }
    }

    // this better have no bugs 😭🙏
    void swap_items(string cords1, string cords2) // this shi was such a pain in the ass to re-impleent
    {

        auto process_cords1_row = [this](string cords1) -> int
        {
            char letter = char(cords1[0]);

            if((int(letter) >= 65) && (int(letter) <= 90)) // from capital A-Z
            {
                for (const auto& pair : this->row_indexes) {
                    if (pair.first == letter)
                    {
                        return pair.second;
                    }
                }
            } else if(int(letter) == 35) // # character
            {
                return -1;
            }
            return -2; // I know it's kinda stupid but I couldn't otherwise because return values are indexes
        };

        auto process_cords1_col = [this](string cords1) -> int
        {
            string number = cords1.substr(1, cords1.size() - 1); // this gets a string value from passed cords and turns a part from index 1 to the end of the string (number part)
            int num;
            try{
                num = stoi(number);
                for (const auto& pair : this->col_indexes) {
                    if (pair.first == number)
                    {
                        return pair.second;
                    }
                }
            } catch (const invalid_argument& e)
            {
                return -1;
            }
            return -1;
        };


        auto process_cords2_row = [this](string cords2) -> int
        {
            char letter = char(cords2[0]);

            if((int(letter) >= 65) && (int(letter) <= 90))
            {
                for (const auto& pair : this->row_indexes) {
                    if (pair.first == letter)
                    {
                        return pair.second;
                    }
                }
            } else if(int(letter) == 35)
            {
                return -1;
            }
            return -2;
        };

        auto process_cords2_col = [this](string cords2) -> int
        {
            string number = cords2.substr(1, cords2.size() - 1);
            int num;
            try{
                num = stoi(number);
                for (const auto& pair : this->col_indexes) {
                    if (pair.first == number)
                    {
                        return pair.second;
                    }
                }
            } catch (const invalid_argument& e)
            {
                return -1;
            }
            return -1;
        };

        // indexes -  do not corelate with numbers in console display // this part should be working(i hope)
        int cords1_row = process_cords1_row(cords1); // from letter to index number
        int cords1_col = process_cords1_col(cords1); // from number to index number

        int cords2_row = process_cords2_row(cords2); // same
        int cords2_col = process_cords2_col(cords2); // same

        auto errorMessage = []() -> void
        {
            cout << "Wrong input or items." << endl;
        };

        // if first input if in gear and second in main inventory
        //if character is #, col not out of range; row not out of range, col not out of range
        if( ((cords1_row == -1) && ((cords1_col >= 0) && (cords1_col <= 5)))  &&  ( ((cords2_row >= 0) && (cords2_row < this->rows)) && ((cords2_col >= 0) && (cords2_col < this->cols)) ) )
        {
            Gear* temp = battle_slots[cords1_col]; // from gear slots
            Item* temp2 = tab[cords2_row][cords2_col]; // from main inventory

            //both slots are NOT empty
            if (!(temp2->name == "none") && !(temp->name == "none"))
            {
                if (temp2->slot_type == temp->slot_type) // both are same gear
                {
                    Gear* toGear = dynamic_cast<Gear*>(temp2); // this turns an Item pointer into a Gear pointer. and I know that the pointer is a Gear because of if, which checks its slot type. hope it's clear
                    Item* toItem = dynamic_cast<Gear*>(temp);

                    tab[cords2_row][cords2_col] = toItem;
                    battle_slots[cords1_col] = toGear;
                } else
                {
                    errorMessage();
                }
            }

            // only first, general inventory slot is empty
            else if((temp2->name == "none") && !(temp->name == "none"))
            {
                Item* toItem = dynamic_cast<Item*>(temp);

                tab[cords2_row][cords2_col] = toItem;
                battle_slots[cords1_col] = new Gear();
            }

            // only second, gear slot is empty
            else if(!(temp2->name == "none") && (temp->name == "none"))
            {
                if (temp2->slot_type == temp->slot_type)
                {
                    Gear* toGear = dynamic_cast<Gear*>(temp2);

                    tab[cords2_row][cords2_col] = new Item();
                    battle_slots[cords1_col] = toGear;
                } else
                {
                    errorMessage();
                }
            }
        }

        // if first input if in general and second in gear
        else if( (((cords1_row >= 0) && (cords1_row < this->rows)) && ((cords1_col >= 0) && (cords1_col < this->cols)))  &&  ((cords2_row == -1) && ((cords2_col >= 0) && (cords2_col <= 5))) )
        {
            Item* temp = tab[cords1_row][cords1_col];
            Gear* temp2 = battle_slots[cords2_col];

            if (!(temp2->name == "none") && !(temp->name == "none"))
            {
                if (temp2->slot_type == temp->slot_type)
                {
                    Gear* toGear = dynamic_cast<Gear*>(temp);
                    Item* toItem = dynamic_cast<Item*>(temp2);

                    tab[cords1_row][cords1_col] = toItem;
                    battle_slots[cords2_col] = toGear;
                } else
                {
                    errorMessage();
                }
            }

            else if((temp2->name == "none") && !(temp->name == "none"))
            {
                Item* toItem = dynamic_cast<Item*>(temp2);

                tab[cords1_row][cords1_col] = toItem;
                battle_slots[cords2_col] = new Gear();
            }

            else if(!(temp2->name == "none") && (temp->name == "none"))
            {
                if (temp2->slot_type == temp->slot_type)
                {
                    Gear* toGear = dynamic_cast<Gear*>(temp);

                    tab[cords1_row][cords1_col] = new Item();
                    battle_slots[cords2_col] = toGear;
                } else
                {
                    errorMessage();
                }
            }
        }

        // 1 - B4 ; 2 - D1
        // if both inputs are in general
        else if ( (((cords1_row >= 0) && (cords1_row < this->rows)) && ((cords1_col >= 0) && (cords1_col < this->cols)))  &&  (((cords2_row >= 0) && (cords2_row < this->rows)) && ((cords2_col >= 0) && (cords2_col < this->cols))) )
        {
            swap(tab[cords1_row][cords1_col], tab[cords2_row][cords2_col]);
        }

        // any other issue idk
        else
        {
            errorMessage();
        }
    } // I think it doesn't work. it's 00:17 Tuesday 😭😭😭😭😭😭😭



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

        //deletes gear items and list
        for (int i = 0; i < 6; i++)
        {
            delete[] battle_slots[i];
        }
        delete[] battle_slots;
    }
// add random will be done differently. how about we make classes
//with specific items like wood, roman shield, knife. this way we have a created set of existing items.
//the classes could have methods like generate random or random stats and so on
// class items, helmets, leggins etc
};

int main()
{

    Inventory I;
    I.display();
    I.add_item_test(2, 4, Item(0, "", "1"));
    I.add_item_test(4, 1, Item(0, "", "2"));
    I.display();
    I.swap_items("B4", "D1");
    I.display();
    return 0;
}
