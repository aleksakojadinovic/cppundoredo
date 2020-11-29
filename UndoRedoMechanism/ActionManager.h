#ifndef ACTIONMANAGER_H
#define ACTIONMANAGER_H

#include <iostream>
#include <vector>
#include <functional>

#include "Action.h"

class ActionManager {
private:
    std::vector<Action*> action_history;
    int at;
public:
    ActionManager();
    void undo();
    void redo();
    void add_action(Action* action);

    friend std::ostream& operator<<(std::ostream& os, const ActionManager& am) {
        os << "=======Action Manager==============" << std::endl;
        for (int i = 0; i < am.action_history.size(); i++) {
            if (i == am.at) {
                os << " --> ";
            }
            else {
                os << "  *  ";
            }
            os << am.action_history[i]->name;
            if (i == am.at) {
                os << " <-- ";
            }
            os << std::endl;
        }
        os << "===================================";
        return os;
    }
};


#endif