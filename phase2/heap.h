#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;
struct node
{
    int start_time;
    int end_time;
    string Brokername;
    string stock_order;
    string item;
    int price;
    int quantity;
    node() : start_time(0), end_time(0), Brokername(""), stock_order(""), item(""), price(0), quantity(0) {}
};
class BHeap
{
private:
    vector<node> heap;
    int l(int parent);
    int r(int parent);
    int par(int child);
    void heapifyup(int index);
    void heapifydown(int index);

public:
    BHeap() {}
    void Insert(node element);
    void DeleteMin();
    void Deleteindex(int i);
    void updatequantity(int i, int q);
    node ExtractMin();
    node thiselement(int i);
    int Size();
};


int BHeap::Size()
{
    return heap.size();
}
void BHeap::Insert(node ele)
{
    heap.push_back(ele);
    heapifyup(heap.size() - 1);
}
void BHeap::DeleteMin()
{
    if (heap.size() == 0)
    {
        cout << "Heap is Empty" << endl;
        return;
    }
    heap[0] = heap.at(heap.size() - 1);
    heap.pop_back();
    heapifydown(0);
    //    cout<<"Element Deleted"<<endl;
}
void BHeap::Deleteindex(int i)
{
    if (heap.size() == 0)
    {
        cout << "Heap is Empty" << endl;
        return;
    }
    heap[i] = heap.at(heap.size() - 1);
    heap.pop_back();
    heapifydown(i);
}
node BHeap::ExtractMin()
{
    if (heap.size() == 0)
    {
        node ele = node();
        return ele;
    }
    else
        return heap[0];
}

node BHeap::thiselement(int i)
{
    return heap[i];
}

void BHeap::updatequantity(int i, int q)
{
    heap[i].quantity = q; 
}

int BHeap::l(int parent)
{
    int l = 2 * parent + 1;
    if (l < heap.size())
        return l;
    else
        return -1;
}
int BHeap::r(int parent)
{
    int r = 2 * parent + 2;
    if (r < heap.size())
        return r;
    else
        return -1;
}
int BHeap::par(int child)
{
    int p = (child - 1) / 2;
    if (child == 0)
        return -1;
    else
        return p;
}
void BHeap::heapifyup(int in)
{
    if (in >= 0 && par(in) >= 0 && heap[par(in)].end_time > heap[in].end_time)
    {
        node temp = heap[in];
        heap[in] = heap[par(in)];
        heap[par(in)] = temp;
        heapifyup(par(in));
    }
}
void BHeap::heapifydown(int in)
{
    int child = l(in);
    int child1 = r(in);
    if (child >= 0 && child1 >= 0 && heap[child].end_time > heap[child1].end_time)
    {
        child = child1;
    }
    if (child > 0 && heap[in].end_time > heap[child].end_time)
    {
        node t = heap[in];
        heap[in] = heap[child];
        heap[child] = t;
        heapifydown(child);
    }
}