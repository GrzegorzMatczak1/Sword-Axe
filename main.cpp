#include <iostream>
#include <cstdlib>
#include <time.h>
#include <map>
#include <vector>
#include <string>
#include "item.h"
#include "inventory.h"

using namespace std;

int main()
{
    
    Inventory I;

    I.add_item(2, 4, Item(0, "", "1"));
    I.add_item(4, 1, Item(0, "", "2"));
    I.add_item(3, 8, Item(0, "", "3"));
    I.add_item(1, 4, Item(0, "", "4"));
    I.add_gear_to_main(1, 1, Boots(0, "", "B"));
    I.add_gear_to_main(1, 6, Weapon(0, "", "W"));

    I.display();

    //I.swap_items();


    I.display();
    return 0;
}
