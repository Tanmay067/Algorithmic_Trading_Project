#include "market.h"
#include "heap.h"
#include "trie.h"
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

market::market(int argc, char **argv)
{
    File.open("output.txt", ios::in);
}

void market::start()
{
    if (!File)
        cout << "File doesn't exist.";
    else
    {
        string line;
        string temp;
        int decision = 0;
        // BHeap h;
        BHeap BUYheap;
        BHeap SELLheap;
        TrieNode *root = new TrieNode();
        int money = 0;
        int shares = 0;
        int trades = 0;
        vector<string> Brokers;

        node n = node();

        int start_time = 0;
        int end_time = 0;
        string Brokername;
        string stock_order;
        string item;
        int price = 0;
        int quantity = 0;

        getline(File, line);
        while (getline(File, line))
        {
            decision = 0;
            item = "";
            temp = "";
            if (line == "!@")
                break;
            for (char i : line + " ")
            {
                if (i == '$')
                {
                    decision = -1;
                }
                else if (i == '#')
                {
                    decision = -3;
                }
                else if (i == ' ')
                {
                    if (decision == 0)
                    {
                        start_time = stoi(temp);
                    }
                    else if (decision == 1)
                    {
                        Brokername = temp;
                    }
                    else if (decision == 2)
                    {
                        stock_order = temp;
                    }
                    else if (decision > 2)
                    {
                        item.append(temp);
                        item.append(" ");
                    }
                    else if (decision == -1)
                    {
                        price = stoi(temp);
                    }
                    else if (decision == -2)
                    {
                        end_time = stoi(temp);
                    }
                    else if (decision == -3)
                    {
                        quantity = stoi(temp);
                    }
                    temp = "";
                    decision++;
                }
                else
                {
                    temp.push_back(i);
                }
            }
            item.pop_back();
            // cout << start_time << " " << Brokername << " " << stock_order << " " << item << " " << price << " " << quantity << " " << end_time << endl;
            n.start_time = start_time;
            n.Brokername = Brokername;
            n.stock_order = stock_order;
            n.item = item;
            n.price = price;
            n.quantity = quantity;
            n.end_time = start_time + end_time;
            if (end_time == -1)
                n.end_time = 2147483647;

            if(search_key(root, n.Brokername)[0] == -1){
                insert_key(root, n.Brokername, 0, 0, 0);
                Brokers.push_back(n.Brokername);
            }

            while (BUYheap.ExtractMin().end_time < n.start_time && BUYheap.Size() != 0)
            {
                BUYheap.DeleteMin();
            }
            while (SELLheap.ExtractMin().end_time < n.start_time && SELLheap.Size() != 0)
            {
                SELLheap.DeleteMin();
            }

            node o = node(); // will store the optimal value at any time t
            int exit = 0;    // will decide when to exit the loop
            int index = 0;

            if (stock_order == "BUY")
            {
                if (SELLheap.Size() != 0)
                {
                    while (exit != 1)
                    {
                        o = node();

                        for (int i = SELLheap.Size() - 1; i >= 0; i--)
                        {
                            node m = SELLheap.thiselement(i);
                            if (check(m.item, n.item) == true)
                            {
                                // if (m.Brokername == n.Brokername)
                                // {
                                //     if (m.price == n.price)
                                //     {
                                //         if (m.start_time <= o.start_time)
                                //         {
                                //             if (m.Brokername.compare(o.Brokername) < 0)
                                //             {
                                //                 o = m;
                                //                 index = i;
                                //             }
                                //         }
                                //     }
                                //     else if (m.price == n.price && m.price < n.price)
                                //     {
                                //         o = m;
                                //         index = i;
                                //     }
                                // }
                                // else
                                // {
                                if (m.price <= n.price && o.price == 0)
                                {
                                    o = m;
                                    index = i;
                                }
                                else if (m.price < o.price && o.price != 0)
                                {
                                    o = m;
                                    index = i;
                                }
                                else if (m.price <= n.price && m.price == o.price && o.price != 0)
                                {
                                    if (m.start_time <= o.start_time)
                                    {
                                        if (compare(o.Brokername, m.Brokername) > 0)
                                        {
                                            o = m;
                                            index = i;
                                        }
                                    }
                                }
                                // }
                            }
                        }
                        if (o.price != 0)
                        {
                            if (o.quantity < n.quantity)
                            {
                                SELLheap.Deleteindex(index);
                                cout << n.Brokername << " purchased " << o.quantity << " share of " << n.item << " from " << o.Brokername << " for "
                                     << "$" << o.price << "/share" << endl;
                                n.quantity = n.quantity - o.quantity;

                                trades++;
                                shares += o.quantity;
                                money += o.quantity * o.price;

                                Update_key(root, n.Brokername, -o.quantity * o.price, o.quantity,0);
                                Update_key(root, o.Brokername, o.quantity * o.price, 0, o.quantity);
                            }
                            else if (o.quantity > n.quantity)
                            {
                                SELLheap.updatequantity(index, o.quantity - n.quantity);
                                cout << n.Brokername << " purchased " << n.quantity << " share of " << n.item << " from " << o.Brokername << " for "
                                     << "$" << o.price << "/share" << endl;
                                exit = 1;

                                trades++;
                                shares += n.quantity;
                                money += n.quantity * o.price;

                                Update_key(root, n.Brokername, -n.quantity * o.price, n.quantity,0);
                                Update_key(root, o.Brokername, n.quantity * o.price, 0, n.quantity);
                            }
                            else
                            {
                                cout << n.Brokername << " purchased " << n.quantity << " share of " << n.item << " from " << o.Brokername << " for "
                                     << "$" << o.price << "/share" << endl;
                                exit = 1;
                                SELLheap.Deleteindex(index);

                                trades++;
                                shares += n.quantity;
                                money += n.quantity * o.price;

                                Update_key(root, n.Brokername, -n.quantity * o.price, n.quantity,0);
                                Update_key(root, o.Brokername, n.quantity * o.price, 0, n.quantity);
                            }
                        }
                        else
                        {
                            exit = 1;
                            BUYheap.Insert(n);
                        }
                    }
                }
                else
                {
                    BUYheap.Insert(n);
                }
            }
            else //-------------------------------------------------------------- for SELL
            {
                if (BUYheap.Size() != 0)
                {
                    while (exit != 1)
                    {
                        o = node();

                        for (int i = BUYheap.Size() - 1; i >= 0; i--)
                        {
                            node m = BUYheap.thiselement(i);
                            if (check(m.item, n.item) == true)
                            {
                                // if (m.Brokername == n.Brokername)
                                // {
                                //     if (m.price == n.price && m.price == o.price)
                                //     {
                                //         if (m.start_time <= o.start_time)
                                //         {
                                //             if (m.Brokername.compare(o.Brokername) < 0)
                                //             {
                                //                 o = m;
                                //                 index = i;
                                //             }
                                //         }
                                //     }
                                //     else if (m.price == n.price && m.price > o.price)
                                //     {
                                //         o = m;
                                //         index = i;
                                //     }
                                // }
                                // else
                                // {
                                if (m.price >= n.price && o.price == 0)
                                {
                                    o = m;
                                    index = i;
                                }
                                else if (m.price > o.price && o.price != 0)
                                {
                                    o = m;
                                    index = i;
                                }
                                else if (m.price >= n.price && m.price == o.price && o.price != 0)
                                {
                                    if (m.start_time <= o.start_time)
                                    {
                                        if (compare(o.Brokername, m.Brokername) > 0)
                                        {
                                            o = m;
                                            index = i;
                                        }
                                    }
                                }
                                // }
                            }
                        }
                        if (o.price != 0)
                        {
                            if (o.quantity < n.quantity)
                            {
                                BUYheap.Deleteindex(index);
                                cout << o.Brokername << " purchased " << o.quantity << " share of " << n.item << " from " << n.Brokername << " for "
                                     << "$" << o.price << "/share" << endl;
                                n.quantity = n.quantity - o.quantity;

                                trades++;
                                shares += o.quantity;
                                money += o.quantity * o.price;

                                Update_key(root, o.Brokername, -o.quantity * o.price, o.quantity,0);
                                Update_key(root, n.Brokername, o.quantity * o.price, 0, o.quantity);
                            }
                            else if (o.quantity > n.quantity)
                            {
                                BUYheap.updatequantity(index, o.quantity - n.quantity);
                                cout << o.Brokername << " purchased " << n.quantity << " share of " << n.item << " from " << n.Brokername << " for "
                                     << "$" << o.price << "/share" << endl;
                                exit = 1;

                                trades++;
                                shares += n.quantity;
                                money += n.quantity * o.price;

                                Update_key(root, o.Brokername, -n.quantity * o.price, n.quantity,0);
                                Update_key(root, n.Brokername, n.quantity * o.price, 0, n.quantity);
                            }
                            else
                            {
                                cout << o.Brokername << " purchased " << n.quantity << " share of " << n.item << " from " << n.Brokername << " for "
                                     << "$" << o.price << "/share" << endl;
                                exit = 1;
                                BUYheap.Deleteindex(index);

                                trades++;
                                shares += n.quantity;
                                money += n.quantity * o.price;

                                Update_key(root, o.Brokername, -n.quantity * o.price, n.quantity,0);
                                Update_key(root, n.Brokername, n.quantity * o.price, 0, n.quantity);
                            }
                        }
                        else
                        {
                            exit = 1;
                            SELLheap.Insert(n);
                        }
                    }
                }
                else
                {
                    SELLheap.Insert(n);
                }
            }
        }
        // -------------------------- End of the Day outputs ---------------------------------------
        cout << endl;
        cout << "---End of Day---" << endl;
        cout << "Total Amount of Money Transferred: $" << money << endl;
        cout << "Number of Completed Trades: " << trades << endl;
        cout << "Number of Shares Traded: " << shares << endl;
        for(string i : Brokers){
            cout << i << " bought " << search_key(root, i)[1] << " and sold " << search_key(root, i)[2] << " for a net transfer of $" << search_key(root, i)[0] << endl;
        }
    }
    File.close();
}
