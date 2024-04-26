#include <iostream>
#include "item.h"
#include "rarity.h"

using namespace std;

Item::Item(string name, string display_name, string slot_type, string rarity, int price, int worth)
    :  name{name}, display_name{display_name}, slot_type{slot_type}, rarity{rarity}, price{price}, worth{worth}
{
    Rarities r;

    //r.applyRarity<Item>(this);
}

Gear::Gear(string name, string display_name, string slot_type, string rarity, int price, int worth,
           vector<Item> components) : Item(name, display_name, slot_type, rarity, price, worth), components(components) {}

void Item::get_data() const
{
    cout << "Name: " << this->name << endl;
    cout << "Type: " << this->slot_type << endl;
    cout << "Rarity: " << this->rarity << endl;
    cout << "Worth: " << this->worth << endl;
}

void Weapon::get_data() const
{
    cout << "Name: " << this->name << endl;
    cout << "Type: " << this->slot_type << endl;
    cout << "Rarity: " << this->rarity << endl;
    cout << "Worth: " << this->worth << endl;
    cout << "Damage: " << this->actual_damage << endl;
}

void Shield::get_data() const
{
    cout << "Name: " << this->name << endl;
    cout << "Type: " << this->slot_type << endl;
    cout << "Rarity: " << this->rarity << endl;
    cout << "Worth: " << this->worth << endl;
    cout << "Defence: " << this->actual_defence << endl;
}

void Helmet::get_data() const
{
    cout << "Name: " << this->name << endl;
    cout << "Type: " << this->slot_type << endl;
    cout << "Rarity: " << this->rarity << endl;
    cout << "Worth: " << this->worth << endl;
    cout << "Defence: " << this->actual_defence << endl;
}
void Chestplate::get_data() const
{
    cout << "Name: " << this->name << endl;
    cout << "Type: " << this->slot_type << endl;
    cout << "Rarity: " << this->rarity << endl;
    cout << "Worth: " << this->worth << endl;
    cout << "Defence: " << this->actual_defence << endl;
}
void Leggins::get_data() const
{
    cout << "Name: " << this->name << endl;
    cout << "Type: " << this->slot_type << endl;
    cout << "Rarity: " << this->rarity << endl;
    cout << "Worth: " << this->worth << endl;
    cout << "Defence: " << this->actual_defence << endl;
}
void Boots::get_data() const
{
    cout << "Name: " << this->name << endl;
    cout << "Type: " << this->slot_type << endl;
    cout << "Rarity: " << this->rarity << endl;
    cout << "Worth: " << this->worth << endl;
    cout << "Defence: " << this->actual_defence << endl;
}
