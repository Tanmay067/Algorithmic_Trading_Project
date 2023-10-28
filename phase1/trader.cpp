#include "receiver.h"
#include "trie.h"
#include <vector>
using namespace std;

int main(int argc, char **argv)
{   
    Receiver rcv;
    sleep(5);
    string message = rcv.readIML();
    vector<vector<string>> inputs;
    vector<string> lines = {""};
    inputs.push_back(lines);
    int j = 0;
    int k = 0;
    for (char i : message)
    {
        if (i == '$')
            break;
        else if (i == '#')
        {
            j = 0;
            k++;
        }
        else if ((int)i == 13)
        {
            inputs.push_back(lines);
        }
        else if (i == ' ')
        {
            j++;
            inputs[k].push_back("");
        }
        else
        {
            inputs[k][j].push_back(i);
        }
    }

    // -------------------------- Part1 ---------------------------
    if (stoi(argv[1]) == 1)
    {   
        TrieNode* root = new TrieNode();
        for(vector<string> v : inputs){

            string company = v[0];
            int price = stoi(v[1]);
            string buy_sale;
            int last_price = search_key(root, company);

            if(v[2] == "s"){
                buy_sale = "b";
            }
            else{
                buy_sale = "s";
            }

            if(last_price == -1){
                insert_key(root, company, price);
                cout << company << " " << price << " " << buy_sale << endl;
            }
            else if(buy_sale == "b"){
                if(price >= last_price){
                    cout << "No Trade" << endl;
                }
                else{
                    insert_key(root, company, price);
                    cout << company << " " << price << " " << buy_sale << endl;
                }
            }
            else{
                if(price <= last_price){
                    cout << "No Trade" << endl;
                }
                else{
                    insert_key(root, company, price);
                    cout << company << " " << price << " " << buy_sale << endl;
                }
            }
        }
    }

    // -------------------------- Part2 ---------------------------
    else if (stoi(argv[1]) == 2)
    {

    }

    // -------------------------- Part3 ---------------------------
    else if (stoi(argv[1]) == 3)
    {

    }

    else
    {
        return 0;
    }
    
    // cout << message;
    return 0;
}
