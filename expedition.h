#ifndef EXPEDITION_H
#define EXPEDITION_H
#include <string>
#include "item.h"
#include "inventory.h"

class Expedition
{
public:
    Item** player_inventory;
    Item** enemy_inventory;
    string enemy_name;


    int calculate_damage(int player_damage, int enemy_damage);


};



#endif // EXPEDITION_H
