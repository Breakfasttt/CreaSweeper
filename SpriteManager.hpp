//@@@@@@@@@@@@@@@@@@@
// Auteur : Y. Colaisseau
// date : 10/11/12
// description : classe qui charge les modèle d'image a partir d'un fichier
//@@@@@@@@@@@@@@@@@@@


#pragma once 

#include "GeneralConfig.h"

class CSpriteManager
{

protected :

	CSpriteManager();

	std::map<std::string,sf::Texture*> m_MapImage;

	std::map<std::string,std::string> m_MapMusique;

	std::map<std::string, std::vector<std::string>> m_MapText;

	float m_GlobalVolume;
	bool m_Langue;


public :

	static CSpriteManager* getSmanager();

	sf::Texture* getTextureByName(std::string _name);
	std::string getMusicByName(std::string _name);

	float getGlobalVolume(){return m_GlobalVolume;};
	void setGlobalVolume(float _f){m_GlobalVolume = _f;};

	~CSpriteManager();

	std::string getTextByName(std::string);

	void setEnglishMode(bool _b) {m_Langue = _b;};
	bool getEnglishMode(){return m_Langue;}




};