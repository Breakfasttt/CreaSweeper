//@@@@@@@@@@@@@@@@@@@
// Auteur : Y. Colaisseau
// date : 24/11/12
// description : classe de recherche de chemin
//@@@@@@@@@@@@@@@@@@@


#include "Cpathfinder.hpp"



CpathFinder::CpathFinder()
{

}

CpathFinder::~CpathFinder()
{

}


void CpathFinder::ReinitPathfinder()
{

	for(int i =0; i < 4 ; ++i)
	{
		m_Neighbourg[i] = NULL;
	}

	for(int i = 0 ; i < 16 ; ++i)
	{
		for(int j = 0 ; j < 30 ; ++j)
		{
			m_tab[16][30] = NULL;
		}	
	
	}

	m_CheminTrouver = false;

	while(m_ListeOuverte.size()>0)
	{
		m_ListeOuverte.pop_back();
	}

	while(m_ListeFermer.size()>0)
	{
		m_ListeFermer.pop_back();
	}



}


//pathfinder
bool CpathFinder::FindPath(Cnode _tab[][30] ,  Cnode* _debut, Cnode* _fin , int _nbreLigne)
{

	ReinitPathfinder();

	for(int i = 0 ; i < 16 ; ++i ) 
	{
		for(int j = 0 ; j < 30 ; ++j ) 
		{
			m_tab[i][j] = &_tab[i][j];
		}
	}


	m_nbreLigne = _nbreLigne;

	Cnode*  currentNode = NULL;

	//Ajout du node de départ à la liste ouverte.

	int posXFin = _fin->getColonne();
	int posYFin = _fin->getLigne();

	int posXDebut = _debut->getColonne();
	int posYDebut = _debut->getLigne();

	_debut->setG(  _debut->getNbreMine() );

	//_debut->setH( abs(posXFin-posXDebut) +  abs(posYFin - posYDebut)  ); //manhattan
	//_debut->setH( ( (float)sqrt( (float)(posXFin-posXDebut) * (posXFin-posXDebut) )  -  (float)( (posYFin - posYDebut) * (posYFin - posYDebut) ) )   ); // euclide
	_debut->setH(0); 

	// tout les H seront a 0 lors du pathfinding afin de trouver le chemin le moins couteux
	// Le seul cas ou la distance sera utilisé sera de déterminer le node le plus avantageux entre 2 nodes ayant le même poids.
	// ceci afin de fournir un chemin visuel cohérent

	_debut->setF();


	AddToOpenList(_debut);

	while( m_ListeOuverte.size() > 0 &&  currentNode != _fin  )
	{
	
		//Récupération du node avec le plus petit F contenu dans la liste ouverte.
        currentNode = getCurrentNode(_fin); 

		if(currentNode == _fin)
			break;


		// on le bascule dans la liste fermée.
		AddToCloseList( currentNode );


		 // récupération des voisins


		for(int i = 0; i < 4 ; ++i)
		{
			m_Neighbourg[i] = NULL;
		}

		getNeighBours(currentNode);



		// Pour chacun des 4 nodes adjacents
		for(int i =0; i < 4 ; ++i)
		{
			if(m_Neighbourg[i] != NULL)
			{

				bool isMine = m_Neighbourg[i]->getIsMine() ;
				bool Oncloselist = isOnCloseList( m_Neighbourg[i] );

				int posXtemp = m_Neighbourg[i]->getColonne();
				int posYtemp = m_Neighbourg[i]->getLigne();

				if( !Oncloselist  && !isMine && posYtemp<_nbreLigne )
				{

					//si il est déja dans la liste ouverte on actualise ses nouvelles valeurs si besoin
					if( isOnOpenList(m_Neighbourg[i])   )
					{

						//on calcul les nouvelle valeur
						int NewG = m_Neighbourg[i]->getParent()->getG() + m_Neighbourg[i]->getNbreMine() ;

						//int NewH = abs(posXFin-posXtemp) +  abs(posYFin - posYtemp); // manhattan
						//int NewH = (int)sqrt ( (float)( (posXFin-posXtemp) * (posXFin-posXtemp) ) -  (float)( (posYFin - posYtemp) * (posYFin - posYtemp) ) ); //euclide
						int NewH =0;

						if( NewG < m_Neighbourg[i]->getG() )
						{
							m_Neighbourg[i]->setG(NewG);
							m_Neighbourg[i]->setH(NewH);
							m_Neighbourg[i]->setF();
						}
					}
					else // sinon on l'ajoute a la liste
					{
						AddToOpenList(m_Neighbourg[i]);
						m_Neighbourg[i]->setParent(currentNode);

						int NewG = m_Neighbourg[i]->getParent()->getG() + m_Neighbourg[i]->getNbreMine() ;

						//int NewH = abs(posXFin-posXtemp) +  abs(posYFin - posYtemp); // manhattan
						//int NewH = (int)sqrt ( (float)( (posXFin-posXtemp) * (posXFin-posXtemp) ) -  (float)( (posYFin - posYtemp) * (posYFin - posYtemp) ) ); //euclide
						int NewH =0;


						m_Neighbourg[i]->setG(NewG);
						m_Neighbourg[i]->setH(NewH);
						m_Neighbourg[i]->setF();
					}
				}
			}
		}
	}

	currentNode = NULL;

	if( m_ListeOuverte.size() ==0)
	{
		return false;
	}
	else
	{
		return true;
	}

}

//supprime un node de la liste fermé
void CpathFinder::RemoveFromCloseList(Cnode* _nodeToRemove) 
{

	for(int i = 0; i < m_ListeFermer.size() ; ++i)
	{
		if( _nodeToRemove == m_ListeFermer[i] )
		{
			Cnode* temp = m_ListeFermer[i];
			m_ListeFermer[i] = m_ListeFermer[m_ListeFermer.size() - 1] ;
			m_ListeFermer[m_ListeFermer.size() - 1] = temp;
			m_ListeFermer.pop_back();
		}
	}

}

// supprime un node de la liste ouvert
void CpathFinder::RemoveFromOpenList(Cnode* _nodeToRemove) 
{
	for(int i = 0; i < m_ListeOuverte.size() ; ++i)
	{
		if( _nodeToRemove == m_ListeOuverte[i] )
		{
			Cnode* temp = m_ListeOuverte[i];
			m_ListeOuverte[i] = m_ListeOuverte[m_ListeOuverte.size() - 1] ;
			m_ListeOuverte[m_ListeOuverte.size() - 1] = temp;
			m_ListeOuverte.pop_back();
		}
	}
}

// ajoute un node a la close list en véifiant qu'il n'y est pas
void CpathFinder::AddToCloseList(Cnode* _nodeToAdd) 
{
	RemoveFromOpenList(_nodeToAdd);
	m_ListeFermer.push_back(_nodeToAdd);


}

// ajoute un node a la open list en véifiant qu'il n'y est pas
void CpathFinder::AddToOpenList(Cnode* _nodeToAdd) 
{
	RemoveFromCloseList(_nodeToAdd);
	m_ListeOuverte.push_back(_nodeToAdd);	
}

//récupére le node avec le poinds le plus faible
Cnode* CpathFinder::getCurrentNode(Cnode* _fin) 
{

	Cnode* _nodeToReturn = NULL;

	for(int i = 0; i < m_ListeOuverte.size() ; ++i)
	{
		if( _nodeToReturn == NULL )
		{
			_nodeToReturn = m_ListeOuverte[i];
		}
		else
		{
			if( m_ListeOuverte[i]->getF() <= _nodeToReturn->getF() )
			{

				if( m_ListeOuverte[i]->getF() == _nodeToReturn->getF() )
				{
					int posXFin = _fin->getLigne();
					int posYFin = _fin->getColonne();

					int posXnode = _nodeToReturn->getLigne();
					int posYnode = _nodeToReturn->getColonne();

					int posXListe = m_ListeOuverte[i]->getLigne();
					int posYListe = m_ListeOuverte[i]->getColonne();


					float DlisteFin = sqrt( (float)( (posXFin - posXListe) * (posXFin - posXListe) )  + (float)( (posYFin-posYListe) * (posYFin-posYListe) ) );
					float DnodeFin = sqrt( (float)( (posXFin - posXnode) * (posXFin - posXnode) )  + (float)( (posYFin-posYnode) * (posYFin-posYnode) ) );

					if(DlisteFin < DnodeFin)
					{
						_nodeToReturn = m_ListeOuverte[i];
					}
				}
				else
				{
					_nodeToReturn = m_ListeOuverte[i];
				}
			}


		}
	}

	return _nodeToReturn;
}

//récupére les 4 voisins d'un node
void CpathFinder::getNeighBours(Cnode* _nodeForNeightbourg) 
{

	int posX = _nodeForNeightbourg->getColonne();
	int posY = _nodeForNeightbourg->getLigne();


	if(  posX - 1 >= 0  )
	{
		m_Neighbourg[2] =  m_tab[posX - 1][posY] ;
	}
	else
	{
		m_Neighbourg[2] = NULL;
	}

	if(  posX + 1 < 16 )
	{
		m_Neighbourg[1] =  m_tab[posX + 1][posY] ;
	}
	else
	{
		m_Neighbourg[1] = NULL;
	}

	if( posY - 1 >= 1 )
	{
		m_Neighbourg[3] =  m_tab[posX][posY -1] ;
	}
	else
	{
		m_Neighbourg[3] = NULL;
	}

	if( posY + 1 < 30 )
	{
		m_Neighbourg[0] =  m_tab[posX][posY + 1] ;
	}
	else
	{
		m_Neighbourg[0] = NULL;
	}
	


}

//si elle est dans la list fermée
bool CpathFinder::isOnCloseList(Cnode* _nodeToVerify) 
{
	for(int i = 0; i < m_ListeFermer.size() ; ++i)
	{
		if( _nodeToVerify == m_ListeFermer[i] )
		{
			return true;
		}
	}

	return false;
}

//si elle est dans la liste ouverte
bool CpathFinder::isOnOpenList(Cnode* _nodeToVerify ) 
{
	for(int i = 0; i < m_ListeOuverte.size() ; ++i)
	{
		if( _nodeToVerify  == m_ListeOuverte[i] )
		{
			return true;
		}
	}

	return false;
}
