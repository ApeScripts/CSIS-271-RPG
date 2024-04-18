#pragma once
#include <iostream>
#include <windows.h>
#include <Lmcons.h>
#include <array>
using namespace std;

class TileMaker
{
public:

	int HealthBoost = 1;
	int WpnLevel = 1;
	int Money = 15;
	int PlrEncounters = 0;

	int Inventory[4] = {0, 0, 0, 0};

	TCHAR PlrName[UNLEN + 1] = TEXT("Player");

	int Problem(int Determined, int EquipedWeapon);

	//Main Prompt for Actions
	int DecisionPrompt(int type)
	{
		string YN;
		while (true) {
			cin >> YN;
			if (YN == "Y" || YN == "y" && type < 4)
				return 1;
			else if (YN == "N" || YN == "n" && type >= 2 && type < 4)
				return 2;
			else if (YN == "H" || YN == "h" && type >= 3 && type < 4)
				return 3;
			else if (YN == "J" || YN == "j" && type == 4)
				return 3;
		//Shopping Prompts Past This

			else if (YN == "0" && type > 4)
				return 0;
			else if (YN == "1" && type > 4)
				return 1;
			else if (YN == "2" && type > 4)
				return 2;
			else if (YN == "3" && type > 4)
				return 3;
			else if (YN == "4" && type > 4)
				return 4;
			else if (YN == "X" || YN == "x" && type > 3)
				return 5;
			else
				cout << "Invalid Input" << endl;
		}
	}

	//Typing to make text fancy
	int Typing(string Text, TCHAR* PlrName = {}, string End = " ")
	{
		for (int i = 0; Text[i] != '\0'; i++) {
			Sleep(70);
			cout << Text[i];
		}
		if (End != " ") {
			wcout << PlrName;
			for (int i = 0; End[i] != '\0'; i++) {
				Sleep(70);
				cout << End[i];
			}
		}
		cout << endl;
		return 0;
	}

private:
	//Situations
	bool intiation = true;

	const string Halo[9] = {
	"Bear", "Wolf", "Boar", "Treasure", "Trader", 
	"Traveller", "Empty", "Inn", "Trap"
	};

	const string Loot[3] = {
	"Meat", "Bandage", "Coins"
	};

	const string Buyables[5] = {
	"Bread", "Cooked Meat", "Bandage","Elixer","Weapon Upgrade"
	};

	bool Battle(int EWD, int BDM, int BHP, int HP, string Event);

	bool Rewards(int type);

	bool GetItems() {
		cout << "Bread: [" << Inventory[0] << "], ";
		cout << "Meat: [" << Inventory[1] << "], ";
		cout << "Cooked Meat: [" << Inventory[2] << "], ";
		cout << "Bandage: [" << Inventory[3] << "]" << endl;
		return false;
	}

	bool RemoveItem(string Item) {
		if (Item == "Bread" && Inventory[0] > 0)
			Inventory[0] = Inventory[0] - 1;
		else if (Item == "Meat" && Inventory[1] > 0)
			Inventory[1] = Inventory[1] - 1;
		else if (Item == "Cooked Meat" && Inventory[2] > 0)
			Inventory[2] = Inventory[2] - 1;
		else if (Item == "Bandage" && Inventory[3] > 0)
			Inventory[3] = Inventory[3] - 1;

		return false;
	}

	bool AddItem(string Item) {
		int BagSize = Inventory[0] + Inventory[1] + Inventory[2] + Inventory[3];

		if (BagSize < 15) {
			if (Item == "Bread")
				Inventory[0] = Inventory[0] + 1;
			else if (Item == "Meat")
				Inventory[1] = Inventory[1] + 1;
			else if (Item == "Cooked Meat")
				Inventory[2] = Inventory[2] + 1;
			else if (Item == "Bandage")
				Inventory[3] = Inventory[3] + 1;

			return true;
		}
		else
			cout << "Not Enough Space!" << endl;

		return false;
	}
};