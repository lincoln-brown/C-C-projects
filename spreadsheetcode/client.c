// GROUP MEMBER
// LINCOLN BROWN 620092180
// KAYLA BLAKE 620096888
// ANTONEEL THOMPSON 620122831

#include <stdio.h>
#include <sys/types.h>	
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>	
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>


#define BUF_SIZE 1620
#define	SERVER_IP	"127.0.0.1"
#define SERVER_PORT	6000
#define MAXCONNECTION 5
#define NUM_RANGE 9
char message[BUF_SIZE];
char corrd[3];
long THREAD_LOG[MAXCONNECTION];
char grid[NUM_RANGE][NUM_RANGE][20];



void drawBoard(){
    //This function prints out the board that was passed. Returns void
    char * const NLINE = "       A       B       C       D       E       F       G       H       I";
    char * const HLINE = "  +-------+-------+-------+-------+-------+-------+-------+-------+-------+";
    char * const VLINE = "  |       |       |       |       |       |       |       |       |       |";

    printf("%s\n",NLINE);
    printf("%s\n",HLINE);
    for (int j = 0; j < NUM_RANGE; j++)
    {  
        printf("%s\n",VLINE);
        printf("%d ",j+1);
        for (int k = 0; k < NUM_RANGE; k++)
        {  if(strcmp(grid[k][j],"   ")==0){
                printf("| %s   ",grid[k][j]);
            }else{
                printf("| %s ",grid[k][j]);
            }
        }
        printf("%s","|");
        printf("\n");
        printf("%s\n",VLINE);
        printf("%s\n",HLINE);
        
    }
    return;
}//EndFunction drawBoard

char *getValidCoordinate(){    
    char num[2];
    do
    {
        /* code */
    
    printf("-------------------------------------------------------------------------\n");
    printf("--      Please enter the cell address you wish to place the input      --\n");
    printf("-------------------------------------------------------------------------\n");
    scanf("%s",corrd);

    // printf("corrd is %ld\n", strlen(corrd));

    if(strlen(corrd)!=2){
        printf("----------------------------------------------------------------------------------\n");
        printf("-                 Coordinates Must be exactly 2 Charaters                        -\n");
        printf("-Please try Entering  the coordinates in the format (LetterNumber) Example: 'A4' -\n");
        printf("----------------------------------------------------------------------------------\n");
        continue;
    }
    // printf(" collume  name %d",corrd[0]);
    // strcpy((num), {(char) corrd[1],'\0'} );
    num[0]=corrd[1];
    num[1]='\0';
    if ((corrd[0]>=97&& corrd[0]<=105|| corrd[0]>=65&&corrd[0]<=73) && (atoi(num)>=1 && atoi(num)<=9 ))
    {
        //  printf("GOOd GOOD\n");
        return corrd;

    }
    else{
        printf("------------------------------------------------------------------------\n");
        printf("-       Invalid Coordinates detected, Please try again                 -\n");
        printf("------------------------------------------------------------------------\n");
    }
    } while (1);


    
}
// this function  check to see if a valid cordinates are enterd 
int coordinatesTester(char corrd[3]){
    char num[2];
    num[0]=corrd[1];
    num[1]='\0';

    if ((corrd[0]>=97&& corrd[0]<=105|| corrd[0]>=65&&corrd[0]<=73) && (atoi(num)>=1 && atoi(num)<=9 ))
    {
        //  printf("GOOd GOOD\n");
        return 1;

    }
    return -1;
}
// this function checks to see if a valid formula is enterd.
int ValidFormula(char formulainput[100]){
    char formula[100];
    char *formulaname;
    char *formulabody;
    char delim[2]="(";
    char delim2[2]=",";
    char *c1, *c2;
    strcpy(formula,formulainput);
    formulaname = strtok(formula, delim);
    formulabody = strtok(NULL, delim);
    // printf("formula is %s \n",formulaname);
    if(strcasecmp(formulaname,"=sum")==0||strcasecmp(formulaname,"=SUM")==0){
        printf("SUM FORMULA DETECTED \n");
    }
    else if(strcasecmp(formulaname,"=average")==0||strcasecmp(formulaname,"=AVERAGE")==0){
        printf("AVERAGE FORMULA DETECTED \n");

    }
    else if (strcasecmp(formulaname,"=RANGE")==0||strcasecmp(formulaname,"=range")==0){
        printf("RANGE FORMULA DETECTED \n");

    }else{
        printf("--------------------------------------------------------------------------\n");
        printf("- Unknown formula please try again. with a SUM AVERAGE or RANGE formula. -\n");
        printf("--------------------------------------------------------------------------\n");
    return -1;
    }

    // printf("formulabody is %s \n",formulabody);
    c1=strtok(formulabody, delim2);
    c2= strtok(NULL,delim2);
    if (coordinatesTester(c1)==-1 ||coordinatesTester(c2)==-1){

        printf("------------------------------------------------------------------------\n");
        printf("-     The Formula contains Invalid Coordinates, Please try again.      -\n");
        printf("------------------------------------------------------------------------\n");

        return-1;
    }
    // printf("c1 is %d\n",coordinatesTester(c1));
    // printf("c2 is %s\n",c2);
    
    
    return 1;
}


// ----------------MAIN PROGRAM--------------------

int main(int argc, char const *argv[])
{
int  thread_count =0;
    char input[100],celladd[5],packet[50];
    int client_socket,s,con,get;
    struct sockaddr_in server_addres;
    
    // create client socket
    client_socket = socket(PF_INET, SOCK_STREAM,0);

    // configure  settings for the server address struncture 
    memset(&server_addres, 0, sizeof (server_addres));
    server_addres.sin_family = AF_INET;
    server_addres.sin_addr.s_addr = inet_addr(SERVER_IP);
    server_addres.sin_port = htons((unsigned short)SERVER_PORT);

    // connect to client socket to server address
    con= connect(client_socket,(struct sockaddr *) &server_addres, sizeof server_addres);
     if (con<0)
     {
         printf("Error occured while connecting to server\n");
         exit(0);
     }
     
      while (1){
            /* send some data */
            printf("--------------------------------------------------------------\n");
            printf("-       Please Enter a Number , a formula or some text       -\n");
            printf("-                             OR                             -\n");
            printf("-                      Type Quit to exit                     -\n");
            printf("-       First client can  type  'save' to save the grid.     -\n");
            printf("--------------------------------------------------------------\n");
            scanf("%s",input);
            strcpy(message,input);
            if (strcasecmp(message,"quit")==0){
                strcpy(message,"kill");
                if (send(client_socket,message,strlen(message),0)>0){
                    printf("Closing  Connection\n");
                    /* code */
                }
                printf("Closing...\n ");
                    break;
            }
            // savefunction
             if (strcasecmp(message,"save")==0){
                // send(client_socket,message,strlen(message),0);
                 strcpy(message,"SAVE");

                  s=send(client_socket,message,strlen(message),0);
                  
                  
                  if((get=recv(client_socket,message,BUF_SIZE,0))>0){
                  message[get]='\0';
                  printf("Server said: %s .\n",message);
                  continue;

                  }
             }else if (atof(input)!=0.0)
            {
            //checking if input is  number 
                printf("Number detected as input\n");
                strcpy(celladd,getValidCoordinate());
                // [type,body,address]
                strcat(packet,"NUMBER&");
                sprintf(input, "%3f", atof(input));
                // input[5]=0;
                strcat(packet,input);
                strcat(packet,"&");
                strcat(packet,celladd);
                //copy packet in to message and send message
                strcpy(message,packet);
                printf("packet is %s\n",packet);
                strcpy(packet,"");
            // checking if input is a formula
            }else if (input[0]=='='){
                
                if (ValidFormula(input)==-1)
                {
                    // formula enterd  by user is not valid so the need to try again
                    continue;
                }
                strcpy(celladd,getValidCoordinate());
                strcat(packet,"FORMULA&");
                // printf("input after %s",input);
                strcat(packet,input);
                strcat(packet,"&");
                strcat(packet,celladd);
                strcpy(message,packet);
                //copy packet in to message and send message
                printf("packet is %s\n",packet);
                strcpy(packet,"");


            // Input default to  text
            }else{
                printf("Zero or text detected\n");
                strcpy(celladd,getValidCoordinate());
                // ValidCoordinate();
                strcat(packet,"TEXT&");
                strcat(packet,input);
                strcat(packet,"&");
                strcat(packet,celladd);
                //copy packet in to message and send message
                strcpy(message,packet);
                printf("packet is %s\n",packet);
                strcpy(packet,"");
                
            }
            
            // printf(" the input is %f\n",atof(input));
            s=send(client_socket,message,strlen(message),0);
            
            if(s<0){
                printf("error occured while sending  message \n");
                exit(0);
                }
            // get data from server 
            // if((get=recv(client_socket,message,BUF_SIZE,0))!=-1 ){
            //     message[get]=0;
            // printf("%d clients connected to the server.\n",atoi(message));
            // if(recv(client_socket,grid,sizeof(grid),0)!=-1){
            // drawBoard();
            //     memset(grid, 0, sizeof(grid));
            //     // TEST  GRID

            // }
            // else{
            //      printf(" ERROR 2 While FETCHING DATA FROM SERVER");

            // }
            // }else{
            //     printf(" ERROR 1 While FETCHING DATA FROM SERVER");
            // }
                recv(client_socket,grid,sizeof(grid),MSG_WAITALL);
                drawBoard();

            get=recv(client_socket,message,BUF_SIZE,0);
            message[get]=0;
            printf("%d clients connected to the server.\n",atoi(message));
                

        }
    //  strcpy(message,"sever are u there");
    //  printf("about to send\n");
    //  s=send(client_socket,message,strlen(message),0);
     printf("Closed socket Goodbye \n");
     close(client_socket);

    return 0;
}
