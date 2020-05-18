//@@@@@@@@@@@@@@@@@@@
// Auteur : Y. Colaisseau
// date : 20/11/12
// description : classe qui gère une partie
//@@@@@@@@@@@@@@@@@@@



#include "Cpartie.hpp"




Cpartie::Cpartie()
{

}

Cpartie::~Cpartie()
{

}


//@@@@@@@@@@@@@ Initialisation d'une partie @@@@@@@@@@@@


void Cpartie::InitPartie()
{
	m_StadeActuel = INTRO_PARTIE;
	m_pScores = NULL,

	m_TextBox.setSize( sf::Vector2f(800.0f, 650.0f) );
	m_TextBox.setOrigin(m_TextBox.getGlobalBounds().width/2.0f , m_TextBox.getGlobalBounds().height/2.0f );
	m_TextBox.setFillColor(sf::Color(0,0,255,190 ) );
	m_TextBox.setOutlineThickness(5.0f);
	m_TextBox.setOutlineColor(sf::Color(255,0,0,255 ) );
	m_TextBox.setPosition( WINDOW_SIZE_X / 2.0f , WINDOW_SIZE_Y / 2.0f );

	

	//background

	sf::Texture* TempTexture = CSpriteManager::getSmanager()->getTextureByName("Jeu_Background");

	if(TempTexture != NULL)
	{
		m_BackgroundParty.setTexture(*TempTexture);	
	}

	InitIntro();
	InitGame();
	InitMort();
	InitEscape();

}

void Cpartie::DeinitPartie()
{

	DeinitIntro();
	DeinitGame();
	DeinitMort();
	DeinitEscape();
}

void Cpartie::ReinitPartie()
{

	m_StadeActuel = INTRO_PARTIE;

	ReinitIntro();
	ReinitGame();
	ReinitMort();
	ReinitEscape();
}

void Cpartie::ActualiseOptions()
{
	ActualiseOptionsEscape();
	ActualiseOptionsMort();
	ActualiseOptionsGame();
	ActualiseOptionsIntro();
}


//@@@@@@@@@@@@@ PARTIE (public) @@@@@@@@@@@@

//update Partie

void Cpartie::UpdatePartie(float _dt)
{

	switch(m_StadeActuel)
	{
		case INTRO_PARTIE :  UpdateIntro(_dt); break;
		case GAME_PARTIE : UpdateGame(_dt); break;
		case MORT_PARTIE : UpdateMort(_dt); break;
		case ECHAP_PARTIE : UpdateEscape(_dt); break;
		default : m_StadeActuel = INTRO_PARTIE; break;
	}

}

//display_Partie

void Cpartie::DisplayPartie(sf::RenderWindow& _render)
{
	_render.draw(m_BackgroundParty);


	switch(m_StadeActuel)
	{
		case INTRO_PARTIE : AfficheIntro(_render); break;
		case GAME_PARTIE : AfficheGame(_render); break;
		case MORT_PARTIE : AfficheMort(_render); break;
		case ECHAP_PARTIE : AfficheEscape(_render); break;
		default : m_StadeActuel = INTRO_PARTIE; break;
	
	}
}

//event Partie

bool Cpartie::EventPartie(sf::Event _event)
{

	switch(m_StadeActuel)
	{
		case INTRO_PARTIE : EventIntro(_event) ;  break;
		case GAME_PARTIE : EventGame(_event) ; break;
		case MORT_PARTIE : EventMort(_event) ; break;
		case ECHAP_PARTIE : EventEscape(_event) ; break;
		default : m_StadeActuel = INTRO_PARTIE; break;
	
	}



	if(_event.type == sf::Event::KeyReleased)
	{
		if( _event.key.code == sf::Keyboard::Return && 
			( m_StadeActuel == ECHAP_PARTIE || NomRentrer)  )
		{	
			ReinitPartie();
			return true;	
		}
		else if( _event.key.code == sf::Keyboard::Escape && m_StadeActuel == ECHAP_PARTIE)
		{
			m_StadeActuel = m_StadeAvant;
		}
		else if( _event.key.code == sf::Keyboard::Escape && m_StadeActuel != ECHAP_PARTIE)
		{	
			m_StadeAvant = m_StadeActuel;
			m_StadeActuel = ECHAP_PARTIE;
		}
	}

	return false;
}



//@@@@@@@@@@@@@  SOUS PARTIE (protected) @@@@@@@@@@@@


// intro

void Cpartie::InitIntro()
{
	m_InfosTitre.setString( CSpriteManager::getSmanager()->getTextByName("Jeu_Intro_Titre")  );
	m_InfosIntro1.setString( CSpriteManager::getSmanager()->getTextByName("Jeu_Intro_Infos") );
	m_InfosIntro2.setString( CSpriteManager::getSmanager()->getTextByName("Jeu_Intro_Infos2") );
	m_InfosIntro3.setString( CSpriteManager::getSmanager()->getTextByName("Jeu_Intro_Infos3") );
	m_InfosIntro4.setString( CSpriteManager::getSmanager()->getTextByName("Jeu_Intro_Infos4") );


	 m_InfosIntro1.setCharacterSize(18);
	 m_InfosIntro2.setCharacterSize(18);
	 m_InfosIntro3.setCharacterSize(18);
	 m_InfosIntro4.setCharacterSize(18);


	 m_InfosTitre.setOrigin( m_InfosTitre.getGlobalBounds().width / 2.0f , 
								m_InfosTitre.getGlobalBounds().height / 2.0f );

	 m_InfosIntro1.setOrigin( m_InfosIntro1.getGlobalBounds().width / 2.0f , 
								m_InfosIntro1.getGlobalBounds().height / 2.0f );

	 m_InfosIntro2.setOrigin( m_InfosIntro2.getGlobalBounds().width / 2.0f , 
								m_InfosIntro2.getGlobalBounds().height / 2.0f );

	 m_InfosIntro3.setOrigin( m_InfosIntro3.getGlobalBounds().width / 2.0f , 
								m_InfosIntro3.getGlobalBounds().height / 2.0f );

	 m_InfosIntro4.setOrigin( m_InfosIntro4.getGlobalBounds().width / 2.0f , 
								m_InfosIntro4.getGlobalBounds().height / 2.0f );

	 float TempOffset = 60.0f;

	 m_InfosTitre.setPosition ( WINDOW_SIZE_X/2.0f , TempOffset );
	 TempOffset += m_InfosTitre.getGlobalBounds().height + 100.0f ;
	 m_InfosIntro1.setPosition ( WINDOW_SIZE_X/2.0f , TempOffset  );
	  TempOffset += m_InfosIntro1.getGlobalBounds().height + 30.0f ;
	 m_InfosIntro2.setPosition ( WINDOW_SIZE_X/2.0f , TempOffset );
	 TempOffset += m_InfosIntro2.getGlobalBounds().height + 30.0f ;
	 m_InfosIntro3.setPosition ( WINDOW_SIZE_X/2.0f ,TempOffset );
	  TempOffset += m_InfosIntro3.getGlobalBounds().height + 30.0f ;
	 m_InfosIntro4.setPosition ( WINDOW_SIZE_X/2.0f , TempOffset );

}

void Cpartie::AfficheIntro(sf::RenderWindow& _render)
{
	_render.draw(m_TextBox);

	_render.draw(m_InfosTitre);
	_render.draw(m_InfosIntro1);
	_render.draw(m_InfosIntro2);
	_render.draw(m_InfosIntro3);
	_render.draw(m_InfosIntro4);
}

void Cpartie::UpdateIntro(float _dt)
{

}

void Cpartie::EventIntro(sf::Event _event)
{
	if(_event.type == sf::Event::KeyReleased)
	{
		if( _event.key.code == sf::Keyboard::Return)
		{	
			GenereMap(n_NombreLigne);
			m_StadeActuel = GAME_PARTIE;
		}
	}
}

void Cpartie::DeinitIntro()
{

}

void Cpartie::ReinitIntro()
{
	InitIntro();
}

void Cpartie::ActualiseOptionsIntro()
{
	InitIntro();
}


//game

void Cpartie::InitGame()
{

	//init fond plateau

	m_FondPlateau.setSize(sf::Vector2f(SIZE_PLATEAU_X , SIZE_PLATEAU_Y  ) ) ;
	m_FondPlateau.setFillColor( sf::Color::White );
	m_FondPlateau.setOutlineThickness( 1.0f );
	m_FondPlateau.setOutlineColor( sf::Color::Black );
	m_FondPlateau.setPosition(WINDOW_SIZE_X - SIZE_PLATEAU_X , 0.0f);


	//init box & text scores

	m_PartyTextScoresTitre.setString( CSpriteManager::getSmanager()->getTextByName("Jeu_Party_ScoreTitre")  ) ;
	m_PartyTextTimerTitre.setString( CSpriteManager::getSmanager()->getTextByName("Jeu_Party_TimerTitre")  ) ;
	m_PartyTextNiveauTitre.setString( CSpriteManager::getSmanager()->getTextByName("Jeu_Party_NiveauTitre")  ) ;
	m_PartyTextScores.setString("0");
	
	m_PartyTextScoresTitre.setCharacterSize(18);
	m_PartyTextTimerTitre.setCharacterSize(18);
	m_PartyTextNiveauTitre.setCharacterSize(18);
	m_PartyTextTimer.setCharacterSize(18);
	m_partyTextNiveau.setCharacterSize(18);
	m_PartyTextScores.setCharacterSize(18);
	
	m_PartyTextScoresTitre.setPosition( 50.0f ,100.0f );
	m_PartyTextScores.setPosition( 50.0f + m_PartyTextScoresTitre.getGlobalBounds().width + 5.0f , 100.0f);
	m_PartyTextTimerTitre.setPosition( 50.0f , 150.0f );
	m_PartyTextTimer.setPosition( 50.0f + m_PartyTextTimerTitre.getGlobalBounds().width + 5.0f , 150.0f);
	m_PartyTextNiveauTitre.setPosition( 50.0f , 200.0f );
	m_partyTextNiveau.setPosition( 50.0f + m_PartyTextNiveauTitre.getGlobalBounds().width + 5.0f , 200.0f);


	m_BoxTextScores.setSize( sf::Vector2f( 500.0f, 200.0f   ) );
	m_BoxTextScores.setFillColor(sf::Color(0,0,255,190 ) );
	m_BoxTextScores.setOutlineThickness(1.0f);
	m_BoxTextScores.setOutlineColor(sf::Color(255,0,0,255 ) );
	m_BoxTextScores.setPosition( 50.0f ,100.0f );


	//init box & text infos

	m_BoxTextPower.setSize( sf::Vector2f( WINDOW_SIZE_X - SIZE_PLATEAU_X , 50.0f  ) );
	m_BoxTextPower.setFillColor(sf::Color(0,0,255,190 ) );
	m_BoxTextPower.setOutlineThickness(1.0f);
	m_BoxTextPower.setOutlineColor(sf::Color(255,0,0,255 ) );
	m_BoxTextPower.setOrigin( 0.0f , m_BoxTextPower.getGlobalBounds().height );
	m_BoxTextPower.setPosition( 0.0f ,720.0f );

	m_indication.setString( CSpriteManager::getSmanager()->getTextByName("Jeu_Party_Indication") );
	m_indication.setCharacterSize(18);
	m_indication.setPosition( 400.0f , 680.0f );


	m_TimerSuperPower.setString( CSpriteManager::getSmanager()->getTextByName("Jeu_Party_Pouvoir") );
	m_TimerSuperPower.setCharacterSize(18);
	m_TimerSuperPower.setPosition( 30.0f , 680.0f );

	m_ClockSuperPower.restart();

	//init du plateau

	n_NombreLigne = 16 ;
	m_niveauUP= 0;
	m_Scores =0;
	m_TimerPouvoir = TEMPS_POUVOIR;

	
	for(int i =0; i < 16 ; ++i)
	{
		for(int j =0; j < 30 ; ++j)
		{

			m_Plateau[i][j].setColonne(i);
			m_Plateau[i][j].setLigne(j);
			m_Plateau[i][j].setIsMine(false);
			m_Plateau[i][j].setSprite("Jeu_Plateau_0");
			m_Plateau[i][j].setPosition( WINDOW_SIZE_X - SIZE_PLATEAU_X + i* SIZE_CASE ,
										 WINDOW_SIZE_Y - j* SIZE_CASE );

		}
	}

	


}

void Cpartie::UpdateGame(float _dt)
{

	int TempPosX =m_perso.getPosX();
	int TempPosY =m_perso.getPosY();


	//actualisation du timer
	float tempSecond = m_ClockTimer.getElapsedTime().asSeconds();

	if( tempSecond >= 1.0f )
	{
		m_ClockTimer.restart();
		m_Timer--;

		std::stringstream oss;

		oss << m_Timer;
		m_PartyTextTimer.setString( oss.str()  ) ;

	}

	//actualisation du score lors du mouvement du perso

	if(m_perso.getAsMoved())
	{
		m_Scores -= m_Plateau[TempPosX][TempPosY].getNbreMine();
		m_perso.setAsmoved(false);

		std::stringstream oss;
		oss << m_Scores;
		m_PartyTextScores.setString( oss.str()  ) ;


		std::stringstream oss2;
		oss2 << CSpriteManager::getSmanager()->getTextByName("Jeu_Party_Indication") << " " 
			  << m_Plateau[TempPosX][TempPosY].getNbreMine() ;

		m_indication.setString( oss2.str()  ) ;

		if(TempPosY!=0 && TempPosY!= (n_NombreLigne-1) )
			DevoileCase( TempPosX , TempPosY );
	}

	//actualisation du superpouvoir!!!


	if( m_ClockSuperPower.getElapsedTime().asSeconds() > 1.0f && m_TimerPouvoir != 0)
	{
		m_ClockSuperPower.restart();
		m_TimerPouvoir--;

		if(m_TimerPouvoir < 0)
			m_TimerPouvoir =0;

		if(m_TimerPouvoir!=0)
		{
			std::stringstream oss ;
			oss << CSpriteManager::getSmanager()->getTextByName("Jeu_Party_Pouvoir") << " " << m_TimerPouvoir;
			m_TimerSuperPower.setString( oss.str() );
		}
		else
		{
			bool Langue = CSpriteManager::getSmanager()->getEnglishMode();

			std::stringstream oss ;
			oss << CSpriteManager::getSmanager()->getTextByName("Jeu_Party_Pouvoir")  << " " ;

			if(!Langue)
			{
				oss << "Prêt !";
			}
			else
			{
				oss << "Ready !";		
			}

			m_TimerSuperPower.setString( oss.str() );
		}
	}

	//autorise le perso a utiliser son pouvoir
	if( m_TimerPouvoir == 0 && !m_perso.getPowerOn() )
	{
		m_perso.setPowerOn(true);	
	}

	//si utilisation du pouvoir

	if( m_perso.getUsedPower() )
	{
		m_TimerPouvoir = TEMPS_POUVOIR;
		//m_ClockSuperPower.restart();
		m_perso.setPowerOn(false);
		m_perso.setUsedPower(false);
		int RandX = 0;
		int RandY = 0;
	
		do
		{
			 RandX = rand() % 16 ;
			 RandY =  (rand() % (n_NombreLigne -2) ) + 1;
		}while( ( RandX == 0 ) || RandY == (n_NombreLigne -1)  || !m_Plateau[RandX][RandY].getCacher() );


		DevoileCase(RandX,RandY);
	
	}


	//condition de réussite
	if(   m_Plateau[TempPosX][TempPosY].getIsEnd() )
	{
		n_NombreLigne++;

		if(n_NombreLigne >30)
		{
			n_NombreLigne = 30;
			m_niveauUP++;
		}

		GenereMap(n_NombreLigne);
		TempPosX =m_perso.getPosX();
		TempPosY =m_perso.getPosY();

		m_Scores += 100 ;
		std::stringstream oss;
		oss << m_Scores;
		m_PartyTextScores.setString( oss.str()  ) ;
	}

	//condition de défaite

	if(  m_Plateau[TempPosX][TempPosY].getIsMine() || 
		  m_Timer == 0)
	{
		AfficheChemin();
		m_StadeActuel = MORT_PARTIE;
		
		if( m_pScores->getMiniScore() < m_Scores )
		{
			isNewRecord = true;
		}
	}



}

void Cpartie::EventGame(sf::Event _event)
{
	m_perso.EventPerso(_event);
}

void Cpartie::AfficheGame(sf::RenderWindow& _render)
{
	_render.draw(m_FondPlateau);

	_render.draw(m_BoxTextScores);
	_render.draw(m_BoxTextPower);

	_render.draw(m_PartyTextScoresTitre);
	_render.draw(m_PartyTextScores);
	_render.draw(m_PartyTextTimerTitre);
	_render.draw(m_PartyTextTimer);
	_render.draw(m_PartyTextNiveauTitre);
	_render.draw(m_partyTextNiveau);
	_render.draw(m_indication);
	_render.draw(m_TimerSuperPower);


	for(int i =0; i < 16 ; ++i)
	{
		for(int j =0; j < 30 ; ++j)
		{

			m_Plateau[i][j].DisplayNode(_render);

		}
	}

	m_perso.DisplayPerso(_render);


}

void Cpartie::DeinitGame()
{

}

void Cpartie::ReinitGame()
{
	ReinitMap();
	m_niveauUP =0;
	m_Scores = 0;
	n_NombreLigne = 16;
	isNewRecord = false;
	m_TimerPouvoir = TEMPS_POUVOIR;

	m_PartyTextScores.setString("0");
}

void Cpartie::ActualiseOptionsGame()
{
	m_PartyTextScoresTitre.setString( CSpriteManager::getSmanager()->getTextByName("Jeu_Party_ScoreTitre")  ) ;
	m_PartyTextTimerTitre.setString( CSpriteManager::getSmanager()->getTextByName("Jeu_Party_TimerTitre")  ) ;
	m_PartyTextNiveauTitre.setString( CSpriteManager::getSmanager()->getTextByName("Jeu_Party_NiveauTitre")  ) ;
	m_indication.setString( CSpriteManager::getSmanager()->getTextByName("Jeu_Party_Indication")  ) ;

	m_PartyTextScoresTitre.setPosition( 50.0f ,100.0f );
	m_PartyTextScores.setPosition( 50.0f + m_PartyTextScoresTitre.getGlobalBounds().width + 5.0f , 100.0f);
	m_PartyTextTimerTitre.setPosition( 50.0f , 150.0f );
	m_PartyTextTimer.setPosition( 50.0f + m_PartyTextTimerTitre.getGlobalBounds().width + 5.0f , 150.0f);
	m_PartyTextNiveauTitre.setPosition( 50.0f , 200.0f );
	m_partyTextNiveau.setPosition( 50.0f + m_PartyTextNiveauTitre.getGlobalBounds().width + 5.0f , 200.0f);
}

void Cpartie::GenereMap(int _nbLigne)
{

	ReinitMap();

	int randX = 0;
	int randY = 0;
	int NbreMine =   ( (40* _nbLigne * 16) / 256)  ;
	m_Timer = TEMPS_BASE +  ( (_nbLigne-16) * TEMPS_ADDITIONNEL ) ;
	m_ClockTimer.restart();

	m_niveau = (_nbLigne+1) -16 + m_niveauUP;

	std::stringstream oss;
	oss << m_Timer;
	m_PartyTextTimer.setString( oss.str()  ) ;

	oss.str("");

	oss << m_niveau ;
	m_partyTextNiveau.setString( oss.str()  ) ;



	randX = rand() % 16 ;
	randY= rand() % 16 ;


	Cnode* NodeDebut = NULL;
	Cnode* NodeFin = NULL;

	// placement du début et de la fin

	for(int i = 0; i < 16 ; ++i)
	{

		if( randX == i)
		{
			m_Plateau[i][_nbLigne-1 ].setSprite("Jeu_Plateau_Debut");
			m_Plateau[i][0].setSprite("Jeu_Plateau_Debut");
			m_Plateau[i][0].setIsBegin(true);

			NodeDebut = &m_Plateau[i][0];
			m_perso.setPosDebut(i,0);
		}

		if(randY == i)
		{
			m_Plateau[i][0].setSprite("Jeu_Plateau_Debut");
			m_Plateau[i][_nbLigne-1 ].setSprite("Jeu_Plateau_Fin");
			m_Plateau[i][_nbLigne-1 ].setIsEnd(true);	

			NodeFin = &m_Plateau[i][_nbLigne-1 ];
		}

		if(randX!=i && randY!=i)
		{
			m_Plateau[i][0].setSprite("Jeu_Plateau_Debut");
			m_Plateau[i][_nbLigne-1 ].setSprite("Jeu_Plateau_Debut");
		}
	}


	//placement des mines

	do
	{
		while(NbreMine != 0)
		{
			randX = rand() % 16 ;
			randY =  (rand() % (_nbLigne -2) ) + 1;

			if( !m_Plateau[randX][randY].getIsMine() && !m_Plateau[randX][randY].getIsEnd() )
			{
				m_Plateau[randX][randY].setIsMine(true);
				m_Plateau[randX][randY].setSprite("Jeu_Plateau_Mine");
				NbreMine--;
			}
		}

		//calcul du nombre de mine

		CalculNombreMine(_nbLigne);

	}while( !m_PathFinder.FindPath(m_Plateau, NodeDebut, NodeFin, _nbLigne  )  );
	//tant qu'un chemin n'est pas trouver


	for(int i = 0 ; i < 16 ; ++i )
	{
		for(int j = 1 ; j < _nbLigne-1 ; ++j )
		{
			
			m_Plateau[i][j].setCacher(true);
		}		
	}

	
	do
	{
		randX = rand() % 16 ;

	}while( m_Plateau[randX][1].getIsMine() );


	DevoileCase(randX,1);

	
	m_NodeDeFin = NodeFin;
	m_NodeDeDebut = NodeDebut;


	NodeDebut = NULL;
	NodeFin = NULL;
}

void Cpartie::AfficheChemin()
{
	Cnode* TempNode = m_NodeDeFin;

	while( TempNode != m_NodeDeDebut)
	{
		TempNode = TempNode->getParent();
		TempNode->setColor(255,0,0);	
	}

	for(int i = 0 ; i < 16 ; ++i )
	{
		for(int j = 1 ; j < n_NombreLigne-1 ; ++j )
		{
			
			m_Plateau[i][j].setCacher(false);
		}		
	}
}

void Cpartie::CalculNombreMine(int _nbLigne)
{
	//calcul du nombre de mine autour d'une case

	for(int i = 0; i < 16 ; ++i)
	{
		for(int j = 1; j < _nbLigne -1 ; ++j)
		{
			if( !m_Plateau[i][j].getIsMine() 
					&& !m_Plateau[i][j].getIsEnd() 
						&&  !m_Plateau[i][j].getIsBegin()  )
			{
				int NbreMineAutour = 0;

				if( i-1 >=0)
				{
					if( m_Plateau[i-1][j].getIsMine() )
					{
						NbreMineAutour++;
					}				
				}

				if( i-1 >=0 && j+1 < _nbLigne-1)
				{
					if( m_Plateau[i-1][j+1].getIsMine() )
					{
						NbreMineAutour++;
					}				
				}

				if( j+1 < _nbLigne-1)
				{
					if( m_Plateau[i][j+1].getIsMine() )
					{
						NbreMineAutour++;
					}				
				}

				if( i+1 < 16 && j+1 < _nbLigne-1 )
				{
					if( m_Plateau[i+1][j+1].getIsMine() )
					{
						NbreMineAutour++;
					}				
				}
			
				if( i+1 < 16  )
				{
					if( m_Plateau[i+1][j].getIsMine() )
					{
						NbreMineAutour++;
					}				
				}
			

				if( i+1 < 16  && j-1 >=1 )
				{
					if( m_Plateau[i+1][j-1].getIsMine() )
					{
						NbreMineAutour++;
					}				
				}		

				if( j-1 >=1 )
				{
					if( m_Plateau[i][j-1].getIsMine() )
					{
						NbreMineAutour++;
					}				
				}		

				if( i-1 >= 0 && j-1 >=0 )
				{
					if( m_Plateau[i-1][j-1].getIsMine() )
					{
						NbreMineAutour++;
					}				
				}		

				std::stringstream oss ; 

				oss << "Jeu_Plateau_" << NbreMineAutour ;

				m_Plateau[i][j].setSprite( oss.str()  );
				m_Plateau[i][j].setNbreMine(NbreMineAutour);
			}
		}
	}
}

void Cpartie::ReinitMap()
{

	m_perso.setMaxY(n_NombreLigne);
	m_perso.setPosDebut(0,0);

	for(int i =0; i < 16 ; ++i)
	{
		for(int j =0; j < 30 ; ++j)
		{

			m_Plateau[i][j].setNbreMine(0);
			m_Plateau[i][j].setIsEnd(false);
			m_Plateau[i][j].setIsBegin(false);
			m_Plateau[i][j].setColonne(i);
			m_Plateau[i][j].setLigne(j);
			m_Plateau[i][j].setIsMine(false);
			m_Plateau[i][j].setCacher(false);
			m_Plateau[i][j].setSprite("Jeu_Plateau_0");
			m_Plateau[i][j].setPosition( WINDOW_SIZE_X - SIZE_PLATEAU_X + i* SIZE_CASE ,
										 WINDOW_SIZE_Y - j* SIZE_CASE );

			m_Plateau[i][j].setColor(255,255,255);
			

		}
	}

}

void Cpartie::DevoileCase(int _x, int _y) 
{

	m_Plateau[_x][_y].setCacher(false);


	if( ( m_Plateau[_x][_y].getNbreMine() == 0 ) && (_y !=0 && _y!= n_NombreLigne )
		&& !m_Plateau[_x][_y].getIsMine() )
	{

		//devoile la croix
		if( (_x-1) >= 0 && m_Plateau[_x-1][_y].getCacher() )
			DevoileCase( _x-1 , _y );

		if( (_x+1) < 16 && m_Plateau[_x+1][_y].getCacher() )
			DevoileCase( _x+1 , _y );

		if( (_y-1) > 0 && m_Plateau[_x][_y-1].getCacher() )
			DevoileCase( _x , _y-1 );

		if( (_y+1) < n_NombreLigne && m_Plateau[_x][_y+1].getCacher() )
			DevoileCase( _x , _y+1 );

		//devoile la diagonale

		if( ( (_y-1) > 0 ) && ( (_x-1) >= 0 ) && m_Plateau[_x-1][_y-1].getCacher() )
			DevoileCase( _x-1 , _y-1 );

		if( ( (_y-1) > 0 ) && ( (_x+1) < 16 ) && m_Plateau[_x+1][_y-1].getCacher() )
			DevoileCase( _x+1 , _y-1 );

		if( ( (_y+1) < n_NombreLigne )  && ( (_x-1) >= 0 ) && m_Plateau[_x-1][_y+1].getCacher() )
			DevoileCase( _x-1 , _y+1 );

		if( ( (_x+1) < 16 ) && ( (_y+1) < n_NombreLigne ) && m_Plateau[_x+1][_y+1].getCacher() )
			DevoileCase( _x+1 , _y+1 );
	
	}

}


// mort


void Cpartie::AfficheMort(sf::RenderWindow& _render)
{

	_render.draw(m_FondPlateau);
	_render.draw(m_BoxTextScores);

	_render.draw(m_PartyTextScoresTitre);
	_render.draw(m_PartyTextScores);

	_render.draw(m_textTitreMort);

	if(isNewRecord)
	{
		_render.draw(m_textNouveauRecord);
		_render.draw(m_NomEntrer);
	}

	for(int i =0; i < 16 ; ++i)
	{
		for(int j =0; j < 30 ; ++j)
		{

			m_Plateau[i][j].DisplayNode(_render);

		}
	}

	m_perso.DisplayPerso(_render);
}

void Cpartie::EventMort(sf::Event _event)
{
	if( (_event.type == sf::Event::TextEntered) && isNewRecord)
	{
		if( ( m_nomEntrerString.size()   < 5 ) && 
			(_event.text.unicode != 8) && 
			(_event.text.unicode != 13) && isNewRecord 
			&& _event.text.unicode < 128)
		{


			char TempChar =  static_cast<char>(_event.text.unicode);

			m_nomEntrerString.push_back ( TempChar ) ;
			
			m_NomEntrer.setString(   m_nomEntrerString.c_str() );


		}
		else if( ( m_nomEntrerString.size() > 0 ) && 
			     (_event.text.unicode == 8) )
		{
			
			m_nomEntrerString.pop_back();
			m_NomEntrer.setString(   m_nomEntrerString.c_str() );
		}
		else if( _event.text.unicode == 13 && m_nomEntrerString.size()>0 )
		{
			NomRentrer = true;
			m_pScores->AddNewScores(m_Scores , m_nomEntrerString );
		}
	}
	else if( !isNewRecord)
	{
		if( _event.key.code == sf::Keyboard::Return   )
		{
			NomRentrer = true;
		}	
	}
}

void Cpartie::InitMort()
{
	NomRentrer = false;
	isNewRecord = false;
	m_textTitreMort.setString( CSpriteManager::getSmanager()->getTextByName("Mort_Titre_Defaite")  ) ;
	m_textNouveauRecord.setString( CSpriteManager::getSmanager()->getTextByName("Mort_Nouveau_Record")  ) ;

	m_textTitreMort.setCharacterSize(18);
	m_textNouveauRecord.setCharacterSize(18);
	m_NomEntrer.setCharacterSize(18);

	m_textTitreMort.setPosition( 50.0f , 150.0f );
	m_textNouveauRecord.setPosition( 50.0f , 200.0f );
	m_NomEntrer.setPosition( 50.0f + m_textNouveauRecord.getGlobalBounds().width + 5.0f
							, 200.0f );

}

void Cpartie::UpdateMort(float _dt)
{

}

void Cpartie::ReinitMort()
{
	NomRentrer = false;
	m_nomEntrerString.clear();
	m_NomEntrer.setString("");
}

void Cpartie::ActualiseOptionsMort()
{
	m_textTitreMort.setString( CSpriteManager::getSmanager()->getTextByName("Mort_Titre_Defaite")  ) ;
	m_textNouveauRecord.setString( CSpriteManager::getSmanager()->getTextByName("Mort_Nouveau_Record")  ) ;
}

void Cpartie::DeinitMort()
{

}


//escape

void Cpartie::UpdateEscape(float _dt)
{

}

void Cpartie::EventEscape(sf::Event _event)
{

}

void Cpartie::DeinitEscape()
{

}

void Cpartie::AfficheEscape(sf::RenderWindow& _render)
{
	_render.draw(m_TextBox);
	_render.draw(m_InfosEscape1);
	_render.draw(m_InfosEscape2);
}

void Cpartie::InitEscape()
{
	 m_InfosEscape1.setString( CSpriteManager::getSmanager()->getTextByName("Jeu_Escape_Infos") ) ;
	 m_InfosEscape2.setString( CSpriteManager::getSmanager()->getTextByName("Jeu_Escape_Infos1") ) ;


	 m_InfosEscape1.setCharacterSize(18);
	 m_InfosEscape2.setCharacterSize(18);


	 m_InfosEscape1.setOrigin( m_InfosEscape1.getGlobalBounds().width / 2.0f , 
								m_InfosEscape1.getGlobalBounds().height / 2.0f );

	 m_InfosEscape2.setOrigin( m_InfosEscape2.getGlobalBounds().width / 2.0f , 
								m_InfosEscape2.getGlobalBounds().height / 2.0f );

	 m_InfosEscape1.setPosition ( WINDOW_SIZE_X/2.0f , 130.0f );
	 m_InfosEscape2.setPosition ( WINDOW_SIZE_X/2.0f , 130.0f + m_InfosEscape1.getGlobalBounds().height + 10.0f );

}


void Cpartie::ReinitEscape()
{
	 m_InfosEscape1.setString( CSpriteManager::getSmanager()->getTextByName("Jeu_Escape_Infos") ) ;
	 m_InfosEscape2.setString( CSpriteManager::getSmanager()->getTextByName("Jeu_Escape_Infos1") ) ;

	 m_InfosEscape1.setOrigin( m_InfosEscape1.getGlobalBounds().width / 2.0f , 
								m_InfosEscape1.getGlobalBounds().height / 2.0f );

	 m_InfosEscape2.setOrigin( m_InfosEscape2.getGlobalBounds().width / 2.0f , 
								m_InfosEscape2.getGlobalBounds().height / 2.0f );

	 m_InfosEscape1.setPosition ( WINDOW_SIZE_X/2.0f , 130.0f );
	 m_InfosEscape2.setPosition ( WINDOW_SIZE_X/2.0f , 130.0f + m_InfosEscape1.getGlobalBounds().height + 10.0f );
}

void Cpartie::ActualiseOptionsEscape()
{
	 m_InfosEscape1.setString( CSpriteManager::getSmanager()->getTextByName("Jeu_Escape_Infos") ) ;
	 m_InfosEscape2.setString( CSpriteManager::getSmanager()->getTextByName("Jeu_Escape_Infos1") ) ;

	 m_InfosEscape1.setOrigin( m_InfosEscape1.getGlobalBounds().width / 2.0f , 
								m_InfosEscape1.getGlobalBounds().height / 2.0f );

	 m_InfosEscape2.setOrigin( m_InfosEscape2.getGlobalBounds().width / 2.0f , 
								m_InfosEscape2.getGlobalBounds().height / 2.0f );

	 m_InfosEscape1.setPosition ( WINDOW_SIZE_X/2.0f , 130.0f );
	 m_InfosEscape2.setPosition ( WINDOW_SIZE_X/2.0f , 130.0f + m_InfosEscape1.getGlobalBounds().height + 10.0f );
}










