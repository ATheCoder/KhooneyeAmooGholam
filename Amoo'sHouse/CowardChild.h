#pragma once
#include "Child.h"
#define PI 3.14159265
class CowardChild : public Child {
public:
	virtual void Hit(Child *secondChild, vector <Child*> &vectorOfChildren) {
		this->setAnger(this->getAnger() + 5);
		if (secondChild->getAnger() > 70) {
			Die(vectorOfChildren);
		}
		else {
			this->setSpeedX(((this->getBellyRadius() * this->getBellyRadius() - secondChild->getBellyRadius() * secondChild->getBellyRadius()) / (secondChild->getBellyRadius() * secondChild->getBellyRadius() + this->getBellyRadius() * this->getBellyRadius())) * this->getSpeedX() + (2 * secondChild->getBellyRadius() * secondChild->getBellyRadius() / (this->getBellyRadius() * this->getBellyRadius() + secondChild->getBellyRadius() * secondChild->getBellyRadius())) * secondChild->getSpeedX());
			this->setSpeedY(((this->getBellyRadius() * this->getBellyRadius() - secondChild->getBellyRadius() * secondChild->getBellyRadius()) / (secondChild->getBellyRadius() * secondChild->getBellyRadius() + this->getBellyRadius() * this->getBellyRadius())) * this->getSpeedY() + (2 * secondChild->getBellyRadius() * secondChild->getBellyRadius() / (this->getBellyRadius() * this->getBellyRadius() + secondChild->getBellyRadius() * secondChild->getBellyRadius())) * secondChild->getSpeedY());
		}
		if (isFragile && bellyRadius + secondChild->getBellyRadius() > 20) {
			Break(vectorOfChildren);
		}
		else if (this->getBellyRadius() < 6) {
			Die(vectorOfChildren);
		}
	}
	void setCharisma(double _Charisma) {
		charisma = 0;
	}
	void setCourage(double _Charisma) {
		courage = 0;
	}
	void setAnger(double _Anger) {
		if (_Anger < 0) {
			anger = 0;
		}
		else {
			anger = _Anger;
		}
	}
	void Die(vector <Child*> &vectorOfChildren) {
		vectorOfChildren.erase(remove(vectorOfChildren.begin(), vectorOfChildren.end(), this), vectorOfChildren.end());
	}
	CowardChild(int _id, string _type, bool _fragile, double _PosX, double _PosY, double _SpeedX, double _SpeedY, double _bellyRadius, double _Anger, double _Charisma, double _Courage) : Child(_id, _type, _fragile, _PosX, _PosY, _SpeedX, _SpeedY, _bellyRadius, _Anger, _Charisma, _Courage) {
		setAnger(_Anger);
		setCourage(_Courage);
		setCharisma(_Charisma);
	}
	void Break(vector <Child*> &vectorOfChildren) {
		double newVelocity = sqrt(this->getSpeedX() * this->getSpeedX() + this->getSpeedY() * this->getSpeedY()) / 6;
		vectorOfChildren.push_back(new CowardChild(vectorOfChildren.size() - 1, Type, isFragile, posX, posY, newVelocity * cos(PI / 3), newVelocity * sin(PI / 3), bellyRadius / 3, anger, charisma, courage));
		vectorOfChildren.push_back(new CowardChild(vectorOfChildren.size() - 1, Type, isFragile, posX, posY, -newVelocity * cos(PI / 3), newVelocity * sin(PI / 3), bellyRadius / 3, anger, charisma, courage));
		vectorOfChildren.push_back(new CowardChild(vectorOfChildren.size() - 1, Type, isFragile, posX, posY, -newVelocity * cos(PI / 3), -newVelocity * sin(PI / 3), bellyRadius / 3, anger, charisma, courage));
		vectorOfChildren.push_back(new CowardChild(vectorOfChildren.size() - 1, Type, isFragile, posX, posY, newVelocity * cos(PI / 3), -newVelocity * sin(PI / 3), bellyRadius / 3, anger, charisma, courage));
		vectorOfChildren.push_back(new CowardChild(vectorOfChildren.size() - 1, Type, isFragile, posX, posY, newVelocity, 0, bellyRadius / 3, anger, charisma, courage));
		vectorOfChildren.push_back(new CowardChild(vectorOfChildren.size() - 1, Type, isFragile, posX, posY, -newVelocity, 0, bellyRadius / 3, anger, charisma, courage));
		vectorOfChildren.erase(vectorOfChildren.end() - 6);
	}
};