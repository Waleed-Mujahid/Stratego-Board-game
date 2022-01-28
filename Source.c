#define _CRT_SECURE_NO_WARNINGS

#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

//Some global variables
char* game[10][10]; //array that stores the PIECES
int pwr[10][10]; // Array to store POWER OF PIECES
int visibility[10][10]; // Array to hide the pieces via on/off switches

//Various functions in the Code
int Goti_Identifier(char*);
int Goti_Identifier_2(char*); // Checks if the input is from  Blue pieces or empty spaces
int colour(char*); // Decides the color of tiles of the board. Yellow for empty tiles, Red for red pieces and Light blue for blue pieces
int special_move(char*); // Checks if the piece being moved is a bomb or the Flag. If so move is blocked as Bomb and Flag are immovable.
void board(); // Prints the board on the screen
void scout_move(int*, int*, int*, int*, int);// Here the unique movement of Scout takes place
int alphatonum(char);
char numtoalpha(int);

int main()
{
	int loop = 1, swtch;
	while (loop == 1) // Keeps the user at the interface untill they 'Start the Game" and loop is ended via break
	{
		puts("\n\n\n\n\n\n");
		printf("\t\t\t \x1b[1m WELCOME TO ONLINE STRATEGO \x1b[0m");
		puts("\n\n\n\x1b[36mTo read the rules Press 1 ");
		puts("\n\n\nTo start New Game Press 2 ");
		puts("\n\n\nTo check the details of the pieces Press 3 \x1b[0m");
		scanf("%d", &swtch);
		system("cls");
		switch (swtch)
		{
		case 1: // RULES OF THE GAME
			puts("\n\n\n\x1b[33mRules of the game\n");
			puts("\x1b[36m1. It is a 2 player game. RED versus BLUE\n");
			puts("2. Red goes first like white in chess\n");
			puts("3. Both players have 40 pieces each\n");
			puts("4. Game is won by capturing the opponent's flag\n");
			puts("5. Flag can be captured by any piece on the board\n");
			puts("6. 8 pieces of the board are empty and can not be occupied by any piece on the board\n These are the the 3rd, 4th, 7th and 8th tiles of the 5th and 6th row\n");
			puts("7. Each player attacks turn by turn\n");
			puts("8. When a piece attacks another piece following things may happen\n");
			puts("\t I) The attacking piece has a greater power level than the defending piece and the attacking piece takes the place of the defending piece\n and the defending piece is removed from the board\n");
			puts("\t II) The attacking piece has a lower power level than the defending piece and the defending piece retains it place. The attacker is removed from the board\n");
			puts("\t III) The attacking and defending piece have equal power levels. In this case both pieces are removed from the board\n");
			puts("9. Opponent pieces are hidden at the start and only revealed when they beat the other player's piece\x1b[0m\n");
			puts("Press any key to continue....");
			getch();
			system("cls");
			break;
		case 2: // BREAKS THE LOOP AND STARTS THE GAME
			loop = 0;
			system("cls");
			break;
		case 3: // INFORMAION ABOUT THE STRATEGO PIECES
			puts("\n\n\n\x1b[33mDetail about the Pieces\x1b[0m\n");
			puts("\x1b[36m1. Bomb is the Strongest piece on the board and Flag is the weakest. Both are immovable\n");
			puts("2. Each player has 1 Flag and has a power level of zero\n");
			puts("3. Each player has 1 Spy and has a power level of 1\n");
			puts("4. Each player has 8 Scouts and Scout has a power level of 2\n");
			puts("5. Each player has 5 Miner and has a power level of 3\n");
			puts("6. Each player has 4 Sergeants and has a power level of 4\n");
			puts("7. Each player has 4 Lieutenants and has a power level of 5\n");
			puts("8. Each player has 4 Captains and has a power level of 6\n");
			puts("9. Each player has 3 Major and has a power level of 7\n");
			puts("10. Each player has 2 Colonels and has a power level of 8\n");
			puts("11. Each player has 1 General and has a power level of 9\n");
			puts("12. Each player has 1 Marshals and has a power level of 10\n");
			puts("13. Each player has 6 Bombs and has a power level of 11\n");
			puts("Unique situations\n");
			puts("\t I)Spy is defeated by every piece that attacks it but it can beat the Marshal if Spy attacks first\n");
			puts("\t II)Bomb can defeat any piece except the Miner that defuses the bomb\x1b[0m");
			puts("\nPress any key to continue....\n");
			getch();
			system("cls");
			break;

		}
	}

	srand((size_t)time(NULL)); // Seed
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			visibility[i][j] = 0; //Initialize the entire board at 0 so no opponent Piece is visible
		}
	}

	//Placement of all RED PIECES randomly
	int bomber = 1, flag = 0, spy = 0, scout = 1, miner = 01, sgt = 01, ltd = 01, marsh = 01, cpt = 01, maj = 01, gen = 01, col = 01; //Counter for all pieces
	int power, r, s;
	r = 0;
	s = rand() % 10;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (i == r && j == s)
				power = 0;
			else
				power = (rand() % 11 + 1); // Randomly generates the power levels of all the pieces to be placed at the board
			if (power == 0)
			{
				pwr[i][j] = 0;
				game[i][j] = "Rflg";
				flag++;
			}
			if (power == 11 && bomber == 7)//If a piece is generated more times than the total number of pieces as pew the game it makes the loop run again for that time
				j--;
			if (power == 10 && marsh == 2)
				j--;
			if (power == 9 && gen == 2)
				j--;
			if (power == 8 && col == 3)
				j--;
			if (power == 7 && maj == 4)
				j--;
			if (power == 6 && cpt == 5)
				j--;
			if (power == 5 && ltd == 5)
				j--;
			if (power == 4 && sgt == 5)
				j--;
			if (power == 3 && miner == 6)
				j--;
			if (power == 2 && scout == 9)
				j--;
			if (power == 1 && spy == 1)
				j--;
			if (power == 11 && bomber < 7)//Place only the specified number of pieces according to the rules of the game
			{
				pwr[i][j] = power;
				game[i][j] = "Rbmb";
				bomber++;
			}
			if (power == 1 && spy < 1)
			{
				pwr[i][j] = power;
				spy++;
				game[i][j] = "Rspy";
			}
			if (power == 2 && scout < 9)
			{
				pwr[i][j] = power;
				scout++;
				game[i][j] = "Rsct";
			}
			if (power == 3 && miner < 6)
			{
				pwr[i][j] = power;
				miner++;
				game[i][j] = "Rmin";
			}
			if (power == 4 && sgt < 5)
			{
				pwr[i][j] = power;
				sgt++;
				game[i][j] = "Rsgt";
			}
			if (power == 5 && ltd < 5)
			{
				pwr[i][j] = power;
				ltd++;
				game[i][j] = "Rltd";
			}
			if (power == 6 && cpt < 5)
			{
				pwr[i][j] = power;
				cpt++;
				game[i][j] = "Rcpt";
			}
			if (power == 7 && maj < 4)
			{
				pwr[i][j] = power;
				maj++;
				game[i][j] = "Rmjr";
			}
			if (power == 8 && col < 3)
			{
				pwr[i][j] = power;
				col++;
				game[i][j] = "Rcol";
			}
			if (power == 9 && gen < 2)
			{
				pwr[i][j] = power;
				gen++;
				game[i][j] = "Rgen";
			}
			if (power == 10 && marsh < 2)
			{
				pwr[i][j] = power;
				game[i][j] = "Rmar";
				marsh++;
			}
		}
	}

	for (int i = 4; i < 6; i++) // Initialize the midddle rows that are empty
	{
		for (int j = 0; j < 10; j++)
		{
			game[i][j] = ""; //Empty space on the board
			pwr[i][j] = -1;
		}
	}

	game[4][2] = "----", game[4][3] = "----", game[4][6] = "----", game[4][7] = "----"; //These are the places on the board that are inaccessible
	game[5][2] = "----", game[5][3] = "----", game[5][6] = "----", game[5][7] = "----";
	pwr[4][2] = 12, pwr[4][3] = 12, pwr[4][6] = 12, pwr[4][7] = 12; // These have max power and no piece can occupy this place
	pwr[5][2] = 12, pwr[5][3] = 12, pwr[5][6] = 12, pwr[5][7] = 12;

	//Placement of all BLUE PIECES randomly
	int p, q, pcor, qcor;
	while (1) {
		puts("\n\n\n\x1b[1mPlease place your flag in a secure location\x1b[0m\n");
		printf("\x1b[33mPlease enter row number for your Flag(between 7 to 10): ");
		scanf("%d", &pcor);
		printf("Please enter column number for your Flag(between 1 to 10): ");
		scanf("%d", &qcor);
		if (pcor < 7 || pcor > 10 || qcor < 1 || qcor > 10) {
			puts("\n\x1b[31mInvalid placement of flag.\nPlease try again");
			puts("Press any key to continue....\x1b[0m");
			getch();
			system("cls");
		}
		else
			break;
	}
	p = pcor - 1, q = qcor - 1;
	bomber = 1, flag = 0, spy = 0, scout = 1, miner = 01, sgt = 01, ltd = 01, marsh = 01, cpt = 01, maj = 01, gen = 01, col = 01; //Counter for all pieces
	for (int i = 6; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (i == p && j == q)
				power = 0;
			else
				power = (rand() % 11 + 1); // Randomly generates the power levels of all the pieces to be placed at the board
			if (power == 0)
			{
				pwr[i][j] = 0;
				game[i][j] = "Bflg";
				flag++;
			}
			if (power == 11 && bomber == 7) //If a piece is generated more times than the total number of pieces as pew the game it makes the loop run again for that time
				j--;
			if (power == 10 && marsh == 2)
				j--;
			if (power == 9 && gen == 2)
				j--;
			if (power == 8 && col == 3)
				j--;
			if (power == 7 && maj == 4)
				j--;
			if (power == 6 && cpt == 5)
				j--;
			if (power == 5 && ltd == 5)
				j--;
			if (power == 4 && sgt == 5)
				j--;
			if (power == 3 && miner == 6)
				j--;
			if (power == 2 && scout == 9)
				j--;
			if (power == 1 && spy == 1)
				j--;
			if (power == 11 && bomber < 7)
			{
				pwr[i][j] = power;
				game[i][j] = "Bbmb";
				bomber++;
			}
			if (power == 1 && spy < 1)
			{
				pwr[i][j] = power;
				spy++;
				game[i][j] = "Bspy";
			}
			if (power == 2 && scout < 9)
			{
				pwr[i][j] = power;
				scout++;
				game[i][j] = "Bsct";
			}
			if (power == 3 && miner < 6)
			{
				pwr[i][j] = power;
				miner++;
				game[i][j] = "Bmin";
			}
			if (power == 4 && sgt < 5)
			{
				pwr[i][j] = power;
				sgt++;
				game[i][j] = "Bsgt";
			}
			if (power == 5 && ltd < 5)
			{
				pwr[i][j] = power;
				ltd++;
				game[i][j] = "Bltd";
			}
			if (power == 6 && cpt < 5)
			{
				pwr[i][j] = power;
				cpt++;
				game[i][j] = "Bcpt";
			}
			if (power == 7 && maj < 4)
			{
				pwr[i][j] = power;
				maj++;
				game[i][j] = "Bmjr";
			}
			if (power == 8 && col < 3)
			{
				pwr[i][j] = power;
				col++;
				game[i][j] = "Bcol";
			}
			if (power == 9 && gen < 2)
			{
				pwr[i][j] = power;
				gen++;
				game[i][j] = "Bgen";
			}
			if (power == 10 && marsh < 2)
			{
				pwr[i][j] = power;
				game[i][j] = "Bmar";
				marsh++;
			}
		}
	}
	puts("\x1b[0m");
	//Following contains all the game and runs till the game is not ended
	while (pwr[p][q] == 0 && pwr[r][s] == 0) //Loop is exited once the place of BLUE OR RED Flag is taken by any other piece
	{
		puts("");
		puts("");
		//Generation of the board
		board();

		puts("");
		puts("\n\x1b[1mPlease wait for your opponent's turn\x1b[0m");
		puts("\x1b[36mPress any key to continue....\x1b[0m");
		getch();

		size_t x, y, a, b, random, limit = 1, loop;
		srand((size_t)time(0));
		//OPPONENT/COMPUTER's turn (Red goes first)
		random = rand() % 7;
		while (limit == 1) //Loop containg opponent turn
		{
			loop = 1;
			while (loop == 1) // Loop that checks if the opponent movemnet is legal
			{
				x = rand() % 10;
				y = rand() % 10;
				a = x, b = y;
				if (random == 0) // Upward movement
					a = x - 1;
				else if (random == 1) // Rightward movement
					b = y + 1;
				else if (random == 2) // Leftward movement
					b = y - 1;
				else // Downward movement takes place more often
					a = x + 1; // Downward movement
				if (a > 9 || a < 0 || b > 9 || b < 0) // Checks if the pieces haved moved outside of the board
				{
					random = rand() % 7; //Adds direction again
					continue;// Restarts the loop if the moving computer piece has moved out of the loop
				}
				char* opp[10] = { "Rspy", "Rsct","Rmjr","Rcol","Rmin", "Rsgt", "Rltd" , "Rcpt" , "Rgen", "Rmar" }; // All moveable Red pieces
				for (size_t i = 0; i < 10; i++)
				{
					flag = strcmp(game[x][y], opp[i]); //Checks if the piece selected is a MOVEABLE RED PIECE.(if not the Loop is restarted at end)
					if (flag == 0)
					{
						size_t flag1 = Goti_Identifier_2(game[a][b]); //Checks if the movement of Red is a legal one (i.e. it moves to an empty place or Attacks a blue piece)
						if (flag1 == 0) // If move is legal loop is exited
							loop = 0;
					}
				}
			}

			char move2[10] = "Rsct";
			int sct_flag, sct_flag1, sct_flag2 = 0;
			sct_flag = strcmp(game[x][y], move2);
			if (sct_flag == 0)
			{
				if (random == 0) {
					for (int i = 1; i < 9; i++)
						if (game[x - i][y] == "")
							sct_flag2 = i + 1;
				}
				else if (random == 1) {
					for (int i = 1; i < 9; i++)
						if (game[x][y + i] == "")
							sct_flag2 = i + 1;
				}
				else if (random == 2) {
					for (int i = 1; i < 9; i++)
						if (game[x][y - i] == "")
							sct_flag2 = i + 1;
				}
				else {
					for (int i = 1; i < 9; i++)
						if (game[x + i][y] == "")
							sct_flag2 = i + 1;
				}

			}

			if (sct_flag == 0)
			{
				sct_flag1 = Goti_Identifier(game[a][b]);
				if (sct_flag1 != 1)
					sct_flag2--;

				if (random == 0)
					a = x - sct_flag2;
				else if (random == 1)
					b = y + sct_flag2;
				else if (random == 2)
					b = y - sct_flag2;
				else
					a = x + ++sct_flag2;
				if (a > 9 || a < 0 || b > 9 || b < 0) // Checks if the pieces haved moved outside of the board
				{
					random = rand() % 7; //Adds direction again
					continue;// Restarts the loop if the moving computer piece has moved out of the loop
				}
			}

			//Unique situations
			if (game[x][y] == "Rspy" && game[a][b] == "Bmar") //An attacking SPY can defeat the Marshal
				pwr[a][b] = 0;
			if (game[x][y] == "Rmin" && game[a][b] == "Bbmb") // Miner can defuse the bomb
				pwr[a][b] = 0;

			system("CLS"); // Clean screen for Players turn

			//Movement takes place here 
			puts("\n\x1b[1mThe computer has done the following move\x1b[0m");
			if (visibility[x][y] == 1)
				printf("\t\x1b[33mPiece |%4s| moved from co-ordinates (%d, %c) to Piece |%4s| located at co-ordinates (%d, %c)\n\x1b[0m", game[x][y], x + 1, numtoalpha(y), game[a][b], a + 1, numtoalpha(b)); //What moved and where
			else
				printf("\t\x1b[33mPiece |****| moved from co-ordinates (%d, %c) to Piece |%4s| located at co-ordinates (%d, %c)\n\x1b[0m ", x + 1, numtoalpha(y), game[a][b], a + 1, numtoalpha(b));

			if (pwr[x][y] < pwr[a][b]) // If red attacks and loses
			{
				printf("\t\x1b[33mPiece |%4s| has been removed from the board\x1b[0m", game[x][y]);
				pwr[x][y] = -1; //Empty space is generated where attacking red pieces was prebiously
				game[x][y] = "";
				visibility[x][y] = 0; //The visibility of the Tile where attacking red is SWITCHED OFF(if it was visible)
				limit = 0; // Break loop
			}
			else if (pwr[x][y] == pwr[a][b]) // If red attacks its blue equivalent
			{
				printf("\t\x1b[33mPieces |%4s| and |%4s| have been removed from the board\x1b[0m", game[x][y], game[a][b]);
				pwr[a][b] = -1; //Both pieces are removed from the board
				pwr[x][y] = -1;
				game[a][b] = "";
				game[x][y] = "";
				visibility[x][y] = 0; //The visibility of the Tile where attacking red is SWITCHED OFF(if it was visible)
				limit = 0; // Break Loop
			}
			else // If red attacks and wins
			{
				if (game[a][b] != "")
					printf("\t\x1b[33mPiece |%4s| has been removed from the board\x1b[0m", game[a][b]);
				int visible = Goti_Identifier(game[a][b]); //Checks if Red is beating a blue piece
				if (visible == 1 || visibility[x][y] == 1) // If the Red is beating a blue piece or was already visible
					visibility[a][b] = 1; // Visibilty of the NEW POSITION OF RED PIECE is switched on
				game[a][b] = game[x][y]; // Red takes the place of the beat blue piiece
				pwr[a][b] = pwr[x][y]; // Power of red is inserted at new position
				game[x][y] = ""; // An empty space is generated at the place of the previous position of red
				pwr[x][y] = -1; // The power of anempty space is put at the previous position of red
				visibility[x][y] = 0; // Visiblity of previous position is switched off
				limit = 0;// Break Loop
			}
			/*board(); //Open this and close limit = 0 to in lines 491, 467 and 477 check (limit=0) unlimited moves of AI till it wins or runs out of valid moves
			if (pwr[p][q] != 0)
				break; */
		} //End of loop containing opponent/ computer turn

		puts("\n\n");

		limit = 1;
		while (pwr[p][q] == 0 && limit == 1)//Player's turn.It is only initiated if the player's Flag has not been captured already 
		{
			// Generation of board
			board();

			puts("");
			puts("");
			int xcor = 0;
			char ycor;
			puts("\x1b[1mPlease Select the Piece to be moved\x1b[0m"); // Player is asked to movethe piece they wantto move
			printf("\x1b[36mEnter row number(1 to 10): ");
			scanf("%d", &xcor);
			printf("Enter column number(a to j): ");
			scanf(" %c", &ycor);
			puts("\x1b[0m");
			x = xcor - 1, y = alphatonum(ycor); // Makes the numbering of rows and columns more user-friendly
			if (x < 0 || x>10 || y < 0 || y >10)
			{
				puts("\x1b[31mPOINT OUTSIDE THE ARRAY ENTERED"); // The user selected invalid point in array
				puts("Press any key to continue\x1b[0m");
				getch();
				system("CLS");
				puts("\n\n\n");
				continue; // Loop is restarted
			}
			size_t goti_check = Goti_Identifier(game[x][y]); // Checks uf user has Selected a valid Piece i.e a Blue one
			if (goti_check != 1)
			{
				puts("\x1b[31mINVALID PIECE ENTERED!"); // The user selected invalid piece
				puts("Press any key to continue\x1b[0m");
				getch();
				system("CLS");
				puts("\n\n\n");
				continue; // Loop is restarted
			}
			a = x, b = y;
			puts("\x1b[1mSelect direction to move your Selected Piece\x1b[0m ");
			puts("\x1b[36mInput 1 for upwards		Input 3 for rightwards");
			puts("Input 2 for downwards		Input 4 for leftwards");
			int direction;
			scanf("%d", &direction); // Takes direction from the user in which they want to move
			if (direction == 1)
				a = x - 1;
			else if (direction == 2)
				a = x + 1;
			else if (direction == 3)
				b = y + 1;
			else if (direction == 4)
				b = y - 1;
			else
				printf("Wrong number entered");
			puts("\x1b[0m");
			scout_move(&x, &y, &a, &b, direction);
			if (a > 9 || a < 0 || b > 9 || b < 0)// Checks whether any piece is  being moved out of the loop 
			{
				puts("\x1b[31mINVALID POSITION MOVED!");
				puts("Press any key to continue\x1b[0m");
				puts("\n\n\n");
				getch();
				system("CLS");
				continue;
			}

			int special_check = special_move(game[x][y]);
			int friendly_fire_check = Goti_Identifier(game[a][b]);
			if (game[x][y] == "Bspy" && game[a][b] == "Rmar")
				pwr[a][b] = 0;
			if (game[x][y] == "Bmin" && game[a][b] == "Rbmb")
				pwr[a][b] = 0;

			if (friendly_fire_check == 1 || special_check == 1) {
				if (friendly_fire_check == 1)
					puts("\x1b[31mINVALID PIECE NAME ENTERED!");
				puts("Press any key to continue\x1b[0m");
				getch();
				system("CLS");
				continue;
			}
			if (pwr[a][b] == 12 || pwr[x][y] == 12) //Checks whether user moved to a blocked spot
			{
				puts("\x1b[31mINVALID POSITION!");
				puts("Press any key to continue\x1b[0m");
				getch();
				system("CLS");
				puts("\n\n\n");
				continue; // If so the move is invalid and loop is restarted
			}
			printf("\t\x1b[33mYou have moved Piece |%4s| moved from co-ordinates (%d, %c) to Piece |%4s| located at co-ordinates (%d, %c)\n", game[x][y], x + 1, numtoalpha(y), game[a][b], a + 1, numtoalpha(b)); //What moved and where

			puts("Press any key to continue.....(Press 'b' to go back)\x1b[0m");
			if (getch() == 'b')
			{
				system("cls");
				puts("\n\n\n");
				continue;
			}

			puts("");
			if (pwr[x][y] < pwr[a][b]) // Blue attacker loses to red defender
			{
				printf("\x1b[1mPiece |%4s| has been removed from the board\x1b[0m", game[x][y]);
				pwr[x][y] = -1; // power at the previous poistion is put that of an empty space
				game[x][y] = ""; // The postion of blue is vacated
				visibility[a][b] = 1; // The defender RED's visiblity is switched on
				limit = 0; // Break loop
			}
			else if (pwr[x][y] == pwr[a][b]) // BLue and Red tie and are both removed from the board
			{
				printf("\x1b[1mPieces |%4s| and |%4s| have been removed from the board\x1b[0m", game[x][y], game[a][b]);
				pwr[a][b] = -1; //Empty power and spots generated at the positions of both red and blue pieces
				pwr[x][y] = -1;
				game[a][b] = "";
				game[x][y] = "";
				limit = 0; // Break Loop
			}
			else // If attacking blue wins
			{
				if (game[a][b] != "")
					printf("\x1b[1mPieces |%4s| has been removed from the board\x1b[0m", game[a][b]);
				visibility[a][b] = 0; // If red was visible it's visibility is switched off
				game[a][b] = game[x][y]; //Blue takes place of the red piece it BEAT
				game[x][y] = ""; // Empty spot at the last location of attacking Blue
				pwr[a][b] = pwr[x][y]; // Power of blue is placed at its new position
				pwr[x][y] = -1; // Power of empty spot is put at the previos location of attacker
				limit = 0; // Break Loop
			}
		}
	}
	puts("\n\x1b[1mGAME OVER!!!!!\x1b[0m"); // The loop is exited once either of the Flags is captured
	if (pwr[p][q] == 0) // If red flag is captured
		puts("\x1b[34m!!!!!!!!!!BLUE WINS!!!!!!!!!!\x1b[0m"); // BLue wins the game
	else
		puts("\x1b[31m!!!!!!!!!!RED WINS!!!!!!!!!!\x1b[0m"); // Otherwise red wins the game
}

void scout_move(int* x, int* y, int* a, int* b, int dir)
{
	char* move1 = "Bsct"; // Here the unique movement of Scout takes place
	char* empt = "";
	int space, flag = strcmp(game[*x][*y], move1), flag1 = 1;
	if (flag == 0)
	{
		puts("\x1b[1mEnter number of spaces to be moved\x1b[0m");
		scanf("%d", &space); // Asks user how many places they want to move the scout
		if (dir == 1)
			for (int i = 1; i < space; i++)
			{
				flag1 = strcmp(game[*x - i][*y], empt); // Checks if all the tiles between the Scout and movement input by the user are epmty
				if (flag1 == 0)
				{
					if (i == space - 1) // If all spaces are empty the move takes plave
						*a = *x - space;
				}
				else { // If any tiles is non empty then move is invalid and loop is restarted
					puts("\x1b[31mInvalid movement");
					puts("Press any key to continue\x1b[0m");
					*a = *x;
					getch();
					break;
				}
			}
		else if (dir == 2)
			for (int i = 1; i < space; i++)
			{
				flag1 = strcmp(game[*x + i][*y], empt);
				if (flag1 == 0)
				{
					if (i == space - 1)
						*a = *x + space;
				}
				else {
					puts("\x1b[31mInvalid movement");
					puts("Press any key to continue\x1b[0m");
					*a = *x;
					getch();
					break;
				}
			}
		else if (dir == 3)
			for (int i = 1; i < space; i++)
			{
				flag1 = strcmp(game[*x][*y + i], empt);
				if (flag == 0)
				{
					if (i == space - 1)
						*b = *y + space;
				}
				else {
					puts("\x1b[31mInvalid movement");
					puts("Press any key to continue\x1b[0m");
					*b = *y;
					getch();
					break;
				}
			}
		else if (dir == 4)
			for (int i = 1; i < space; i++)
			{
				flag1 = strcmp(game[*x][*y - i], empt);
				if (flag1 == 0)
				{
					if (i == space - 1)
						*b = *y - space;
				}
				else {
					puts("\x1b[31mInvalid movement");
					puts("Press any key to continue\x1b[0m");
					*b = *y;
					getch();
					break;
				}
			}
	}
}

int Goti_Identifier(char* goti) //Checks if the input is from the below array i.e. Blue pieces
{
	size_t check = 0; // Initialize a check-variable to 0 which gives boolean yes 1 if situation holds true 
	char* arr[12] = { "Bflg", "Bbmb", "Bspy", "Bsct","Bmjr","Bcol","Bmin", "Bsgt", "Bltd" , "Bcpt" , "Bgen", "Bmar" };
	for (int j = 0; j < 12; j++)
	{
		size_t flag = 1;
		flag = strcmp(goti, arr[j]);
		if (flag == 0)
		{
			check = 1;
			break;
		}
	}
	return check;
}

int Goti_Identifier_2(char* goti) //Checks if the input is from the below array i.e. Blue pieces or empty spaces
{
	size_t check = 1; // Initialize a check-variable to 0 which gives boolean yes 1 if situation holds true
	char* opp[13] = { "", "Bflg", "Bbmb", "Bspy", "Bsct","Bmjr","Bcol","Bmin", "Bsgt", "Bltd" , "Bcpt" , "Bgen", "Bmar" };
	for (size_t j = 0; j < 13; j++)
	{
		size_t flag = 1;
		flag = strcmp(goti, opp[j]);
		if (flag == 0)
		{
			check = 0;
			break;
		}
	}
	return check;
}

int colour(char* num) // Decides the color of tiles of the board. Yellow for empty tiles, Red for red pieces and Light blue for blue pieces
{
	int check = 1;
	char* arr1[2] = { "" , "----" }; // Empty or Blocked tile of the board
	char* arr2[12] = { "Bflg", "Bbmb", "Bspy", "Bsct","Bmjr","Bcol","Bmin", "Bsgt", "Bltd" , "Bcpt" , "Bgen", "Bmar" }; //Blue pieces
	char* arr3[12] = { "Rflg", "Rbmb", "Rspy", "Rsct","Rmjr","Rcol","Rmin", "Rsgt", "Rltd" , "Rcpt" , "Rgen", "Rmar" }; //Red pieces
	int flag = 1;
	for (int j = 0; j < 2; j++)
	{
		flag = strcmp(num, arr1[j]);
		if (flag == 0)
			check = 0;
	}
	for (int j = 0; j < 12; j++)
	{
		flag = strcmp(num, arr2[j]);
		if (flag == 0)
			check = 1;
	}
	for (int j = 0; j < 12; j++)
	{
		flag = strcmp(num, arr3[j]);
		if (flag == 0)
			check = 2;
	}
	return check;

}

int special_move(char* num) // Checks if the piece being moved is a bomb or the Flag. If so move is blocked as Bomb and Flag are immovable.
{
	int check = 0, flag = 1;
	char* move = "Bbmb";
	char* move1 = "Bflg";
	flag = strcmp(num, move);
	if (flag == 0)
	{
		puts("BOMB CAN NOT BE MOVED!!!!");
		check = 1;
	}
	flag = strcmp(num, move1);
	if (flag == 0)
	{
		puts("FLAG CAN NOT BE MOVED!!!!");
		check = 1;
	}
	return check;
}

void board() // Prints the board on the screen
{
	for (size_t i = 0; i <= 9; i++)
		printf(" \t%4c", numtoalpha(i)); // Shows the numbering of columns

	puts("");
	for (int i = 0; i < 10; i++)
	{
		printf("%8d", i + 1);// Shows the numbering of Rows
		for (int j = 0; j < 10; j++)
		{
			int clr_checker = colour(game[i][j]);
			if (clr_checker == 1) // Prints al blue pieces in Light Blue colour
				printf("\x1b[34m\x1b[1m|%s|\x1b[0m \t", game[i][j]);
			else if (clr_checker == 2 && visibility[i][j] == 1) // Checks if pieces is RED and if it is HIDDEN OR NOT
				printf("\x1b[31m|%s|\x1b[0m \t", game[i][j]); // Prints all the RED pieces in red clr if the are NOT HIDDEn
			else if (clr_checker == 0)
				printf("\x1b[33m|%4s|\x1b[0m\t", game[i][j]); // Prints empty and blocked tiles as yellow
			else
				printf("\x1b[31m|****|\x1b[0m\t");
		}
		printf("%d\n", i + 1); // Shows the numbering of Rows
	}
	for (size_t i = 0; i <= 9; i++)
		printf(" \t%4c", numtoalpha(i)); // Shows the numbering of columns
}

int alphatonum(char alpha)
{
	int num;
	switch (alpha)
	{
	case 'a':
		num = 0; break;
	case 'b':
		num = 1; break;
	case 'c':
		num = 2; break;
	case 'd':
		num = 3; break;
	case 'e':
		num = 4; break;
	case 'f':
		num = 5; break;
	case 'g':
		num = 6; break;
	case 'h':
		num = 7; break;
	case 'i':
		num = 8; break;
	case 'j':
		num = 9; break;
	default:
		num = 10;

	}
	return num;
}

char numtoalpha(int num)
{
	char alpha;
	switch (num)
	{
	case 0:
		alpha = 'a'; break;
	case 1:
		alpha = 'b'; break;
	case 2:
		alpha = 'c'; break;
	case 3:
		alpha = 'd'; break;
	case 4:
		alpha = 'e'; break;
	case 5:
		alpha = 'f'; break;
	case 6:
		alpha = 'g'; break;
	case 7:
		alpha = 'h'; break;
	case 8:
		alpha = 'i'; break;
	case 9:
		alpha = 'j'; break;
	default:
		alpha = 'R';
	}
	return alpha;
}