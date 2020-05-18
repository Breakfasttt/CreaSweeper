//@@@@@@@@@@@@@@@@@@@
// Auteur : Y. Colaisseau
// date : 24/11/12
// description : classe Node Du pathfinding
//@@@@@@@@@@@@@@@@@@@


#pragma once

#include "GeneralConfig.h"

class Cnode
{

protected :

	Cnode* m_Parent;

	int m_GDistanceSinceDepart;
	int m_HDistanceToFin;
	int m_Fsomme;
	int m_PNbreMine;

	int m_Ligne;
	int m_colonne;

	bool isMine;
	bool isEnd;
	bool isBegin;

	bool isCacher;

	sf::Sprite m_NodeSprite;
	sf::Sprite m_NodeCache;

public :

	Cnode();
	~Cnode();

	void setCacher(bool _b){isCacher = _b;};
	void setParent(Cnode* _n){m_Parent = _n;};
	void setG(int _i){m_GDistanceSinceDepart = _i;};
	void setH(int _i){m_HDistanceToFin = _i;};
	void setF(){m_Fsomme = m_GDistanceSinceDepart + m_HDistanceToFin ;};
	void setLigne(int _i){m_Ligne = _i;};
	void setNbreMine(int _i){m_PNbreMine = _i;};
	void setColonne(int _i){m_colonne = _i;};
	void setIsMine(bool _b){ isMine = _b;};
	void setIsEnd(bool _b){ isEnd = _b;};
	void setIsBegin(bool _b){ isBegin = _b;};
	void setSprite(std::string _sz);
	void setPosition(float _x , float _y);
	

	void setColor(int _r, int _g , int _b) { m_NodeSprite.setColor( sf::Color(_r,_g,_b,255)  );}; 

	Cnode* getParent(){return m_Parent;};
	int getG(){return m_GDistanceSinceDepart;};
	int getH(){return m_HDistanceToFin;};
	int getF(){return m_Fsomme;};
	int getLigne(){return m_Ligne;};
	int getColonne(){return m_colonne;};
	int getNbreMine(){return m_PNbreMine;};

	bool getIsMine(){return isMine;};
	bool getIsEnd(){return isEnd;};
	bool getIsBegin(){return isBegin;};
	bool getCacher() {return isCacher;};


	void DisplayNode(sf::RenderWindow& _render);

};