#ifndef NOBLE_H
#define NOBLE_H

#include <iostream>
#include <vector>
#include <string>

namespace WarriorCraft {
	class Protector;

	// Noble class
	class Noble {
	public:
		Noble(const std::string& name, double strength);

		const std::string& getName() const;

		bool isDead() const;

		void setDead();

		void setStrength(double newStrength);

		double getStrength() const;

		void battle(Noble& opponent);

		// abstract method because different noble strengths are dependent
		// on different factors (i.e. individual or army strength)
		virtual void winnerStrength(Noble& loser) = 0;

		// abstract method because different noble strengths are dependent
		// on different factors (i.e. individual or army strength)
		virtual void loserStrength() = 0;

		// abstract method because each lord has a different
		// statment displayed when called upon to battle
		virtual void defend() const = 0;

	private:
		std::string name;
		double strength;
		bool dead;
	};

	// Lord class
	class Lord : public Noble {
	public:
		Lord(const std::string& name);

		// only lord hires protectors
		bool hires(Protector& protector);

		// only lords fire protectors
		bool fires(Protector& protector);

		// only lords can remove protectors if they hired them
		bool removeProtector(const Protector& protector);

		void winnerStrength(Noble& loser) override;

		void loserStrength() override;

		void defend() const override;
	private:
		std::vector<Protector*> army;
	};

	class PersonWithStrengthToFight : public Noble {
	public:
		PersonWithStrengthToFight(const std::string& name, double strength);

		void winnerStrength(Noble& loser) override;

		void loserStrength() override;

		void defend() const override;
	};
}
#endif // !NOBLE_H
