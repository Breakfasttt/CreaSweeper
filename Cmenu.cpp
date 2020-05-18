//@@@@@@@@@@@@@@@@@@@
// Auteur : Y. Colaisseau
// date : 10/11/12
// description : classe qui gère le menu
//@@@@@@@@@@@@@@@@@@@


#include "Cmenu.hpp"


Cmenu::Cmenu()
{

}

Cmenu::~Cmenu()
{

}

void Cmenu::UpdateMenu(float _dt)
{


}

void Cmenu::DisplayMenu(sf::RenderWindow& _RenderWindows)
{
	_RenderWindows.draw(m_FondMenu);

	_RenderWindows.draw(m_Titre);
	_RenderWindows.draw(m_Jouer);
	_RenderWindows.draw(m_Option);
	_RenderWindows.draw(m_Scores);
	_RenderWindows.draw(m_Credit);
	_RenderWindows.draw(m_Quitter);

	_RenderWindows.draw(m_Selection);

}

int Cmenu::EventMenu(sf::Event& _event)
{

	if(_event.type == sf::Event::KeyReleased)
	{
		if( _event.key.code == sf::Keyboard::Up )
		{
			m_MenuChoix--;

			if(m_MenuChoix <1)
				m_MenuChoix = 5;

			m_Selection.setPosition( 650.0f, (float)(150 + 50 * m_MenuChoix) );		
		}
		else if(_event.key.code == sf::Keyboard::Down )
		{

			m_MenuChoix++;

			if(m_MenuChoix >5)
				m_MenuChoix = 1;

			m_Selection.setPosition( 650.0f, (float)(150 + 50 * m_MenuChoix) );
		}
		else if(_event.key.code == sf::Keyboard::Return )
		{
			return m_MenuChoix;
		}
	}

	return -1;

}

void Cmenu::InitMenu()
{

	m_MenuChoix = 1;

	sf::Texture* TempTexture = NULL;

	TempTexture = CSpriteManager::getSmanager()->getTextureByName("Background_Intro_3");

	if(TempTexture)
		m_FondMenu.setTexture( *TempTexture );

	TempTexture = CSpriteManager::getSmanager()->getTextureByName("Mine");

	if(TempTexture)
		m_Selection.setTexture( *TempTexture );

	m_Selection.setPosition( 650.0f, (float)(150 + 50 * m_MenuChoix) );

	m_Titre.setString( CSpriteManager::getSmanager()->getTextByName("Menu_Titre") );
	m_Jouer.setString( CSpriteManager::getSmanager()->getTextByName("Menu_option_Jouer") );
	m_Option.setString( CSpriteManager::getSmanager()->getTextByName("Menu_option_Options") );
	m_Scores.setString( CSpriteManager::getSmanager()->getTextByName("Menu_option_Scores") );
	m_Credit.setString( CSpriteManager::getSmanager()->getTextByName("Menu_option_Credits") );
	m_Quitter.setString( CSpriteManager::getSmanager()->getTextByName("Menu_option_Quitter") );


	m_Titre.setPosition( 650 , 150 );
	m_Jouer.setPosition( 700 , 200 );
	m_Option.setPosition( 700 , 250 );
	m_Scores.setPosition( 700 , 300 );
	m_Credit.setPosition( 700 , 350 );
	m_Quitter.setPosition( 700 , 400 );

	m_Titre.setColor(sf::Color::Red);
	m_Titre.setCharacterSize(32);

}

void Cmenu::DeinitMenu()
{
	sf::Texture* tempText = NULL;
	m_FondMenu.setTexture(*tempText);
}


void Cmenu::ActualiseOptions()
{
	m_Titre.setString( CSpriteManager::getSmanager()->getTextByName("Menu_Titre") );
	m_Jouer.setString( CSpriteManager::getSmanager()->getTextByName("Menu_option_Jouer") );
	m_Option.setString( CSpriteManager::getSmanager()->getTextByName("Menu_option_Options") );
	m_Scores.setString( CSpriteManager::getSmanager()->getTextByName("Menu_option_Scores") );
	m_Credit.setString( CSpriteManager::getSmanager()->getTextByName("Menu_option_Credits") );
	m_Quitter.setString( CSpriteManager::getSmanager()->getTextByName("Menu_option_Quitter") );

}