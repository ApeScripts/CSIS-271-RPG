#include <iostream>
#include <windows.h>
#include <Lmcons.h>
#include <cstdlib>
#include <time.h> 

#include "TileMaker.h"
using namespace std;

int Gameplay(int weapon)
{
	TileMaker Tiles;

	//Smart Randomizer
	int SmartRand[5] = {};
	int SmartRandC = 0;

	int Poop = 1;
	while (true) {
		bool Bad = false;
		Poop = rand() % 8;

		for (int i = 0; i < 5; i++) {
			SmartRand[i];
			if (SmartRand[i] == Poop)
				Bad = true;
		}

		if (Bad == false)
			break;
	}
	if (Poop != 7) {
		SmartRand[SmartRandC];
		SmartRandC++;
	}

	//Activate Tile
	if (Tiles.Problem(Poop,weapon))
		return 0;

	return 0;
}

int main()
{
	TileMaker Tiles;
	string SaveCode;
	int tool = 1;

	//Setting UP User's Name
	DWORD size = UNLEN + 1;
	GetUserName((TCHAR*)Tiles.PlrName, &size);

	//Text Art Piece

	cout << "              .        ....                                      " << endl
		<< "         .:...:...::...---.           .....::..                  " << endl
		<< "         .::.::...:-:..--.            .:-:---.....  ....         " << endl
		<< "         ......  ...::.::.            .::::-=----:...::. ...     " << endl
		<< "     ..:...:::.    .....:=.      ... .-*%+**=:.. . .::..:--:.    " << endl
		<< "       .:-----.    .:-:-=#-. ..=#%#*-...-@@%-... ......::....    " << endl
		<< "       .-:-==::    .:#%%#%-..*@%##%%@%:.:--..:.  :-...:::.       " << endl
		<< "        .-----.     .::::-:..*++====+#*.::..-:.  .-:::-=:.       " << endl
		<< "        ..:--..     .....:-:-=**+=+*+=#::-:      .:-=---.        " << endl
		<< "       ..=-:::.     ::::----+=====---=====-.   ...:--==:.        " << endl
		<< "     .::::::::::....:.......:==+++=--=-:::::::....::.:......     " << endl
		<< "     .:::....::::............:====-==-::::::.....::........       " << endl
		<< "    ...::.....::::.........:..-+++==-:::::::.....:.......::..    " << endl
		<< "  ..::::::.....::::........:..-===----:::::......:.......:::::.  " << endl
		<< " .::::::::.....::::....:-++#%#-==----=%%#+-::....:.:::..::::::.  " << endl
		<< "  ::::::::..::::-::.:#%%%%%%%%%+-==*%%%%%%%%#-:.:::::::.-:::::.  " << endl
		<< " .:::::::::::::::::-%%%%%%%%%%%%%%%%%%%%%%%%%%*:::::.........:.. " << endl
		<< ".:::::::::::::::::*%%@%%%%%%%%%%%%%%%%%%@%%%%%#:....::::::::::::." << endl
		<< ".::::::::::::::::*%%%@%#+%+##=****%#+#%@%%%%%%%-:::::::::::::::.." << endl
		<< " .::::--::::::::=%@%%@%#=+=#=-*+=+#++=+-%@%%%%%-:::::::::::::::.." << endl
		<< " .::::::::::::::#%%%*+%%*=:+:=%++=*--#*+@%%%%%%-::::::::::::::::." << endl
		<< ".-::::::::::::::%%%%%%+#%%%%%%%##%%%##=#@@@%%%#:::::::::::::::::." << endl
		<< ".-::::::::::::::#%%%%%%%%%@%%%%%#%%%%%@@@%%%%%%-:::::::::::::::-." << endl
		<< "..:::::.........*%%%%%%%%%%%@%%%%#=--*%@%%%%%%#.................." << endl
		<< "                  Welcome to CS271 RPG ";
	wcout << Tiles.PlrName << endl;
	
	//Asking to Load Save
	cout << "Do you want to Load a Save (Y/N)" << endl;
	bool Newbie = false;
	
	if (Tiles.DecisionPrompt(2) == 1) {
		cout << "Input Save Code: " << endl;
		cin >> SaveCode;
		//Remember to put sutff here when figuring out save stuff :))
		Newbie = true;
	}
	
	system("cls");

	//=============================== START GAME ===============================

	if (Newbie) {
		Tiles.Typing("Welcome back ", Tiles.PlrName, " I've been waiting...");
		
		//This is All testing
		Tiles.Problem(4, tool);
	}
	else {
		//TUTORIAL

		Tiles.Typing("France July, 1916");
		Tiles.Typing("You've been selected for the next charge at dawn");
		Tiles.Typing("Death awaits anyone who leaves the trench, but you don't plan on leaving");
		Tiles.Typing("You've heard from others of a forest nearby that disappears people");
		Tiles.Typing("You plan on waiting out the war there");

		cout << "Press Y to continue..." << endl;
		Tiles.DecisionPrompt(1);
		system("cls");

		//Picking your Weapon
		cout << "The night before the charge..." << endl;
		Tiles.Typing("You prepare to go and grab your...");
			cout << "[Y] Rifle (High DMG, Low Accuracy)" << endl
			<< "[N] Pistol (Medium DMG, Average Accuracy)" << endl
			<< "[H] Sword (Low DMG, High Accuracy)" << endl;
		tool = Tiles.DecisionPrompt(3);

		if (tool == 1)
			Tiles.Typing("With your RIFLE, you leave for the forest");
		else if (tool == 2)
			Tiles.Typing("With your PISTOL, you leave for the forest");
		else if (tool == 3)
			Tiles.Typing("With your SWORD, you leave for the forest");

		cout << "Press Y to continue..." << endl;
		Tiles.DecisionPrompt(1);
		system("cls");

		//First fight
		Tiles.Typing("You enter the forest edge when you get suddenly attacked");

		if (Tiles.Problem(0, tool) == 1) {
			Tiles.Typing("On the brink of death, you escape into a small trench");
			Tiles.Typing("Seeing its prey gone, the bear wanders into the fog");
		}

		Tiles.Typing("You look around yourself and notice you no longer can see the outside");
		Tiles.Typing("And so your adventure begins...");

		cout << "Press Y to continue..." << endl;
		Tiles.DecisionPrompt(1);
		system("cls");

		//Start game
		Gameplay(tool);
	}

	return 0;
}

