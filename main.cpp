#include "CGame.hpp"
#include "Cscores.hpp"


int main()
{
	srand(time(NULL));
	
	Cgame MainGame = Cgame() ;

	MainGame.GameUpdate();

    return 0;
}