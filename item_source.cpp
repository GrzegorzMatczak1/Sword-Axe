#include <iostream>
#include "item.h"

using namespace std;

Item::Item(int amount, string name, string display_name, string item_type, string slot_type, string rarity)
    : amount{amount}, name{name}, display_name{display_name}, item_type{item_type}, slot_type{slot_type}, rarity{rarity} {}

Gear::Gear(int amount, string name, string display_name, string item_type, string slot_type,
           int durability, string quality) : Item(amount, name, display_name, item_type, slot_type) {}

void Item::get_data() const
{
    cout << "Name: " << this->name << endl;
    cout << "Amount: " << this->amount << endl;
    cout << "Type: " << this->item_type << endl;
}

void Weapon::get_data() const
{
    Item::get_data();
    cout << "Damage: " << this->actual_damage << endl;
    cout << "Crit chance: " << this->crit_chance << endl;
}

void Armor::get_data() const
{
    Item::get_data();
    cout << "Defence: " << this->actual_defence << endl;
}

void Shield::get_data() const
{
    Item::get_data();
    cout << "Defence: " << this->actual_defence << endl;
}
