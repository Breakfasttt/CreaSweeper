//@@@@@@@@@@@@@@@@@@@
// Auteur : Y. Colaisseau
// date : 24/11/12
// description : classe de recherche de chemin
//@@@@@@@@@@@@@@@@@@@


#pragma once

#include "GeneralConfig.h"
#include "Cnode.hpp"


class CpathFinder
{

protected :

	std::vector<Cnode*> m_ListeOuverte;
	std::vector<Cnode*> m_ListeFermer;

	std::vector<Cnode*> m_CheminRetenu;

	Cnode* m_tab[16][30];
	Cnode* m_Neighbourg[4];

	bool m_CheminTrouver;
	int m_nbreLigne;

	void ReinitPathfinder();

public : 

	CpathFinder();
	~CpathFinder();


	bool FindPath(Cnode _tab[][30] , Cnode* _debut, Cnode* _fin , int _nbreLigne);

	void RemoveFromCloseList(Cnode*); //supprime un node de la liste ferm�
	void RemoveFromOpenList(Cnode*); // supprime un node de la liste ouverte
	void AddToCloseList(Cnode*); // ajoute un node a la close list en v�ifiant qu'il n'y est pas
	void AddToOpenList(Cnode*); // ajoute un node a la open list en v�ifiant qu'il n'y est pas
	Cnode* getCurrentNode(Cnode*); //r�cup�re le node avec le poinds le plus faible
	void getNeighBours(Cnode*); //r�cup�re les 4 voisins d'un node
	bool isOnCloseList(Cnode*); //si elle est dans la list ferm�e
	bool isOnOpenList(Cnode*); //si elle est dans la liste ouverte

};