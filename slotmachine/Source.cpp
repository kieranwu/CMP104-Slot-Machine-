/* Created by Kieran Wu - ID: 1801249
	 This is a slot machine game*/

//This includes all the libaries needed for the slot machine to work
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <iostream>

//This will tell the VS to use the std namespace.
using namespace std;

//This sets up the two global functions
void MainMenu();
int MainGame();

//This creates a HANDEL named hConsole
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

//This creates the two global variables
int tokens = 10;
int speed = 60;

//This Function will prevent the program from continuing until it detects the enter key press
void GameWait() 
{
	//initialise local variables
	char  key = 'm';
	bool waitStart = true;
	
	//A conditional loop created to wait until 'waitStart' is false
	while (waitStart)
	{
		//Detects if key has been pressed
		if (_kbhit())
		{
			// sets the variable key to the uppercase character of what key was detected
			key = toupper(_getch());
		}

		// This is check if the key pressed was the enter key and set 'waitStart' to false if the condition is true
		if (key == VK_RETURN) { waitStart = false; }
	}
}

//This function will display the settings menu and allow you to edit the global variables
void Settings()
{
	//initialise local variables
	bool wait = true;
	bool press = true;
	char key = 'm';
	int selected = 1;

	//A conditional loop is used to keep the menu displaying after the console is cleared
	while (wait)
	{
		//Checks if the variable press is true
		if (press)
		{
			//Detects if key has been pressed
			if (_kbhit())
			{
				// sets the variable key to the uppercase character of what key was detected
				key = toupper(_getch());
			}
			
			//Checks if the 'S' key was pressed
			if (key == 'S')
			{
				//This will set the variables bellows to prevent the next lines running more than it should
				//This safeguard is in place as the program runs very quickly and the time taken to press the key is enough for the program to run multiple times.
				//Therefore this will only accept the next input after it has completed its full function
				press = false;
				key = 'm';

				//This if statement is used to allow the user to press 'S' continueously so when it is at the end it will go back to the start
				if (selected == 3)
				{
					selected = 1;
				}
				else
				{
					//Otherwise it will simply add 1 to selected
					selected += 1;
				}

				//sets press to true allowing input from the user again
				press = true;
			}

			//Checks if the 'W' key was pressed
			if (key == 'W')
			{
				//safeguard for unwanted inputs. see line 71 for more information
				press = false;
				key = 'm';

				//This if statement is used to allow the user to press 'W' continueously so when it is at the start it will go to the end
				if (selected == 1)
				{
					selected = 3;
				}
				else
				{
					//Otherwise it will decrease selected by 1
					selected -= 1;
				}

				//sets press to true allowing input from the user again
				press = true;
			}

			//Checks if the 'A' key was pressed
			if (key == 'A')
			{
				////safeguard for unwanted inputs. see line 71 for more information
				press = false;
				key = 'm';

				//This will check if tokens is greater than one and selected is one
				//It is important to have both conditions met as it wont allow the user to decrease the amount of tokens if it is on zero or below
				if (tokens > 1 && selected == 1)
				{
					//decreases the amount of tokens by one
					tokens -= 1;
				}

				// This will check if the speed is greater than 40 and selected is 2
				//It is important that both conditions are met as it wont allow the user to decrease the speed if it is on 40.
				if (speed > 40 && selected == 2)
				{
					//decreases the speed by five
					speed -= 5;
				}

				//sets press to true allowing input from the user again
				press = true;
			}

			//Checks if the 'D' key was pressed
			if (key == 'D')
			{
				//safeguard for unwanted inputs. see line 71 for more information
				press = false;
				key = 'm';

				//This will check if selected is one and if tokens is less than 99
				//This will prevent user from setting the tokens to 100+
				if (selected == 1 && tokens < 99)
				{
					//increases the number of tokens by one
					tokens += 1;
				}
				
				//This will check if selected is two and check if the speed is below 999
				//This will prevent the user from increasing the speed beyond 999
				if (selected == 2 && speed < 999)
				{
					//increases the speed by five
					speed += 5;
				}

				//sets press to true allowing input from the user again
				press = true;
			}

			//Checks if the enter key is pressed and selected is 3
			if (key == VK_RETURN && selected == 3)
			{
				//this will run the main menu function taking the user back to the main menu
				MainMenu();
			}
		}

		//This will set the colour of the next line of text to green
		SetConsoleTextAttribute(hConsole, 10);
		
		//This will print out the next block of text
		cout << R"(
   _________________________ 
  |       Settings          |
  |                         |
  |_________________________|
)";
	
		//This will check if selected is one and point an arrow to tokens
		if (selected == 1)
		{
			SetConsoleTextAttribute(hConsole, 10);
			cout << "  |";
			SetConsoleTextAttribute(hConsole, 9);	
			cout << "-->Number of Tokens: " << tokens;

			//This line will adjust the line which connects the box if the number of tokens is less than 10
			if (tokens < 10) { cout << " "; }
			SetConsoleTextAttribute(hConsole, 10);
			cout << "  |\n";
		}
		else
		{
			//Otherwise it will output it as normal
			SetConsoleTextAttribute(hConsole, 10);
			cout << "  |   Number of Tokens: " << tokens;
			if (tokens < 10) { cout << " "; }
			cout << "  |\n";
		}

		//This will check if selected is two and point an arrow to speed
		if (selected == 2)
		{
			SetConsoleTextAttribute(hConsole, 10);
			cout << "  |      ";
			SetConsoleTextAttribute(hConsole, 9);
			cout << "-->Spin Speed: " << speed;
			SetConsoleTextAttribute(hConsole, 10);
			//This line will adjust the line which connects the box if the number of tokens is less than 10
			//For speed the user may increase the speed into three digits therefore the if statement is needed to adjust the line
			if (speed < 10) { cout << " "; }
			if (speed > 99) { cout << " |\n"; }
			else { cout << "  |\n"; }
		}
		else
		{
			//Otherwise it will print it as normal
			SetConsoleTextAttribute(hConsole, 10);
			cout << "  |         Spin Speed: " << speed;
			if (speed < 10) { cout << " "; }
			if (speed > 99) { cout << " |\n"; }
			else { cout << "  |\n"; }
		}

		//This will check if selected is three and point an arrow to exit
		if (selected == 3)
		{
			SetConsoleTextAttribute(hConsole, 10);
			cout << "  |        ";
			SetConsoleTextAttribute(hConsole, 9);
			cout << "-->Exit          ";
			SetConsoleTextAttribute(hConsole, 10);
			cout<< "|\n";
		}
		else
		{
			//Otherwise it will print it as normal
			SetConsoleTextAttribute(hConsole, 10);
			cout << "  |           Exit          |\n";
		}

		//This will output the rest of the settings menu
		SetConsoleTextAttribute(hConsole, 10);
		cout << "  |_________________________|\n";
		cout << "  |Use A to decrease and    |\n";
		cout << "  |Use D to increase!       |\n";
		cout << "  |_________________________|\n";

		//This will check if wait is true and clear the screen for updates to be made
		if (wait)
		{
			//This will stop the console for the set time
			Sleep(90);
			
			//This will clear the console
			system("CLS"); 
		}
	}
}

//This function will display the main menu where the user can access the main game and settings menu
void MainMenu()
{
	//initailise the local variables
	bool wait = true;
	bool press = true;
	int selected = 0;
	char key = 'm';

	//A conditional loop is used to keep the next lines running while wait is true
	while (wait)
	{
		//Checks if the variable press is true
		if (press)
		{
			//This again is getting user key press and changing the variable selected
			// for more information see line 59
			if (_kbhit())
			{
				key = toupper(_getch());
			}
			if (key == 'S')
			{
				press = false;
				key = 'm';
				if (selected == 2)
				{
					selected = 0;
				}
				else
				{
					selected += 1;
				}
				press = true;

			}
			if (key == 'W')
			{
				press = false;
				key = 'm';
				if (selected == 0)
				{
					selected = 2;
				}
				else
				{
					selected -= 1;
				}
				press = true;

			}
			if (key == VK_RETURN)
			{
				//Switch statement is used to give the correct output
				switch (selected)
				{
				case 0: MainGame(); break;
				case 1: Settings(); break;
				case 2: exit(0); break;
				}
			}
		}


		//This will print out the main menu in green and the selected option in blue 
		//for more information see line 179
		SetConsoleTextAttribute(hConsole, 10);
		cout <<
			R"(
     ________________________________________________________
    /  ______    __    __  ___         __   _           __  /
   /  / __/ ___ / /_  /  |/  ___ _____/ /  (____ ___   / / /
  /  _\ \/ / _ / __/ / /|_/ / _ `/ __/ _ \/ / _ / -_) /_/ /
 /  /___/_/\___\__/ /_/  /_/\_,_/\__/_//_/_/_//_\__/ (_) /
/_______________________________________________________/)" << endl;

		if (selected == 0)
		{
			SetConsoleTextAttribute(hConsole, 9);
			cout << "                     -->Play\n";
		}
		else
		{
			SetConsoleTextAttribute(hConsole, 10);
			cout << "                        Play\n";
		}
		if (selected == 1)
		{
			SetConsoleTextAttribute(hConsole, 9);
			cout << "                     -->Settings\n";
		}
		else
		{
			SetConsoleTextAttribute(hConsole, 10);
			cout << "                        Settings\n";
		}
		if (selected == 2)
		{
			SetConsoleTextAttribute(hConsole, 9);
			cout << "                     -->Exit\n";
		}
		else
		{
			SetConsoleTextAttribute(hConsole, 10);
			cout << "                        Exit\n";
		}
		SetConsoleTextAttribute(hConsole, 14);
		cout << "\n		Use W and S to navigate!\n";

		//this will check if wait is true and clear the screen for any updates
		//for more information see line 257
		if (wait)
		{
			Sleep(90);
			system("CLS"); // clears the console
		}
	}

}

//This function will create a random number  and return it
int Rolltime() 
{
	//initalise roll which will store the random number
	int roll;
	roll = rand() % 10 + 6; // generate a random number between 5 and 10
	//cout << roll << endl; *ignore this, only use for testing*

	//This will return the value stored in roll
	return roll;
}

//This function will take the slots and check if the user has won the jackpot
int results(char Slot1,char Slot2,char Slot3) 
{
	//This will take the variables passed in and compare them to check if all three are the same
	if (Slot1 == Slot2 && Slot1 == Slot3)
	{
		//This will check if all the slots is character '6' and award the user 666 tokens and output 
		if (Slot1 == '6' && Slot2 == '6' && Slot3 == '6')
		{
			tokens += 666;
			cout << "You rolled 666! \n";
			cout << "You won 666 tokens! \n";
		}
		else
		{
			//Otherwise it will simply add 30 to the users tokens and output
			tokens += 30;
			cout << "You rolled three in a roll! \n";
			cout << "You won 30 tokens! \n";
		}
	}
	else if (Slot1 == Slot2 || Slot1 == Slot3 || Slot2 == Slot3) 
	{
		//This will add 3 to the users tokens if atleast 2 of the slots are the same
		tokens += 3;
		cout << "You rolled two in a roll! \n";
		cout << "You won 3 tokens! \n";
	}
	else
	{
		//Othewise it will just remove one token from the user
		cout << "you lost one token! \n";
		tokens -= 1;
	}

	//This will run the game run function 
	GameWait();

	//This will run the Main game function
	MainGame();

	//This will return the tokens out of the function 
	return tokens;
}

//This function will check which number comes before in the slot
int CheckBefore(int num)
{
	//This will check if the number is zero
	//It is important that this exists as it will return the last number to make the slot seem circular
	if (num == 0)
	{
		//This will return 5
		num = 5;
		return num;
	}
	else
	{
		//otherwise it will return one minus of the original value
		num -= 1;
		return num;
	}
}

//This function will check which number comes after in the slot
int CheckAfter(int num)
{
	//This will check if the number passed in is five
	//It is important that this exists as it will return the first number to make the slot seem circular
	if (num == 5)
	{
		//This will return zero
		num = 0;
		return num;
	}
	else
	{
		//Otherwise it will return one added to the orginal value
		num += 1;
		return num;
	}
}

//This function is the main game where the user may spin the slot machine
int MainGame()
{
	//initialise the local variables
	int aone, atwo, athree, bone, btwo, bthree;
	int i = 0;
	int j = 0;
	int k = 0;
	int press = 0;
	int time = 0;
	bool spin = true;
	bool wait = false;
	bool end = false;
	int temp = 0;
	char key = 'm';
	//This will set up the slot pattern
	char Slot1[6] = { '+','%','$','@','&','6' };
	char Slot2[6] = { '@','%','+','6','$','&' };
	char Slot3[6] = { '6','%','@','&','$','+' };

	//This will check if the user has enough tokens to play
	if (tokens < 1) 
	{
		//This will output the end game message 
		SetConsoleTextAttribute(hConsole, 12);
		cout << "You have no tokens left!\n";

		//This will run the game wait function
		GameWait();

		//This will run the main menu function taking the user back to the main menu
		MainMenu();
	}
	
	//A conditional loop is used to keep the next lines running while spin is true
	while (spin)
	{
		//This will update variables for the slot animation 
		char *one = &Slot1[i];
		char *two = &Slot2[j];
		char *three = &Slot3[k];
		
		//This will run the check before and after functions to find out which characters to display
		bone = CheckBefore(i);
		btwo = CheckBefore(j);
		bthree = CheckBefore(k);
		aone = CheckAfter(i);
		atwo = CheckAfter(j);
		athree = CheckAfter(k);

		//this will check if spin is true and clear the screen 
		//see line 257 for more information
		if (spin) {
			Sleep(speed);
			system("CLS"); 
		}

		//This will output the slot machine 
		// for more information see line 176
		SetConsoleTextAttribute(hConsole, 10);
		cout << R"(
     ________________________
    |      Slot Machine!     |
    |________________________|
)";
		SetConsoleTextAttribute(hConsole, 10);
		cout << "    |";
		SetConsoleTextAttribute(hConsole, 11);
		cout << "  You have " << tokens << " tokens!";

		//This will adjust the line if the number of tokens is less than 10
		if (tokens < 10)
		{
			cout << " ";
		}

		//This will output the three rows and three columbs of the slot machine characters 
		//Again see line 179 for more information
		SetConsoleTextAttribute(hConsole, 10);
		cout << "   |\n";
		cout << "    |     _______________    |\n";
		SetConsoleTextAttribute(hConsole, 10);
		cout << "    |     |   |" << Slot1[bone] << "|" << Slot2[btwo] << "|" << Slot3[bthree] << "|   |    |\n";
		SetConsoleTextAttribute(hConsole, 14);
		cout << "    |     |-->|" << *one << "|" << *two << "|" << *three << "|<--|    |\n";
		SetConsoleTextAttribute(hConsole, 10);
		cout << "    |     |   |" << Slot1[aone] << "|" << Slot2[atwo] << "|" << Slot3[athree] << "|   |    |\n";
		
			cout << "    |     |_____________|    |\n";
			cout << "    |                        |\n";

		//This will check if the slot machine is waiting for user input and output
		if (!wait)
		{
			cout << "    |  Press Enter to Spin!  |\n";
		}
		else
		{
			//Otherwise it will output this
			cout << "    |       Spinning...      |\n";
		}
			cout << "    |________________________|\n";

			SetConsoleTextAttribute(hConsole, 14);
		cout << "\n\n\n\nPress 'Z' Key to go to main menu\n";
		
		//This will check if wait is false and detect a key press
		if (wait == false)
		{
			//for more information about this go to line 58
			if (_kbhit())
			{
				key = toupper(_getch());
			}

			//This will check if the enter key was pressed 
			if (key == VK_RETURN)
			{
				//Safeguard used to prevent too many inputs
				// for more information goto line 69
				wait = true;
				key = 'm';

				//this will add one to press which dictates which slot is being rolled
				press++;

				//This will run the rolltime function and set time to the random number returned
				time = Rolltime();

				//this is a place holder for the timer
				temp = 0;

			}
			//Checks if the Z key has been pressed
			if (key == 'Z')
			{
				//This runs the main menu function
				MainMenu();
			}
		}
		
		//This next block of code will:
		//1. Check if the index is greater than 4, if so it will set it back to 0.
		//2. Check which slot press is on , if so it will continue.
		//3. Check if the timer is done, if not it will add one to temp whilst adding one to the index until temp = timer.
		//4. Check if the timer is done and the slot has stopped, if so it will set wait to false allowing input.
		//5. If 4. is false  then it will keep the index the same, stopping the slot from moving.
		if (i > 4){i = 0;}

		if (press > 0)
		{
			if (temp != time && press == 1)
			{
				temp += 1;
				i++;
			}
			else if (temp == time && press == 1){wait = false;}
			else{i = i;}
		}
		else{i++;}

		if (j > 4){j = 0;}
		if (press > 1)
		{
			if (temp != time && press == 2)
			{
				temp += 1;
				j++;
			}
			else if (temp == time && press == 2){wait = false;}
			else{j = j;}
		}
		else{j++;}

		if (k > 4){k = 0;}
		if (press > 2)
		{
			if (temp != time && press == 3)
			{
				temp += 1;
				k++;
			}
			else if (temp == time && press == 3)
			{
				wait = false;
				end = true;
			}
			else{k = k;}
		}
		else{k++;}
		
		if (end) { spin = false; }
		
	}

	//This will set tokens to the output of the results function
	tokens =  results(Slot1[i], Slot2[j], Slot3[k]);
	return 0;
}

//IGNORE THIS - this function is used for testing
void testing()
{
	bool wait = true;
	char key = 'm';
	bool test = true;
	bool goop = false;
	
	while (test)
	{
		if (wait)
		{
			if (_kbhit())
			{
				// get keyboard data, and filter it
				key = toupper(_getch());
			}
			if (key == VK_RETURN)
			{
				wait = false;
				key = 'm';
				cout << "click" << endl;
				goop = true;

			}
		}
		if (goop)
		{
			goop = false;
			for (int i = 0; i < 10; i++)
			{
				Sleep(60);
				cout << i << endl;
			}
			wait = true;
			
		}

	}

}

//This is the main function of the program
int main()
{
	//This will run the main menu function
	MainMenu();
	//testing(); *ignore this- used for testing*

	//used to keep program from shutting itself dowm at the end
	int stop;
	cin >> stop;
}