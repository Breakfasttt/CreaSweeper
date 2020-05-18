


#ifndef GENERAL_CONFIG_H
#define GENERAL_CONFIG_H


#include <stdio.h>
#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <time.h>

#include <SFML\Graphics.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>



#include "SpriteManager.hpp"

#define WINDOW_SIZE_X 1024
#define WINDOW_SIZE_Y 720
#define WINDOW_NAME "CreaSweeper"

#define TIME_INTRO 9.0f

#define INITIAL_GLOBAL_VOLUME 50.0f

#define WINDOW_WITHOUT_RESIZE sf::Style::Titlebar | sf::Style::Close


#define SIZE_CASE 24.0f
#define SIZE_PLATEAU_X  SIZE_CASE*16
#define SIZE_PLATEAU_Y  SIZE_CASE*30

#define TEMPS_BASE 200
#define TEMPS_ADDITIONNEL 5
#define TEMPS_POUVOIR 30


enum TypeGameParty
{
	INTRO =0,
	MENU ,
	GAME,
	OPTION,
	SCORE,
	CREDITS,
};

#endif