#ifndef INVENTORY_H
#define INVENTORY_H
#include <iostream>
#include <map>
#include "item.h"

using namespace std;

class Inventory //Inventory Class
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


    Inventory(int rows = 4, int cols = 9); //Inventory Constructor


    // this one creates a map (dictionary) of letters and their matching indexes
    // depending on amound of rows. example: 'A': 0, 'B': 1 and so on until the amout is equeal to rows
    void fill_row_indexes();


    // indexes of gear slots // used in swap items
    void fill_gear_slots();


    // is used to return a number value that corelates to an Item slot type in gear_slots
    int get_gear_slot_index(string item_slot_type);


    // displays out inventory with every item that's in there
    void display();


    void displayGold();

    void increaseGold(int amount);

    void decreaseGold(int amount);


    // adds an item to the inventory // user won't be able to specify where the items will be added because he sohouldn't be able to
    void add_item(int row_cords, int col_cords, const Item& itemToAdd);

    // returns processed cord
    auto get_processed_cords(string cords) -> vector<int>;


    int is_valid_cords_input(string cords);


    string swap_items(string cords1, string cords2);


    string delete_an_item(string cords);


    string getInfo(string cords);


    vector<int> getFirstEmptySlot();


    string upgradeAnItem(string cords, int* playerGold);


    string disassembleAnItem(string cords);


    ~Inventory();
};

#endif // INVENTORY_H
