// This is your trader. Place your orders from here

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

struct ll2
{
    string broker_name;     // broker
    vector<string> company; // AMD, AMZN types
    vector<int> number;     // number of stocks of each company
    int price;
    int quantity;
    string type; // sell or buy
    ll2 *parent;
    int start;
    int end;
    ll2 *next;
    // ll2() : broker_name(""), company({""}), number({0}), price(0), quantity(0), type(""), parent(nullptr), start(0), end(0), next(nullptr) {}
    // we can use for directly initializing a ll2
};

void check_arbitrarge(ll2 *head, ll2 *tail, int median)
{

}

void delete_stock(vector<vector<int>> array, vector<int> stock)
{
    for (int i = 0; i < array.size(); i++)
    {
        if (array[i][0] == stock[0] && array[i][1] == stock[1])
        {
            for (int j = i; j < array.size() - 1; j++)
            {
                array[j][0] = array[j + 1][0];
                array[j][1] = array[j + 1][1];
            }
            array.pop_back();
            break;
        }
    }
    total_quantity -= stock[1];
}

void add_stock(vector<vector<int>> array, vector<int> stock)
{
    if (array.size() == 0)
        array.push_back(stock);
    else
    {
        int j = 0;
        for (int i = 0; i < array.size(); i++)
        {
            if (array[i][0] < stock[0])
            {
                j = i;
                break;
            }
        }
        array.push_back({0,0});
        for(int i = array.size()-1; i > j;i--)
        {
            array[i][0] = array[i-1][0];
            array[i][1] = array[i-1][1];
        }
        array[j][0] = stock[0];
        array[j][1] = stock[1];
    }
    total_quantity += stock[1];
}

int calculate_median(vector<vector<int>> array)
{
    int mid = total_quantity/2;
    int sum = 0;
    if(total_quantity%2 == 1)
    {
        for (int i = 0; i < array.size(); i++)
        {
            sum += array[i][1];
            if (sum >= mid)
            {
                return array[i][0];
                break;
            }
        }
    }
    else
    {
        for (int i = 0; i < array.size(); i++)
        {
            sum += array[i][1];
            if (sum > mid)
            {
                return array[i][0];
                break;
            }
            else if (sum == mid)
            {
                return (array[i][0] + array[i+1][0])/2;
                break;
            }            
        }
    }
}

ll2 *head = nullptr;
ll2 *tail = nullptr;

vector<vector<int>> array;
int median = 0;
int total_quantity = 0;
int a = 1;
int reader(int time)
{
    bool flag = false;
    fstream File_1;
    File_1.open("output.txt", ios::in);
    string line;
    int b = 0;
    int decision = 0;
    int j = 0;
    string temp = "";
    string item = "";
    while (getline(File_1, line))
    {
        b++;
        if (line == "!@")
        {
            flag = true;
            break;
        }
        if (b > a)
        {
            ll2 *node;
            decision = 0;
            j = 0;
            item = "";
            temp = "";
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
                        node->start = stoi(temp);
                    }
                    else if (decision == 1)
                    {
                        node->broker_name = temp;
                    }
                    else if (decision == 2)
                    {
                        node->type = temp;
                    }
                    else if (decision > 2)
                    {
                        if (decision % 2 == 1)
                        {
                            node->company[j++] = temp;
                        }
                        else
                        {
                            node->number[j++] = stoi(temp);
                        }
                    }
                    else if (decision == -1)
                    {
                        node->price = stoi(temp);
                    }
                    else if (decision == -2)
                    {
                        node->end = stoi(temp) + node->start;
                    }
                    else if (decision == -3)
                    {
                        node->quantity = stoi(temp);
                    }
                    temp = "";
                    decision++;
                }
                else
                {
                    temp.push_back(i);
                }
            }
            // parse

            if (tail == nullptr)
            {
                head = node;
                tail = node;
                node->next = nullptr;
                node->parent = nullptr;
            }
            else
            {
                tail->next = node;
                node->parent = tail;
                tail = tail->next;
                node->next = nullptr;
            }
            // add the new orders as the a node of the linked list

            add_stock(array, {node->price, node->quantity});// added to the array
            // add the new order to the array for median calculation
        }
    }
    ll2 *it = head;
    ll2 *p;
    while (it != nullptr)
    {
        if (it->end < tail->start)
        {
            delete_stock(array, {it->price, it->quantity});// deleted the stock
            if (it == head)
            {
                head->next->parent = nullptr;
                head = head->next;
                it->next = nullptr;
                it = head;
            }
            else if (it == tail)
            {
                it->parent->next = nullptr;
                tail = tail->parent;
                it->parent = nullptr;
                it = tail->next; // shud be nullptr only
            }
            else
            {
                p = it->next;
                p->parent = it->parent;
                it->parent = nullptr;
                p->parent->next = p;
                it->next = nullptr;
                it = p;
            }
        }
    }
    // delete the outdated orders from linked list and array
    

    // calculate median
    median = calculate_median(array);
    
    check_arbitrarge(head, tail, median);
    a = b;
    File_1.close();
    if (flag)
        return 1;

    return 0;
}

int trader(std::string *message)
{
    return 1;
}