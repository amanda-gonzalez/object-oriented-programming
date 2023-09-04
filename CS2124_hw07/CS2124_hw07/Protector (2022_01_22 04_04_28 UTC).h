#ifndef PROTECTOR_H
#define PROTECTOR_H

#include <iostream>
#include <vector>
#include <string>

namespace WarriorCraft {
	class Lord;

	// Protector class
	class Protector {
	public:
		Protector(const std::string& name, double strength);

		const std::string& getName() const;

		const std::string& getLordName() const;

		double getStrength() const;

		void setpStrength(double newStrength);

		bool isHired() const;

		void setHired(Lord& newLord);

		void setFired();

		bool runaway();

		// abstract method because each protector has a different
		// statment displayed when called upon to battle
		virtual void defend() = 0;

	private:
		std::string name;
		double strength;
		Lord* lord;
	};

	class Wizard : public Protector {
	public:
		Wizard(const std::string& name, double strength) : Protector(name, strength) {}

		void defend() override;
	};

	class Warrior : public Protector {
	public:
		Warrior(const std::string& name, double strength) : Protector(name, strength) {}

		void defend() override;
	};

	class Archer : public Warrior {
	public:
		Archer(const std::string& name, double strength) : Warrior(name, strength) {}

		void defend() override;
	};

	class Swordsman : public Warrior {
	public:
		Swordsman(const std::string& name, double strength) : Warrior(name, strength) {}

		void defend() override;
	};
}
#endif // !PROTECTOR_H
