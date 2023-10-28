#include "receiver.h"

int main() {

    Receiver rcv;
    sleep(5);
    std::string message = rcv.readIML();
    int spaces = 0;
    for (char i : message)
    {
        if (i == ' ') spaces++;
        if (i == '#') break;
    }
    if (spaces == 2)
    {
        
    }
    else if (spaces % 2 == 1)
    {

    }
    else if (spaces % 2 == 0)
    {

    }
    else
    {
        return 0;
    }
    std::cout << message;
    return 0;
}
