//@@@@@@@@@@@@@@@@@@@
// Auteur : Y. Colaisseau
// date : 10/11/12
// description : classe qui gère la aprtie Credits
//@@@@@@@@@@@@@@@@@@@


#pragma once

#include "GeneralConfig.h"

class Ccredits
{

protected :

	sf::Text m_TitreCredits;

	sf::Sprite m_CreditsBackground;
	sf::Sprite m_LogoCrea;

	std::string m_Titre;

	sf::Text m_InfosText;

	sf::Clock m_clockCredits;

	int m_NbreInfos;


public :

	Ccredits();
	~Ccredits();

	void CreditInit();
	void CreditDeinit();
	void CreditUpdate(float _dt);
	void CreditDisplay(sf::RenderWindow& _render );
	bool CreditEvent(sf::Event&);


	void ActualiseOptions();


};