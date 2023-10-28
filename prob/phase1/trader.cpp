#include "receiver.h"
#include <vector>

int main(int argc, char **argv)
{
    Receiver rcv;
    sleep(3);
    std::string message = rcv.readIML();
    std::vector<std::vector<std::string>> inputs;
    std::vector<std::string> lines = {""};
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
    if (argc == 1)
    {
    }
    else if (argc == 2)
    {
        for (std::vector<std::string> i : inputs)
        {
            for (std::string x : i)
            {
                std::cout << x;
                std::cout << std::endl;
            }
        }
    }
    else if (argc == 3)
    {
    }
    else
    {
        return 0;
    }
    std::cout << message;
    return 0;
}
