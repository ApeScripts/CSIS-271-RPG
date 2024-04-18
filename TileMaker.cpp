#include "TileMaker.h"
#include <iostream>
#include <cstdlib>
#include <array>
#include <time.h> 
using namespace std;

//Fighting Block
bool TileMaker::Battle(int EWD, int BDM, int BHP, int HP, string Event) {
	int Roll;
	int Chance = 50;
	if (EWD == 1)
		Chance = 40;
	else if (EWD == 2)
		Chance = 60;
	else if (EWD == 3)
		Chance = 80;

	while (true) {
		cout << "[Y] Attack" << endl
			<< "[N] Food" << endl
			<< "[H] Run" << endl;

		int choice = DecisionPrompt(3);
		
		system("cls");
		if (choice == 1) {
			//Damage Deciders
			int DMG = EWD + rand() % 3;
			int BDMG = BDM + rand() % 3;

			//Chance of Hit / Being Hit
			Roll = rand() % 100;
			

			if (Roll >= 0 || Roll <= Chance)
			{
				BHP = BHP - DMG;
				cout << "The " << Event << " was hit! " << endl
					<< Event << ": " << BHP << " HP" << endl;
			}
			else
				cout << "The " << Event << " avoided your attack! " << endl
				<< Event << ": " << BHP << " HP" << endl;

			Roll = rand() % 100;

			if (Roll > 50)
			{
				HP = HP - BDMG;
				cout << "The you've been hit! " << endl;
				wcout << PlrName;
				cout << " HP:" << HP << " HP" << endl;
			}
			else
			{
				cout << "You've avoided the attack! " << endl;
				wcout << PlrName;
				cout << " HP:" << HP << " HP" << endl;
			}
		}
		else if (choice == 2) {
			GetItems();
		}
		else if (choice == 3) {
			//Escaping the battle
			Roll = rand() % 100;
			if (Roll >= 0 || Roll <= 30) {
				cout << "You've escaped the " << Event << endl;
				return true;
			}
			else
				cout << "You failed to escape the " << Event << endl;
		}
	if (BHP <= 0) {
		cout << "You defeated the " << Event << endl;
		return false;
	}
	else if (HP <= 0) {
		cout << "You died to the " << Event << " L bozo" << endl;
		return true;
	}
	}
	return false;
}

//Loot Function
bool TileMaker::Rewards(int type) {
	int RewardAmt = rand() % 3;
	if (RewardAmt > 0) {
		string ReList[3] = {};
		for (int i = 0; i < RewardAmt; i++) {
			string Stuff;
			if (type == 1)
				Stuff = Loot[rand() % 2];
			else if (type == 2)
				Stuff = Buyables[rand() % 2];

			//Add to loot list
			if (ReList[0] == Stuff + ": 1")
				ReList[0] = Stuff + ": 2";
			else if (ReList[1] == Stuff + ": 1")
				ReList[1] = Stuff + ": 2";
			else if (ReList[0] == Stuff + ": 2")
				ReList[1] = Stuff + ": 3";
			else
				ReList[i] = Stuff + ": 1";

			//Adding Items to Inventory
			if (Stuff == "Coins")
				Money = Money + rand() & 10;
			else
				AddItem(Stuff);
		}
		for (int i = 0; i < 3; i++)
			if (ReList[i] != "")
				cout << ReList[i] << ", ";

		cout << endl;
	}
	else {
		cout << "Nothing" << endl;
		return false;
	}

	return true;
}

int TileMaker::Problem(int Determined, int EquipedWeapon) {
	string Event = Halo[Determined];
	if (intiation) {
		srand((unsigned int)time(NULL));
		intiation = false;
	}

	//Player's HP
	int HP = 40 + (HealthBoost / 2);
	
	if (Event == "Bear" || Event == "Wolf" || Event == "Boar") {
		//Weapon's Normal Damage
		int EWD = 0;
		if (EquipedWeapon == 1)
			EWD = 4 + (WpnLevel * (3/2));
		else if (EquipedWeapon == 2)
			EWD = 2 * (WpnLevel * (3 / 2));
		else if (EquipedWeapon == 3)
			EWD = WpnLevel * 2;
		
		//Challenger's Stuff
		int BHP = 0, BDM = 0;
		if (Event == "Bear") {
			BHP = 20 + rand() % 20;
			BDM = 3;
		}
		else if (Event == "Wolf") {
			BHP = 15 + rand() % 15;
			BDM = 2;
		}
		else if (Event == "Boar") {
			BHP = 10 + rand() % 10;
			BDM = 1;
		}
		cout << "A " << Event << " Blocks your path!" << endl;

		if (Battle(EWD, BDM, BHP, HP, Event))
			if (HP <= 0)
				return 1;
			else
				return 0;
		
		//Rewards for win
		cout << "Loot: ";

		if (!Rewards(1))
			cout << "The " << Event << " dropped no items" << endl;
	}
	else if (Event == "Treasure") {
		int Rando = rand() % 3;

		//Story Prompts
		if (Rando == 1) {
			Typing("You stumble accross a chest halfway burried in the ground");
			Typing("You open it and discover; ");
		}
		else if (Rando == 2) {
			Typing("Walking through the woods you discover a skeleton holding a box");
			Typing("You grab the box to find; ");
		}
		else if (Rando == 3) {
			Typing("There is a broken crate laying against a large tree");
			Typing("You look inside to find; ");
		}

		//Rewards
		Rewards(2);
	}
	else if (Event == "Trader") {
		//Story Prompts
		if (PlrEncounters == 0 || PlrEncounters == 2) {
			Typing("In the distance you see a light as you come closer you see that its a cart and a mysterious figure");
			cout << "TRADER;" << endl;

			Typing("Ah a new customer!");
			Typing("I have anything you need as long as you have the money for it");
		}
		else if (PlrEncounters == 1 || PlrEncounters == 3) {
			Typing("In the distance you see a fimiliar light where a friend stands by their cart");
			cout << "TRADER;" << endl;

			Typing("Returning again?");
			Typing("I'm not surprised, no one can resist these deals!");
		}

		Typing("Now what would you like?");

		int Cost = 10;
		int Shopper = 0;
		while (true) {
			//Start of Shop
			for (int i = 0; i < 5; i++) {
				if (i > 0)
					Cost = i * 20;

				cout << i << ": " << Buyables[i] << "¢" << Cost << endl;
			}
			GetItems();
			wcout << PlrName;
			cout << "'s Wallet: ¢" << Money << endl;
			cout << "Type the associated number to buy and type 'X' to exit" << endl;

			//Purchase / Exit
			Shopper = DecisionPrompt(5);

			if (Shopper == 5)
				break;
			else {
				system("cls");
				if (Shopper == 0)
					Cost = 10;
				else
					Cost = 20 * Shopper;

				//Seeing if they can buy
				if (Money >= Cost) {
					if (Shopper == 3){ 
						HealthBoost = HealthBoost + 1;
						Money = Money - Cost;
						Typing("Your soul ascends higher, would you like to buy more?");
					}
					else if (Shopper == 4) {
						WpnLevel = WpnLevel + 1;
						Money = Money - Cost;
						Typing("Your sword glows with power, would you like to buy more?");
					}
					else {
						if (AddItem(Buyables[Shopper])) {
							Money = Money - Cost;
							Typing("Fine Purchase, would you like to buy more?");
						}
						else
							cout << "Transaction failed, you've not been charge" << endl;
					}
				}
				else
					Typing("You're short in money, would you like to buy something cheaper?");
			}
		}

		Typing("Good luck on your journey traveller!");
	}
	return 0;
}