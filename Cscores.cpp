


#include "Cscores.hpp"



Cscores::Cscores()
{

}

Cscores::~Cscores()
{

}

void Cscores::InitScores()
{

	m_bActualiseScore = false;

	m_RectScores.setSize( sf::Vector2f(350.0f, 600.0f) );
	m_RectScores.setFillColor( sf::Color( 0 , 0 , 255, 90 ) );
	m_RectScores.setOutlineThickness(3.0f);
	m_RectScores.setOutlineColor( sf::Color( 255 , 0 , 0, 200 ) );
	m_RectScores.setPosition (600.0f , 50.0f );


	m_TitreScores.setString(CSpriteManager::getSmanager()->getTextByName("Scores_Titre"));
	m_TitreScores.setOrigin( m_TitreScores.getGlobalBounds().width/2.0f ,
							 m_TitreScores.getGlobalBounds().height/2.0f);
	m_TitreScores.setPosition(775.0f , 65.0f  ) ;


	m_TitreInfosReinit.setString(CSpriteManager::getSmanager()->getTextByName("Scores_Infos"));
	m_TitreInfosReinit.setCharacterSize(18);
	m_TitreInfosReinit.setOrigin( m_TitreInfosReinit.getGlobalBounds().width/2.0f ,
							      m_TitreInfosReinit.getGlobalBounds().height/2.0f);
	m_TitreInfosReinit.setPosition(775.0f , 600.0f  ) ;


	sf::Texture* TempTexture = CSpriteManager::getSmanager()->getTextureByName("Scores_Background");

	if(TempTexture != NULL)
	{
		m_ScoresBackground.setTexture(*TempTexture);
	}

	std::ifstream DataScores  ;

	DataScores.open("Assets/DataScores.DAT",std::ios::in | std::ios::binary);

	if( !DataScores.is_open() )
	{
		std::cout << "ouverture du fichier scores echoue ! " << std::endl;
	}
	else
	{
		while( !DataScores.eof() )
		{

			T_Score tempScore;
			DataScores.read( (char*)&tempScore,sizeof(T_Score) );

			m_VecScore.push_back(tempScore);
		}

		TrierMap();

		DataScores.close();
	}

}

void Cscores::DeinitScores()
{
	std::ofstream DataScores  ;
	
	m_bActualiseScore = false;

	DataScores.open("Assets/DataScores.DAT",  std::ios::out | std::ios::binary);

	if( !DataScores.is_open() )
	{
		std::cout << "ouverture du fichier scores echoue ! " << std::endl;
	}
	else
	{

		TrierMap();

		DataScores.clear();

		for(unsigned int i = 0 ; i < m_VecScore.size() ; ++i)
		{

			DataScores.write( (char*)&m_VecScore[i],sizeof(T_Score) );

		}

		DataScores.close();
	}
}

void Cscores::UpdateScores(float _dt)
{
	if(!m_bActualiseScore)
	{
		m_bActualiseScore = true;

		TrierMap();

		for(int i = 0; i < 10 ; ++i)
		{

			std::stringstream oss;
			std::stringstream oss2;

			oss << m_VecScore[i].Score;
			oss2 << m_VecScore[i].Name;

			m_TabTextName[i].setString( oss2.str() );
			m_TabTextScore[i].setString(  oss.str()  );

			m_TabTextName[i].setPosition( 610.0f,
										  (float)(150 + i * 40) );

			m_TabTextScore[i].setOrigin( m_TabTextScore[i].getGlobalBounds().width , 0.0f );
			m_TabTextScore[i].setPosition( 940.0f , 
										  (float)(150 + i * 40) );
		}	
	}
}

void Cscores::DisplayScores(sf::RenderWindow& _render)
{

	_render.draw( m_ScoresBackground );
	_render.draw( m_RectScores );
	_render.draw( m_TitreScores );
	_render.draw( m_TitreInfosReinit );

	for(unsigned int i = 0 ; i < m_VecScore.size() && i < 10 ; ++i)
	{
		_render.draw(m_TabTextName[i]);
		_render.draw(m_TabTextScore[i]);	
	}
}

bool Cscores::EventScores(sf::Event _event)
{
	if(_event.type == sf::Event::KeyReleased)
	{
		if( _event.key.code == sf::Keyboard::Return )
		{	
			m_bActualiseScore =  false;
			return true;	
		}
		if( _event.key.code == sf::Keyboard::F12 )
		{ 		
			ReinitScore();
		}
	}
	return false;
}

void Cscores::AddNewScores(int _i, std::string _name)
{
	T_Score TempNewScore;

	TempNewScore.Score = _i;

	int NameSize = _name.size();

	if( NameSize > 15)
		NameSize = 15;


	for( int j = 0; j < NameSize ; ++j)
	{
		TempNewScore.Name[j] = _name[j];
	}

	if( NameSize < 15)
		TempNewScore.Name[NameSize] = '\0';
	else
		TempNewScore.Name[NameSize-1] = '\0';



	m_VecScore.push_back(TempNewScore);

	TrierMap();

}

void Cscores::TrierMap()
{
	for(unsigned int i = 0; i < m_VecScore.size() ; ++i)
	{
		for(unsigned int j = i; j < m_VecScore.size() ; ++j)
		{
			
			if( m_VecScore[i].Score < m_VecScore[j].Score)
			{
				T_Score temp = m_VecScore[i];
				m_VecScore[i] = m_VecScore[j];
				m_VecScore[j] = temp;			
			}
		}		
	}

	while( m_VecScore.size() > 10)
	{
		m_VecScore.pop_back();	
	}


}

void Cscores::ReinitScore() 
{

	std::ofstream DataScores  ;
		
	DataScores.open("Assets/DataScores.DAT",std::ios::out | std::ios::binary);

	if( !DataScores.is_open() )
	{
		std::cout << "ouverture du fichier scores echoue ! " << std::endl;
	}
	else
	{
		m_bActualiseScore = false;

		while( m_VecScore.size() > 0)
		{
			m_VecScore.pop_back();	
		}

		T_Score tempScore;

		tempScore.Name[0] = 'M';
		tempScore.Name[1] = 'I';
		tempScore.Name[2] = 'L';
		tempScore.Name[3] = 'L';
		tempScore.Name[4] = 'E';
		tempScore.Name[5] = 0 ;
		tempScore.Score = -1000;
		
		for(int i = 0 ; i < 10 ; ++i)
		{
			m_VecScore.push_back(tempScore);
			DataScores.write( (char*)&tempScore,sizeof(T_Score) );
		}

		void TrierMap();


		DataScores.close();
	}

}


void Cscores::ActualiseScoresoptions()
{
	m_TitreScores.setString(CSpriteManager::getSmanager()->getTextByName("Scores_Titre"));
	m_TitreScores.setOrigin( m_TitreScores.getGlobalBounds().width/2.0f ,
							 m_TitreScores.getGlobalBounds().height/2.0f);
	m_TitreScores.setPosition(775.0f , 65.0f  ) ;


	m_TitreInfosReinit.setString(CSpriteManager::getSmanager()->getTextByName("Scores_Infos"));
	m_TitreInfosReinit.setCharacterSize(18);
	m_TitreInfosReinit.setOrigin( m_TitreInfosReinit.getGlobalBounds().width/2.0f ,
							      m_TitreInfosReinit.getGlobalBounds().height/2.0f);
	m_TitreInfosReinit.setPosition(775.0f , 600.0f  ) ;
}