//@@@@@@@@@@@@@@@@@@@
// Auteur : Y. Colaisseau
// date : 10/11/12
// description : classe qui charge les modèle d'image a partir d'un fichier
//@@@@@@@@@@@@@@@@@@@


#include "SpriteManager.hpp"


CSpriteManager* CSpriteManager::getSmanager()
{
	static CSpriteManager Instance = CSpriteManager();
	return &Instance;
}

CSpriteManager::CSpriteManager() : m_MapImage()
{
	

	m_GlobalVolume = INITIAL_GLOBAL_VOLUME;
	m_Langue =  false;

	std::ifstream DataCenter  ;

	DataCenter.open("Assets/DataSprite.txt",std::ifstream::in);

	// chargement des assets
	if( DataCenter == NULL)
	{
		std::cout << "Erreur lors de l'ouverture du DataSprite" << std::endl;
	}
	else
	{
		
		while( !DataCenter.eof() )
		{
			std::string TextureKey;
			std::string TextureLink;

			DataCenter >> TextureKey >> TextureLink ;

			sf::Texture* tempTexture = new sf::Texture();
			tempTexture->loadFromFile(TextureLink);

			m_MapImage[TextureKey] = tempTexture;

			tempTexture = NULL;			
		}

		DataCenter.close();
	}

	DataCenter.open("Assets/DataMusic.txt",std::ifstream::in);
	//chargement des musiques

	if( DataCenter == NULL)
	{
		std::cout << "Erreur lors de l'ouverture du DataMusic" << std::endl;
	}
	else
	{
		
		while( !DataCenter.eof() )
		{
			std::string MusicName;
			std::string MusicLink;

			DataCenter >> MusicName >> MusicLink ;

			m_MapMusique[MusicName] = MusicLink;
		
		}

		DataCenter.close();
	}

	//chargements des text

	DataCenter.open("Assets/DataText.txt",std::ifstream::in);

	if( DataCenter == NULL)
	{
		std::cout << "Erreur lors de l'ouverture du DataText" << std::endl;
	}
	else
	{
		
		while( !DataCenter.eof() )
		{
			std::string TextKey;
			std::string TextFr;
			std::string TextEn;


			DataCenter >> TextKey >> TextFr >> TextEn ;


			for(unsigned int i = 0 ; i < TextFr.size() ; ++i)
			{
				if( TextFr[i] == '_')
				{
					TextFr[i] = ' ';
				}
				if( TextFr[i] == '@')
				{
					TextFr[i] = '\n';
				}
			}

			for(unsigned int i = 0 ; i < TextEn.size() ; ++i)
			{
				if( TextEn[i] == '_')
				{
					TextEn[i] = ' ';
				}
				if( TextEn[i] == '@')
				{
					TextEn[i] = '\n';
				}
			}

			m_MapText[TextKey].push_back(TextFr);
			m_MapText[TextKey].push_back(TextEn);
		
		}

		DataCenter.close();
	}

}


sf::Texture* CSpriteManager::getTextureByName(std::string _name)
{

	if( m_MapImage[_name] != NULL )
		return m_MapImage[_name] ;

	return NULL;
}

std::string CSpriteManager::getMusicByName(std::string _name)
{
	return m_MapMusique[_name] ;
}

std::string CSpriteManager::getTextByName(std::string _name)
{
	if(!m_Langue && m_MapText[_name].size() >=1)
	{
		return m_MapText[_name][0];
	}		
	else if( m_MapText[_name].size() >=2 )
	{
		return m_MapText[_name][1];
	}

	return "";
}


CSpriteManager::~CSpriteManager()
{
	std::map<std::string,sf::Texture*>::iterator _iterator;

	for(_iterator = m_MapImage.begin(); _iterator != m_MapImage.end(); ++_iterator )
	{
		delete (*_iterator).second;
	}

	m_MapImage.clear();

}
