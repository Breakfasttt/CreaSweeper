//@@@@@@@@@@@@@@@@@@@
// Auteur : Y. Colaisseau
// date : 10/11/12
// description : classe qui gère la partie Credits
//@@@@@@@@@@@@@@@@@@@



#include "Ccredits.hpp"



Ccredits::Ccredits()
{


}

void Ccredits::CreditInit()
{
	m_TitreCredits.setString(CSpriteManager::getSmanager()->getTextByName("Credit_Titre"));
	m_InfosText.setString("");

	m_Titre = m_TitreCredits.getString();

	sf::Texture* TempTexture = CSpriteManager::getSmanager()->getTextureByName("Credits_logo");

	if(TempTexture != NULL)
	{
		m_LogoCrea.setTexture(*TempTexture);
		m_LogoCrea.setPosition( 1024.0f - m_LogoCrea.getGlobalBounds().width ,
								720.0f - m_LogoCrea.getGlobalBounds().height );
	}

	TempTexture = CSpriteManager::getSmanager()->getTextureByName("Credits_Background");

	if(TempTexture != NULL)
	{
		m_CreditsBackground.setTexture(*TempTexture);
	}

	m_TitreCredits.setPosition( 20.0f,
								50.0f );

	m_TitreCredits.setColor(sf::Color::Black);


	m_InfosText.setPosition(  250.0f ,
							  50.0f  );

	m_InfosText.setColor(sf::Color::Black);

	m_clockCredits.restart();

	m_NbreInfos = 0;
}

Ccredits::~Ccredits()
{

}

void Ccredits::CreditUpdate(float _dt)
{

	if( m_clockCredits.getElapsedTime().asSeconds() >=1.8f && m_NbreInfos <4)
	{
		std::stringstream oss;
		std::stringstream oss2;
		std::string TempString;

		oss << "Credit_Infos" << m_NbreInfos;
		oss2 << "Credit_Infos_titre" << m_NbreInfos;

		m_InfosText.setString(CSpriteManager::getSmanager()->getTextByName(oss.str()));


		TempString = m_Titre + " " +  CSpriteManager::getSmanager()->getTextByName(oss2.str()) ;

		m_TitreCredits.setString(TempString);


		m_InfosText.setPosition(  m_TitreCredits.getPosition().x + m_TitreCredits.getGlobalBounds().width + 20.0f ,
								  50.0f  );

		m_NbreInfos++;

		if(m_NbreInfos == 3)
			m_NbreInfos = 0;

		m_clockCredits.restart();
	
	}

}

void Ccredits::CreditDisplay(sf::RenderWindow& _render )
{
	_render.draw(m_CreditsBackground);
	_render.draw(m_LogoCrea);
	_render.draw(m_TitreCredits);
	_render.draw(m_InfosText);

}

bool Ccredits::CreditEvent(sf::Event& _event)
{
	if(_event.type == sf::Event::KeyReleased)
	{
		if( _event.key.code == sf::Keyboard::Return )
		{	
			m_NbreInfos = 0;
			m_InfosText.setString("");
			return true;	
		}
	}
	return false;
}

void Ccredits::CreditDeinit()
{

}


void Ccredits::ActualiseOptions()
{
	m_Titre = CSpriteManager::getSmanager()->getTextByName("Credit_Titre");
}