#include <iostream>
#include <cstdlib>
#include <time.h>
#include <map>
#include <vector>
#include <string>
#include "item.h"
#include "inventory.h"
#include "items.h"

// for platform specific functionality //  for now only clear() method in Game
#if defined(_WIN32)
#define PLATFORM_WINDOWS
#elif defined(__APPLE__)
#define PLATFORM_MACOS
#else
#endif


using namespace std;

class Shop
{
public:
    bool inShop;
    vector<string> itemChoices;
    Item*** shopItems;
    int rows;
    int cols;


    Shop()
    {
        rows = 3;
        cols = 5;
        inShop = true;
        itemChoices = {
            "item", "weapon", "shield", "helmet", "chestplate", "leggins", "boots"
        };
    }

    int getRandomIndex()
    {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, itemChoices.size() - 1);
        return dis(gen);
    }

    void fillShopItems()
    {

    }

    void shop()
    {

    }
};

class Game
{
public:
    Inventory* I;
    bool isRunning;
    string currentOperation;
    string logsMessage;
    enum class Operations
    {
        Default,
        Swap,
        Inspect,
        Drop,
        Blacksmith,
        Upgrade,
        Disassemble,
        
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
        Weapons W;
        Helmets H;
        Shields S;

        I->add_item(2, 4, It.getRandomItem());
        I->add_item(4, 1, It.getRandomItem());
        I->add_item(3, 8, It.getRandomItem());
        I->add_item(1, 4, It.getRandomItem());
        I->add_item(1, 1, W.getRandomItem());
        I->add_item(1, 6, H.getRandomItem());
        I->add_item(3, 3, S.getRandomItem());


        typesOfOperations[Operations::Default] = "default"; // display main menu
        typesOfOperations[Operations::Swap] = "swap";
        typesOfOperations[Operations::Inspect] = "inspect";
        typesOfOperations[Operations::Drop] = "drop";
        typesOfOperations[Operations::Blacksmith] = "blacksmith";
        typesOfOperations[Operations::Upgrade] = "upgrade";
        typesOfOperations[Operations::Disassemble] = "disassemble";

        typesOfOperations[Operations::Exit] = "exit";

        }

    void run()
    {
        while(isRunning){
            clear();
            gameDisplay();
        }

        clear();

        cout << endl;
        cout << "-----------------------------------------" << endl;
        cout << "  Thanks for playing!" << endl;
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
        case Operations::Blacksmith:
            blacksmithMenu();
            break;
        case Operations::Upgrade:
            upgradeMenu();
            break;
        case Operations::Disassemble:
            disassembleSelectMenu();
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
                return pair.first;
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
        cout << "  4. Visit the blacksmith" << endl;
        cout << "  exit. Exit game." << "\n\n";

        string input;
        cout << "  Input: ";
        cin >> input;
        cout << endl;

        if (input == "1")
        {
            currentOperation = "swap";
            logsMessage = "Item swapping!";
        }
        else if (input == "2")
        {
            currentOperation = "inspect";
            logsMessage = "Item inspecting!";
        }
        else if (input == "3")
        {
            currentOperation = "drop";
            logsMessage = "Item dropping!";
        }
        else if (input == "4")
        {
            currentOperation = "blacksmith";
            logsMessage = "Welcome to the blacksmith!";
        }

        else if (input == "exit")
        {
            currentOperation = "exit";
        }
        else
        {
            logsMessage = "Couldn't pick an option. Your input must be invalid! Try typing a number!";
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
        inventoryDisplay();

        string input;
        cout << "  Select an item: ";
        cin >> input;

        cout << endl;

        logsMessage = I->getInfo(input);

        cout << endl;
        string input1;
        cout << "  Type anything to continue: ";
        cin >> input1;

        currentOperation = "default";
    }

    void blacksmithMenu()
    {
        inventoryDisplay();

        cout << "  Chose an operation you'd like to perform." << endl;
        cout << "  1. Upgrade an item." << endl;
        cout << "  2. Disassemble an item." << endl;
        cout << "  3. Exit." << endl << endl;

        string input;
        cout << "  Input: ";
        cin >> input;

        if (input == "1")
        {
            logsMessage = "Upgrading!";
            currentOperation = "upgrade";
        }
        else if (input == "2")
        {
            logsMessage = "Disassembling!";
            currentOperation = "disassemble";
        }
        else if (input == "3")
        {
            logsMessage = "Blacksmith exited.";
            currentOperation = "default";
        }
        else
        {
            logsMessage = "Nonexistent input! Try again.";
            currentOperation = "blacksmith";
        }
    }

    void upgradeMenu()
    {
        inventoryDisplay();
        I->displayGold();

        cout << endl << "  Costs:"  << endl;
        cout << "  Common->Uncommon - 15" << endl;
        cout << "  Uncommon->Rare - 25" << endl;
        cout << "  Rare->Epic - 35" << endl;
        cout << "  Common->Uncommon - 50" << endl << endl;

        string input;
        cout << "  Select an item to upgrade: ";
        cin >> input;

        logsMessage = I->upgradeAnItem(input, &I->gold);

        currentOperation = "blacksmith";
    }

    void disassembleSelectMenu()
    {
        inventoryDisplay();
        
        string input;
        cout << "  Select an item to disassemble: ";
        cin >> input;
        cout << endl;
        
        if (I->validItem(input) != "correct")
        {
            logsMessage = I->validItem(input);
        }
        else
        {
            disassembleConfirmation(input);
        }
        
        currentOperation = "blacksmith";
    }
    
    void disassembleConfirmation(string userInput)
    {
        logsDisplay();
        inventoryDisplay();
        
        cout << endl << "  Selected item's components:" << "\n\n";
        I->displayItemComponents(userInput);
        cout << "\n\n";
        
        string choice;
        cout << "  Would you like to disassemble the item?  [y/n]  : ";
        cin >> choice;
        cout << endl;
        
        if (choice == "y")
        {
            logsMessage = I->disassembleAnItem(userInput);
        }
        else if (choice == "n")
        {
            logsMessage = "Canceled.";
        }
        else
        {
            logsMessage = "Invalid choice!";
            disassembleConfirmation(userInput);
        }
        
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
        cout << "--------------------------------------------------------------------------------" << endl;
        cout << "  " << logsMessage << endl;
        cout << "--------------------------------------------------------------------------------" << endl;
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

    Inventory I;
    Items It;

//    I.add_item(2, 4, It.getRandomItem());
//    I.add_item(4, 1, It.getRandomItem());
//    I.add_item(3, 8, It.getRandomItem());
//    I.add_item(1, 4, It.getRandomItem());
//    I.add_gear_to_main(1, 1, Boots("", "B"));
//    I.add_gear_to_main(1, 6, Weapon("Sigma", "W"));

//    cout << I.swap_items("A1", "#4") << endl;

//    I.display();

//    I.getInfo("D1");

    return 0;
}
