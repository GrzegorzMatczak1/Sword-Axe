#include <iostream>
#include <cstdlib>
#include <time.h>
#include <map>
#include <vector>
#include <string>
#include "item.h"
#include "inventory.h"
#include <random>

// for platform specific functionality //  for now only clear() method in Game
#if defined(_WIN32)
#define PLATFORM_WINDOWS
#elif defined(__APPLE__)
#define PLATFORM_MACOS
#else
#endif


using namespace std;

class Items
{
public:
    vector<Item> item_list;

    Items()
    {
        item_list = {
            Item(1, "Wood", "W", "Resourse", "general", "Common"),
            Item(1, "Stone", "S", "Resourse", "general", "Common"),
            Item(1, "Metal", "M", "Resourse", "general", "Uncommon"),
            Item(1, "Rope", "R", "Resourse", "general", "Uncommon"),
            Item(1, "Stick", "S", "Resourse", "general", "Common")
        };
    }

    int getRandomIndex()
    {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, item_list.size() - 1); // nwm jak to działa. ale przynajmniej nie zwraca takich samych wartości jak sie wywoła kilka razy w tej samej sekundzie
        return dis(gen);
    }

    Item getRandomItem()
    {
        return item_list[getRandomIndex()];
    }

    void setRandomAmount(int itemIndex) // can be specific or random
    {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(1, item_list.size());

        for (int i = 0; i < item_list.size(); i++)
        {
            int randAmount = dis(gen);
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
    string logsMessage; // logs info //  example: "Swap successful", "Couldn't inspect an item. Wrong input!" etc
    enum class Operations
    {
        Default,
        Swap,
        Inspect,
        Drop,

        Exit,
        Error
    };
    map<Operations, string> typesOfOperations;

    Game()
    {
        I = new Inventory();
        isRunning = true;
        logsMessage = "Welcome!";
        currentOperation = "default";

        Items It;

        I->add_item(2, 4, It.getRandomItem());
        I->add_item(4, 1, It.getRandomItem());
        I->add_item(3, 8, It.getRandomItem());
        I->add_item(1, 4, It.getRandomItem());
        I->add_gear_to_main(1, 1, Boots(0, "", "B"));
        I->add_gear_to_main(1, 6, Weapon(0, "", "W"));

        // this all will basically be used for displaying specific operations
        // when we select some, the terminal will be cleared and display the specific menu
        // that way we have only what's necessary on display
        // example: during inputing an item to inspect, we don't need to have a shop displayed

        typesOfOperations[Operations::Default] = "default"; // display main menu
        typesOfOperations[Operations::Swap] = "swap";
        typesOfOperations[Operations::Inspect] = "inspect";
        typesOfOperations[Operations::Drop] = "drop";

        typesOfOperations[Operations::Exit] = "exit";

        //we'll probably need to add: delete/disassemble, exit menu, shop, blacksmith, combat(fighting enemies or whatever) and maybe something else
        }

    void run()
    {
        while(isRunning){
            clear();



            gameDisplay();
        }

        clear();

        clear();

        cout << endl;
        cout << "-----------------------------------------" << endl;
        cout << "Thanks for playing!" << endl;
        cout << "-----------------------------------------" << endl;
    }

    void gameDisplay()
    {

        logsDisplay();

        Operations op = getCurrentOperation(currentOperation);
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
        case Operations::Drop:
            dropMenu();
            break;

        case Operations::Exit:
            isRunning = !isRunning;
            break;
        case Operations::Error:
            cout << "Some kind of error!" << endl;
            break;
        default:
            cout << "Some kind of error!" << endl;
            break;
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
        return Operations::Error;
    }

    void mainMenu()
    {
        inventoryDisplay();

        cout << endl << "  Possible actions:" << endl;
        cout << "  1. Swap items." << endl;
        cout << "  2. Inspect an item." << endl;
        cout << "  3. Drop an item" << endl;
        cout << "  exit. Exit game." << "\n\n";

        string input;
        cout << "  Input: ";
        cin >> input;
        cout << endl;

        if (input == "1")
        {
            currentOperation = "swap";
        }
        else if (input == "2")
        {
            currentOperation = "inspect";
        }
        else if (input == "3")
        {
            currentOperation = "drop";
        }

        else if (input == "exit")
        {
            currentOperation = "exit";
        }
        else
        {
            logsMessage = "Couldn't pick an option. Your input must be invalid! Try typing a number next time!";
        }
    }

    void swapMenu()
    {
        inventoryDisplay();

        cout << endl << "  Enter two coordinates to swap." << endl;

        string cords1;
        string cords2;

        cout << "  First element: ";
        cin >> cords1;
        cout << endl;

        cout << "  Second element: ";
        cin >> cords2;
        cout << endl;

        logsMessage = I->swap_items(cords1, cords2);

        currentOperation = "default";
    }

    void inspectMenu()
    {
        // work in progress
    }

    void dropMenu()
    {
        inventoryDisplay();

        cout << endl << "  Enter coordinate to delete." << endl;

        string cords;

        cout << "  Delete an item: ";
        cin >> cords;
        cout << endl;

        logsMessage = I->delete_an_item(cords);

        currentOperation = "default";
    }

    void sortMenu()
    {
        // empty
    }

    void logsDisplay()
    {
        cout << "-----------------------------------------" << endl;
        cout << "  " << logsMessage << endl;
        cout << "-----------------------------------------" << endl;
        cout << "\n";
    }

    void inventoryDisplay()
    {
        cout << endl << "  Inventory:" << endl;
        I->display();
        cout << endl;
    }

    void clear()
    {
#ifdef PLATFORM_WINDOWS
        system("cls");
#elif defined(PLATFORM_MACOS)
        system("clear");
#else
#endif
    }

    ~Game()
    {
        delete I;
    }
};

int main()
{

    Game game;

    //game.gameDisplay();
    game.run();

    //Inventory I;
    //Items It;

    //I.add_item(2, 4, It.getRandomItem());
    //I.add_item(4, 1, It.getRandomItem());
    //I.add_item(3, 8, It.getRandomItem());
    //I.add_item(1, 4, It.getRandomItem());
    //I.add_gear_to_main(1, 1, Boots(0, "", "B"));
    //I.add_gear_to_main(1, 6, Weapon(0, "", "W"));

    return 0;
}
