#ifndef ENTITY_H  
#define ENTITY_H  

#include <string>

using namespace std;

class Entity {
private:
    string id;

public:
    // Entity(const string& id) : id(id) {}
    Entity(const string& idd){
        id = idd;
    }

    string getId() const { 
        return id; 
    }

    virtual ~Entity() {}
    virtual void display() const = 0;
};

#endif // ENTITY_H
