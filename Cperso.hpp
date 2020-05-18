//@@@@@@@@@@@@@@@@@@@
// Auteur : Y. Colaisseau
// date : 24/11/12
// description : classe qui gére le perso
//@@@@@@@@@@@@@@@@@@@



#pragma once

#include "GeneralConfig.h"


enum T_Sens
{
	BOT =0,
	LEFT,
	TOP,
	RIGHT,

};

class Cperso
{

protected :

	int m_posX;
	int m_posY;

	T_Sens m_sens;

	sf::Sprite m_SpritePerso;

	int m_maxY ;

	bool m_asMoved;
	bool m_PowerOn;
	bool m_asUsedPower;


public :

	Cperso(),
	~Cperso();


	void EventPerso(sf::Event);
	void DisplayPerso(sf::RenderWindow& _render);


	int getPosX() {return m_posX;};
	int getPosY() {return m_posY;};

	void setPosDebut(int , int);

	void setMaxY(int _i) { m_maxY = _i ; } ;

	bool getAsMoved() {return m_asMoved;};
	void setAsmoved(bool _b) {m_asMoved = _b;};

	bool getPowerOn() {return m_PowerOn;};
	void setPowerOn(bool _b) {m_PowerOn = _b;};

	bool getUsedPower() {return m_asUsedPower;};
	void setUsedPower(bool _b) {m_asUsedPower = _b;};


};
