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
    string item_type;
    string slot_type;
    string rarity;


    Item(string name = "", string display_name = "", string slot_type = "general", string rarity = "common");

    virtual void get_data() const;
};


class Gear : public Item
{
public:
    vector<Item> components;

    Gear(string name = "", string display_name = "", string slot_type = "gear", string rarity = "common", vector<Item> components = {});

};


class Weapon : public Gear
{
public:
    int base_damage;
    int actual_damage;
    float crit_chance;

    Weapon(string name = "", string display_name = "", string slot_type = "weapon",
           string rarity = "common", vector<Item> components = {}, int base_damage = 0)
        : Gear(name, display_name, slot_type),
        base_damage(base_damage) {

        Rarities r;

        //r.applyRarity<Weapon>(this);
    }

    void get_data() const override;
};

class Shield : public Gear
{
public:
    int base_defence;
    int actual_defence;

    Shield(string name = "", string display_name = "", string slot_type = "shield",
           string rarity = "common", vector<Item> components = {}, int base_defence = 0)
        : Gear(name, display_name, slot_type, rarity, components), base_defence(base_defence) {

        Rarities r;

        //r.applyRarity<Shield>(this);
    }

    void get_data() const override;
};

class Armor : public Gear
{
public:
    int base_defence;
    int actual_defence;

    Armor(string name = "", string display_name = "", string slot_type = "armor",
          string rarity = "common", vector<Item> components = {}, int base_defence = 0)
        : Gear(name, display_name, slot_type, rarity, components), base_defence(base_defence) {

        Rarities r;

        //r.applyRarity<Armor>(this);
    }


};

class Helmet : public Armor
{
public:
    Helmet(string name = "none", string display_name = "", string slot_type = "helmet",
           string rarity = "common", vector<Item> components = {}, int base_defence = 0)
        : Armor(name, display_name, slot_type, rarity, components, base_defence) {

    }
    void get_data() const override;
};

class Chestplate : public Armor
{
public:
    Chestplate(string name = "none", string display_name = "", string slot_type = "chestplate",
               string rarity = "common", vector<Item> components = {}, int base_defence = 0)
        : Armor(name, display_name, slot_type, rarity, components, base_defence) {}
    void get_data() const override;
};

class Leggins : public Armor
{
public:
    Leggins(string name = "none", string display_name = "", string slot_type = "leggins",
            string rarity = "common", vector<Item> components = {}, int base_defence = 0)
        : Armor(name, display_name, slot_type, rarity, components, base_defence) {}
    void get_data() const override;
};

class Boots : public Armor
{
public:
    Boots(string name = "none", string display_name = "", string slot_type = "boots",
          string rarity = "common", vector<Item> components = {}, int base_defence = 0)
        : Armor(name, display_name, slot_type, rarity, components, base_defence) {}
    void get_data() const override;
};



#endif // ITEM_H
