
#include "TTTModel.h"
#include "TTTView.h"
#include "TTTController.h"
#include "TTT_AI.h"


int main()
{
	system ("cls");

	TTTModel TTTM;
	TTTView TTTV(&TTTM);
	TTT_AI oTTT_AI(&TTTM);
	TTTController TTTC(&TTTM,&oTTT_AI);
	
	TTTC.AI_Off();
	
	TTTV.ShowBoard();

	for(;;){	
		bool res = TTTC.Process();
		TTTV.ShowBoard();
		if (!res) break;
	}

	system("pause");
	return 0;
}