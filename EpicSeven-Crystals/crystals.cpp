#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
short  days;
std::string NRL;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
struct Division
{
	std::vector<std::string> Leagues = { "LEGEND 1","LEGEND 2","LEGEND 3","LEGEND 4","LEGEND 5","LEGEND 6",
										"CHAMPION 1","CHAMPION 2","CHAMPION 3","CHAMPION 4","CHAMPION 5",
										"CHALLENGER 1","CHALLENGER 2","CHALLENGER 3","CHALLENGER 4","CHALLENGER 5",
										"MASTER 1","MASTER 2","MASTER 3","MASTER 4","MASTER 5",
										"GOLD 1","GOLD 2","GOLD 3","GOLD 4","GOLD 5",
										"SILVER 1","SILVER 2","SILVER 3","SILVER 4","SILVER 5",
										"BRONZE 1","BRONZE 2","BRONZE 3","BRONZE 4","BRONZE 5" };

	std::vector<float> gems =		  { 1800,1500,1200,1100,1050,1000,
										840,830,820,810,800,
										640,630,620,610,600,
										490,480,470,460,450,
										360,345,330,315,300,
										285,270,255,240,225,
										210,195,180,165,150 };
}league;

//Crystal Count
void MaximizingSavings(short needed, float b)
{
	std::string Division;
	float gemsL = b;
	float NeededGems = (needed / 50) * 950;
	float WeeklyArenaDiamond;
	if (NRL == "Limited")
		WeeklyArenaDiamond = (days / 7) + 3;
	else if (NRL == "Rerun")
		WeeklyArenaDiamond = (days / 7) + 1;
	else
		WeeklyArenaDiamond = (days / 7) + 2;
	
	for (int i = league.Leagues.size()-1; i >= 0; i--)
	{
		if ((league.gems[i] * WeeklyArenaDiamond + gemsL) - NeededGems >= 0)
		{
			Division = league.Leagues[i];
			SetConsoleTextAttribute(hConsole, 12);
			std::cout << "\nYou need to be at least:\t" << Division << " if you want to pity the banner hero.";
			SetConsoleTextAttribute(hConsole, 7);
			break;
		}
		else if ((league.gems[0] * WeeklyArenaDiamond + gemsL) - NeededGems < 0)
		{
			std::cout << "\nWon't have enough gems to pity the hero unless you finish challenges and events.";
		}
	}
	std::cout << "\n\n\n";

}
void BookmarksNeeded(int rn, short gemsL)
{
	short needed = (121 * 5) - rn;
	if (needed > 0) {
		std::cout << "\nYou need another:\t" << needed << " bookmarks";
		MaximizingSavings(needed,gemsL);
	}
	else {
		SetConsoleTextAttribute(hConsole, 12);
		std::cout << "\nYou have enough bookmarks for the upcoming banner\n\n\n";
		SetConsoleTextAttribute(hConsole, 7);
	}
}
void CrystalSaved( short gems,short bookmarks)
{
	short packs = gems / 950;
	short gemsAfterC = gems - packs * 950;
	int savedRightNow = bookmarks + (packs * 50);
	std::cout << "\nConverting gems right now will lead to:\t" << savedRightNow << " bookmarks.";
	std::cout << "\nGems left after converting:\t" << gemsAfterC;
	BookmarksNeeded(savedRightNow, gemsAfterC);

}
void QuestionsNeeded()
{
	int gem_number;
	short bookmarks;
	std::cout << "Gem number:\t";
	std::cin >> gem_number;
	std::cout << "\nBookmark number:\t";
	std::cin >> bookmarks;
	std::cout << "\nDays until next banner:\t";
	std::cin >> days;
	std::cout << "\nLimited/New/Rerun Banner(Rerun limited count as limited):\t";
	std::cin >> NRL;
	CrystalSaved(gem_number,bookmarks);
}

//Fodder Count
void FQuestionsNeeded();
void CalculateFodderNeeded(short,short,short);

int main()
{
	std::string choice;
	std::cout << "Do you want to: \n1.Fodder Count\n2.Crystal Count\n\n";
	std::cout << "Choice:\t";
	std::cin >> choice;
	std::cout << "\n";
	while (choice != "fooder count" && choice != "1" && choice != "crystal count" && choice != "2")
	{
		std::cout << "Please pick between the two:\t";
		std::cin >> choice;
		std::cout << "\n";
	}
	if (choice == "crystal count" || choice == "2")
		QuestionsNeeded();
	else
		FQuestionsNeeded();
}

void FQuestionsNeeded()
{
	short f3, f4, f5;
	std::cout << "How many 3* do you have:\t";
	std::cin >> f3;
	std::cout << "\nHow many 4* do you have:\t";
	std::cin >> f4;
	std::cout << "\nHow many 5* do you have:\t";
	std::cin >> f5;

	CalculateFodderNeeded(f3, f4, f5);

}
void CalculateFodderNeeded(short f3, short f4, short f5)
{

	int f2L,f3L, f4L, f5L;
	f5L = 5 - f5;
	f4L = 20 - f4 - (f5 * 4);
	f3L = 60 - f3 - (f4 * 3) - (f5 * 12);
	f2L = 120 - (f3 * 2) - (f4 * 6) - (f5 * 24);
	float runsLeft = 779 - ((float)(f2L * 1.3) + (float)(f3 * 5) + (float)(f4 * 15.95) + (float)(f5 * 155.8));
	//How many more fodder the user needs
	SetConsoleTextAttribute(hConsole, 12);
	if (f3L <= 0)
		f3L = 0;
	std::cout << "\n\nYou need:\t" << f3L << " 3* Fodders.\nThese 3* fodder can be promoted to the remaining: " << f4L <<" 4* fodders needed."<< "\nThose 4* fodder can be promoted to the remaining: " << f5L << " 5* fodders needed.\n\n";
	
	//Runs Left after calculating how many fodder the user already has
	if (runsLeft <= 0)
		std::cout << "\n\nYou have enough fodder to 6* a unit";
	else
		std::cout << "\nYou need:\t" << runsLeft << " more runs to 6* your hero";
	SetConsoleTextAttribute(hConsole, 7);
	std::cout<<"\n\n\n\n\n";
}