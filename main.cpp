#include <iostream>
#include <time.h>
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
    Item** battle_slots;
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

        battle_slots = new Item*[6];
        battle_slots[0] = nullptr;
        battle_slots[1] = nullptr;
        battle_slots[2] = nullptr;
        battle_slots[3] = nullptr;
        battle_slots[4] = nullptr;
        battle_slots[5] = nullptr;

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

    void fill_gear_slots() // indexes of gear slots // used in swap items
    {
        gear_slots["helmet"] = 0;
        gear_slots["chestplate"] = 1;
        gear_slots["leggins"] = 2;
        gear_slots["boots"] = 3;
        gear_slots["weapon"] = 4;
        gear_slots["shield"] = 5;
    }


    int get_gear_slot_index(string item_slot_type)
    {
        for (const auto& pair : this->gear_slots) {
            if (item_slot_type == pair.first)
            {
                return pair.second;
            }
        }
        return -1;
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


    void add_item(int row_cords, int col_cords, const Item& itemToAdd) //This code adds temprorary items to the inventory
    {
        tab[row_cords - 1][col_cords - 1] = new Item(itemToAdd);
    }


    void add_gear_to_main(int row_cords, int col_cords, const Gear& gearToAdd)
    {
        const Item* itemToAdd = dynamic_cast<const Item*>(&gearToAdd);
        tab[row_cords - 1][col_cords - 1] = new Item(*itemToAdd);
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
        if (cords.size() > 2 || cords.size() < 2)
        {
            return -1;
        }

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
        if (is_valid_cords_input(cords1) >= 0 && is_valid_cords_input(cords2) >= 0)
        {
            // indexes -  do not corelate with numbers in console display // prc = processed (integer indexes)

            vector<int> cords1_prc = get_processed_cords(cords1); // list[0] - row ; list[1] - col
            vector<int> cords2_prc = get_processed_cords(cords2);

            // if first input is in gear and second in main inventory
            if(cords1_prc[0] == -1 && cords2_prc[0] >= 0)
            {
                Item* first = battle_slots[cords1_prc[1]]; // from gear slots
                Item* second = tab[cords2_prc[0]][cords2_prc[1]]; // from main inventory

                //both slots are NOT empty
                if (first != nullptr && second != nullptr)
                {
                    if (first->slot_type == second->slot_type) // both are same gear
                    {
                        battle_slots[cords1_prc[1]] = second;
                        tab[cords2_prc[0]][cords2_prc[1]] = first;
                    } else
                    {
                        cout << "The selected items are not the same gear!" << endl;
                    }
                }

                // only first, gear slot is empty
                else if(first == nullptr && second != nullptr)
                {
                    if (cords1_prc[1] == get_gear_slot_index(second->slot_type)) // if slot is correct
                    {
                        battle_slots[cords1_prc[1]] = second;
                        tab[cords2_prc[0]][cords2_prc[1]] = nullptr;
                    } else
                    {
                        cout << "Wrong slot!" << endl;
                    }
                }

                // only second, general inventory slot is empty
                else if(first != nullptr && second == nullptr)
                {
                    battle_slots[cords1_prc[1]] = nullptr;
                    tab[cords2_prc[0]][cords2_prc[1]] = first;
                }

                // both are empty
                else if (first == nullptr && second == nullptr)
                {
                    cout << "Both slots are empty!" << endl;
                }
            }


            // if first input is in main and second in gear
            else if(cords1_prc[0] >= 0 && cords2_prc[0] == -1)
            {
                Item* first = tab[cords1_prc[0]][cords1_prc[1]];
                Item* second = battle_slots[cords2_prc[1]];

                //both slots are NOT empty
                if (first != nullptr && second != nullptr)
                {
                    if (first->slot_type == second->slot_type)
                    {
                        tab[cords1_prc[0]][cords1_prc[1]] = second;
                        battle_slots[cords2_prc[1]] = first;
                    } else
                    {
                        cout << "The selected items are not the same gear!" << endl;
                    }
                }

                // first, main slot is empty
                else if(first == nullptr && second != nullptr)
                {
                    tab[cords1_prc[0]][cords1_prc[1]] = second;
                    battle_slots[cords2_prc[1]] = nullptr;
                }

                // second, gear slot is empty
                else if(first != nullptr && second == nullptr)
                {
                    if (get_gear_slot_index(first->slot_type) == cords2_prc[1]) // correct slot
                    {
                        tab[cords1_prc[0]][cords1_prc[1]] = nullptr;
                        battle_slots[cords2_prc[1]] = first;
                    } else
                    {
                        cout << "Wrong slot!" << endl;
                    }
                }

                // both are empty
                else if (first == nullptr && second == nullptr)
                {
                    cout << "Both slots are empty!" << endl;
                }
            }


            // if both inputs are in general
            else if (cords1_prc[0] >= 0 && cords2_prc[0] >= 0)
            {

                Item* first = tab[cords1_prc[0]][cords1_prc[1]];
                Item* second = tab[cords2_prc[0]][cords2_prc[1]];

                // both NOT empty
                if (first != nullptr && second != nullptr)
                {
                    tab[cords1_prc[0]][cords1_prc[1]] = second;
                    tab[cords2_prc[0]][cords2_prc[1]] = first;
                }

                // first empty
                if (first == nullptr && second != nullptr)
                {
                    tab[cords1_prc[0]][cords1_prc[1]] = second;
                    tab[cords2_prc[0]][cords2_prc[1]] = nullptr;
                }

                // second empty
                if (first != nullptr && second == nullptr)
                {
                    tab[cords1_prc[0]][cords1_prc[1]] = nullptr;
                    tab[cords2_prc[0]][cords2_prc[1]] = first;
                }

                // both are empty
                else if (first == nullptr && second == nullptr)
                {
                    cout << "Both slots are empty!" << endl;
                }
            }
        } else
        {
            cout << "Your input is invalid!" << endl;
        }
    }
    
    void getInfo(string cords)
    {
        if (is_valid_cords_input(cords) >= 0)
        {
            vector<int> cords_prc = get_processed_cords(cords);
            
            // in main
            if (cords_prc[0] >= 0)
            {
                tab[cords_prc[0]][cords_prc[1]]->get_data();
            }
            
            // in gear
            else if (cords_prc[0] == -1)
            {
                battle_slots[cords_prc[0]]->get_data();
            }
            
        } else
        {
            cout << "Your input is invalid!" << endl;
        }
    }

    ~Inventory()
    {
        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < cols; j++)
            {
                delete[] tab[i][j];
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

class Items
{
public:
    vector<Item> item_list;

    Items()
    {
        item_list = {
            Item(1, "Wood", "W", "Resourse", "General", "Common"),
            Item(1, "Stone", "S", "Resourse", "General", "Common"),
            Item(1, "Metal", "M", "Resourse", "General", "Uncommon"),
            Item(1, "Rope", "R", "Resourse", "General", "Uncommon"),
            Item(1, "Stick", "S", "Resourse", "General", "Common")
        };
    }

    int getRandomIndex()
    {
        srand(time(NULL));
        return rand() % item_list.size();
    }

    Item getRandomItem()
    {
        return item_list[getRandomIndex()];
    }

    void setRandomAmount(int itemIndex) // can be specific or random
    {
        srand(time(NULL));

        for (int i = 0; i < item_list.size(); i++)
        {
            int randAmount = rand() % 5 + 1;
            item_list[i].amount = randAmount;
        }
    }

};

int main()
{

    Inventory I;

    I.add_item(2, 4, Item(0, "", "1"));
    I.add_item(4, 1, Item(0, "", "2"));
    I.add_item(3, 8, Item(0, "", "3"));
    I.add_item(1, 4, Item(0, "", "4"));
    I.add_gear_to_main(1, 1, Boots(0, "", "B"));
    I.add_gear_to_main(1, 6, Weapon(0, "", "W"));

    I.display();

    //I.swap_items("#5", "A6");
    //I.display();
    //I.swap_items("#5", "D1");
    I.swap_items("D2", "#3");


    I.display();
    return 0;
}

