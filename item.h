#ifndef ITEM_H
#define ITEM_H
#include <string>
#include <vector>
#include "rarity.h"


using namespace std;



class Item
{
public:
    string name;
    string display_name;
    string slot_type;
    string rarity;
    int price;
    int worth;
    vector<Item> components;
    int base_damage;
    int base_defence;

    int actual_damage;
    int actual_defence;


    Item(string name = "", string display_name = "", string slot_type = "general", string rarity = "Common", int price = 0, int worth = 0,
         vector<Item> components = {}, int base_damage = 0, int base_defence = 0)
        :  name{name}, display_name{display_name}, slot_type{slot_type}, rarity{rarity}, price{price}, worth{worth},
        components(components), base_damage(base_damage), base_defence(base_defence)
    {
        applyToItem();
    }

    void get_data()
    {
        if(display_name == "")
        {
            cout << "This is an empty item!" << endl;
        }
        else
        {
            cout << "  Name: " << name << endl;
            cout << "  Type: " << slot_type << endl;
            cout << "  Rarity: " << rarity << endl;
            cout << "  Worth: " << worth << endl;
            if (base_damage > 0)
            {
                cout << "  Damage: " << actual_damage << endl;
            }
            else if (base_defence > 0)
            {
                cout << "  Defence: " << actual_defence << endl;
            }
        }


    }

    void applyToItem()
    {
        Rarities r;
        r.applyRarity<Item>(this);
    }

};

#endif // ITEM_H
