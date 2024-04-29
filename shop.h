#ifndef SHOP_H
#define SHOP_H
#include <iostream>
#include <map>
#include "item.h"
#include "items.h"
#include "inventory.h"

using namespace std;

class Shop
{
public:
    Item*** shopItems;
    int rows;
    int cols;
    string letters;
    map<int, string> items;
    map<char, int> row_indexes;
    Items I;
    Weapons W;
    Shields S;
    Helmets H;
    Chestplates C;
    Legginses L;
    Bootses B;

    Shop()
    {
        letters = "ABC";
        rows = 3;
        cols = 5;

        shopItems = new Item**[rows];
        for(int i = 0; i < rows; i++)
        {
            shopItems[i] = new Item*[cols];
        }
        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < cols; j++)
            {
                shopItems[i][j] = nullptr;
            }
        }

        items[0] = "general";
        items[1] = "weapon";
        items[2] = "shield";
        items[3] = "helmet";
        items[4] = "chestplate";
        items[5] = "leggins";
        items[6] = "boots";

        fillShopItems();
        fill_row_indexes();
    }

    void display()
    {
        cout << "   ";
        for(int numeration = 0; numeration < cols; numeration++)
        {
            cout << " " << numeration + 1 << " ";
        }
        cout << endl << "  ";


        for (int i = 0; i < rows; i++)
        {
            cout << letters[i];
            for(int j = 0; j < cols; j++)
            {
                if(shopItems[i][j] == nullptr)
                {
                    cout << "[ ]";
                }
                else
                {
                    cout <<"[" << shopItems[i][j]->display_name << "]";
                }
            }
            cout << endl << "  ";
        }
    }

    string rerollShop(int* playerGold)
    {
        int rerollCost = 50;
        if (*playerGold >= rerollCost)
        {
            *playerGold -= rerollCost;
            clearShop();
            fillShopItems();
            return "Rerolled the shop stock!";
        }
        else
        {
            return "Not enough gold.";
        }
    }

    string buyAnItem(string cords, Inventory* I, int* playerGold)
    {
        if (is_valid_cords_input(cords) > 0)
        {
            vector<int> cords_prc = get_processed_cords(cords);
            Item* itemToBuy = shopItems[cords_prc[0]][cords_prc[1]];

            if (itemToBuy != nullptr)
            {
                int itemPrice = itemToBuy->price;

                if (*playerGold >= itemPrice)
                {
                    *playerGold -= itemPrice;
                    vector<int> firstFreeSlot = I->getFirstEmptySlot();

                    I->tab[firstFreeSlot[0]][firstFreeSlot[1]] = itemToBuy;
                    shopItems[cords_prc[0]][cords_prc[1]] = nullptr;

                    return "An item has been successfully bought!";
                }
                else
                {
                    return "Not enough money!";
                }
            }
            else
            {
                return "The selected item has already been bought!";
            }
        }
        else
        {
            return "The input is invalid!";
        }
        return "Hi!";
    }

    string check(string cords)
    {
        if (is_valid_cords_input(cords) > 0)
        {
            vector<int> cords_prc = get_processed_cords(cords);
            Item* itemToCheck = shopItems[cords_prc[0]][cords_prc[1]];

            if (itemToCheck != nullptr)
            {
                itemToCheck->get_data();
                return "Item info has been checked!";
            }
            else
            {
                return "The selected slot is empty!";
            }
        }
        else
        {
            return "The input is invalid!";
        }
        return "Hi!";
    }

    void clearShop()
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                delete shopItems[i][j];
                shopItems[i][j] = nullptr;
            }
        }
    }

    void fill_row_indexes()
    {
        int numeric_value_of_capital_letter = 65;
        for (int i = 0; i < rows; i++)
        {
            row_indexes[char(numeric_value_of_capital_letter)] = i;
            numeric_value_of_capital_letter++;
        }
    }

    int randomNumber(int min_range = 0, int max_range = 6) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distribution(min_range, max_range);
        return distribution(gen);
    }

    string getRandomItem()
    {
        int rand = randomNumber();
        auto getItemName = [](map<int, string> items, int rand) -> string
        {
            for (const auto& pair : items)
            {
                if (pair.first == rand)
                {
                    return pair.second;
                }
            }
            return "Hi";
        };

        return getItemName(items, rand);
    }

    void fillShopItems() // assuming shop is fully empty // always do clearShop() first
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                string randomItem = getRandomItem();

                if (randomItem == "general")
                {
                    shopItems[i][j] = new Item(I.getRandomItem());
                }
                else if (randomItem == "weapon")
                {
                    shopItems[i][j] = new Item(W.getRandomItem());
                }
                else if (randomItem == "shield")
                {
                    shopItems[i][j] = new Item(S.getRandomItem());
                }
                else if (randomItem == "helmet")
                {
                    shopItems[i][j] = new Item(H.getRandomItem());
                }
                else if (randomItem == "chestplate")
                {
                    shopItems[i][j] = new Item(C.getRandomItem());
                }
                else if (randomItem == "leggins")
                {
                    shopItems[i][j] = new Item(L.getRandomItem());
                }
                else if (randomItem == "boots")
                {
                    shopItems[i][j] = new Item(B.getRandomItem());
                }
            }
        }
    }

    auto get_processed_cords(string cords) -> vector<int>
    {
        auto process_cords_row = [this](string cords) -> int
        {
            char letter = char(cords[0]);

            if((int(letter) >= 65) && (int(letter) <= 90)) // from capital A-Z
            {
                for (const auto& pair : this->row_indexes) {
                    if (pair.first == letter)
                    {
                        return pair.second;
                    }
                }
            }
            return -1;
        };

        int cords_row = process_cords_row(cords);
        int cords_col = (cords[1] - '0') - 1;

        return {cords_row, cords_col};
    }

    int is_valid_cords_input(string cords)
    {
        if (cords.size() > 2 || cords.size() < 2)
        {
            return -1;
        }

        int cords_row = get_processed_cords(cords)[0];
        int cords_col = get_processed_cords(cords)[1];

        // in main
        if ((cords_row >= 0 && cords_row < this->rows) && (cords_col >= 0 && cords_col < this->cols))
        {
            return 1;
        }
        // out of range/complete nonsense
        else
        {
            return 0;
        }
    }

    ~Shop()
    {
        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < cols; j++)
            {
                delete[] shopItems[i][j];
            }
        }
        for(int i = 0; i < rows; i++)
        {
            delete[] shopItems[i];
        }
        delete[] shopItems;
    }
};

#endif // SHOP_H
