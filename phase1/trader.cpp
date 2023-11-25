#include "receiver.h"
#include "trie.h"
#include <vector>

using namespace std;

struct ll1
{
    vector<string> company;
    vector<int> number;
    int price;
    string type;
    ll1 *parent;
    ll1 *next;
};

bool check1(ll1 *&head1, ll1 *&tail, vector<string> line)
{
    if (head1 == nullptr)
        return true;
    ll1 *head = head1;
    while (head != nullptr)
    {
        if (line.size() != head->company.size() * 2 + 2)
        {
            head = head->next;
            continue;
        }
        int j;
        bool flag = true;
        int n = 1;
        if (line[line.size() - 1] == "s")
            n = -1;
        for (int i = 0; i < line.size() / 2 - 1; i++)
        {
            j = 0;
            for (string k : head->company)
            {
                if (k == line[2 * i])
                    break;
                j++;
            }
            if (stoi(line[2 * i + 1]) * n != -head->number[j])
            {
                flag = false;
                break;
            }
        }
        if (flag)
        {
            if (line[line.size() - 1] == "b" && head->price == -1 * stoi(line[line.size() - 2]) && head->type == "s")
            {
                if (head->next == nullptr)
                    tail = tail->parent;
                if (head->parent == nullptr)
                    head1 = head1->next;
                if (head->next != nullptr)
                    head->next->parent = head->parent;
                if (head->parent != nullptr)
                    head->parent->next = head->next;
                delete head;
                return false;
            }
            if (line[line.size() - 1] == "s" && head->price == stoi(line[line.size() - 2]) && head->type == "b")
            {
                if (head->next == nullptr)
                    tail = tail->parent;
                if (head->parent == nullptr)
                    head1 = head1->next;
                if (head->next != nullptr)
                    head->next->parent = head->parent;
                if (head->parent != nullptr)
                    head->parent->next = head->next;
                delete head;
                return false;
            }
        }
        flag = true;
        for (int i = 0; i < line.size() / 2 - 1; i++)
        {
            j = 0;
            for (string k : head->company)
            {
                if (k == line[2 * i])
                    break;
                j++;
            }
            if (stoi(line[2 * i + 1]) * n != head->number[j])
            {
                flag = false;
                break;
            }
        }
        if (flag)
        {
            if (line[line.size() - 1] == "b" && head->type == "b")
            {
                if (stoi(line[line.size() - 2]) >= head->price)
                {
                    if (head->next == nullptr)
                        tail = tail->parent;
                    if (head->parent == nullptr)
                        head1 = head1->next;
                    if (head->next != nullptr)
                        head->next->parent = head->parent;
                    if (head->parent != nullptr)
                        head->parent->next = head->next;
                    delete head;
                }
                return true;
            }
            if (line[line.size() - 1] == "s" && head->type == "s")
            {
                if (stoi(line[line.size() - 2]) <= -1 * head->price)
                {
                    if (head->next == nullptr)
                        tail = tail->parent;
                    if (head->parent == nullptr)
                        head1 = head1->next;
                    if (head->next != nullptr)
                        head->next->parent = head->parent;
                    if (head->parent != nullptr)
                        head->parent->next = head->next;
                    delete head;
                }
                return true;
            }
        }
        head = head->next;
    }
    return true;
}

vector<ll1 *> insert1(ll1 *head, ll1 *tail, vector<string> line)
{
    ll1 *a = new ll1;
    for (int i = 0; i < line.size() / 2 - 1; i++)
    {
        a->company.push_back(line[2 * i]);
        a->number.push_back(stoi(line[2 * i + 1]));
    }
    if (line[line.size() - 1] == "b")
        a->price = stoi(line[line.size() - 2]);
    else
    {
        a->price = -1 * stoi(line[line.size() - 2]);
        for (int i = 0; i < a->number.size(); i++)
            a->number[i] = -a->number[i];
    }
    a->type = line[line.size() - 1];
    if (head == nullptr)
    {
        head = a;
        head->next = nullptr;
        a->parent = nullptr;
        tail = a;
    }
    else
    {
        tail->next = a;
        a->parent = tail;
        a->next = nullptr;
        tail = a;
    }
    return {head, tail};
}

int check_combination(vector<ll1 *> v)
{
    // for (ll1* a : v)
    // {
    //     cout << a->price << " ";
    // }
    // cout << endl;
    vector<string> x;
    vector<int> y;
    int l = 0;
    for (ll1 *a : v)
    {
        int i = 0;
        for (string b : a->company)
        {
            int j = 0;
            for (string c : x)
            {
                if (c == b)
                    break;
                j++;
            }
            if (j == l)
            {
                x.push_back(b);
                y.push_back(a->number[i]);
                l++;
            }
            else
            {
                y[j] += a->number[i];
            }
            i++;
        }
    }
    for (int a : y)
    {
        if (a != 0)
            return -1;
    }
    int sum = 0;
    for (ll1 *a : v)
    {
        sum += a->price;
    }
    return sum;
}

bool add(vector<ll1 *> &v, int a)
{
    if (a < 0)
        return true;
    bool b;
    if (v[a]->next != nullptr && a < v.size() - 1 && v[a + 1] == v[a]->next)
    {
        b = add(v, a - 1);
        if (b)
            return true;
        if (v[a - 1]->next == nullptr)
            return true;
        v[a] = v[a - 1]->next;
        return false;
    }
    if (v[a]->next == nullptr)
    {
        b = add(v, a - 1);
        if (b)
            return true;
        if (v[a - 1]->next == nullptr)
            return true;
        v[a] = v[a - 1]->next;
        return false;
    }
    v[a] = v[a]->next;
    return false;
}

int check_arbitrarge1(ll1 *&head1, ll1 *&tail)
{
    vector<ll1 *> vec;
    vector<ll1 *> vec2;
    vector<ll1 *> output;
    int b;
    int out = 0;
    bool a;
    ll1 *head = head1;
    while (head != nullptr)
    {
        vec.push_back(head);
        vec2 = vec;
        while (true)
        {
            b = check_combination(vec2);
            if (b > out)
            {
                out = b;
                output = vec2;
            }
            a = add(vec2, vec2.size() - 1);
            if (a)
                break;
        }
        head = head->next;
    }
    if (output.empty())
    {
        cout << "No Trade" << endl;
        return 0;
    }
    for (int a = output.size() - 1; a >= 0; a--)
    {
        int i = 0;
        for (string b : output[a]->company)
        {
            if (output[a]->type == "b")
                cout << b << ' ' << output[a]->number[i] << ' ';
            else
                cout << b << ' ' << -1 * output[a]->number[i] << ' ';
            i++;
        }
        if (output[a]->type == "b")
            cout << output[a]->price << " s#" << "\r\n";
        else
            cout << output[a]->price << " b#" << "\r\n";
    }
    head = head1;
    for (ll1 *a : output)
    {
        if (head == a)
        {
            if (head->next == nullptr)
                tail = tail->parent;
            if (head->parent == nullptr)
                head1 = head1->next;
            if (head->next != nullptr)
                head->next->parent = head->parent;
            if (head->parent != nullptr)
                head->parent->next = head->next;
            ll1 *k = head->next;
            delete head;
            head = k;
        }
        else
            head = head->next;
    }
    return out;
}

struct ll2
{
    vector<string> company;
    vector<int> number;
    int price;
    int quantity;
    string type;
    ll2 *parent;
    ll2 *next;
};

bool check2(ll2 *&head1, ll2 *&tail, vector<string> &line)
{
    if (head1 == nullptr)
        return true;
    ll2 *head = head1;
    while (head != nullptr)
    {
        if (line.size() != head->company.size() * 2 + 3)
        {
            head = head->next;
            continue;
        }
        int j;
        bool flag = true;
        int n = 1;
        if (line[line.size() - 1] == "s")
            n = -1;
        for (int i = 0; i < line.size() / 2 - 1; i++)
        {
            j = 0;
            for (string k : head->company)
            {
                if (k == line[2 * i])
                    break;
                j++;
            }
            if (stoi(line[2 * i + 1]) * n != -head->number[j])
            {
                flag = false;
                break;
            }
        }
        if (flag)
        {
            if (line[line.size() - 1] == "b" && head->price == -1 * stoi(line[line.size() - 3]) && head->type == "s" && stoi(line[line.size() - 2]) > head->quantity)
            {
                if (head->next == nullptr)
                    tail = tail->parent;
                if (head->parent == nullptr)
                    head1 = head1->next;
                if (head->next != nullptr)
                    head->next->parent = head->parent;
                if (head->parent != nullptr)
                    head->parent->next = head->next;
                delete head;
                line[line.size() - 2] = to_string(stoi(line[line.size() - 2]) - head->quantity);
                return true;
            }
            if (line[line.size() - 1] == "b" && head->price == -1 * stoi(line[line.size() - 3]) && head->type == "s" && stoi(line[line.size() - 2]) < head->quantity)
            {
                head->quantity -= stoi(line[line.size() - 2]);
                return false;
            }
            if (line[line.size() - 1] == "b" && head->price == -1 * stoi(line[line.size() - 3]) && head->type == "s" && stoi(line[line.size() - 2]) == head->quantity)
            {
                if (head->next == nullptr)
                    tail = tail->parent;
                if (head->parent == nullptr)
                    head1 = head1->next;
                if (head->next != nullptr)
                    head->next->parent = head->parent;
                if (head->parent != nullptr)
                    head->parent->next = head->next;
                delete head;
                return false;
            }
            if (line[line.size() - 1] == "s" && head->price == stoi(line[line.size() - 3]) && head->type == "b" && stoi(line[line.size() - 2]) > head->quantity)
            {
                if (head->next == nullptr)
                    tail = tail->parent;
                if (head->parent == nullptr)
                    head1 = head1->next;
                if (head->next != nullptr)
                    head->next->parent = head->parent;
                if (head->parent != nullptr)
                    head->parent->next = head->next;
                delete head;
                line[line.size() - 2] = to_string(stoi(line[line.size() - 2]) - head->quantity);
                return true;
            }
            if (line[line.size() - 1] == "s" && head->price == stoi(line[line.size() - 3]) && head->type == "b" && stoi(line[line.size() - 2]) < head->quantity)
            {
                head->quantity -= stoi(line[line.size() - 2]);
                return false;
            }
            if (line[line.size() - 1] == "s" && head->price == stoi(line[line.size() - 3]) && head->type == "b" && stoi(line[line.size() - 2]) == head->quantity)
            {
                if (head->next == nullptr)
                    tail = tail->parent;
                if (head->parent == nullptr)
                    head1 = head1->next;
                if (head->next != nullptr)
                    head->next->parent = head->parent;
                if (head->parent != nullptr)
                    head->parent->next = head->next;
                delete head;
                return false;
            }
        }
        head = head->next;
    }
    return true;
}

void insert2(ll2 *&head, ll2 *&tail, vector<string> line)
{
    ll2 *a = new ll2;
    for (int i = 0; i < line.size() / 2 - 1; i++)
    {
        a->company.push_back(line[2 * i]);
        a->number.push_back(stoi(line[2 * i + 1]));
    }
    if (line[line.size() - 1] == "b")
        a->price = stoi(line[line.size() - 3]);
    else
    {
        a->price = -1 * stoi(line[line.size() - 3]);
        for (int i = 0; i < a->number.size(); i++)
            a->number[i] = -a->number[i];
    }
    a->type = line[line.size() - 1];
    a->quantity = stoi(line[line.size() - 2]);
    if (head == nullptr)
    {
        head = a;
        head->next = nullptr;
        a->parent = nullptr;
        tail = a;
    }
    else
    {
        tail->next = a;
        a->parent = tail;
        a->next = nullptr;
        tail = a;
    }
}

int check_combination2(vector<ll2 *> v1, vector<int> &v)
{
    // for (ll2* a : v1)
    // {
    //     cout << a->price << " ";
    // }
    // cout << endl;
    vector<string> x;
    vector<int> y;
    int l = 0;
    int m = 0;
    for (ll2 *a : v1)
    {
        int i = 0;
        for (string b : a->company)
        {
            int j = 0;
            for (string c : x)
            {
                if (c == b)
                    break;
                j++;
            }
            if (j == l)
            {
                x.push_back(b);
                y.push_back(a->number[i]*v[m]);
                l++;
            }
            else
            {
                y[j] += a->number[i]*v[m];
            }
            i++;
        }
        m++;
    }
    for (int a : y)
    {
        if (a != 0)
            {
                // cout << "nothing" << endl;
                return -1;
            }
    }
    int sum = 0;
    m = 0;
    for (ll2 *a : v1)
    {
        // cout << a->price << v[m] << endl;
        sum += a->price*v[m];
        m++;
    }
    // cout << v[1];
    // cout << sum << endl;
    return sum;
}

bool add2(vector<ll2 *> &v1, vector<int> &v, int a)
{
    if (a < 0)
        return true;
    bool b;
    if (v[a] == v1[a]->quantity)
    {
        b = add2(v1, v, a - 1);
        if (b)
            return true;
        v[a] = 1;
        return false;
    }
    v[a] = v[a] + 1;
    return false;
}

bool add3(vector<ll2 *> &v, int a)
{
    if (a < 0)
        return true;
    bool b;
    if (v[a]->next != nullptr && a < v.size() - 1 && v[a + 1] == v[a]->next)
    {
        b = add3(v, a - 1);
        if (b)
            return true;
        if (v[a - 1]->next == nullptr)
            return true;
        v[a] = v[a - 1]->next;
        return false;
    }
    if (v[a]->next == nullptr)
    {
        b = add3(v, a - 1);
        if (b)
            return true;
        if (v[a - 1]->next == nullptr)
            return true;
        v[a] = v[a - 1]->next;
        return false;
    }
    v[a] = v[a]->next;
    return false;
}

int check_arbitrarge2(ll2 *&head1, ll2 *&tail)
{
    vector<ll2 *> vec;
    vector<ll2 *> vec2;
    vector<int> vec3;
    vector<int> vec4;
    vector<ll2 *> output;
    vector<int> output2;
    int b;
    int out = 0;
    bool a;
    bool c;
    ll2 *head = head1;
    while (head != nullptr)
    {
        vec.push_back(head);
        vec2 = vec;
        vec3.push_back(1);
        while (true)
        {
            vec4 = vec3;
            while (true)
            {
                b = check_combination2(vec2, vec4);
                if (b > out)
                {
                    out = b;
                    output = vec2;
                    output2 = vec4;
                }
                c = add2(vec2, vec4, vec4.size() - 1);
                if (c)
                    break;
            }
            a = add3(vec2, vec2.size() - 1);
            if (a)
                break;
        }
        head = head->next;
    }
    if (output.empty())
    {
        cout << "No Trade" << endl;
        // cout << 4;
        return 0;
    }
    for (int a = output.size() - 1; a >= 0; a--)
    {
        int i = 0;
        for (string b : output[a]->company)
        {
            if (output[a]->type == "b")
                cout << b << ' ' << output[a]->number[i] << ' ';
            else
                cout << b << ' ' << -1 * output[a]->number[i] << ' ';
            i++;
        }
        if (output[a]->type == "b")
            cout << output[a]->price << " " << output2[a] << " s#" << endl;
        else
            cout << output[a]->price << " " << output2[a] << " b#" << endl;
    }
    // cout << 2 << endl;
    head = head1;
    for (ll2 *a : output)
    {
        if (head == a)
        {
            if (head->next == nullptr)
                tail = tail->parent;
            if (head->parent == nullptr)
                head1 = head1->next;
            if (head->next != nullptr)
                head->next->parent = head->parent;
            if (head->parent != nullptr)
                head->parent->next = head->next;
            ll2 *k = head->next;
            delete head;
            head = k;
        }
        else
            head = head->next;
    }

    // cout << 2<< endl;
    return out;
}

int main(int argc, char **argv)
{
    Receiver rcv;
    sleep(3);
    string message = rcv.readIML();
    if (stoi(argv[1]) == 1)//-------------------------------------------------------------------------PART1---------------------------------------------------------------------------------------
    {
        TrieNode *root = new TrieNode();
        vector<string> lines = {""};
        string temp = "";
        for (char i : message)
        {
            if (i == '$'){
                break;
            }
            else if (i == '#')
            {
                lines.push_back(temp);

                string company = lines[1];
                int price = stoi(lines[2]);
                string buy_sale;
                vector<int> last_price(3);
                last_price = search_key(root, company);
                if (lines[3] == "s")
                {
                    buy_sale = "b";
                }
                else
                {
                    buy_sale = "s";
                }

                if (last_price[0] == -1)
                {
                    insert_key(root, company, price, -1, -1);
                    cout << company << " " << price << " " << buy_sale << endl;
                }
                else if (last_price[1] == -1 && last_price[2] == -1)//------------------------------------------------------------------------
                {
                    if (buy_sale == "b")
                    {
                        if (price >= last_price[0])
                        { // not strictly greater
                            cout << "No Trade" << endl;
                            insert_key(root, company, last_price[0], price, last_price[2]);
                        }
                        else
                        {
                            insert_key(root, company, price, last_price[1], last_price[2]);
                            cout << company << " " << price << " " << buy_sale << endl;
                        }
                    }
                    else
                    {
                        if (price <= last_price[0])
                        { // not strictly lesser
                            cout << "No Trade" << endl;
                            insert_key(root, company, last_price[0], last_price[1], price);
                        }
                        else
                        {
                            insert_key(root, company, price, last_price[1], last_price[2]);
                            cout << company << " " << price << " " << buy_sale << endl;
                        }
                    }
                }
                else if (last_price[2] == -1)//------------------------------------------------------------------------
                {
                    if (buy_sale == "b")
                    {
                        if (price >= last_price[1])
                        { // not strictly greater
                            cout << "No Trade" << endl;
                        }
                        else
                        {
                            if (price >= last_price[0])
                            { // not strictly greater
                                cout << "No Trade" << endl;
                                if (price < last_price[1])
                                {
                                    insert_key(root, company, last_price[0], price, last_price[2]);
                                }
                            }
                            else
                            {
                                insert_key(root, company, price, -1, last_price[2]);
                                cout << company << " " << price << " " << buy_sale << endl;
                            }
                        }
                    }
                    else
                    {
                        if (price == last_price[1])
                        { // not strictly greater
                            cout << "No Trade" << endl;
                            insert_key(root, company, last_price[0], -1, last_price[2]);
                        }
                        else
                        {
                            if (price <= last_price[0])
                            { // not strictly greater
                                cout << "No Trade" << endl;
                                insert_key(root, company, last_price[0], last_price[1], price);
                            }
                            else
                            {
                                insert_key(root, company, price, last_price[1], last_price[2]);
                                cout << company << " " << price << " " << buy_sale << endl;
                            }
                        }
                    }
                }
                else if (last_price[1] == -1)//------------------------------------------------------------------------
                {
                    if (buy_sale == "s")
                    {   
                        
                        if (price <= last_price[2])
                        { // not strictly greater
                            cout << "No Trade" << endl;
                        }
                        else
                        {
                            if (price <= last_price[0])
                            { // not strictly greater
                                cout << "No Trade" << endl;
                                if (price > last_price[2])
                                {
                                    insert_key(root, company, last_price[0], last_price[1], price);
                                }
                            }
                            else
                            {
                                insert_key(root, company, price, last_price[1], last_price[2]);
                                cout << company << " " << price << " " << buy_sale << endl;
                            }
                        }
                    }
                    else
                    {
                        if (price == last_price[2])
                        { // not strictly greater
                            cout << "No Trade" << endl;
                            insert_key(root, company, last_price[0], last_price[1], -1);
                        }
                        else
                        {
                            if (price >= last_price[0])
                            { // not strictly greater
                                cout << "No Trade" << endl;
                                insert_key(root, company, last_price[0], price, last_price[2]);
                            }
                            else
                            {
                                insert_key(root, company, price, last_price[1], -1);
                                cout << company << " " << price << " " << buy_sale << endl;
                            }
                        }
                    }
                }
                else//---------------------------------------------------------------------------------------------------
                {
                    if (buy_sale == "b")
                    {
                        if (price >= last_price[1])
                        { // not strictly greater
                            cout << "No Trade" << endl;
                        }
                        else if (price == last_price[2])
                        { // not strictly greater
                            cout << "No Trade" << endl;
                            insert_key(root, company, last_price[0], last_price[1], -1);
                        }
                        else
                        {
                            if (price >= last_price[0])
                            { // not strictly greater
                                cout << "No Trade" << endl;
                                if (price < last_price[1])
                                {
                                    insert_key(root, company, last_price[0], price, last_price[2]);
                                }
                            }
                            else
                            {
                                insert_key(root, company, price, last_price[1], last_price[2]);
                                cout << company << " " << price << " " << buy_sale << endl;
                            }
                        }
                    }
                    else
                    {
                        if (price <= last_price[2])
                        { // not strictly greater
                            cout << "No Trade" << endl;
                        }
                        else if (price == last_price[1])
                        { // not strictly greater
                            cout << "No Trade" << endl;
                            insert_key(root, company, last_price[0], -1, last_price[2]);
                        }
                        else
                        {
                            if (price <= last_price[0])
                            { // not strictly lesser
                                cout << "No Trade" << endl;
                                if (price > last_price[2])
                                {
                                    insert_key(root, company, last_price[0], last_price[1], price);
                                }
                            }
                            else
                            {
                                insert_key(root, company, price, last_price[1], last_price[2]);
                                cout << company << " " << price << " " << buy_sale << endl;
                            }
                        }
                    }
                }
            }
            else if ((int)i == 13)
            {
                temp = "";
                lines = {""};
            }
            else if (i == ' ')
            {
                lines.push_back(temp);
                temp = "";
            }
            else
            {
                temp.push_back(i);
            }
        }
    }
    else if (stoi(argv[1]) == 2)
    {
        ll1 *head = nullptr;
        ll1 *tail = nullptr;
        vector<string> lines = {""};
        int j = 0;
        int sum = 0;
        while (true)
        {
            for (char i : message)
            {
                if (i == '$')
                    continue;
                if (i == '#')
                {
                    if (check1(head, tail, lines))
                    {
                        vector<ll1 *> k = insert1(head, tail, lines);
                        head = k[0];
                        tail = k[1];
                    }
                    sum += check_arbitrarge1(head, tail);
                    // ll1 *head1 = head;
                    // while (head1 != nullptr)
                    // {
                    //     cout << head1->price << " ";
                    //     head1 = head1->next;
                    // }
                    // cout << 1 << endl;
                    // for (string i : lines)
                    // {
                    //     cout << i << ' ';
                    // }
                    // cout << endl;
                    j = 0;
                }
                else if ((int)i == 13)
                {
                    lines = {""};
                }
                else if (i == ' ')
                {
                    j++;
                    lines.push_back("");
                }
                else
                {
                    lines[j].push_back(i);
                }
            }
            if (message.length() == 0)
                break;
            message = rcv.readIML();
        }
        cout << sum << endl;
    }
    else if (stoi(argv[1]) == 3)
    {
        ll2 *head = nullptr;
        ll2 *tail = nullptr;
        vector<string> lines = {""};
        int j = 0;
        int sum = 0;
        while (true)
        {
            for (char i : message)
            {
                // cout << i;
                if (i == '$')
                    continue;
                if (i == '#')
                {
                    if (check2(head, tail, lines))
                    {
                        // cout << 1;
                        insert2(head, tail, lines);
                    }
                    sum += check_arbitrarge2(head, tail);
                    // cout << 3;
                    // ll2 *head1 = head;
                    // while (head1 != nullptr)
                    // {
                    //     cout << head1->price << " ";
                    //     head1 = head1->next;
                    // }
                    // cout << 1 << endl;
                    // for (string i : lines)
                    // {
                    //     cout << i << ' ';
                    // }
                    // cout << endl;
                    j = 0;
                }
                else if ((int)i == 13)
                {
                    lines = {""};
                }
                else if (i == ' ')
                {
                    j++;
                    lines.push_back("");
                }
                else
                {
                    lines[j].push_back(i);
                }
            }
            if (message.length() == 0)
                break;
            message = rcv.readIML();
        }
        cout << sum << endl;
    }
    else
    {
        return 0;
    }
    return 0;
}
