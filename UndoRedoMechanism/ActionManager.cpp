#include "ActionManager.h"

ActionManager::ActionManager()
    :at(-1)
{

}

void ActionManager::undo() {
    if (at < 0)
        return;
    action_history[at--]->unact();
}
void ActionManager::redo() {
    if (at == action_history.size() - 1)
        return;
    action_history[++at]->act();
}
void ActionManager::add_action(Action* action) {
    if (at == action_history.size() - 1) {
        action_history.push_back(action);
    }
    else {
        for (int i = at + 1; i < action_history.size(); i++) {
            delete action_history[i];
        }
        action_history.resize(at + 1);
        action_history.push_back(action);
    }
    at++;
    action->act();
}
