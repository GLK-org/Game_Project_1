#pragma once
#include <string>
static char * MakeLPCSTR(float args[],std::string text="") {
	std::string temp = text;
	temp = temp + " " + std::to_string(args[0]);
	char buffer[64];
	if (args == nullptr) {
		std::snprintf(buffer, 64, text.c_str());
		return buffer;
	}
	std::snprintf(buffer, 64, text.c_str(), (int)(args[0] * 1000));
	return buffer;
}

static void MakeMesBoxA(float args[], std:: string text="") {
	//na razie tylko jeden element do zczytania
	
	std::string temp = text + " " + std::to_string(args[0]);

	// nie wiem po cholerê obudowa³em w funkcjê ale do bardziej dla przyk³adu chyba
		//okno rodzica, tekst, tytu³, standard zachowania
	
	MessageBoxA(0,temp.c_str(),0,0);
}

