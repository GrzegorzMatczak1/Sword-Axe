#ifndef INVENTORY_H
#define INVENTORY_H
#include <iostream>
#include <map>
#include <vector>
#include "item.h"

using namespace std;

class Inventory //Inventory Class
{
public:
    Item*** tab;
    Item** battle_slots;
    int rows;
    int cols;
    int gold;
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


    // adds an item to the inventory // user won't be able to specify where the items will be added because he sohouldn't be able to
    void add_item(int row_cords, int col_cords, const Item& itemToAdd);


    void add_gear_to_main(int row_cords, int col_cords, const Gear& gearToAdd);


    // returns processed cord
    auto get_processed_cords(string cords) -> vector<int>;


    int is_valid_cords_input(string cords);


    void swap_items(string cords1, string cords2);


    void getInfo(string cords);

    void add_gold(int ammount);


    ~Inventory();
};

#endif // INVENTORY_H
