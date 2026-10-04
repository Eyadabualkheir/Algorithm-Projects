//Project 1 ===> Rock , Paper , Sciccors
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

int RandomNumber( int From, int To )
{

	int RandNum = rand() % ( To - From + 1 ) + From ;
	return RandNum ;
}

enum enGameChoice { rock = 1, paper = 2, sciccors = 3  } ;

short ReadHowManyRound()
{

	int Number = 0;
	do
	{
		cout << "Please Enter How Many Round Do You Want To Play : " << endl;
		cin >> Number;
	} while (Number <= 0);

	return Number;
}

short ReadPlayerChoice()
{
	short Choice = 0;
	do
	{

		cout<<"\nWhat is your Choice?\n"
		    <<"(1).Rock\n"
		    <<"(2).Paper\n"
		    <<"(3).Sciccors\n";


		cin >> Choice;

	} while (Choice < 1 || Choice > 3);



	return Choice ;
}

string From_int_To_string( enGameChoice Choice )
{
	switch( Choice )

	{
	case rock:
		return "Rock";
	case paper:
		return "Paper";
	case sciccors:
		return "Sciccors";
	}

	return "";
}


void CompareChoice(enGameChoice PlayerChoice, enGameChoice ComputerChoice, int &Draw, int &PlayerWin, int &ComputerWin)
{

	if ( PlayerChoice == ComputerChoice )
	{
		cout<<"Draw!!!!\n";

		Draw++;
	}


	else if
	(
	    (PlayerChoice == rock && ComputerChoice == sciccors) ||
	    (PlayerChoice == paper && ComputerChoice == rock) ||
	    (PlayerChoice == sciccors && ComputerChoice == paper)
	)
	{

		cout<<"You WIN!!!!!\n";

		PlayerWin++;
	}

	else
	{
		cout<<"You LOSS!!!!\n";

		ComputerWin++;

	}



}

void FinalResult(int PlayerWin, int ComputerWin, int Draw, short Round)
{
	cout << "\t------------------------------------------------------------------" << "\n";
	cout << "\t\t\t\t**** Game Over! ****" << "\n";
	cout << "\t------------------------------------------------------------------" << "\n";
	cout << "Game rounds     : " << Round << "\n";
	cout << "Player Wins     : " << PlayerWin << "\n";
	cout << "Computer Wins   : " << ComputerWin << "\n";
	cout << "Draws            : " << Draw << "\n";
	cout << "Final Results   : " ;

	if (PlayerWin > ComputerWin)

		cout << "Congratulations! You are the overall winner!" << "\n";
	else if (ComputerWin > PlayerWin)

		cout << "Computer wins overall! Better luck next time!" << "\n";

	else
		cout << "It's a draw overall! " << "\n";
	cout << "\t------------------------------------------------------------------" << "\n";


}

void StartGame()
{

	short Round = ReadHowManyRound();

	int ComputerChoice = 0 ;
	int PlayerChoice = 0 ;
	int Draw = 0 ;
	int PlayerWin = 0 ;
	int ComputerWin = 0 ;


	cout<<"\n******************GAMESTARTED******************\n";
	
	for( int i = 1 ; i <= Round ; i++ )

	{

		cout<<"\n******************ROUND["<<i<<"]******************\n"   ;

		enGameChoice PlayerChoice = (enGameChoice)ReadPlayerChoice();
		enGameChoice ComputerChoice = (enGameChoice)RandomNumber(1, 3);



		cout<<"\n============ROUND["<<i<<"]RESULTS============\n";


		cout<<"Player Choice is "<<From_int_To_string(PlayerChoice)<<endl;

		cout<<"Computer Choice is "<<From_int_To_string(ComputerChoice)<<endl;

		CompareChoice(PlayerChoice, ComputerChoice, Draw,  PlayerWin, ComputerWin);


	}

	cout<<"\n***********************************************\n";

	FinalResult( PlayerWin,  ComputerWin, Draw,  Round);

}

bool PlayAgain()
{
	cout << "Do you want to play again? (y/n): ";
	char choice;
	cin >> choice;
	if (choice == 'y' || choice == 'Y')
		return true;
	else
		return false;
}

void ResetGame()
{
	while (PlayAgain())
	{
		StartGame();
	}
}

int main ()
{

	srand ( (unsigned) time(NULL) ) ;

	StartGame();

	ResetGame();

	return 0 ;
}