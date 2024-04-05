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
    map<string, int> gear_slots;

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
                tab[i][j] = nullptr;
            }
        }

        battle_slots = new Gear*[6];
        battle_slots[0] = nullptr; // helmet slot
        battle_slots[1] = nullptr; // chestplate
        battle_slots[2] = nullptr; // leggins
        battle_slots[3] = nullptr; // boots
        battle_slots[4] = nullptr; // weapons like sword, trident or whatever
        battle_slots[5] = nullptr; // shield
        fill_row_indexes();
        fill_gear_slots();
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

    void fill_gear_slots()
    {
        gear_slots["helmet"] = 0;
        gear_slots["chestplate"] = 0;
        gear_slots["leggins"] = 0;
        gear_slots["boots"] = 0;
        gear_slots["weapon"] = 0;
        gear_slots["shield"] = 0;
    }


    bool compare_item_slot_type_with_slot(string item_slot_type)
    {
        for (const auto& pair : this->gear_slots) {
            if (item_slot_type == pair.first)
            {
                return true;
            }
        }
        return false;
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
                if(tab[i][j] == nullptr)
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
            if(battle_slots[i] == nullptr)
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


    void add_gear_to_main(int row_cords, int col_cords, const Item& gearToAdd)
    {
        tab[row_cords - 1][col_cords - 1] = new Item(gearToAdd);
    }


    void add_gear_to_gear(int col_cords, const Gear& gearToAdd)
    {
        battle_slots[col_cords - 1] = new Gear(gearToAdd);
    }


    // returns processed cord
    auto get_processed_cords(string cords) -> vector<int>
    {
        auto process_cords_row = [this](string cords) -> int
        {
            char letter = char(cords[0]);

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
            return -2;
        };

        int cords_row = process_cords_row(cords);
        int cords_col = (cords[1] - '0') - 1;

        return {cords_row, cords_col};
    }


    int is_valid_cords_input(string cords)
    {

        int cords_row = get_processed_cords(cords)[0];
        int cords_col = get_processed_cords(cords)[1];

        // in main
        if ((cords_row >= 0 && cords_row < this->rows) && (cords_col >= 0 && cords_col < this->cols))
        {
            return 1;
        }
        // in gear
        else if((cords_row == -1) && (cords_col >= 0 && cords_col <= 5))
        {
            return 0;
        }
        // out of range/complete nonsense
        else
        {
            return -1;
        }
    }


    void swap_items(string cords1, string cords2)
    {
        if (is_valid_cords_input(cords1) >= 0 || is_valid_cords_input(cords2) >= 0)
        {
            // indexes -  do not corelate with numbers in console display // prc = processed (integers)
            vector<int> cords1_prc =

            int cords2_row = process_cords2_row(cords2); // same
            int cords2_col = (cords2[1] - '0') - 1; // same

            auto errorMessage = []() -> void
            {
                cout << "Wrong input or items." << endl;
            };

            cout << "B4: " << cords1_row << " " << cords1_col << endl;
            cout << "D1: " << cords2_row << " " << cords2_col << endl;


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
    //I.display();
    I.add_item_test(2, 4, Item(0, "", "1"));
    I.add_item_test(4, 1, Item(0, "", "2"));
    //I.add_gear_to_main(0, 0, Boots(0, "", "B"));
    //I.add_gear_to_gear(1, Helmet(0, "", "H"));
    I.display();
    I.swap_items("B4", "D1");


    I.display();
    return 0;
}
