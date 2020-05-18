//@@@@@@@@@@@@@@@@@@@
// Auteur : Y. Colaisseau
// date : 10/11/12
// description : classe qui gère les scores
//@@@@@@@@@@@@@@@@@@@


#pragma once

#include "GeneralConfig.h"


typedef struct T_Score
{
	char Name[15];
	int Score;
};


class Cscores
{

protected :


std::vector<T_Score> m_VecScore;

sf::Sprite m_ScoresBackground;
sf::RectangleShape m_RectScores;

sf::Text m_TabTextName[10] ;
sf::Text m_TabTextScore[10] ;
sf::Text m_TitreScores;
sf::Text m_TitreInfosReinit;

bool m_bActualiseScore;


void TrierMap();


public :

	Cscores();
	~Cscores();

	void InitScores();
	void DeinitScores();
	void UpdateScores(float _dt);
	void DisplayScores(sf::RenderWindow& _render);
	bool EventScores(sf::Event _event);

	void AddNewScores(int _i , std::string _name);

	int getMiniScore() {  return m_VecScore[9].Score; };

	void ReinitScore() ;

	void ActualiseScoresoptions() ;


};