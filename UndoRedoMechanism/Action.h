#ifndef ACTION_H
#define ACTION_H

#include <string>

class Action {
public:
    Action(const std::string& name = "Unnamed")
        :name(name)
    {

    }
    std::string name;
    virtual void act() = 0;
    virtual void unact() = 0;
};

#endif