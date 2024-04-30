#ifndef INVENTORY_H
#define INVENTORY_H
#include <iostream>
#include <map>
#include "item.h"

using namespace std;

class Inventory
{
public:
    Item*** tab;
    Item** battle_slots;
    int gold;
    int rows;
    int cols;
    string letters;
    map<char, int> row_indexes;
    map<string, int> gear_slots;

    Inventory(int rows = 4, int cols = 9);


    void fill_row_indexes();


    void fill_gear_slots();


    int get_gear_slot_index(string item_slot_type);


    void display();


    void displayGold();


    void add_item(int row_cords, int col_cords, const Item& itemToAdd);


    auto get_processed_cords(string cords) -> vector<int>;


    int is_valid_cords_input(string cords);


    string swap_items(string cords1, string cords2);


    string delete_an_item(string cords);


    string getInfo(string cords);


    vector<int> getFirstEmptySlot();


    string upgradeAnItem(string cords, int* playerGold);


    string disassembleAnItem(string cords);


    void displayItemComponents(string cords);

    string validItem(string cords);

    string sellAnItem(string cords);


    ~Inventory();
};

#endif // INVENTORY_H
