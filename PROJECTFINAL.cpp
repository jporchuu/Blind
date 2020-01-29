#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include "console.h"
#include <time.h>

void gameTitle();
void gameIntro();

void displayBorder();
void displayDirections(int x, int y);

float soundIntensity(float distanceFinal, float initialDistance, float dBFinal, float dBInitial);
void plotCircle(int xcoord, int ycoord, int distance, int angle, int color, int xObstacle[], int yObstacle[], int goalx, int goaly);
void removeCircle(int xcoord, int ycoord, int distance, int angle, int color);
int navigationConditions(int x,int y, int xObstacle[], int yObstacle[]);

void quittingMessage();
void winningMessage(int moveCounter, int soundCounter);
void losingMessage(int moveCounter);

int main(){
	
	system("CLS");
	
	int n=79,x=5,y=15,i,l,rad=0,angle, xObstacle[9], yObstacle[9], goalx, goaly, win, moveCounter=0, soundCounter=0;
	
	float dBInitial, dBFinal = 20, initialDistance = 0.1, distanceFinal=0;
	
	char ch = n, input;

	setWindowSize(100,40);
	
	srand(time(NULL));
	
	// Displays the game's Title Screen.
	gameTitle();
	
	// Displays the game's intro before playing the game.
	gameIntro();
	
	// Randomizes, as well as places the location of the various obstacles.
	for(l=0;l<10;l++){
		
		xObstacle[l] = rand() % (74 + 1 - 6) + 6;
		yObstacle[l] = rand() % (29 + 1 - 6) + 6;
	
	}
	
	// Randomizes, as well as places the location of the goal area.
	goalx = rand() % (74 + 1 - 50) + 50;
	goaly = rand() % (29 + 1 - 2) + 2;
	
	
	do{
		system("CLS");
		
		// Displays the limit of the room.
		displayBorder();
		
		// Displays the obstacles.
		for(l=0;l<10;l++){
			putxy(xObstacle[l],yObstacle[l],TBLACK,"\u0004"); // Also, it displays as black so that it gives the obstacles a "hidden" look.
		}
		
		// Displays the goal area.
		putxy(goalx,goaly,TBLACK,"G");
		
		// Displaying of your Character
		gotoxy(x,y);
		printf("%c", ch);
		
		// Display the Coordinates and Game Directions
		displayDirections(x,y);
		
		input = getch();
		
		// Arrow Key Navigation and Conditions
		if(input==72){
			/* if the player inputs the up arrow key, it is represented as the game character moving to the positive y-position, but that is a lesser y-value.
			it keeps decrementing if the player wishes to do so. */
		 	--y;
		 	  
		 	// Calls the navigationConditions() function for the checking of these "if statements"
			// if "0" will be the specific return statement for that function, then that means the player loses the game.  
			if( navigationConditions(x,y,xObstacle,yObstacle) == 0 ) { win = 0; break; }
			
			/* if "2" will be the specific return statement for that function,
			then that means the player's path is being "blocked" and returns the y-value back to its original state before decrementing, making it look like the player did not move at all. */
			if( navigationConditions(x,y,xObstacle,yObstacle) == 2 ) ++y;
		}
		
		else if(input==80){
		 	/* if the player inputs the down arrow key, it is represented as the game character moving to the negative y-position, but that is a greater y-value.
		 	it keeps incrementing if the player wishes to do so. */
		 	++y;
		 	  
		 	// Calls the navigationConditions() function for the checking of these "if statements"
			// if "0" will be the specific return statement for that function, then that means the player loses the game.  		 	  
			if(navigationConditions(x,y,xObstacle,yObstacle) == 0) { win = 0; break; }

			/* if "2" will be the specific return statement for that function,
			then that means the player's path is being "blocked" and returns the y-value back to its original state before incrementing, making it look like the player did not move at all. */
			if(navigationConditions(x,y,xObstacle,yObstacle) == 2) --y;
		}
		
		else if(input==77){
			/* if the player inputs the right arrow key, it is represented as the game character moving to the positive/greater x-position
		 	it keeps incrementing if the player wishes to do so.*/
		 	++x;

		 	// Calls the navigationConditions() function for the checking of these "if statements"
			// if "0" will be the specific return statement for that function, then that means the player loses the game.  		 	  
			if(navigationConditions(x,y,xObstacle,yObstacle) == 0) { win = 0; break; }
			
			/* if "2" will be the specific return statement for that function,
			then that means the player's path is being "blocked" and returns the x-value back to its original state before incrementing, making it look like the player did not move at all. */
			if(navigationConditions(x,y,xObstacle,yObstacle) == 2) --x;
		}
		
		else if(input==75){
			/* if the player inputs the left arrow key, it is represented as the game character moving to the negative x-position
			it keeps decrementing if the player wishes to do so. */
			--x;
			
		 	// Calls the navigationConditions() function for the checking of these "if statements"
			// if "0" will be the specific return statement for that function, then that means the player loses the game.  		 	  
			if(navigationConditions(x,y,xObstacle,yObstacle) == 0) { win = 0; break; }
			
			/* if "2" will be the specific return statement for that function,
			then that means the player's path is being "blocked" and returns the x-value back to its original state before decrementing, making it look like the player did not move at all. */
			if(navigationConditions(x,y,xObstacle,yObstacle) == 2) ++x;
		}
		
		// Displays the various sound waves if the player will press the SPACEBAR key.
		if(input==32){
			// First for-loop to constantly displays the next "waves" until it reaches a sound threshold that is inaudible, represented my the "distanceFinal" variable.
			// The distanceFinal variable a.k.a. the final distance before reaching an inaudible sound.
		    for(rad=1;rad<distanceFinal;rad++){
		    	// The next for-loop is to give the sound wave its complete circular look.
		    	for(angle=0;angle<360;angle++){
		    		// This function creates each cell of the sound wave, and the various conditions where it "senses" the various entities of the room, which changes the behavior of each cell.  
		    		plotCircle(x,y,rad,angle,BWHITE,xObstacle,yObstacle,goalx,goaly);
		    	}
		    	// Each new wave has a delay to be displayed by 45 seconds
				// **not representative to any real-world example since sound travels WAY faster and would make the game almost impossible to play
		    	Sleep(45);
		    	// This for loop is to clear out the whole circle at the middle, so it will look like one cell thick each time the sound wave is projected
		    	for(angle=0;angle<360;angle++){
		    		removeCircle(x,y,rad,angle,TYELLOW);
		    	}
		   	}
		   	
		// these conditions are the counters to track how many sound waves you have projected. 
		// If the final distance of the sound is equal to zero (meaning that you did not make any sound) then the counter won't increment anything.
		if(distanceFinal==0) soundCounter = soundCounter;
		else soundCounter++;
		}
		
		// If the player decides to change sounds Intensity
		if(input==49){
			
			distanceFinal = soundIntensity(distanceFinal, initialDistance, dBFinal, dBInitial);
		
		}   
		
		
		
		// Winning Conditions
		if(x==goalx&&y==goaly) { win = 1; break; } // The game won't break the loop as long as you have not won yet.
		
		// Adds 1 for every movement the player makes. 
		moveCounter++;
		
	}while(input!='0'); // The game won't break the loop as long as you have not pressed the exit button yet.
	
	// Clears the screen whether you win, lose or quit the game.
	system("CLS");
	
	// Exit message
	if(input==48) {
		quittingMessage();
	}
	
	// Winning Message
	else if(win==1){
		winningMessage(moveCounter, soundCounter);
	}  
	
	// Losing Message
	else {
		losingMessage(moveCounter);
	}
	
}



void gameTitle(){
	
	gotoxy(15,3);
	printf("==========================================================");
	gotoxy(15,5);
	printf("oooooooooo.  ooooo        ooooo ooooo      ooo oooooooooo.   ");
	gotoxy(15,6);
	printf("`888'   `Y8b `888'        `888' `888b.     `8' `888'   `Y8b  ");
	gotoxy(15,7);
	printf(" 888     888  888          888   8 `88b.    8   888      888 ");
	gotoxy(15,8);
	printf(" 888oooo888'  888          888   8   `88b.  8   888      888 ");
	gotoxy(15,9);
	printf(" 888    `88b  888          888   8     `88b.8   888      888 ");
	gotoxy(15,10);
	printf(" 888    .88P  888       o  888   8       `888   888     d88' ");
	gotoxy(15,11);
	printf("o888bood8P'  o888ooooood8 o888o o8o        `8  o888bood8P'   ");
	gotoxy(15,13);
	printf(" ============ ");
	textcolor(BWHITE);
	printf("The Echolocation Navigation Game");
	textcolor(BBLACK|TWHITE);
	printf(" ============ ");
	
	gotoxy(28,16);
	printf(" A Game By Joseph Portugal ");
	
	gotoxy(28,18);
	printf(" Press any key to continue ");

	getch();
	
}

void gameIntro(){
	
	system("CLS");
	gotoxy(15,3);
	printf("Find your way out of the room.");
	gotoxy(15,5);
	printf("Avoid the obstacles.");
	putxy(15,7,TRED,"SURVIVE.");
	
	gotoxy(15,10);
	printf("Press any key to start.");
	
	getch();
}

void displayBorder(){
	
	int borderx, bordery;
	
	for(bordery=1;bordery<30;bordery++) putxy(1,bordery,BWHITE," ");
	for(borderx=1;borderx<75;borderx++) putxy(borderx,1,BWHITE," ");
	for(bordery=1;bordery<31;bordery++) putxy(75,bordery,BWHITE," ");
	for(borderx=1;borderx<75;borderx++) putxy(borderx,30,BWHITE," ");
	
}

void displayDirections(int x, int y){
	
		// Coordiante System
		gotoxy(80,5);
		printf("CURRENT COORDINATES:");
		gotoxy(80,6);
		printf("X:  %i  |  Y:  %i", x-2, y-2);
		
		// Basic Game Instructions are Displayed
		gotoxy(80,8);
		printf("GAME DIRECTIONS");
		gotoxy(80,10);
		printf("Use the ARROW KEYS to navigate around the map");
		gotoxy(80,12);
		printf("Press SPACEBAR to make a sound");
		gotoxy(80,14);
		printf("Press 1 to adjust the sound intensity (dB)");
		gotoxy(80,16);
		printf("Press 0 to exit the game");
		gotoxy(80,19);
		printf("WHEN USING ECHOLOCATION:");
		gotoxy(80,21);
		printf("AVOID:");
		putxy(87,21,TBLACK|BWHITE,"\u0004");
		gotoxy(80,23);
		printf("FIND: ");
		putxy(86 ,23,BYELLOW," ");
		gotoxy(80,24);
	
}

float soundIntensity(float distanceFinal, float initialDistance, float dBFinal, float dBInitial){
			
	while(1){
		
		// Sound intensity input
		gotoxy(1,32);
		printf("Input decibel(dB) intensity for the sound you will make (45 dB - 65 dB): ");
		scanf("%f", &dBInitial);
			
			
		// Condtitions that warn the player if the sound intensity that they wish to produce is either too quiet or too loud.	
		if(dBInitial<45){		
			gotoxy(1,34);
			printf("That sound is too quiet");			
		}
				
		else if(dBInitial>65){
			gotoxy(1,34);
			printf("That sound is too loud for the room");	
		}
		
		// If the sound is within the acceptable threshold, it will proceed to compute for the final audible sound distance.	
		else{
					
		/*
		The main STEM Application of this program, this comes from a real life equation
		given how intense the sound was at an initial distance, solve for the Final Sound Intensity given a target distance:
					
		IntensityFinal = IntensityInitial + 20 log(DistanceInitial/DistanceFinal)
					
		Now this equation that will be used for the program is an equated version of the original formula 
		to be able to find for the final distance and where the sound wave given here at this program visually will end, 
		again that represents the the final distance before reaching an inaudible sound. 
		At this case given a distance if the sound intensity falls of to 20 decibels (which is almost inaudible) 
		sound waves will not show anymore. Initial distance in this case is "0.1" representing 0.1 meters since that is a close area of sound to begin with.
		*/
					
			distanceFinal = initialDistance / pow(10,(dBFinal-dBInitial)/20);
					
			break;
		}
				
	}
			
	return distanceFinal;
}

void plotCircle(int xcoord, int ycoord, int distance, int angle, int color, int xObstacle[], int yObstacle[], int goalx, int goaly) {
	
   int x, y, toPrintx, toPrinty;
   
   // computation of the distance and the angle to how far the cell is from the center.
   x = distance * sin(angle*M_PI/180);
   y = distance * cos(angle*M_PI/180);
   
   // the acutal cell to be printed out.
   toPrintx = xcoord + x;
   toPrinty = ycoord + y;
   
   // These are where the various behavioral changes the sound wave has are present. 
	
	// This displays a diamond with a white background each time the obstacle is whitin the correct set of coordinateds to be detected by the sound wave.
	if (toPrintx == xObstacle[0] && toPrinty == yObstacle[0]) putxy(toPrintx,toPrinty,TBLACK|color,"\u0004");
	else if (toPrintx == xObstacle[1] && toPrinty == yObstacle[1]) putxy(toPrintx,toPrinty,TBLACK|color,"\u0004");
	else if (toPrintx == xObstacle[2] && toPrinty == yObstacle[2]) putxy(toPrintx,toPrinty,TBLACK|color,"\u0004");
	else if (toPrintx == xObstacle[3] && toPrinty == yObstacle[3]) putxy(toPrintx,toPrinty,TBLACK|color,"\u0004");
	else if (toPrintx == xObstacle[4] && toPrinty == yObstacle[4]) putxy(toPrintx,toPrinty,TBLACK|color,"\u0004");
	else if (toPrintx == xObstacle[5] && toPrinty == yObstacle[5]) putxy(toPrintx,toPrinty,TBLACK|color,"\u0004");
	else if (toPrintx == xObstacle[6] && toPrinty == yObstacle[6]) putxy(toPrintx,toPrinty,TBLACK|color,"\u0004");
	else if (toPrintx == xObstacle[7] && toPrinty == yObstacle[7]) putxy(toPrintx,toPrinty,TBLACK|color,"\u0004");
	else if (toPrintx == xObstacle[8] && toPrinty == yObstacle[8]) putxy(toPrintx,toPrinty,TBLACK|color,"\u0004");
	else if (toPrintx == xObstacle[9] && toPrinty == yObstacle[9]) putxy(toPrintx,toPrinty,TBLACK|color,"\u0004");
	
	// Displays the yellow "light within the end of the tunnel"-eque cell with a yellow background each time the goal area is within the correct set of coordinates to be detected by the sound wave.
	else if (toPrintx == goalx && toPrinty == goaly) putxy(toPrintx,toPrinty,BYELLOW," ");
	else putxy(toPrintx,toPrinty,color," ");
   
}

void removeCircle(int xcoord, int ycoord, int distance, int angle, int color){
	
	// Same functionality as the plotCircle function, but for "clearing" the whole (and not hollow) circle that the plotCircle function creates, in order to make it look hollow and wave-like.
   int x,y;
   
   x = distance * sin(angle*M_PI/180);
   y = distance * cos(angle*M_PI/180);
   
   putxy(xcoord+x,ycoord-y,color," ");
}

int navigationConditions(int x,int y, int xObstacle[], int yObstacle[]){
	
	int condition, l;
	
	/*
	condition = 0 -- The player has touched the coordinate of the obstacle and has lost the game.
	condition = 1 -- The player may continue on with the game.
	condition = 2 -- The player's path has been blocked.
	*/
	
	if(x == xObstacle[0] &&  y == yObstacle[0] )condition=0;
	else if(x == xObstacle[1] &&  y == yObstacle[1] )condition=0;
	else if(x == xObstacle[1] &&  y == yObstacle[1] )condition=0;
	else if(x == xObstacle[2] &&  y == yObstacle[2] )condition=0;
	else if(x == xObstacle[3] &&  y == yObstacle[3] )condition=0;
	else if(x == xObstacle[4] &&  y == yObstacle[4] )condition=0;
	else if(x == xObstacle[5] &&  y == yObstacle[5] )condition=0;
	else if(x == xObstacle[6] &&  y == yObstacle[6] )condition=0;
	else if(x == xObstacle[7] &&  y == yObstacle[7] )condition=0;
	else if(x == xObstacle[8] &&  y == yObstacle[8] )condition=0;
	else if(x == xObstacle[9] &&  y == yObstacle[9] )condition=0;
	else if (x <= 1 || y <= 1 || x >= 75 || y >= 30) condition=2;
	
	else condition = 1;
	
	return condition;
}
	

void quittingMessage(){
	
	gotoxy(5,5);
	printf("You have just quitted the game.\n\n");
	
	gotoxy(5,7);
	printf("Have a great day/night.");
	
	getch();
	
	gotoxy(0,10);
	
}

void winningMessage(int moveCounter, int soundCounter){
	int i;
	
		for(i=0;i<=116;i++) putxy(5+i,1,TWHITE,"-");
		
		gotoxy(15,3);
		printf("oooooo   oooo   .oooooo.   ooooo     ooo     oooooo   oooooo     oooo   .oooooo.   ooooo      ooo \n");
		gotoxy(15,4);
		printf(" `888.   .8'   d8P'  `Y8b  `888'     `8'      `888.    `888.     .8'   d8P'  `Y8b  `888b.     `8' \n");
		gotoxy(15,5);
		printf("  `888. .8'   888      888  888       8        `888.   .8888.   .8'   888      888  8 `88b.    8  \n");
		gotoxy(15,6);
		printf("   `888.8'    888      888  888       8         `888  .8'`888. .8'    888      888  8   `88b.  8  \n");
		gotoxy(15,7);
		printf("    `888'     888      888  888       8          `888.8'  `888.8'     888      888  8     `88b.8  \n");
		gotoxy(15,8);
		printf("     888      `88b    d88'  `88.    .8'           `888'    `888'      `88b    d88'  8       `888  \n");
		gotoxy(15,9);
		printf("    o888o      `Y8bood8P'     `YbodP'              `8'      `8'        `Y8bood8P'  o8o        `8  \n");
		
		for(i=0;i<=116;i++) putxy(5+i,11,TWHITE,"-");
		
		gotoxy(43,13);
		printf("Congratulations, you made it out alive.");
		
		// Displays the total amount of moves the player made once they have completed the game.
		gotoxy(50,15);
		printf("You finished in");
		textcolor(TGREEN);
		printf(" %i ", moveCounter);
		textcolor(TWHITE); 
		printf("moves\n");
		
		// Displays the total amount of sound waves the player made once they have completed the game.
		gotoxy(50,17);
		printf("and made a sound");
		textcolor(TBLUEGREEN);
		printf(" %i ", soundCounter);
		textcolor(TWHITE);
		printf("times.");
		
		getch();
		
}

void losingMessage(int moveCounter){
	int i;
	
		for(i=0;i<=114;i++) putxy(5+i,1,TWHITE,"-");
		
		textcolor(TRED);
		
		gotoxy(15,3);
		printf("oooooo   oooo   .oooooo.   ooooo     ooo 	oooooooooo.   ooooo oooooooooooo oooooooooo.   \n");
		gotoxy(15,4);
		printf(" `888.   .8'   d8P'  `Y8b  `888'     `8' 	`888'   `Y8b  `888' `888'     `8 `888'   `Y8b  \n");
		gotoxy(15,5);
		printf("  `888. .8'   888      888  888       8  	 888      888  888   888          888      888 \n");
		gotoxy(15,6);
		printf("   `888.8'    888      888  888       8  	 888      888  888   888oooo8     888      888 \n");
		gotoxy(15,7);
		printf("    `888'     888      888  888       8  	 888      888  888   888    '     888      888 \n");
		gotoxy(15,8);
		printf("     888      `88b    d88'  `88.    .8'  	 888     d88'  888   888       o  888     d88' \n");
		gotoxy(15,9);
		printf("    o888o      `Y8bood8P'     `YbodP'    	o888bood8P'   o888o o888ooooood8 o888bood8P'   \n");
		
		textcolor(TWHITE);
		
		for(i=0;i<=114;i++) putxy(5+i,11,TWHITE,"-");
		
		// Displays the total amount of moves the player made before they lost.
		gotoxy(48,13);
		printf("You failed in");
		textcolor(TRED);
		printf(" %i ", moveCounter);
		textcolor(TWHITE); 
		printf("moves\n");
		
		getch();
		
		gotoxy(0,15);
		
}


