#ifndef INVENTORY_H
#define INVENTORY_H

#include <list>
#include "armor.h"
#include "weapon.h"
#include "useable.h"

extern Weapon fists;
extern Armor shirt;

class Inventory
{
private:
    Armor* equippedArmor = &shirt;
    Weapon* equippedWeapon = &fists;
    std::list<Item*> items;
public:
    Inventory();

    std::list<Item *> &getItems();
    Item* getItem(std::string name);
    bool drop(std::string name);
    void takeItem(Item* item_);
    int totallWeight() const;
    bool equip(std::string name);
    Armor* getEquippedArmor();
    Weapon* getEquippedWeapon();
};

#endif // INVENTORY_H
