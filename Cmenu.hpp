//@@@@@@@@@@@@@@@@@@@
// Auteur : Y. Colaisseau
// date : 10/11/12
// description : classe qui gère le menu
//@@@@@@@@@@@@@@@@@@@


#pragma once 

#include "GeneralConfig.h"


class Cmenu
{

protected :

	sf::Sprite m_FondMenu;
	sf::Sprite m_Selection;

	sf::Text m_Titre;

	sf::Text m_Jouer;
	sf::Text m_Option;
	sf::Text m_Scores;
	sf::Text m_Credit;
	sf::Text m_Quitter;

	int m_MenuChoix;



public :

	Cmenu();
	~Cmenu();


	void UpdateMenu(float _dt);
	void DisplayMenu(sf::RenderWindow& _RenderWindows);
	int EventMenu(sf::Event& );

	void InitMenu();
	void DeinitMenu();

	int getMenuChoix();

	void ActualiseOptions();


};