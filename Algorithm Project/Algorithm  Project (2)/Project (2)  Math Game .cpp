// project (2) : Math game (BONUS project)
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

int RandomNumber( int From, int To )
{

	int RandNum = rand() % ( To - From + 1 ) + From ;
	return RandNum ;
}

short HowManyQuestions()
{

	int Number = 0;
	do
	{
		cout << "Please Enter How Many Questions Do You Want To Answer From ( 1 ===> 100 ) : " << endl;
		cin >> Number;
	} while ( Number < 1 || Number > 100 );

	return Number;
}

enum enDiffculty { Easy = 1, Medium = 2, Hard = 3, Mix = 4 } ;
enum enOperators { Add = 1, Sub = 2, Multi = 3, Div = 4, Mix2 = 5 } ;

enDiffculty DiffcultyChoice ()
{
	short Choice = 0;
	do
	{

		cout << "Choose Difficulty: { EASY [1], MEDIUM [2], HARD [3], MIX [4] }\n";
		cin >> Choice;
	} while (Choice < 1 || Choice > 4);

	return (enDiffculty)Choice;
}

enOperators OperatorsChoice ()
{
	short Choice = 0;
	do
	{

		cout << "Choose Operator: { ADD [1], SUB [2], MULTI [3], DIV [4], MIX [5] }\n";
		cin >> Choice;
	} while (Choice < 1 || Choice > 5);

	return (enOperators)Choice;
}

string From_int_To_string( enOperators Choice ) //For Result
{
	switch( Choice )

	{
	case Add:
		return "+";
	case Sub:
		return "-";
	case Multi:
		return "*";
	case Div:
		return "/";

	}

	return "";
}

//Math Function
void GenerateNumbers(enDiffculty Difficulty, int &Num1, int &Num2)
{
	enDiffculty ActualDifficulty = Difficulty;

	if (ActualDifficulty == Mix) ActualDifficulty = (enDiffculty)RandomNumber(1, 3);

	switch (ActualDifficulty) {
	case Easy:
		Num1 = RandomNumber(1, 10);
		Num2 = RandomNumber(1, 10);
		break;
	case Medium:
		Num1 = RandomNumber(11, 50);
		Num2 = RandomNumber(11, 50);
		break;
	case Hard:
		Num1 = RandomNumber(51, 100);
		Num2 = RandomNumber(51, 100);
		break;


	}

}

float CalculationFunction(int Num1, int Num2, enOperators Choice )
{

	switch (Choice) {
	case Add:
		return Num1 + Num2;
	case Sub:
		return Num1 - Num2;
	case Multi:
		return Num1 * Num2;
	case Div:
		return (float)Num1 / Num2;
	default:
		return 0;
	}
}

string GetDifficultyName(enDiffculty Difficulty) {
    string arrDiff[] = { "Easy", "Medium", "Hard", "Mix" };
    return arrDiff[Difficulty - 1];
}

string GetOpTypeName(enOperators Op) {
    string arrOp[] = { "Add", "Sub", "Multi", "Div", "Mix" };
    return arrOp[Op - 1];
}

void StartQuestions ()
{

	short Questions = HowManyQuestions(), CorrectAnswers = 0 , WrongAnswer = 0 ;
    
    string Work ;  
 
	enDiffculty UserDefculityChoice = DiffcultyChoice() ;
	enOperators UserOperatorsChoice = OperatorsChoice() ;

	cout<<"\t\t======================== [ GAME STARTED ] ======================== \n";

	for ( int i = 0 ; i < Questions ; i++  )
	{
		int Num1, Num2 ;

		GenerateNumbers(UserDefculityChoice, Num1, Num2) ;

		enOperators CurrentOp = UserOperatorsChoice;

		if (CurrentOp == Mix2) CurrentOp = (enOperators)RandomNumber(1, 4);

		string OP = From_int_To_string (CurrentOp);




		//Display Questions

		cout<<"Question ["<< i +  1 <<"/"<< Questions <<"]"<<endl;

		cout<<Num1<<" "<<OP<<" "<<Num2<<" = ?"<<endl;

		float UserAnswer;
		cin >> UserAnswer;

		// Calculate Correct Answer
		
		float CorrectAnswer = CalculationFunction(Num1, Num2, CurrentOp);

		if (UserAnswer == CorrectAnswer)
		{
			cout << "Correct Answer! \n";
			CorrectAnswers++;

		}

		else
		{

			cout << "Wrong Answer! The correct answer was: " << CorrectAnswer << "\n\n";
			WrongAnswer++;
		}

		cout << "-------------------\n\n\n";
	}
	
	if ( CorrectAnswers >= WrongAnswer) { Work = "Success" ; }
 	
	else { Work = "Fail"; }
	
	
	
	
	cout<<"\t\t\t======================== [ GAME ENDED ] ========================\n\n";
	
	cout<<"\t\t\t\t\t    =====> YOU "<<Work<<"!!! <====="<<endl;
	
	cout<<"\n\t\t\t======================== [ GAME ENDED ] ========================\n\n\n";
	
	
	
	
	
	cout << "-------------------------------------------\n";
cout << "                 GAME RESULTS              \n";
cout << "-------------------------------------------\n";
cout << "Number Of Questions     : " << Questions << endl;
cout << "Questions Difficulty    : " << GetDifficultyName(UserDefculityChoice) << endl;
cout << "Operation Type          : " << GetOpTypeName(UserOperatorsChoice) << endl;
cout << "Correct Answers         : " << CorrectAnswers << endl;
cout << "Wrong Answers           : " << WrongAnswer << endl;
cout << "-------------------------------------------\n";
    
  
}
int main()
{
    srand((unsigned)time(NULL));
    
    char PlayAgain = 'Y';

    do {

   
        StartQuestions();

        cout << "\nDo you want to play again? (Y/N): ";
        cin >> PlayAgain;

    } while (PlayAgain == 'y' || PlayAgain == 'Y');

   

    return 0;
}
