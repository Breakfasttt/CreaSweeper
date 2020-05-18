//@@@@@@@@@@@@@@@@@@@
// Auteur : Y. Colaisseau
// date : 20/11/12
// description : classe qui gère les options
//@@@@@@@@@@@@@@@@@@@



#include "Coptions.hpp"



Coptions::Coptions()
{

}

Coptions::~Coptions()
{

}

void Coptions::InitOptions()
{

	m_bOptionsChanger = false;

	sf::Texture* TempTexture = CSpriteManager::getSmanager()->getTextureByName("Options_Background") ;

	if(TempTexture != NULL)
		m_backgroundOptions.setTexture(*TempTexture);


	TempTexture = CSpriteManager::getSmanager()->getTextureByName("HUD_DOWN") ;

	if(TempTexture != NULL)
		m_ButtonHUD[0].setTexture(*TempTexture);

	TempTexture = CSpriteManager::getSmanager()->getTextureByName("HUD_UP") ;

	if(TempTexture != NULL)
		m_ButtonHUD[1].setTexture(*TempTexture);

	TempTexture = CSpriteManager::getSmanager()->getTextureByName("HUD_RIGHT") ;

	if(TempTexture != NULL)
		m_ButtonHUD[2].setTexture(*TempTexture);

	TempTexture = CSpriteManager::getSmanager()->getTextureByName("HUD_LEFT") ;

	if(TempTexture != NULL)
		m_ButtonHUD[3].setTexture(*TempTexture);

	m_OptionsTitre.setString( CSpriteManager::getSmanager()->getTextByName("Options_Titre") );
	m_OptionsVolume.setString( CSpriteManager::getSmanager()->getTextByName("Options_Volume") );
	m_OptionsLangue.setString( CSpriteManager::getSmanager()->getTextByName("Options_Langue") );

	m_ValeurLangue.setString( CSpriteManager::getSmanager()->getTextByName("Options_LangueChoisie") );


	std::stringstream oss ;

	oss << (int)(CSpriteManager::getSmanager()->getGlobalVolume());

	m_ValeurVolume.setString( oss.str() );


	//titre

	m_OptionsTitre.setOrigin( m_OptionsTitre.getGlobalBounds().width/2.0f , 
							  m_OptionsTitre.getGlobalBounds().height/2.0f);

	m_OptionsTitre.setPosition( 1024.0f / 2.0f , 30.0f);


	m_OptionsTitre.setColor(sf::Color::Black);


	//volume

	m_OptionsVolume.setOrigin( m_OptionsTitre.getGlobalBounds().width/2.0f , 
							  m_OptionsTitre.getGlobalBounds().height/2.0f);

	m_OptionsVolume.setPosition( 1024.0f / 4.0f , 90.0f);

	m_OptionsVolume.setColor(sf::Color::Black);


	m_ValeurVolume.setOrigin( m_OptionsTitre.getGlobalBounds().width/2.0f , 
							  m_OptionsTitre.getGlobalBounds().height/2.0f);

	m_ValeurVolume.setPosition( 1024.0f / 4.0f , 140.0f);

	m_ValeurVolume.setColor(sf::Color::Black);


	//langue

	m_OptionsLangue.setOrigin( m_OptionsTitre.getGlobalBounds().width/2.0f , 
							  m_OptionsTitre.getGlobalBounds().height/2.0f);

	m_OptionsLangue.setPosition( 1024.0f / 2.0f + 1024.0f / 4.0f , 90.0f);

	m_OptionsLangue.setColor(sf::Color::Black);


	m_ValeurLangue.setOrigin( m_OptionsTitre.getGlobalBounds().width/2.0f , 
							  m_OptionsTitre.getGlobalBounds().height/2.0f);

	m_ValeurLangue.setPosition( 1024.0f / 2.0f + 1024.0f / 4.0f , 140.0f);


	m_ValeurLangue.setColor(sf::Color::Black);



	//HUD

	for(int i = 0 ; i < 4 ; ++i )
	{
		m_ButtonHUD[i].setOrigin( m_ButtonHUD[i].getGlobalBounds().width/2.0f , 
							  m_ButtonHUD[i].getGlobalBounds().height/2.0f);
	
	}

	sf::Vector2f TempPosVolume = m_OptionsVolume.getPosition();
	sf::FloatRect TempRectVolume = m_OptionsVolume.getGlobalBounds();

	sf::Vector2f TempPosLangue = m_OptionsLangue.getPosition();
	sf::FloatRect TempRectLangue = m_OptionsLangue.getGlobalBounds();


	m_ButtonHUD[0].setPosition( TempPosLangue.x + TempRectLangue.width  , TempPosLangue.y + 50.0f); // up
	m_ButtonHUD[1].setPosition( TempPosLangue.x - TempRectLangue.width  , TempPosLangue.y + 50.0f); // down
	m_ButtonHUD[2].setPosition( TempPosVolume.x + TempRectVolume.width  , TempPosVolume.y + 50.0f); // right
	m_ButtonHUD[3].setPosition( TempPosVolume.x - TempRectVolume.width  , TempPosVolume.y + 50.0f); // left
	 

}

void Coptions::DeinitOptions()
{

}

void Coptions::UpdateOptions(float _dt)
{

}

void Coptions::DisplayOptions(sf::RenderWindow& _render)
{

	_render.draw(m_backgroundOptions);
	_render.draw(m_OptionsTitre);
	_render.draw(m_OptionsVolume);
	_render.draw(m_OptionsLangue);
	_render.draw(m_ValeurLangue);
	_render.draw(m_ValeurVolume);

	for(int i = 0 ; i < 4 ; ++i )
	{
		_render.draw(m_ButtonHUD[i]);	
	}

}

bool Coptions::EventOptions(sf::Event _event)
{
	if(_event.type == sf::Event::KeyReleased)
	{
		if( _event.key.code == sf::Keyboard::Return )
		{	
			m_bOptionsChanger =  false;
			return true;	
		}


		if( _event.key.code == sf::Keyboard::Up || _event.key.code == sf::Keyboard::Down )
		{	
			bool TempLangue = CSpriteManager::getSmanager()->getEnglishMode();
			TempLangue = !TempLangue;
			CSpriteManager::getSmanager()->setEnglishMode(TempLangue);
			m_bOptionsChanger =  true;	
		}


	}
	else if(_event.type == sf::Event::KeyPressed)
	{
		if( _event.key.code == sf::Keyboard::Left )
		{	
			float TempVolume = CSpriteManager::getSmanager()->getGlobalVolume();
			TempVolume -= 1.0f;

			if(TempVolume <0.0f)
				TempVolume = 0.0f;

			CSpriteManager::getSmanager()->setGlobalVolume(TempVolume);

			m_bOptionsChanger =  true;	
		}

		if( _event.key.code == sf::Keyboard::Right )
		{	
			float TempVolume = CSpriteManager::getSmanager()->getGlobalVolume();
			TempVolume += 1.0f;

			if(TempVolume >100.0f)
				TempVolume = 100.0f;

			CSpriteManager::getSmanager()->setGlobalVolume(TempVolume);

			m_bOptionsChanger =  true;	
		}

	}


	return false;
}


void Coptions::ActualiseOptions()
{

	m_OptionsTitre.setString( CSpriteManager::getSmanager()->getTextByName("Options_Titre") );
	m_OptionsVolume.setString( CSpriteManager::getSmanager()->getTextByName("Options_Volume") );
	m_OptionsLangue.setString( CSpriteManager::getSmanager()->getTextByName("Options_Langue") );

	m_ValeurLangue.setString( CSpriteManager::getSmanager()->getTextByName("Options_LangueChoisie") );


	std::stringstream oss ;

	oss << (int)(CSpriteManager::getSmanager()->getGlobalVolume());

	m_ValeurVolume.setString( oss.str() );


}


