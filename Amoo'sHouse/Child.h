#pragma once
#include <math.h>
#include <string>
#include <iostream>
#include <exception>
#include <vector>
#include <algorithm>
using namespace std;
class IDException : public exception {
	virtual const char *what() const throw() {
		return "ID is Invalid!";
	}
}IDExc;
class Child {
protected:
	int id;
	bool isFragile;
	string Type;

	vector <int> CollidedWith; //Vector Containing the ID of the Children that have Collided with This Child, On the Current Frame Cycle.

	double anger;
	double charisma;
	double courage;
	double speedX;
	double speedY;
	double bellyRadius;
	double posX;
	double posY;
public:
	void MoveSingleFrame() { //Since my Game has a FPS of 60 Frames, the SpeedX and SpeedY are devided by 60 for a single Frame movemnt
		posX += speedX / 60;
		posY += speedY / 60;
	}
	void setCollidedWith(Child *collider) { //Adding a child to the CollidedWith Vector
		CollidedWith.push_back(collider->getID());
	}
	void clearCollision(Child *collider) { //Removing a child from the CollidedWith Vector
		CollidedWith.erase(remove(CollidedWith.begin(), CollidedWith.end(), collider->getID()), CollidedWith.end());
	}
	bool hasCollided(Child *collider) { //Checking if a Child is inside the CollidedWith Vector
		for (int i = 0; i < CollidedWith.size(); i++) {
			if (CollidedWith[i] == collider->getID()) {
				return true;
			}
		}
		return false;
	}
	//Setters and Getters needed:
	double getPosX() {
		return posX;
	}
	int getID() {
		return id;
	}
	string getType() {
		return Type;
	}
	double getPosY() {
		return posY;
	}
	virtual double getAnger() {
		return anger;
	}
	virtual double getCharisma() {
		return charisma;
	}
	virtual double getCourage() {
		return courage;
	}
	virtual double getSpeedX() {
		return speedX;
	}
	virtual double getSpeedY() {
		return speedY;
	}
	virtual void setSpeedX(double _speedX) {
		speedX = _speedX;
	}
	virtual void setSpeedY(double _speedY) {
		speedY = _speedY;
	}
	virtual double getBellyRadius() {
		return bellyRadius;
	}
	virtual void setBellyRadius(double _BellyRadius) {
		bellyRadius = _BellyRadius;
	}
	//Virtual Methods:
	virtual void Hit(Child *secondChild, vector <Child*> &vectorOfChildren) = 0;
	virtual void setAnger(double _Anger) = 0;
	virtual void setCourage(double _Courage) = 0;
	virtual void setCharisma(double _Charisma) = 0;
	virtual void Break(vector <Child*> &vectorOfChildren) = 0;
	//Constructor:
	Child(int _id, string _Type ,bool _fragile, double _PosX, double _PosY, double _SpeedX, double _SpeedY, double _bellyRadius, double _Anger, double _Charisma, double _Courage) {
		try {
			if (_id > 0) {
				id = _id;
			}
			else {
				throw(1);
			}
		}
		catch (int a) {
			cout << "The ID of " << _id << " Is Invalid!" << endl;
			id = 0;
			cout << "The ID was set to " << 20 << endl;
		}
		Type = _Type;
		isFragile = _fragile;
		posX = _PosX;
		posY = _PosY;
		speedX = _SpeedX;
		speedY = _SpeedY;
		try {
			if(_bellyRadius > 0)
				bellyRadius = _bellyRadius;
			else {
				throw(20);
			}
		}
		catch (int e) {
			bellyRadius = 20;
			cout << "Belly Radius was set to a Invalid number, Belly Radius set to 20" << endl;
		}
	}
	bool operator ==(Child *SecondChild) {
		if (id == SecondChild->getID()) {
			return true;
		}
		return false;
	}
	virtual void Die(vector <Child*> &vectorOfChildren) = 0;
	void MirrorSpeedX() {
		speedX = -speedX;
	}
	void MirrorSpeedY() {
		speedY = -speedY;
	}
};