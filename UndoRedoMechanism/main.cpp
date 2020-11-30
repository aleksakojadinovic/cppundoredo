#include <iostream>
#include <vector>
#include <algorithm>
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

class DeleteDummyObjectAction: public Action {
private:
    DummyObject* obj;
    std::vector<DummyObject*>& from;
    bool was_there;
    int was_at_idx;
public:
    DeleteDummyObjectAction(DummyObject * obj, std::vector<DummyObject *>& from)
        :   Action("Remove " + obj->getName()),
            obj(obj),
            from(from),
            was_there(false),
            was_at_idx(-1)
    {

    }

    void act() override {
        auto begin = std::begin(from);
        auto end = std::end(from);
        auto it = std::find(begin, end, obj);
        if (it != end) {
            int idx = it - begin;
            was_there = true;
            was_at_idx = idx;

            from.erase(it);
        }
    }

    void unact() override {
        if (!was_there)
            return;
        from.insert(std::begin(from) + was_at_idx, obj);
    }


    ~DeleteDummyObjectAction() {
        std::cout << "[" << this->name << "] removed" << std::endl;
    }
};

std::vector<DummyObject*> dummy_objects = { new DummyObject("Dummy 1"),
                                            new DummyObject("Dummy2"),
                                            new DummyObject("Dummy 3"),
                                            new DummyObject("And so on") 
                                          };

int main()
{

    
    ActionManager am;

    auto testDelete1 = new DeleteDummyObjectAction(dummy_objects[2], dummy_objects);
    auto testDelete2 = new DeleteDummyObjectAction(dummy_objects[0], dummy_objects);

    std::cout << "initial vector state: " << std::endl;
    std::for_each(std::begin(dummy_objects), std::end(dummy_objects), [](auto o) { std::cout << o->getName() << std::endl; });
    std::cout << "----------------------------------------" << std::endl;

    

    std::cout << "adding two actions" << std::endl;
    am.add_action(testDelete1);
    am.add_action(testDelete2);
    std::cout << am << std::endl;
    std::cout << "vector state: " << std::endl;
    std::for_each(std::begin(dummy_objects), std::end(dummy_objects), [](auto o) { std::cout << o->getName() << std::endl; });
    std::cout << "----------------------------------------" << std::endl;

    std::cout << "undoing" << std::endl;
    am.undo();
    std::cout << am << std::endl;
    std::cout << "vector state: " << std::endl;
    std::for_each(std::begin(dummy_objects), std::end(dummy_objects), [](auto o) { std::cout << o->getName() << std::endl; });
    std::cout << "----------------------------------------" << std::endl;

    std::cout << "redoing" << std::endl;
    am.redo();
    std::cout << am << std::endl;
    std::cout << "vector state: " << std::endl;
    std::for_each(std::begin(dummy_objects), std::end(dummy_objects), [](auto o) { std::cout << o->getName() << std::endl; });
    std::cout << "----------------------------------------" << std::endl;

    std::cout << "undoing" << std::endl;
    am.undo();
    std::cout << am << std::endl;
    std::cout << "vector state: " << std::endl;
    std::for_each(std::begin(dummy_objects), std::end(dummy_objects), [](auto o) { std::cout << o->getName() << std::endl; });
    std::cout << "----------------------------------------" << std::endl;

    std::cout << "undoing" << std::endl;
    am.undo();
    std::cout << am << std::endl;
    std::cout << "vector state: " << std::endl;
    std::for_each(std::begin(dummy_objects), std::end(dummy_objects), [](auto o) { std::cout << o->getName() << std::endl; });
    std::cout << "----------------------------------------" << std::endl;

    std::cout << "redoing" << std::endl;
    am.redo();
    std::cout << am << std::endl;
    std::cout << "vector state: " << std::endl;
    std::for_each(std::begin(dummy_objects), std::end(dummy_objects), [](auto o) { std::cout << o->getName() << std::endl; });
    std::cout << "----------------------------------------" << std::endl;
    

    
    
    

    return 0;
}