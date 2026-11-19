#include <string>
#include <iostream>
#include <vector>


class Item {
public:
  Item(double w) : weight(w) {}
  virtual ~Item() = default;

  double get_weight() const {
    return weight;
  }
  virtual void print(std::ostream& os) const = 0;

protected:
  virtual void print_info(std::ostream& os) const  {
    os << weight;
    os << " kg";
  }

private:
  double weight;
};

class Shovel : public Item {
public:
  Shovel() : Item(3.0) {}

  void print(std::ostream& os) const override {
    os << "this is a shovel";
    print_info(os);
  }
};

class Weapon : public Item {
public:
  Weapon(double d, double w) : Item(w), damage(d) {};

  double get_damage() const {
    return damage;
  }

protected:
  void print_info(std::ostream& os) const override {
    os << "dealing ";
    os << damage;
    os << " damage";
    Item::print_info(os);
  }

private:
  double damage;

};

class Sword : public Weapon {
public:
 Sword(std::string n, double w, double d) : Weapon(d, w), name(n) {}

  void print(std::ostream& os) const override {
    os << "A sword named '";
    os << name;
    os << "' ";
    Weapon::print_info(os);
  }

private:
  std::string name;
};


class Bow : public Weapon { 
public:
  using Weapon::Weapon;

  void print(std::ostream& os) const override {
    os << "A bow ";
    Weapon::print_info(os);
  }

private:
  // the instructions says bow should have the same constructor as sweod, but it dows not say
  // anything about name, asume the instructions mean that bow are supose to have a member name to.
};





int main()
{

  std::vector<Item*> bag {
    new Sword { "Sword of stabbing", 10.0, 2.5 },
    new Sword { "Sword of pricking", 5.0, 0.9 },
    new Bow   { 7.5, 0.6 },
    new Shovel { }
  };

  double total_weight { 0.0 };
  double greatest_damage { 0.0 };

  std::cout << "Your bag contains: " << std::endl;
  for (Item* item : bag)
  {
    std::cout << " - ";
    item->print(std::cout);
    std::cout << std::endl;

    // alltså om weapon faktiskt är et weapon
    Weapon* weapon = dynamic_cast<Weapon*>(item);
    if (weapon != nullptr)
    {
      if (weapon->get_damage() > greatest_damage)
      {
        greatest_damage = weapon->get_damage();
      }
    }

    total_weight += item->get_weight();
  }
  std::cout << "Total weight: " << total_weight << " kg" << std::endl;
  std::cout << "Best damage: " << greatest_damage << " damage" << std::endl;

  for (Item* item : bag) {
    delete item;
  }
}

