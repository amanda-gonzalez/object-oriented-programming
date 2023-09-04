#include "Noble.h"
#include "Protector.h"

#include <iostream>
#include <vector>
#include <string>
using namespace std;

namespace WarriorCraft {
	// Noble class constructor
	// parameter constant string reference to name
	// initializer list initializes name to name variable
	// armystrength to 0 because there is no army
	// dead to false because a noble is alive when created
	Noble::Noble(const string& name, double strength) : name(name), strength(strength), dead(false) {}

	// getter returns constant reference to noble name
	// constant because it does not modify name
	const string& Noble::getName() const { return name; }

	// returns bool of if warrior is dead
	// constant because it does not modify dead
	bool Noble::isDead() const { return dead; }

	// sets dead to true
	void Noble::setDead() { dead = true; }

	// sets army strength to new strength
	void Noble::setStrength(double newStrength) { strength = newStrength; }

	// getter returns warrior strength
	// constant because it does not modify strength
	double Noble::getStrength() const { return strength; }

	// displays outcomes of battle depending on the noble strengths
	// updates army strengths and noble's health status
	void Noble::battle(Noble& opponent) {
		cout << this->getName() << " battles " << opponent.getName() << endl;
		double strength = this->getStrength();
		double oppStrength = opponent.getStrength();
		// if noble is not dead and he has the same strength as his opponent
		// both nobles are losers (method called to update strength to 0 and status to dead)
		if (!this->isDead() && strength == oppStrength) {
			this->loserStrength();
			opponent.loserStrength();
			cout << "Mutual Annihilation: " << this->getName() << " and " << opponent.getName() <<
				" die at eachother's hands" << endl;
		}
		// if both noble and opponenet are dead then message is displayed
		// no need to update health and status because they cannot come back to life
		else if (this->isDead() && opponent.isDead()) {
			cout << "Oh, NO! They're both dead! Yuck!" << endl;
		}
		// if only the instigator noble is dead, then the opponent wins
		// nothing is updated in terms of opponent strength or health status
		// because nothing occurred in the battle
		else if (this->isDead()) {
			// opponent still tries to defend
			opponent.defend();
			cout << "He's dead, " << opponent.getName() << endl;
		}
		// if only the oponent noble is dead, then the insitigator noble wins
		// nothing is updated in terms of opponent strength or health status
		// because nothing occurred in the battle since opponent is dead
		else if (opponent.isDead()) {
			// noble still tries to defend
			this->defend();
			cout << "He's dead, " << this->getName() << endl;
		}
		// if noble strength is greater than opponent strength, then 
		// the noble is the winner (method call to decrease strength by ratio)
		// and opponent loses (method called to set strength to 0 and set to dead)
		else if (strength > oppStrength) {
			this->winnerStrength(opponent);
			opponent.loserStrength();
			cout << this->getName() << " defeats " << opponent.getName() << endl;
		}
		// if opponent strength is greater than instigator noble strength, then 
		// the opponent is the winner (method call to decrease strength by ratio)
		// and noble loses (method called to set strength to 0 and set to dead)
		else if (oppStrength > strength) {
			this->loserStrength();
			opponent.winnerStrength(*this);
			cout << opponent.getName() << " defeats " << this->getName() << endl;
		}
	}

	// Lord constructor
	// sets strength to 0 because there is no army yet
	Lord::Lord(const string& name) : Noble(name, 0) {}

	// boolean hire method returns true if lord was able to 
	// be hire, returns false if not
	bool Lord::hires(Protector& protector) {
		// hires protector if the warrior does not already have a lord
		// and the lord is not dead which returns true
		// returns false if either the noble is dead or protector already hired
		if (!protector.isHired() && !isDead()) {
			// protector now hired
			protector.setHired(*this);
			setStrength(this->getStrength() + protector.getStrength());
			army.push_back(&protector);
			return true;
		}
		else {
			cout << "Attempt to hire " << protector.getName() << " by " <<
				this->getName() << " failed!" << endl;
			return false;
		}
	}

	// boolean fires method returns true if protector is able to
	// be fired, returns false if not
	bool Lord::fires(Protector& protector) {
		// checks if noble is alive and warrior is hired first
		if (!isDead() && protector.isHired()) {
			// looks for protector to fire if they are in the army
			if (removeProtector(protector)) {
				cout << "You don't work for me anymore " << protector.getName() << "! -- " <<
					this->getName() << endl;
				protector.setFired();
				return true;
			}
			return false;
		}
		return false;
	}

	// removes protector from army if they are in it and returns true
	// returns false if protector not in army
	bool Lord::removeProtector(const Protector& protector) {
		for (size_t i = 0; i < army.size(); i++) {
			if (army[i] == &protector) {
				// army strength is reduced to exclude fired warrior
				setStrength(this->getStrength() - army[i]->getStrength());
				// pointer from the fired protector address points to next address
				// and so on until the end of the army vector
				for (size_t j = i; j < army.size() - 1; j++) {
					army[j] = army[j + 1];
				}
				// last vector object is popped off as a result of firing the protector
				army.pop_back();
				return true;
			}
		}
		return false;
	}

	// updates the winner army strength and protectors' strength by reducing it by the 
	// ratio of the loser's strength to the winner's strength
	void Lord::winnerStrength(Noble& loser) {
		defend();
		double ratio = loser.getStrength() / this->getStrength();
		// the strength of each protector in the army is reduced by the ratio
		for (Protector* const protector : army) {
			// ratio is losing army strength to winning army strength
			protector->setpStrength(protector->getStrength() * (1 - ratio));
		}
		// lord strength reduced by ratio
		setStrength(this->getStrength() * (1 - ratio));
	}

	// updates the loser's strength and its protectors' strengths to 0
	// sets lord to dead
	void Lord::loserStrength() {
		defend();
		// strength of each protector is set to 0
		for (Protector* const protector : army) {
			protector->setpStrength(0);
		}
		// lord strength set to 0
		setStrength(0);
		// lord set to dead
		setDead();
	}

	// displays statment for each protector during battle when called
	void Lord::defend() const {
		for (Protector* protector : army) {
			protector->defend();
		}
	}

	// person with strength to fight constructor
	PersonWithStrengthToFight::PersonWithStrengthToFight(const string& name, double strength) :
		Noble(name, strength) {}

	// updates the winner strength by reducing it by the 
	// ratio of the loser's strength to the winner's strength
	void PersonWithStrengthToFight::winnerStrength(Noble& loser) {
		defend();

		double ratio = loser.getStrength() / this->getStrength();

		// noble strength reduced by ratio
		setStrength(this->getStrength() * (1 - ratio));
	}

	// updates the loser's army strength to 0
	// sets noble to dead
	void PersonWithStrengthToFight::loserStrength() {
		defend();
		// noble strength set to 0
		setStrength(0);
		// noble set to dead
		setDead();
	}

	// displays statment during battle when called
	void PersonWithStrengthToFight::defend() const {
		cout << "Ugh!\t" << endl;
	}
}