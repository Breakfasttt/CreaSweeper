//@@@@@@@@@@@@@@@@@@@
// Auteur : Y. Colaisseau
// date : 10/11/12
// description : classe qui gère l'introduction du jeu
//@@@@@@@@@@@@@@@@@@@


#pragma once

#include "GeneralConfig.h"


class Cintro
{

protected :

	sf::Sprite m_Background;
	sf::Clock m_IntroClock;
	sf::Clock m_NextBackgroundClock;

	bool m_breturn;
	int m_NbreBackground;

	bool m_EndIntro;

	float TimeIntro;
	float TimeAlpha;
	float DeltaAlphaIntro;

	void ChangeBackGroundWithId(int);

public :

	Cintro();
	~Cintro();


	void Init();
	void Deinit();
	void Update(float _deltaTime);
	void Display(sf::RenderWindow& _RenderWindows);
	void IntroEvent(sf::Event&);

	bool isIntroEnd(){return m_EndIntro;};


};