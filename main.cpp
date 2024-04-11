#include <iostream>
#include <cstdlib>
#include <time.h>
#include <map>
#include <vector>
#include <string>
#include <windows.h>
#include "item.h"
#include "inventory.h"


using namespace std;

class Items
{
public:
    vector<Item> item_list;

    Items()
    {
        item_list = {
            Item(1, "Wood", "W", "Resourse", "General", "Common"),
            Item(1, "Stone", "S", "Resourse", "General", "Common"),
            Item(1, "Metal", "M", "Resourse", "General", "Uncommon"),
            Item(1, "Rope", "R", "Resourse", "General", "Uncommon"),
            Item(1, "Stick", "S", "Resourse", "General", "Common")
        };
    }

    int getRandomIndex()
    {
        srand(time(NULL));
        return rand() % item_list.size();
    }

    Item getRandomItem()
    {
        return item_list[getRandomIndex()];
    }

    void setRandomAmount(int itemIndex) // can be specific or random
    {
        srand(time(NULL));

        for (int i = 0; i < item_list.size(); i++)
        {
            int randAmount = rand() % item_list.size() + 1;
            item_list[i].amount = randAmount;
        }
    }
};

class Game
{
public:
    Inventory* I;
    bool isRunning;
    string currentOperation;
    string mostRecentOperation;
    enum class Operations
    {
        Default,
        Swap,
        Inspect
    };
    map<Operations, string> typesOfOperations;

    Game()
    {
        I = new Inventory();
        isRunning = true;

        // this all will basically be used for displaying specific operations
        // when we select some, the terminal will be cleared and display the specific menu
        // that way we have only what's necessary on display
        // example: during inputing an item to inspect, we don't need to have a shop displayed

        typesOfOperations[Operations::Default] = "default"; // display main menu
        typesOfOperations[Operations::Swap] = "swap";
        typesOfOperations[Operations::Inspect] = "inspect";

        //we'll probably need to add: delete/disassemble, exit menu, shop, blacksmith, combat(fighting enemies or whatever) and maybe something else
    }

    void run()
    {
        do {
            gameDisplay();
        } while(isRunning);

        clear();
        cout << "Thanks for playing!" << endl;
    }

    void gameDisplay()
    {
        Operations op = Operations::Default;//getCurrentOperation(currentOperation);
        switch (op)
        {
        case Operations::Default:
            mainMenu();
            break;
        case Operations::Swap:
            swapMenu();
            break;
        case Operations::Inspect:
            inspectMenu();
            break;
        default:
            cout << "Some kind of error!" << endl;
        }
    }

    Operations getCurrentOperation(string currentOperation)
    {
        for (const auto& pair : typesOfOperations)
        {
            if (pair.second == currentOperation)
            {
                return pair.first; // returns a enum operation value // will be used in gameDisplay
            }
        }
    }

    void mainMenu()
    {
        clear();

        cout << endl << "  Inventory:" << endl;
        I->display();
        cout << endl;

        cout << endl << "  Possible actions:" << endl;
        cout << "  1. Swap items." << endl;
        cout << "  2. Inspect an item." << endl;
        cout << "  3. Drop an item" << endl;
        cout << "  4. Exit game." << "\n\n";

        cout << "  Input:" << endl;

    }

    void swapMenu()
    {
    // nothing yet
    }

    void inspectMenu()
    {
    // work in progress
    }

    void logsDisplay()
    {
        cout << "-----------------------------------------" << endl;
        cout << mostRecentOperation << endl;
    }

    void clear()
    {
        system("cls");
    }

    ~Game()
    {
        delete I;
    }
};
/*

*/
int main()
{
    Game game;
    game.gameDisplay();

    Inventory I;

    //I.add_item(2, 4, Item(0, "", "1"));
    //I.add_item(4, 1, Item(0, "", "2"));
    //I.add_item(3, 8, Item(0, "", "3"));
    //I.add_item(1, 4, Item(0, "", "4"));
    //I.add_gear_to_main(1, 1, Boots(0, "", "B"));
    //I.add_gear_to_main(1, 6, Weapon(0, "", "W"));

    //I.display();

    //I.swap_items();

    //I.display();
    return 0;
}

