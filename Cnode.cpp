//@@@@@@@@@@@@@@@@@@@
// Auteur : Y. Colaisseau
// date : 24/11/12
// description : classe qui gère une partie
//@@@@@@@@@@@@@@@@@@@



#include "Cnode.hpp"



Cnode::Cnode()
{
	m_NodeSprite.setOrigin(0.0f,SIZE_CASE);
	m_NodeCache.setOrigin(0.0f,SIZE_CASE);

	m_Parent = NULL;

	m_GDistanceSinceDepart =0 ;
	m_HDistanceToFin = 0;
	m_Fsomme = 0;
	m_PNbreMine = 0;

	m_Ligne = 0;
	m_colonne = 0;

	isMine = false;
	isEnd = false;
	isBegin = false;

	isCacher = false;

	sf::Texture* TempTexture;

	TempTexture = CSpriteManager::getSmanager()->getTextureByName("Jeu_Plateau_Cache");

	if(TempTexture)
	{
		m_NodeCache.setTexture(*TempTexture);
	}

}

Cnode::~Cnode()
{

}

void Cnode::setSprite(std::string _sz)
{
	sf::Texture* TempTexture;

	TempTexture = CSpriteManager::getSmanager()->getTextureByName(_sz);

	if(TempTexture)
	{
		m_NodeSprite.setTexture(*TempTexture);
	}
}


void Cnode::DisplayNode(sf::RenderWindow& _render)
{
	_render.draw(m_NodeSprite);

	if(isCacher)
	{
		_render.draw(m_NodeCache);
	}

}

void Cnode::setPosition(float _x , float _y)
{
	m_NodeSprite.setPosition(_x , _y);
	m_NodeCache.setPosition(_x , _y);
}