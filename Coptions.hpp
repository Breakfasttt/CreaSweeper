//@@@@@@@@@@@@@@@@@@@
// Auteur : Y. Colaisseau
// date : 20/11/12
// description : classe qui gère les options
//@@@@@@@@@@@@@@@@@@@


#pragma once 

#include "GeneralConfig.h"


class Coptions
{

protected :


	bool m_bOptionsChanger;

	sf::Sprite m_backgroundOptions;

	sf::Text m_OptionsTitre;
	sf::Text m_OptionsVolume;
	sf::Text m_OptionsLangue;

	sf::Text m_ValeurVolume;
	sf::Text m_ValeurLangue;

	sf::Sprite m_ButtonHUD[4];


public :

	Coptions();
	~Coptions();

	void InitOptions();
	void DeinitOptions();
	void UpdateOptions(float _dt);
	void DisplayOptions(sf::RenderWindow& _render);
	bool EventOptions(sf::Event _event);

	void ActualiseOptions();


	inline bool isOptionChanger(){return m_bOptionsChanger;};
	void setOptionChanger(bool _b) {m_bOptionsChanger = _b;};


};