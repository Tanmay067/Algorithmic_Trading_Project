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
};


void check_arbitrarge(ll2* head, ll2* tail, int median)
{

}


ll2 *head;
ll2 *tail;

vector<vector<int>> array;
int median = 0;

int a = 1;
int reader(int time)
{
    bool flag = false;
    fstream File_1;
    File_1.open("output.txt", ios::in);
    string line;
    int b = 0;
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
            // add the new orders as the a node of the linked list
            // add the new order to the array for median calculation
        }
    }
    // delete the outdated orders from linked list and array
    // calculate median
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
