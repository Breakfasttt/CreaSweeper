//@@@@@@@@@@@@@@@@@@@
// Auteur : Y. Colaisseau
// date : 10/11/12
// description : classe qui g�re les boucle de jeu et charge la fen�tre
//@@@@@@@@@@@@@@@@@@@



#pragma once


#include "GeneralConfig.h"
#include "Cintro.hpp"
#include "Cmenu.hpp"
#include "Ccredits.hpp"
#include "Cscores.hpp"
#include "Coptions.hpp"
#include "Cpartie.hpp"


class Cgame
{

protected :

	//attributs
	sf::RenderWindow window;

	Cintro m_intro;
	Cmenu m_menu;
	Ccredits m_credits;
	Cscores m_scores;
	Coptions m_options;
	Cpartie m_Party;

	CSpriteManager* m_Smanager;

	sf::Clock m_ClockDeltaTime;
	float DeltaTime;

	sf::Music m_MusiqueIntro;


	TypeGameParty m_GameParty;

	//m�thode
	void GameDisplay();
	void GameEvent();
	void GameInit();
	void GameDeinit();

	void setIntroVolume(float);

public :

	//constructeur - destructeur
	Cgame();
	~Cgame();

	//m�thode

	void GameUpdate();


};


