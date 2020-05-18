#include "CGame.hpp"




Cgame::Cgame()
{
	window.create(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), WINDOW_NAME, WINDOW_WITHOUT_RESIZE );
	//window.setFramerateLimit(60);
	m_ClockDeltaTime.restart();
	DeltaTime= 0.0f;

	m_Smanager = CSpriteManager::getSmanager();

	GameInit();

	std::string TempLinkMusic = CSpriteManager::getSmanager()->getMusicByName("Music_Intro_1");

	if(TempLinkMusic != "" )
	{
		if( !m_MusiqueIntro.openFromFile(TempLinkMusic) )
			std::cout << "Erreur loading Musique Intro" << std::endl;
		else
		{
			m_MusiqueIntro.play();
			m_MusiqueIntro.setVolume( CSpriteManager::getSmanager()->getGlobalVolume() ) ;
			m_MusiqueIntro.setLoop(true);
		}
	}

	m_GameParty = INTRO;

	
}

Cgame::~Cgame()
{
	GameDeinit();
	m_MusiqueIntro.stop();
}

void Cgame::GameUpdate()
{
	 while (window.isOpen())
    {
		sf::Time TempDeltaTime = m_ClockDeltaTime.restart();
		DeltaTime = TempDeltaTime.asSeconds();


        GameEvent();

		switch(m_GameParty)
		{
			case INTRO :  m_intro.Update(DeltaTime); 

							if(m_intro.isIntroEnd())
							{
								m_GameParty = MENU;
							}	

							break;

			case MENU  : m_menu.UpdateMenu(DeltaTime);
				
						 break;

			case OPTION :  m_options.UpdateOptions(DeltaTime) ; 
							
							if(m_options.isOptionChanger() )
							{

								m_MusiqueIntro.setVolume(CSpriteManager::getSmanager()->getGlobalVolume());

								m_options.ActualiseOptions();
								m_menu.ActualiseOptions();
								m_credits.ActualiseOptions();
								m_Party.ActualiseOptions();
								m_scores.ActualiseScoresoptions();
								
								m_options.setOptionChanger(false);			
							}
							
							break;

			case GAME : m_Party.UpdatePartie(DeltaTime); break;

			case SCORE : m_scores.UpdateScores(DeltaTime) ; break;

			case CREDITS : m_credits.CreditUpdate(DeltaTime); break;

			default : m_GameParty = MENU; break;
	
		}

		
		GameDisplay();
       
    }
}

void Cgame::GameDisplay()
{
	window.clear();

		switch(m_GameParty)
		{
			case INTRO :  m_intro.Display(window); break;

			case MENU  :  m_menu.DisplayMenu(window); break;

			case OPTION : m_options.DisplayOptions(window); break;

			case GAME : m_Party.DisplayPartie(window); break;

			case SCORE : m_scores.DisplayScores(window); break;

			case CREDITS : m_credits.CreditDisplay(window); break;

			default : m_GameParty = MENU; break;
	
		}
	

	window.display();
}

void Cgame::GameEvent()
{
	sf::Event event;

	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}

		int Temp = -1;

		switch(m_GameParty)
		{
		case INTRO : m_intro.IntroEvent(event) ; break;

		case MENU  : 	Temp = m_menu.EventMenu(event); 


						if(Temp != -1  )
						{
							Temp = Temp + 1;

							if(Temp == 6)
							{
								window.close();
								break;
							}

							m_GameParty = (TypeGameParty)Temp;

							if( m_GameParty == GAME )
							{

								std::string TempLinkMusic = CSpriteManager::getSmanager()->getMusicByName("Music_Jeu");

								if(TempLinkMusic != "" )
								{
									if( !m_MusiqueIntro.openFromFile(TempLinkMusic) )
										std::cout << "Erreur loading Musique Intro" << std::endl;
									else
									{
										m_MusiqueIntro.play();
										m_MusiqueIntro.setVolume( CSpriteManager::getSmanager()->getGlobalVolume() ) ;
										m_MusiqueIntro.setLoop(true);
									}
								}
							}
							
						}
			break;

		case OPTION : if(m_options.EventOptions(event) )
					  {
							m_GameParty = MENU;
					  } break;

		case GAME :		if( m_Party.EventPartie(event) )
						{

							std::string TempLinkMusic = CSpriteManager::getSmanager()->getMusicByName("Music_Intro_1");

							if(TempLinkMusic != "" )
							{
								if( !m_MusiqueIntro.openFromFile(TempLinkMusic) )
									std::cout << "Erreur loading Musique Intro" << std::endl;
								else
								{
									m_MusiqueIntro.play();
									m_MusiqueIntro.setVolume( CSpriteManager::getSmanager()->getGlobalVolume() ) ;
									m_MusiqueIntro.setLoop(true);
								}
							}

							m_GameParty = MENU;
						} break;

		case SCORE :  if(m_scores.EventScores(event) )
					  {
							m_GameParty = MENU;
					  } 
					  break;

		case CREDITS :  if(m_credits.CreditEvent(event) )
						{
							m_GameParty = MENU;
						}	

						break;

		default : m_GameParty = MENU; break;

		}	   
	}

}

void Cgame::GameInit()
{
	m_intro.Init();
	m_menu.InitMenu();
	m_credits.CreditInit();
	m_scores.InitScores();
	m_options.InitOptions();
	m_Party.InitPartie();
	m_Party.setScore(&m_scores);
}

void Cgame::GameDeinit()
{
	m_intro.Deinit();
	m_menu.DeinitMenu();
	m_credits.CreditDeinit();
	m_scores.DeinitScores();
	m_options.DeinitOptions();
}


void Cgame::setIntroVolume(float _volume)
{
	m_MusiqueIntro.setVolume(_volume);
}
