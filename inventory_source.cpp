#include <iostream>
#include <iomanip>
#include "inventory.h"
#include <vector>

using namespace std;

Inventory::Inventory(int rows, int cols) : rows{rows}, cols{cols}
{
    letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    gold = 250;
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

void Inventory::fill_row_indexes()
{
    int numeric_value_of_capital_letter = 65;
    for (int i = 0; i < rows; i++)
    {
        row_indexes[char(numeric_value_of_capital_letter)] = i;
        numeric_value_of_capital_letter++;
    }
}

void Inventory::fill_gear_slots()
{
    gear_slots["helmet"] = 0;
    gear_slots["chestplate"] = 1;
    gear_slots["leggins"] = 2;
    gear_slots["boots"] = 3;
    gear_slots["weapon"] = 4;
    gear_slots["shield"] = 5;
}

void Inventory::display()
{
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

void Inventory::displayGold()
{
    cout << "  Gold: " << this->gold << endl;
}

void Inventory::increaseGold(int amount)
{
    this->gold += amount;
}

void Inventory::decreaseGold(int amount)
{
    if (this->gold < amount)
    {
        this->gold = 0;
    }
    else
    {
        this->gold -= amount;
    }
}

int Inventory::get_gear_slot_index(string item_slot_type)
{
    for (const auto& pair : this->gear_slots) {
        if (item_slot_type == pair.first)
        {
            return pair.second;
        }
    }
    return -1;
}

void Inventory::add_item(int row_cords, int col_cords, const Item& itemToAdd)
{
    tab[row_cords - 1][col_cords - 1] = new Item(itemToAdd);
}

auto Inventory::get_processed_cords(string cords) -> vector<int>
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

int Inventory::is_valid_cords_input(string cords)
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

string Inventory::swap_items(string cords1, string cords2)
{
    if (is_valid_cords_input(cords1) >= 0 && is_valid_cords_input(cords2) >= 0)
    {
        // indexes -  do not corelate with numbers in console display // prc = processed (integer indexes)

        vector<int> cords1_prc = get_processed_cords(cords1); // list[0] - row ; list[1] - col
        vector<int> cords2_prc = get_processed_cords(cords2);

        auto successMessage = []() -> string
        {
            return "Swap successful.";
        };

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

                    return successMessage();
                } else
                {
                    return "The selected items are not the same gear! Swap unsuccessful.";
                }
            }

            // only first, gear slot is empty
            else if(first == nullptr && second != nullptr)
            {
                if (cords1_prc[1] == get_gear_slot_index(second->slot_type)) // if slot is correct
                {
                    battle_slots[cords1_prc[1]] = second;
                    tab[cords2_prc[0]][cords2_prc[1]] = nullptr;

                    return successMessage();
                } else
                {
                    return "Wrong slot! Swap unsuccessful.";
                }
            }

            // only second, general inventory slot is empty
            else if(first != nullptr && second == nullptr)
            {
                battle_slots[cords1_prc[1]] = nullptr;
                tab[cords2_prc[0]][cords2_prc[1]] = first;

                return successMessage();
            }

            // both are empty
            else if (first == nullptr && second == nullptr)
            {
                return "Both slots are empty! Swap unsuccessful.";
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

                    return successMessage();
                } else
                {
                    return "The selected items are not the same gear! Swap unsuccessful.";
                }
            }

            // first, main slot is empty
            else if(first == nullptr && second != nullptr)
            {
                tab[cords1_prc[0]][cords1_prc[1]] = second;
                battle_slots[cords2_prc[1]] = nullptr;

                return successMessage();
            }

            // second, gear slot is empty
            else if(first != nullptr && second == nullptr)
            {
                if (get_gear_slot_index(first->slot_type) == cords2_prc[1]) // correct slot
                {
                    tab[cords1_prc[0]][cords1_prc[1]] = nullptr;
                    battle_slots[cords2_prc[1]] = first;

                    return successMessage();
                } else
                {
                    return "Wrong slot! Swap unsuccessful.";
                }
            }

            // both are empty
            else if (first == nullptr && second == nullptr)
            {
                return "Both slots are empty! Swap unsuccessful.";
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

                return successMessage();
            }

            // first empty
            if (first == nullptr && second != nullptr)
            {
                tab[cords1_prc[0]][cords1_prc[1]] = second;
                tab[cords2_prc[0]][cords2_prc[1]] = nullptr;

                return successMessage();
            }

            // second empty
            if (first != nullptr && second == nullptr)
            {
                tab[cords1_prc[0]][cords1_prc[1]] = nullptr;
                tab[cords2_prc[0]][cords2_prc[1]] = first;

                return successMessage();
            }

            // both are empty
            else if (first == nullptr && second == nullptr)
            {
                return "Both slots are empty! Swap unsuccessful.";
            }
        }
    } else
    {
        return "Your input is invalid! Swap unsuccessful.";
    }
    return "Hi!";
}


string Inventory::delete_an_item(string cords)
{
    // input is valid
    if (is_valid_cords_input(cords) >= 0)
    {
        vector<int> cords_prc = get_processed_cords(cords);

        // in general
        if (cords_prc[0] >= 0)
        {

            if (tab[cords_prc[0]][cords_prc[1]] != nullptr)
            {
                delete tab[cords_prc[0]][cords_prc[1]];

                tab[cords_prc[0]][cords_prc[1]] = nullptr;

                return "Delete successful!";
            }
            else
            {
                return "The slot is empty! Delete unsuccessful!";
            }
        }
        // in gear
        else if(cords_prc[0] == -1)
        {

            if (battle_slots[cords_prc[1]] != nullptr)
            {
                delete battle_slots[cords_prc[1]];

                battle_slots[cords_prc[1]] = nullptr;

                return "Delete successful!";
            }
            else
            {
                return "The slot is empty! Delete unsuccessful!";
            }
        }
        else
        {
            return "Some kind of error! Delete unsuccessful.";
        }
    }
    else
    {
        return "Invalid input! Delete unsuccessful.";
    }
}


string Inventory::getInfo(string cords)
{
    if (is_valid_cords_input(cords) >= 0)
    {
        vector<int> cords_prc = get_processed_cords(cords);

        Item* item;

        if (cords_prc[0] >= 0)
        {
            if (tab[cords_prc[0]][cords_prc[1]] != nullptr)
            {
                item = tab[cords_prc[0]][cords_prc[1]];
            }
            else
            {
                return "The slot is empty!";
            }
        }
        else if (cords_prc[0] == -1)
        {
            if (battle_slots[cords_prc[1]] != nullptr)
            {
                item = battle_slots[cords_prc[1]];
            }
            else
            {
                return "The slot is empty!";
            }
        }
        else
        {
            return "Invalid input!";
        }

        item->get_data();
        return "Inspection successful!";

    }
    else
    {
        return "Your input is invalid!";
    }
}

vector<int> Inventory::getFirstEmptySlot()
{
    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < this->cols; j++)
        {
            return {rows, cols};
        }
    }
    return {-1, -1}; // inventory full
}

string Inventory::upgradeAnItem(string cords, int* playerGold)
{
    Rarities r;
    vector<Rarity> rarities = r.rarities;

    if (is_valid_cords_input(cords) >= 0)
    {
        vector<int> cords_prc = get_processed_cords(cords);

        if (cords_prc[0] >= 0) // main eq
        {
            Item* item = tab[cords_prc[0]][cords_prc[1]];

            if (item->rarity == "Legendary")
            {
                return "Max rarity. Can't upgrade.";
            }

            for (int i = 0; i < rarities.size(); i++)
            {
                if (rarities[i].name == item->rarity)
                {
                    int cost = rarities[i+1].cost;
                    if (cost > *playerGold)
                    {
                        return "Cant afford!";
                    }
                    else
                    {
                        item->rarity = rarities[i+1].name;
                        *playerGold -= cost;
                        return "Upgraded an item to " + item->rarity + " for " + to_string(cost) + " gold.";
                    }
                }
            }
            return "Undefined rarity.";
        }

        else if(cords_prc[0] == -1) // gear eq
        {
            Item* item = battle_slots[cords_prc[1]];

            if (item->rarity == "Legendary")
            {
                return "Max rarity. Can't upgrade.";
            }

            for (int i = 0; i < rarities.size(); i++)
            {
                if (rarities[i].name == item->rarity)
                {
                    int cost = rarities[i+1].cost;
                    if (cost > *playerGold)
                    {
                        return "Cant afford!";
                    }
                    else
                    {
                        item->rarity = rarities[i+1].name;
                        *playerGold -= cost;
                        return "Upgraded an item to " + item->rarity + " for " + to_string(cost) + " gold.";
                    }
                }
            }
            return "Undefined rarity.";
        }
    }
    else
    {
        return "Invalid input! Upgrade unsuccessful.";
    }
    return "Hi!";
}


string Inventory::disassembleAnItem(string cords)
{

    return "";

}

Inventory::~Inventory()
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
