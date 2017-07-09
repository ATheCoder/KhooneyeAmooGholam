#pragma once
#include "Child.h"
#define PI 3.14159265
class PeaceChild : public Child {
public:
	virtual void Hit(Child *secondChild, vector <Child*> &vectorOfChildren) {
		if (secondChild->getAnger() > 70 && secondChild->getCourage() > 50) {
			this->setBellyRadius(this->getBellyRadius() - ((1 - (secondChild->getCourage() + secondChild->getCharisma()) / 200) * 0.8 * secondChild->getBellyRadius()));
			this->setCourage(this->getCourage() - 10);
		}
		else if (secondChild->getCourage() > 30 && secondChild->getCharisma() > 50) {
			Follow(secondChild);
			this->setCourage(this->getCourage() + 2);
			this->setCharisma(this->getCharisma() + 2);
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
	void Follow(Child *secondChild) {
		double medianX = (this->speedX + secondChild->getSpeedX()) / 2;
		double medianY = (this->speedY + secondChild->getSpeedY()) / 2;
		this->setSpeedX(medianX);
		this->setSpeedY(medianY);
		secondChild->setSpeedX(medianX);
		secondChild->setSpeedY(medianY);
	}
	void setAnger(double _Anger) {
		if (_Anger > 30) {
			anger = 30;
		}
		else {
			anger = _Anger;
		}
	}
	void setCharisma(double _Charisma) {
		if (_Charisma < 50) {
			charisma = 50;
		}
		else {
			charisma = _Charisma;
		}
	}
	void setCourage(double _Courage) {
		if (_Courage < 30) {
			courage = 30;
		}
		else {
			courage = _Courage;
		}
	}
	PeaceChild(int _id, string _type, bool _fragile, double _PosX, double _PosY, double _SpeedX, double _SpeedY, double _bellyRadius, double _Anger, double _Charisma, double _Courage) : Child(_id, _type, _fragile, _PosX, _PosY, _SpeedX, _SpeedY, _bellyRadius, _Anger, _Charisma, _Courage) {
		setAnger(_Anger);
		setCourage(_Courage);
		setCharisma(_Charisma);
	}
	void Break(vector <Child*> &vectorOfChildren) {
		double newVelocity = sqrt(this->getSpeedX() * this->getSpeedX() + this->getSpeedY() * this->getSpeedY()) / 6;
		vectorOfChildren.push_back(new PeaceChild(vectorOfChildren.size() - 1, Type, isFragile, posX, posY, newVelocity * cos(PI / 3), newVelocity * sin(PI / 3), bellyRadius / 3, anger, charisma, courage));
		vectorOfChildren.push_back(new PeaceChild(vectorOfChildren.size() - 1, Type, isFragile, posX, posY, -newVelocity * cos(PI / 3), newVelocity * sin(PI / 3), bellyRadius / 3, anger, charisma, courage));
		vectorOfChildren.push_back(new PeaceChild(vectorOfChildren.size() - 1, Type, isFragile, posX, posY, -newVelocity * cos(PI / 3), -newVelocity * sin(PI / 3), bellyRadius / 3, anger, charisma, courage));
		vectorOfChildren.push_back(new PeaceChild(vectorOfChildren.size() - 1, Type, isFragile, posX, posY, newVelocity * cos(PI / 3), -newVelocity * sin(PI / 3), bellyRadius / 3, anger, charisma, courage));
		vectorOfChildren.push_back(new PeaceChild(vectorOfChildren.size() - 1, Type, isFragile, posX, posY, newVelocity, 0, bellyRadius / 3, anger, charisma, courage));
		vectorOfChildren.push_back(new PeaceChild(vectorOfChildren.size() - 1, Type, isFragile, posX, posY, -newVelocity, 0, bellyRadius / 3, anger, charisma, courage));
		vectorOfChildren.erase(vectorOfChildren.end() - 6);
	}
	void Die(vector <Child*> &vectorOfChildren) {
		vectorOfChildren.erase(remove(vectorOfChildren.begin(), vectorOfChildren.end(), this), vectorOfChildren.end());
	}
};