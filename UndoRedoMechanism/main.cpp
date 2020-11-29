#include <iostream>
#include <vector>
#include "ActionManager.h"

class DummyObject {
private:
    std::string name;
public:
    DummyObject(const std::string& name = "Unnamed object")
        : name(name)
    {}

    std::string getName()
    {
        return name;
    }
};

std::vector<DummyObject*> dummy_objects;

int main()
{
    ActionManager am;
    
    std::cout << am << std::endl;

    return 0;
}