//@@@@@@@@@@@@@@@@@@@
// Auteur : Y. Colaisseau
// date : 24/11/12
// description : classe qui gére le perso
//@@@@@@@@@@@@@@@@@@@


#include "Cperso.hpp"




Cperso::Cperso()
{
	m_posX = 0;
	m_posY = 0;

	m_sens = BOT;

	m_SpritePerso.setOrigin(0.0f,SIZE_CASE);

	sf::Texture* TempTexture = NULL;

	TempTexture = CSpriteManager::getSmanager()->getTextureByName("Joueur_Top");

	m_asMoved = false;
	m_PowerOn = false;
	m_asUsedPower = false;

	if(TempTexture)
		m_SpritePerso.setTexture( *TempTexture   );
}

Cperso::~Cperso()
{

}


void Cperso::EventPerso(sf::Event _event)
{
	if(_event.type == sf::Event::KeyReleased)
	{

		sf::Texture* TempTexture = NULL;

		if( _event.key.code == sf::Keyboard::Up && m_posY + 1 <= m_maxY-1 )
		{	

			m_asMoved = true;
			m_sens = TOP;
			m_posY++;

			TempTexture = CSpriteManager::getSmanager()->getTextureByName("Joueur_Top");

			if(TempTexture)
				m_SpritePerso.setTexture( *TempTexture   );
		}

		if( _event.key.code == sf::Keyboard::Down && m_posY - 1 >= 0)
		{	
			m_asMoved = true;
			m_sens = BOT;
			m_posY--;
			TempTexture = CSpriteManager::getSmanager()->getTextureByName("Joueur_Bot")  ;

			if(TempTexture)
				m_SpritePerso.setTexture( *TempTexture   );

		}

		if( _event.key.code == sf::Keyboard::Left && m_posX -1 >= 0 )
		{	
			m_asMoved = true;
			m_sens = LEFT;
			m_posX--;
			TempTexture = CSpriteManager::getSmanager()->getTextureByName("Joueur_Left")   ;

			if(TempTexture)
				m_SpritePerso.setTexture( *TempTexture   );

		}

		if( _event.key.code == sf::Keyboard::Right  && m_posX +1 <= 15 )
		{	
			m_asMoved = true;
			m_sens = RIGHT;
			m_posX++;
			TempTexture = CSpriteManager::getSmanager()->getTextureByName("Joueur_Right")   ;

			if(TempTexture)
				m_SpritePerso.setTexture( *TempTexture  );

		}

		if( _event.key.code == sf::Keyboard::Space && m_PowerOn)
		{	
			m_PowerOn = false;
			m_asUsedPower = true;			
		}

		m_SpritePerso.setPosition( (WINDOW_SIZE_X - SIZE_PLATEAU_X) + (m_posX * SIZE_CASE) ,
										(WINDOW_SIZE_Y ) - (m_posY * SIZE_CASE)	);
	}
}

void Cperso::DisplayPerso(sf::RenderWindow& _render)
{
	_render.draw(m_SpritePerso);
}


void Cperso::setPosDebut(int _x , int _y)
{
	m_posX = _x ;
	m_posY = _y;

	m_SpritePerso.setPosition( (WINDOW_SIZE_X - SIZE_PLATEAU_X) + (m_posX * SIZE_CASE) ,
										(WINDOW_SIZE_Y ) - (m_posY * SIZE_CASE)	);
}
