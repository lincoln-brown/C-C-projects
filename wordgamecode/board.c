// LINCOLN BROWN 62009218

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>






int main(){

char *letters[]={"A","B","C","D","E","F","G","H","I","J",
                "K","L","M","N","O","P","Q","R","S","T","U",
                "V","W","X","Y","Z"};
int k,j,Xcord,Ycord,num,num2,chnum;

int const NUM_RANGE=8;
char play[5];
//global declaration structure grid
char * grid[NUM_RANGE][NUM_RANGE];
struct PLAYER
    {
        char name[10];
        int lastscore;
        int totalscore;
    };
struct PLAYER p1 ={"BOB",0,0};
struct PLAYER p2 ={"Alice",0,0};



// --------------------------------function declarations---------------------
struct PLAYER * changeplayer(struct PLAYER *p){ 
    // this function accepts a player and returns the address pointer for the opposite player
    // a strruct was used to keep the player's info in one location in memeory
     if (strcmp(p->name,"BOB")==0){
          return &p2;}
     else{
         return &p1;
     }     
 }


int isvalidinput(char * input){
    int z;
// write a funtuion to ensure that th input of the user is a valid letter or satement
// only "quit" or capitalletters are seenas valid input
    if((strcmp(input,"quit") ==0||strcmp(input,"Quit") ==0) ||
    (input[0]>=65 && input[0]<=90 ) ){
             
    /*valid*/ return 1;}
    
    else{/*invalid*/ return 0; }

}

void getNewBoard(){
    //creates a brand new blank board. Returns a pointer to the array 
    for (j = 0; j < NUM_RANGE; j++){
        for (k = 0; k < NUM_RANGE; k++)
        {
            grid[k][j]="   ";
        }//Endfor
    }//Endfor
    return;
}//EndFunction getNewBoard

void drawBoard(){
    //This function prints out the board that was passed. Returns void
    char * const NLINE = "    1    2    3    4    5    6    7    8";
    char * const HLINE = "  +----+----+----+----+----+----+----+----+";
    char * const VLINE = "  |    |    |    |    |    |    |    |    |";

    printf("%s\n",NLINE);
    printf("%s\n",HLINE);
    for (j = 0; j < NUM_RANGE; j++)
    {  
        printf("%s\n",VLINE);
        printf("%d ",j+1);
        for (k = 0; k < NUM_RANGE; k++)
        {  if(strcmp(grid[k][j],"   ")==0){
                printf("| %s",grid[k][j]);
            }else{
                printf("| %s  ",grid[k][j]);
            }
        }
        printf("%s","|");
        printf("\n");
        printf("%s\n",VLINE);
        printf("%s\n",HLINE);
        
    }
    return;
}//EndFunction drawBoard

   
void makePlay(int x, int y, char* c){
   //Arrays are zero indexed but our grid starts at index 1
   grid[x-1][y-1]=c;
   
   return;
}
int isOnBoard(int x, int y){
    // This function determines if the X and Y cordinates are valid or not 

    if ((x>=1 && x<=8)&& (y>=1 && y<=8))
    {
        return 1 ;
    }
    else{
        return 0;
    }
}



 int getPlayerMove(){   
    // This function get the letter and cordinates to that  the  play  want to play the letter
    do
    {
        //asking the user to enter  a valid response if invalid response is detected then  we ask them to re-enter a valid response.
    printf("Enter the letter you wish to play or type 'Quit' to end the game.");
    scanf("%s",play);
    // fgets(play, sizeof(play), stdin);
    
    if (isvalidinput(play)==0)
    {
        printf("Invalid character detected, please try a capital letter between(A-Z)!!\n\n");
    }
    //here we call the is valid function to ensure that a valid response is given before moving on
    } while (isvalidinput(play)==0);    
    
    if (strcmp(play,"quit") ==0||strcmp(play,"Quit") ==0 )
    //checking if the user wants to quit or continue playing
    {
        printf("Good game see you later\n"); 
        
        return 0;     
    }
    else{
        do
        {
        printf("Enter X Coordinates: ");
        scanf("%d", &Xcord);
        printf("Enter Y Coordinates: ");
        scanf("%d", &Ycord);
       
        if (isOnBoard(Xcord,Ycord)==0)
        {
            printf("Invalid coordinates please try again.\n");
        }
        
            /* code */
        } while (isOnBoard(Xcord,Ycord)!=1);
        
        
        // printf("the coods are  X=%d Y=%d", Xcord,Ycord);
        }
    


}
int calculateScore(char * word){
    int sum=0;
    struct keys
    {
        char letter;
        int value;
    };
    struct keys arry_key[26]= {
        {'A', 1,},{'B', 3},{'C', 3},{'D', 2},{'E', 1},{'F', 4},{'G', 2}, {'H', 4}, 
        {'I', 1}, {'J', 8}, {'K', 5}, {'L', 1}, {'M', 3}, {'N', 1}, {'O', 1}, {'P', 3},
        {'Q', 10}, {'R', 1}, {'S', 1}, {'T', 1},{ 'U', 1}, {'V', 4}, {'W', 4,}, {'X', 8},
        {'Y', 4}, {'Z', 10},
    };
    // declaring  struct and array of struct to store letters and there value;
    
    for (int n = 0; n < strlen(word); n++)
    {
        for (int i = 0; i < 26; i++){
            // looping over  each character  in the word then finding its respective value which is then added to sum 
            if (word[n]==arry_key[i].letter)
            {
            sum =sum + arry_key[i].value;
                        
            }
        }
    }
    // printf("sum is %d", sum);
    // returning the sum of the word.
    return sum ;

}




void startBoard(){
    srand(time( NULL));
    for (int c = 1; c <= 11; c++)
    {//finding random  numbers  between 1 and 8 to  use as the index for the board.
        num =(int)(rand() % 8)+1;
        num2 = (int)(rand() % 8)+1;
        //finding random numbers  between 1 and 26 to use as the index for the letters array 
        chnum= rand()%26;
        // printf("%d%d%s \n",num,num2,letters[chnum]);   
        //using the random numbers as coordinates and index for the letters array to start board with 10 random letters and coordinates.
        makePlay(num,num2,letters[chnum]);
        
            
    }




}

int inwordlist(char * word){
    // This function takes a word then checkes if it is in the word list if a match is found 1 is returned.
    FILE *fle;
    char ch[200],compch[50];
    if ((fle = fopen("./words.txt", "r")) == NULL) 
    {// checking if the  file was opened witout error.
        printf("Error! opening word list file");
        // Program could not find file 
        exit(1);
    }
    //  printf("WORD ENTERED IS: %s: \n",word);
    do
    { //fetching  letter before \n then store them in ch 
        fscanf(fle, "%s", ch);              
        if (strcmp(ch,word)==0)
        { //checking if the words watch, if a match is found 1 is returned and the loop ends 
             printf("!!! CONGRATULATIONS  A YOU FOUND A WORD !!!\n!!! THE WORD FOUND WAS: %s  !!! \n", ch);
             return 1;
            
        }
        
    } while ((fgetc(fle)) != EOF);
    // if EOF(end of file) is reached then the loop ends 
    // close the file  then return 0 because no match for the word was found.     
    fclose(fle);
    return 0;
    }


    int finddown(int xcord, int ycord){
        // the finddown function finds all words on the y axis going DOWNWARD to the end of the board,
        // it then checks if the words are in the word list using the inwordlist function. If it is in the word list 
        // then the score for that word is calculated  using the calculate score function. The total sum for the words
        /// found are returend.
        int y2, i=0,SUM=0;
        char Tword[50] ="";
        // printf("letter is %s and the cordinates  are x=%d y=%d\n", grid[xcord-1][ycord-1], xcord,ycord);
        if (ycord>=8 || strcmp(grid[xcord-1][ycord-1+1],"   ")==0){            
            // printf("empty spot OR end or board  :\n");
            //the next spot is empty or end of board is reached so no need to carry on
            return 0;
        }
        
        do
        {
            y2 =(ycord-1)+i;//y2 is incremented by on each time the loop runs so the we can get the next charater down.
            
            if ( y2>=8 || strcmp(grid[xcord-1][y2],"   ")==0)
            //here we check if y2 is greater than the size of the board/array or it the next spot is aa empty spot.
            //if either contition is true then we can stop looping 
            {
                // printf("empty spot IS FOUND :\n");
                break;
            }else{
                
                strcat(Tword,grid[xcord-1][y2]);//here we create the words  down the grid.
                
                if (inwordlist(Tword))//here we check if the word is in the word list 
                {                
                SUM=SUM+calculateScore(Tword);// calculate the sum of the score for each word.                     
                }
            }
            i=i+1;            
        } while (strcmp(grid[xcord-1][y2],"   ")!=0 || y2<7);        
        return SUM;
    }
int findup(int xcord, int ycord){
    // the findUP function finds all words on the y axis going UPWARD to the end of the board,
    // it then checks if the words are in the word list using the inwordlist function. If it is in the word list 
    // then the score for that word is calculated  using the calculate score function. The total sum for the words
    // found are returend.
    int y2, i=0,SUM=0;
    char Tword[50] ="";
     
    if (ycord<=1 || strcmp(grid[xcord-1][ycord-1-1],"   ")==0){            
        // printf("empty spot OR end or board up  :\n");
        //the next spot is empty or end of board is reached so no need to carry on
        return 0;
    }
    do
    {
        y2 =(ycord-1)-i;
        // printf("Y2 IS %d", y2);

        if (y2<=0|| strcmp(grid[xcord-1][y2],"   ")==0)
        {
            //THE NEXT SPOT IS empty SO NO NEED TO CONTINUE.
            // printf("empty spot IS FOUND :\n");
            break;
        }
        
        strcat(Tword,grid[xcord-1][y2]);
        if (inwordlist(Tword))//here we check if the word is in the word list 
        {                
        SUM=SUM+calculateScore(Tword);// calculate the sum of the score for each word.                     
        }
    
        i=i+1;
    } while (y2>0|| strcmp(grid[xcord-1][y2],"   ")!=0 );
    

return SUM;
}
int findright(int xcord, int ycord){
    // the findRIGHT function finds all words on the x axis going from left to right untill the end of the board,
    // it then checks if the words are in the word list using the inwordlist function. If it is in the word list 
    // then the score for that word is calculated  using the calculate score function. The total sum for the words
    // found are returend.
    int x2, i=0,SUM=0;
    char Tword[50] ="";

    if (xcord>=8 || strcmp(grid[xcord-1+1][ycord-1],"   ")==0){            
        // printf("empty spot OR end or board RIGHT  :\n");
        //the next spot is empty or end of board is reached so no need to carry on
        return 0;
    }
    do
    {
        x2 =(xcord-1)+i;
        // printf("x2 IS %d ", x2);
        if (x2>=8|| strcmp(grid[x2][ycord-1],"   ")==0)
        {
            //THE NEXT SPOT IS empty SO NO NEED TO CONTINUE.
            // printf("empty spot IS FOUND :\n");
            break;
        }
        strcat(Tword,grid[x2][ycord-1]);
         if (inwordlist(Tword))//here we check if the word is in the word list 
        {                
        SUM=SUM+calculateScore(Tword);// calculate the sum of the score for each word.                     
        }

        i=i+1;
    } while (x2<7||strcmp(grid[x2][ycord-1],"   ")!=0 );
    


return SUM;
}
int findleft(int xcord, int ycord){
    // the findleft function finds all words on the x axis going from right to left untill the end of the board,
    // it then checks if the words are in the word list using the inwordlist function. If it is in the word list 
    // then the score for that word is calculated  using the calculate score function. The total sum for the words
    // found are returend.
    int x2, i=0,SUM=0;
    char Tword[50] ="";

    if (xcord<=1 || strcmp(grid[xcord-1-1][ycord-1],"   ")==0){            
        // printf("empty spot OR end of board RIGHT  :\n");
        //the next spot is empty or end of board is reached so no need to carry on
        return 0;
    }
    do
    {
        x2 =(xcord-1)-i;
        
         if (x2<=0|| strcmp(grid[x2][ycord-1],"   ")==0)
        {
            //THE NEXT SPOT IS empty SO NO NEED TO CONTINUE.
            // printf("empty spot IS FOUND :\n");
            break;
        }
        strcat(Tword,grid[x2][ycord-1]);
         if (inwordlist(Tword))//here we check if the word is in the word list 
        {                
        SUM=SUM+calculateScore(Tword);// calculate the sum of the score for each word.                     
        }

    
    i=i+1;
    } while (x2>0|| strcmp(grid[x2][ycord-1],"   ")!=0);
    

return SUM;
}
int findupright(int xcord, int ycord){
    // the findupRIGHT function finds all words on the diagonal  going from bottom left to  top right untill the end of the board,
    // it then checks if the words are in the word list using the inwordlist function. If it is in the word list 
    // then the score for that word is calculated  using the calculate score function. The total sum for the words
    // found are returend.
    int x2,y2, i=0,SUM=0;
    char Tword[50] ="";

    if ((xcord>=8 || ycord<=1 ) || strcmp(grid[xcord-1+1][ycord-1-1],"   ")==0){            
        // printf("empty spot OR end of board UPRIGHT  :\n");
        //the next spot is empty or end of board is reached so no need to carry on
        return 0;
    }
    do
    {
        x2 =(xcord-1)+i;
        y2 =(ycord-1)-i;
        if (x2>=8 ||y2<=0 ||strcmp(grid[x2][y2],"   ")==0)
        {
            // printf("empty spot FOUND  :\n");
            break;
        }
        
        //  printf("x2 is %d and y2 is %d CONTENT IS %s :\n",x2,y2,grid[x2][y2]);
        strcat(Tword,grid[x2][y2]);
         if (inwordlist(Tword))//here we check if the word is in the word list 
        {                
        SUM=SUM+calculateScore(Tword);// calculate the sum of the score for each word.                     
        }


       i=i+1;
    } while (x2<8 && y2>0);
    

return SUM;
}
int findupleft(int xcord, int ycord){
    // the findupleft function finds all words on the diagonal  going from bottom right to  top left untill the end of the board,
    // it then checks if the words are in the word list using the inwordlist function. If it is in the word list 
    // then the score for that word is calculated  using the calculate score function. The total sum for the words
    // found are returend.
     int x2,y2, i=0,SUM=0;
    char Tword[50] ="";

    if ((xcord>=1 || ycord<=1 ) || strcmp(grid[xcord-1-1][ycord-1-1],"   ")==0){            
        // printf("empty spot OR end of board UPleft  :\n");
        //the next spot is empty or end of board is reached so no need to carry on
        return 0;
    }
    do
    {
        x2 =(xcord-1)-i;
        y2 =(ycord-1)-i;
        if (x2<=-1 ||y2<=-1 ||strcmp(grid[x2][y2],"   ")==0)
        {
            // printf("empty spot OR END OR BOARD FOUND  :\n");
            break;
        }

        // printf("x2 is %d and y2 is %d CONTENT IS %s :\n",x2,y2,grid[x2][y2]);
         strcat(Tword,grid[x2][y2]);
         if (inwordlist(Tword))//here we check if the word is in the word list 
        {                
        SUM=SUM+calculateScore(Tword);// calculate the sum of the score for each word.                     
        }

        i=i+1;
    } while ((!(x2==0)) || (!(y2==0)));//CHECK THIS LOGIC BEFORE SUBMIT 
    
    return SUM;
    
    }
int findbottomright(int xcord, int ycord){
    // the findbottomright function finds all words on the diagonal  going from top left to  bottom right untill the end of the board,
    // it then checks if the words are in the word list using the inwordlist function. If it is in the word list 
    // then the score for that word is calculated  using the calculate score function. The total sum for the words
    // found are returend.
    int x2,y2, i=0,SUM=0;
    char Tword[50] ="";

    if ((xcord>=8 || ycord>=8 ) || strcmp(grid[xcord-1+1][ycord-1+1],"   ")==0){            
        // printf("empty spot OR end of board BOTTOMRIGHT  :\n");
        //the next spot is empty or end of board is reached so no need to carry on
        return 0;
    }
    do
    {
        x2 =(xcord-1)+i;
        y2 =(ycord-1)+i;
        if (x2>=8 || y2>=8 ||strcmp(grid[x2][y2],"   ")==0)
        {
            // printf("empty spot OR END OR BOARD FOUND  :\n");
            break;
        }

        // printf("x2 is %d and y2 is %d CONTENT IS %s :\n",x2,y2,grid[x2][y2]);
        strcat(Tword,grid[x2][y2]);
         if (inwordlist(Tword))//here we check if the word is in the word list 
        {                
        SUM=SUM+calculateScore(Tword);// calculate the sum of the score for each word.                     
        }

        i=i+1;
    } while (x2<7||y2<7);
    

return SUM;
}

int findbottomleft(int xcord, int ycord){
    // the findbottomleft function finds all words on the diagonal  going from top right to  bottom left untill the end of the board,
    // it then checks if the words are in the word list using the inwordlist function. If it is in the word list 
    // then the score for that word is calculated  using the calculate score function. The total sum for the words
    // found are returend.
    int x2,y2, i=0,SUM=0;
    char Tword[50] ="";

    if ((xcord<=1 || ycord>=8 ) || strcmp(grid[xcord-1-1][ycord-1+1],"   ")==0){            
        // printf("empty spot OR end of board BOTTOMleft  :\n");
        //the next spot is empty or end of board is reached so no need to carry on
        return 0;
    }
    do
    {
        x2 =(xcord-1)-i;
        y2 =(ycord-1)+i;

        if ((x2<=0 || y2>=8 )||strcmp(grid[x2][y2],"   ")==0)
        {
            // printf("empty spot OR END OR BOARD FOUND  :\n");
            break;
        }


         printf("x2 is %d and y2 is %d CONTENT IS %s :\n",x2,y2,grid[x2][y2]);
         strcat(Tword,grid[x2][y2]);
         if (inwordlist(Tword))//here we check if the word is in the word list 
        {                
        SUM=SUM+calculateScore(Tword);// calculate the sum of the score for each word.                     
        }



        i=i+1;
    } while (x2>1||y2<7);
    
return SUM;
}

int getmovescore(int xcord, int ycord){
    int movesum, s1,s2,s3,s4,s5,s6,s7,s8;

    s1=finddown(Xcord,Ycord);
    s2=findup(Xcord,Ycord);
    s3=findright(Xcord,Ycord);
    s4=findleft(Xcord,Ycord);
    s5=findupright(Xcord,Ycord);
    s6=findupleft(Xcord,Ycord);
    s7=findbottomright(Xcord,Ycord);
    s8=findbottomleft(Xcord,Ycord);
    movesum=s1+s2+s3+s4+s5+s6+s7+s8;
    return movesum;

}
 int  isboardfull(){
     for (int i = 0; i < NUM_RANGE; i++)
    {
        for (int n = 0; n < NUM_RANGE; n++)
        
        {
            if (strcmp(grid[i][n],"   ")==0){
                return 0;
            }
        }
    }
    return 1;
 }
void startgame(){
    static int again=-999;
    struct PLAYER *HOLD =&p1;//p1 is always the first player of the game.    
    
    getNewBoard();
    startBoard();
    drawBoard();
    
    do
    {        
        again= getPlayerMove();
        // searchiong for a match in letters array before adding to the boards 
        if(again==0)// if the user wants to end the game, the scores are displayed.
        {
            printf("The scores are Player 1(%s) = %d and Player 2 (%s)= %d\n",p1.name,p1.totalscore,p2.name,p2.totalscore);
            exit(1);
        }
        if (isboardfull()==1){
            printf("The board is full we can not continue");
            printf("The scores are Player 1(%s) = %d and Player 2 (%s)= %d\n",p1.name,p1.totalscore,p2.name,p2.totalscore);
            exit(1);
        }
        for (int i = 0; i < 25; i++)
        {// here we loop through the letters array to find which letter the play made,
        //when the letter is found a play is made with the coordinates and letter.
            if (*letters[i]==play[0])
            {
                makePlay(Xcord,Ycord,letters[i]); 
                HOLD->lastscore = getmovescore(Xcord,Ycord);
                HOLD->totalscore =(HOLD->totalscore + HOLD->lastscore);
                printf("%s's TOTAL SUM FOR THAT PLAY IS %d\n",HOLD->name,HOLD->lastscore);


                printf("Nice play  %s\n", HOLD->name);
                HOLD =changeplayer(HOLD);//here we call on the change player function to swap the player structere. 
                printf("Now your play %s\n",HOLD->name);

            }
        }
    drawBoard();
        
    } while (again!=0);
    


}


// ------------------------End of function declaration --------------------------------
//  getPlayerMove();
startgame();
// for (int i = 0; i < NUM_RANGE; i++)
// {
//     for (int n = 0; n < NUM_RANGE; n++)
    
//     {
//         printf("at x= %d and y= %d array is %s\n",i,n,grid[i][n]);
//     }
    
// }
// char ord[50], ch1[50],ch2[50];
// // strcpy(ch1,"A");
// // strcpy(ch2,"A");
// // strcat(ord,ch1);
// // strcat(ord,ch2);
// // inwordlist(ord);
// strcpy(ch1,"A");
// for (int i = 0; i < 2; i++)
// {
//     strcat(ord,ch1);
// }
// inwordlist(ord);


    // getNewBoard();
    // drawBoard();
    // //notice the use of spaces
    // makePlay(3,7,"a");    
    // makePlay(4,5,"b");  
    // drawBoard();
 
    // getNewBoard();
    // startBoard();
    // drawBoard();
    // calculateScore("HEello");



    return 0;
}
