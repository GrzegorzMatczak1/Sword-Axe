#ifndef ITEM_H
#define ITEM_H
#include <string>
#include <vector>

using namespace std;

class Item
{
public:
    int amount;
    int max_amount;
    string name;
    string display_name;
    string item_type;
    string slot_type;
    string rarity;

    Item(int amount = 0, string name = "", string display_name = "", string item_type = "", string slot_type = "general", string rarity = "common");

    virtual void get_data() const;
};


class Gear : public Item
{
public:
    vector<Item> components;

    Gear(int amount = 0, string name = "", string display_name = "", string item_type = "", string slot_type = "gear", string rarity = "common", vector<Item> components = {});

};


class Weapon : public Gear
{
public:
    int base_damage;
    int actual_damage;
    float crit_chance;

    Weapon(int amount = 0, string name = "", string display_name = "", string item_type = "", string slot_type = "weapon",
           string rarity = "common", vector<Item> components = {}, int base_damage = 0, float crit_chance = 0.0)
        : Gear(amount, name, display_name, item_type, slot_type),
        base_damage(base_damage), crit_chance(crit_chance) {}

    void get_data() const override;
};

class Shield : public Gear
{
public:
    int base_defence;
    int actual_defence;

    Shield(int amount = 0, string name = "", string display_name = "", string item_type = "", string slot_type = "shield", string rarity = "common", vector<Item> components = {}, int base_defence = 0)
        : Gear(amount, name, display_name, item_type, slot_type, rarity, components), base_defence(base_defence) {}

    void get_data() const override;
};

class Armor : public Gear
{
public:
    int base_defence;
    int actual_defence;

    Armor(int amount = 0, string name = "", string display_name = "", string item_type = "", string slot_type = "armor",
          string rarity = "common", vector<Item> components = {}, int base_defence = 0)
        : Gear(amount, name, display_name, item_type, slot_type, rarity, components), base_defence(base_defence) {}


};

class Helmet : public Armor
{
public:
    Helmet(int amount = 0, string name = "none", string display_name = "", string item_type = "", string slot_type = "helmet",
           string rarity = "common", vector<Item> components = {}, int base_defence = 0)
        : Armor(amount, name, display_name, item_type, slot_type, rarity, components, base_defence) {}
    void get_data() const override;
};

class Chestplate : public Armor
{
public:
    Chestplate(int amount = 0, string name = "none", string display_name = "", string item_type = "", string slot_type = "chestplate",
               string rarity = "common", vector<Item> components = {}, int base_defence = 0)
        : Armor(amount, name, display_name, item_type, slot_type, rarity, components, base_defence) {}
    void get_data() const override;
};

class Leggins : public Armor
{
public:
    Leggins(int amount = 0, string name = "none", string display_name = "", string item_type = "", string slot_type = "leggins",
            string rarity = "common", vector<Item> components = {}, int base_defence = 0)
        : Armor(amount, name, display_name, item_type, slot_type, rarity, components, base_defence) {}
    void get_data() const override;
};

class Boots : public Armor
{
public:
    Boots(int amount = 0, string name = "none", string display_name = "", string item_type = "", string slot_type = "boots",
          string rarity = "common", vector<Item> components = {}, int base_defence = 0)
        : Armor(amount, name, display_name, item_type, slot_type, rarity, components, base_defence) {}
    void get_data() const override;
};

#endif // ITEM_H
