#include "Cintro.hpp"


Cintro::Cintro()
{

}

Cintro::~Cintro()
{
	

}

void Cintro::Init()
{


	m_NbreBackground = 0;

	ChangeBackGroundWithId(m_NbreBackground);

	sf::Color TempColor = m_Background.getColor();
	TempColor.a = 0;
	m_Background.setColor(TempColor);

	m_breturn = false;
	m_EndIntro = false;


	TimeIntro = TIME_INTRO / 3.0f;
	TimeAlpha = 0.33f * TimeIntro;

	DeltaAlphaIntro = 1.0f/TimeAlpha;

	m_IntroClock.restart();
		

}

void Cintro::Deinit()
{
	//sf::Texture* tempText = NULL;
	//m_Background.setTexture(*tempText);
}


void Cintro::IntroEvent(sf::Event& _event)
{
	if(_event.type == sf::Event::KeyReleased)
	{
		if( _event.key.code == sf::Keyboard::Return )
		{
			m_EndIntro = true;	
		}
	}
}

void Cintro::Update(float _deltaTime)
{	

	if(!m_EndIntro)
	{
		sf::Color TempColor = m_Background.getColor();

		sf::Time tempClock = m_IntroClock.getElapsedTime();
		float TimeElapsed = tempClock.asSeconds() ;

		if( TimeElapsed < TimeAlpha )
		{
			TempColor.a = (sf::Uint8)(255 * (DeltaAlphaIntro * TimeElapsed)) ;
			m_Background.setColor(TempColor);
		}
		else if( TimeElapsed > TimeAlpha && TimeElapsed < TimeIntro - TimeAlpha  )
		{
		}
		else if( TimeElapsed > TimeIntro - TimeAlpha && TimeElapsed < TimeIntro && m_NbreBackground != 2)
		{
			if( TempColor.a != 0 )
			{
				TempColor.a = (sf::Uint8)(255 * (1 - (DeltaAlphaIntro * (TimeElapsed - TimeAlpha ) ) ) );
			}


			m_Background.setColor(TempColor);
		}
		else
		{

			m_NbreBackground++;
			if(m_NbreBackground !=3)
			{
				ChangeBackGroundWithId(m_NbreBackground);
			}
			else
			{
				m_EndIntro = true;
			}

			m_IntroClock.restart();
		}
	}
}

void Cintro::Display(sf::RenderWindow& _RenderWindows)
{
	_RenderWindows.draw(m_Background);
}


void Cintro::ChangeBackGroundWithId(int _id)
{

	sf::Texture* textureTemp = NULL; 

	switch(_id)
	{
		case 0 : textureTemp = CSpriteManager::getSmanager()->getTextureByName("Background_Intro_1");  break;
		case 1 : textureTemp = CSpriteManager::getSmanager()->getTextureByName("Background_Intro_2");break;
		case 2 : textureTemp = CSpriteManager::getSmanager()->getTextureByName("Background_Intro_3");break;
		default : std::cout << "ErreurChangeBackgroundIntro" << std::endl; break;
		
	}


	if(textureTemp != NULL)
	{
		m_Background.setTexture( *textureTemp  );

		sf::Color TempColor = m_Background.getColor();
		TempColor.a = 0;
		m_Background.setColor(TempColor);
	}
}


