#include <iostream>
#include <math.h>
#include <fstream>
#include <string>
#include <vector>
#include <conio.h>
#include <iomanip>
#include "AngryChild.h"
#include "CowardChild.h"
#include "PeaceChild.h"
double StringToDouble(string input);
void RunSimulation(int timeStep, int totalTime);
using namespace std;
vector <Child*> vectorOfChildren;
struct WallPos {
	int posX;
	int posY;
};
vector <WallPos> wallPos;
int widthint;
int main(int argc, char *argv[]) {
	//Start Reading Map.dat:
	int line = -1;
	int characterNO = 0;
	string width;
	char currentChar;
	fstream mapInput("map.dat", ios::in);
	mapInput.get(currentChar);
	while (!mapInput.eof()) {
		if (line == -1) {
			width += currentChar;
		}
		if (currentChar == '\n' && line == -1) {
			widthint = stoi(width);
			line = widthint - 1;
			characterNO = 0;
			characterNO = -1;
		}
		else if (currentChar == 'b'){
			WallPos currentPos;
			currentPos.posX = characterNO;
			currentPos.posY = line;
			wallPos.push_back(currentPos);
		}
		else if (currentChar == '\n') {
			line--;
			characterNO = -1;
		}
		characterNO++;
		mapInput.get(currentChar);
	}
	//Std IN:
	int numberOfChildren = 2;
	cout << "Pick the number of children: ";
	cin >> numberOfChildren;
	int i = 0;
	cout << "id, type, fragile, posX, posY, Vx, Vy, radius, anger, charisma, courage" << endl;
	/*while (i < numberOfChildren) {
		string idStr; string typeStr; string fragileStr; string posXStr; string posYStr; string velXStr; string velYStr; string radiusStr; string angerStr; string charismaStr; string courageStr;
		int id; bool fragile; double posX; double posY; double velX; double velY; double radius; double anger; double charisma; double courage;
		cin >> idStr >> typeStr >> fragileStr >> posXStr >> posYStr >> velXStr >> velYStr >> radiusStr >> angerStr >> charismaStr >> courageStr;
		id = stoi(idStr.substr(0, idStr.find(",")));
		fragile = (fragileStr == "false" ? false : true);
		posX = StringToDouble(posXStr);
		posY = StringToDouble(posYStr);
		velX = StringToDouble(velXStr);
		velY = StringToDouble(velYStr);
		radius = StringToDouble(radiusStr);
		anger = StringToDouble(angerStr);
		charisma = StringToDouble(charismaStr);
		courage = StringToDouble(courageStr);
		//Child Creation:
		cout << typeStr << endl;
		if (typeStr == "Peaceful,") 
			vectorOfChildren.push_back(new PeaceChild(id, typeStr, fragile, posX, posY, velX, velY, radius, anger, charisma, courage));
		else if (typeStr == "Angry,")
			vectorOfChildren.push_back(new AngryChild(id, typeStr, fragile, posX, posY, velX, velY, radius, anger, charisma, courage));
		else if (typeStr == "Coward,")
			vectorOfChildren.push_back(new CowardChild(id, typeStr, fragile, posX, posY, velX, velY, radius, anger, charisma, courage));
		i++;
	}*/
	//vectorOfChildren.push_back(new PeaceChild(1, "Peaceful", false, 19, 40, 2, 0, 12, 21, 51, 31));
	vectorOfChildren.push_back(new PeaceChild(2, "Peaceful", false, 2, 2, -1, 0, 1, 21, 51, 31));
	RunSimulation(stoi(argv[1]), stoi(argv[2]));
	_getch();
	return 0;
}
double StringToDouble(string input) {
	return stod(input.substr(0, input.find(",")));
}
void RunSimulation(int timeStep, int totalTime) {
	int currentTimeStep = 0;
	int frameNO;
	cout << "id, type, posX, posY, Vx, Vy, radius, anger, charisma, courage" << endl;
	while (currentTimeStep <= totalTime) {
		frameNO = 0;
		cout << "#" << currentTimeStep << endl;
		for (int i = 0; i < vectorOfChildren.size(); i++) {
			cout << fixed; //Fixed Precision
			cout << setprecision(2); //Double Precision set to 2
			cout << vectorOfChildren[i]->getID() << ", " << vectorOfChildren[i]->getType() << " " << vectorOfChildren[i]->getPosX() << ", " << vectorOfChildren[i]->getPosY() << ", " << vectorOfChildren[i]->getBellyRadius() << ", " << vectorOfChildren[i]->getAnger() << ", " << vectorOfChildren[i]->getCharisma() << ", " << vectorOfChildren[i]->getCourage() << endl;
		}
		while (frameNO < 60) {
			//Check for Collision on the Next Frame:
			for (int i = 0; i < vectorOfChildren.size(); i++) {
				//Check Wall Collision:
				for (int Wall = 0; Wall < wallPos.size(); Wall++) {
					double distance = sqrt((vectorOfChildren[i]->getPosX() - wallPos[Wall].posX) * (vectorOfChildren[i]->getPosX() - wallPos[Wall].posX) + (vectorOfChildren[i]->getPosY() - wallPos[Wall].posY) * (vectorOfChildren[i]->getPosY() - wallPos[Wall].posY));
					if (distance < vectorOfChildren[i]->getBellyRadius()) {
						if (wallPos[Wall].posX == 0 || wallPos[Wall].posX == widthint + 1) {
							vectorOfChildren[i]->MirrorSpeedX();
						}
						else if (wallPos[Wall].posY == 0 || wallPos[Wall].posY == widthint + 1) {
							vectorOfChildren[i]->MirrorSpeedY();
						}
						else {
							vectorOfChildren[i]->MirrorSpeedX();
							vectorOfChildren[i]->MirrorSpeedY();
						}
					}
				}
				for (int j = i + 1; j < vectorOfChildren.size(); j++) {
					if (i == j) {
						continue;
					}
					//Box Collison with an other Child:
					if (vectorOfChildren[i]->getPosX() + vectorOfChildren[i]->getBellyRadius() + vectorOfChildren[j]->getBellyRadius() > vectorOfChildren[j]->getBellyRadius()
						&& vectorOfChildren[i]->getPosX() < vectorOfChildren[j]->getPosX() + vectorOfChildren[i]->getBellyRadius() + vectorOfChildren[j]->getBellyRadius()
						&& vectorOfChildren[i]->getPosY() + vectorOfChildren[i]->getBellyRadius() + vectorOfChildren[j]->getBellyRadius() > vectorOfChildren[j]->getPosY()
						&& vectorOfChildren[i]->getPosY() < vectorOfChildren[j]->getPosY() + vectorOfChildren[i]->getBellyRadius() + vectorOfChildren[j]->getBellyRadius()) {
						double distance = sqrt(
							((vectorOfChildren[i]->getPosX() - vectorOfChildren[j]->getPosX()) * (vectorOfChildren[i]->getPosX() - vectorOfChildren[j]->getPosX()))
							+ ((vectorOfChildren[i]->getPosY() - vectorOfChildren[j]->getPosY()) * (vectorOfChildren[i]->getPosY() - vectorOfChildren[j]->getPosY()))
						);
						//Circle Collision with an other Child:
						if (distance < vectorOfChildren[i]->getBellyRadius() + vectorOfChildren[j]->getBellyRadius() && !(vectorOfChildren[i]->hasCollided(vectorOfChildren[j]))){
							vectorOfChildren[i]->Hit(vectorOfChildren[j], vectorOfChildren);
							vectorOfChildren[j]->Hit(vectorOfChildren[i], vectorOfChildren);
							vectorOfChildren[i]->setCollidedWith(vectorOfChildren[j]);
							vectorOfChildren[j]->setCollidedWith(vectorOfChildren[i]);
						}
						else if(distance > vectorOfChildren[i]->getBellyRadius() + vectorOfChildren[j]->getBellyRadius()) {
							vectorOfChildren[i]->clearCollision(vectorOfChildren[j]);
							vectorOfChildren[j]->clearCollision(vectorOfChildren[i]);
						}
					}
				}
			}
			//Move for a single Frame:
			for (int i = 0; i < vectorOfChildren.size(); i++) {
				vectorOfChildren[i]->MoveSingleFrame();
			}
			frameNO++;
		}
		currentTimeStep++;
	}
}