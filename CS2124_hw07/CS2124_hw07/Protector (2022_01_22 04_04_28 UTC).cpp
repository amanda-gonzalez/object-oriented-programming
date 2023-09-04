#include "Noble.h"
#include "Protector.h"

#include <iostream>
#include <vector>
#include <string>
using namespace std;

namespace WarriorCraft {
	// warrior class constructor 
	// constant reference to name and a strength parameter
	// initializer list initializes name to name variable, strength to 
	// strength variable and hired to false because a warrior is 
	// created without ties to a noble
	Protector::Protector(const string& name, double strength) : name(name), strength(strength), lord(nullptr) {}

	// returns constant reference to warrior name
	// constant getter because it does not modify constant name
	const string& Protector::getName() const { return name; }

	// returns constant reference to lord name
	// constant getter because it does not modify constant name
	const string& Protector::getLordName() const { return lord->getName(); }

	// getter returns warrior strength
	// constant because it does not modify strength
	double Protector::getStrength() const { return strength; }

	// sets protector strength to new strength value
	void Protector::setpStrength(double newStrength) { strength = newStrength; }

	// returns bool of if warrior has noble
	// constant because it does not modify noble pointer
	bool Protector::isHired() const { return !(lord == nullptr); }

	// sets noble pointer to address of new noble
	void Protector::setHired(Lord& newLord) { lord = &newLord; }

	// set noble pointer to nullptr
	void Protector::setFired() { lord = nullptr; }

	// returns bool if warriror is able to run away
	// calls noble pointer remove method
	// if remove returns true, statement will be printed and noble pointer set to nullptr
	bool Protector::runaway() {
		// if noble is able to remove warrior (return of true)
		// then noble pointer set to nullptr
		if (lord->removeProtector(*this)) {
			cout << name << " flees in terror, abandoning his lord, " << lord->getName() << endl;
			lord = nullptr;
			return true;
		}
		return false;
	}

	// displays statement for wizard defending lord
	void Wizard::defend() {
		cout << "POOF!\t" << endl;
	}

	// displays statement for warrior defending lord
	void Warrior::defend() {
		cout << this->getName() << " says: Take that in the name of my lord, " << getLordName() << endl;
	}

	// displays statement for archer as defending lord
	void Archer::defend() {
		cout << "TWANG!\t";
		// calls warrior defend method
		Warrior::defend();
	}

	// displays statement for swordsman defending lord
	void Swordsman::defend() {
		cout << "CLANG!\t";
		// calls warrior defend method
		Warrior::defend();
	}
}