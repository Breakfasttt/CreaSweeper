//@@@@@@@@@@@@@@@@@@@
// Auteur : Y. Colaisseau
// date : 20/11/12
// description : classe qui gère une partie
//@@@@@@@@@@@@@@@@@@@


#pragma once 



#include "GeneralConfig.h"
#include "Cnode.hpp"
#include "Cpathfinder.hpp"
#include "Cperso.hpp"
#include "Cscores.hpp"


enum T_Stade
{
	INTRO_PARTIE = 0,
	GAME_PARTIE,
	MORT_PARTIE,
	ECHAP_PARTIE,
};


class Cpartie
{


protected :


	//@@@@@@@@@@@@@ PARTIE @@@@@@@@@@@@

	sf::Sprite m_BackgroundParty;

	Cnode m_Plateau[16][30] ;
	CpathFinder m_PathFinder;
	int n_NombreLigne;

	T_Stade m_StadeActuel;

	sf::RectangleShape m_TextBox;

	Cscores* m_pScores;


	//@@@@@@@@@@@@@  SOUS PARTIE @@@@@@@@@@@@


	//intro 

	sf::Text m_InfosTitre;
	sf::Text m_InfosIntro1;
	sf::Text m_InfosIntro2;
	sf::Text m_InfosIntro3;
	sf::Text m_InfosIntro4;

	void AfficheIntro(sf::RenderWindow& _render);
	void UpdateIntro(float _dt);
	void EventIntro(sf::Event _event);

	void InitIntro();
	void DeinitIntro();
	void ReinitIntro();
	void ActualiseOptionsIntro();

	// game

	sf::RectangleShape m_FondPlateau;
	sf::RectangleShape m_BoxTextScores;
	sf::RectangleShape m_BoxTextPower;

	sf::Text m_indication;
	sf::Text m_TimerSuperPower;

	sf::Text m_PartyTextScoresTitre;
	sf::Text m_PartyTextTimerTitre ;
	sf::Text m_PartyTextNiveauTitre ;

	sf::Text m_PartyTextScores;
	sf::Text m_PartyTextTimer ;
	sf::Text m_partyTextNiveau;

	sf::Clock m_ClockTimer;
	sf::Clock m_ClockSuperPower;

	int m_Timer ;
	int m_TimerPouvoir;
	int m_Scores;
	int m_niveau;
	int m_niveauUP;


	Cperso m_perso;
	Cnode* m_NodeDeFin;
	Cnode* m_NodeDeDebut;


	void AfficheGame(sf::RenderWindow& _render);
	void UpdateGame(float _dt);
	void EventGame(sf::Event _event);

	void InitGame();
	void DeinitGame();
	void ReinitGame();
	void ActualiseOptionsGame();

	void GenereMap(int _nbLigne);
	void ReinitMap();
	void CalculNombreMine(int _nbLigne);
	void AfficheChemin();
	void DevoileCase(int , int);

	//mort

	sf::Text m_textTitreMort;
	sf::Text m_textNouveauRecord;
	sf::Text m_NomEntrer;
	std::string m_nomEntrerString;

	bool isNewRecord;
	bool NomRentrer;


	void AfficheMort(sf::RenderWindow& _render);
	void UpdateMort(float _dt);
	void EventMort(sf::Event _event);

	void InitMort();
	void DeinitMort();
	void ReinitMort();
	void ActualiseOptionsMort();

	//escape

	T_Stade m_StadeAvant;
	sf::Text m_InfosEscape1;
	sf::Text m_InfosEscape2;

		
	void AfficheEscape(sf::RenderWindow& _render);	
	void UpdateEscape(float _dt);	
	void EventEscape(sf::Event _event);

	void InitEscape();
	void DeinitEscape();
	void ReinitEscape();
	void ActualiseOptionsEscape();



public :

	Cpartie();
	~Cpartie();

	
	//@@@@@@@@@@@@@ PARTIE @@@@@@@@@@@@

	void InitPartie();
	void DeinitPartie();
	void ReinitPartie();

	void ActualiseOptions();

	void UpdatePartie(float _dt);
	void DisplayPartie(sf::RenderWindow& _render);
	bool EventPartie(sf::Event _event);

	void setScore(Cscores* _c) {m_pScores = _c;};


};