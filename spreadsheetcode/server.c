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



#define BUF_SIZE	1024
#define	SERVER_IP	"127.0.0.1"
#define SERVER_PORT	6000
#define MAXCONNECTION 5
#define NUM_RANGE 9
#define GRID_SIZE 20
long THREAD_LOG[MAXCONNECTION];
int THREAD_COUNTER=0;
char grid[NUM_RANGE][NUM_RANGE][GRID_SIZE],play[GRID_SIZE];
char *TYPE, *DATUM, *CADDR;

void spliter(char message[BUF_SIZE]){
    // this function splits the  message from the clint in to  3 parts
    // the type data and cell address
    char msg[BUF_SIZE];
    char delim[2]="&";
    strcpy(msg,message);
    TYPE=strtok(msg,delim);
    DATUM=strtok(NULL,delim);
    CADDR= strtok(NULL,delim);
}

int fcoodtonum(char * c_add){
    // this function returns the cell number i.e it converts the  leters to numbers
    // printf("c add %c\n",c_add[0]);
    if (c_add[0]>=97&& c_add[0]<=105)
    {
       return c_add[0]-96 ;
    }else if (c_add[0]>=65&&c_add[0]<=73)
    {
       return c_add[0]-64 ;
    }
}
int scoodtonum(char * c_add){
    // this function returns the y coordinates and in integer 
    char num[2];
    num[0]=c_add[1];
    num[1]='\0';
    return atoi(num);


}

void getNewBoard(){
    //creates a brand new blank board. Returns a pointer to the array 
    for (int j = 0; j < NUM_RANGE; j++){
        for (int k = 0; k < NUM_RANGE; k++)
        {
            strcpy(grid[k][j],"   ");
            // grid[k][j]="   ";
        }//Endfor
    }//Endfor
    return;
}//EndFunction getNewBoard
void saveWorksheet(){
    //This function prints out the board that was passed. Returns void
    FILE * fPtr;
    fPtr = fopen("spreadsheet.txt", "w");
    if(fPtr == NULL)
    {
        /* File not created hence exit */
        printf("Unable to create file.\n");
        exit(EXIT_FAILURE);
    }
    char * const NLINE = "       A       B       C       D       E       F       G       H       I";
    char * const HLINE = "  +-------+-------+-------+-------+-------+-------+-------+-------+-------+";
    char * const VLINE = "  |       |       |       |       |       |       |       |       |       |";

    fprintf(fPtr,"%s\n",NLINE);
    fprintf(fPtr,"%s\n",HLINE);
    
   
    for (int j = 0; j < NUM_RANGE; j++)
    {  
        fprintf(fPtr,"%s\n",VLINE);
        fprintf(fPtr,"%d ",j+1);
        for (int k = 0; k < NUM_RANGE; k++)
        {  if(strcmp(grid[k][j],"   ")==0){
                fprintf(fPtr,"| %s   ",grid[k][j]);
            }else{
                fprintf(fPtr,"| %s ",grid[k][j]);
            }
        }
        fprintf(fPtr,"%s","|");
        fprintf(fPtr,"\n");
        fprintf(fPtr,"%s\n",VLINE);
        fprintf(fPtr,"%s\n",HLINE);
        
    }
     fclose(fPtr);
    return;
}//EndFunction drawBoard
void makePlay(int x, int y, char c[GRID_SIZE]){
   //Arrays are zero indexed but our grid starts at index 1
    // printf("data is %s\n",c);
   strcpy(grid[x-1][y-1],c);
   
   return;
}
int range(char *cord1, char *cord2){
    //  this get the number of  cells between two points 
    // this function is used in the average function 
    int x1,y1,x2,y2;
    x1=fcoodtonum(cord1);
    y1=scoodtonum(cord1);
    x2=fcoodtonum(cord2);
    y2=scoodtonum(cord2);
    if (x1==x2)
    {
        return( y2-y1);
        /* code */
    }else if (y2==y1)
    {
        return (x2-x1);
    }else{
        return 0;
    }
}

float theRange(char *cord1, char *cord2){
    // this function calculates the range i.e  the Range Formula 
  float largest,smallest;
    float temp1,temp2;
    int x1,y1,x2,y2;
    x1=fcoodtonum(cord1);
    y1=scoodtonum(cord1);
    x2=fcoodtonum(cord2);
    y2=scoodtonum(cord2);
    if (x1==x2)
    {
        if(y1<y2){
                 smallest=atof(grid[x1-1][y1-1]);
                 largest=atof(grid[x1-1][y1-1]);
                  printf("BFsmalest%.2f\n",smallest);
                printf("BFlargest%.2f\n",largest);
             while (y1<y2)
             {
                 temp1=atof(grid[x1-1][y1]);
                  if (temp1<smallest)
                  {
                    smallest=temp1;
                  }else if(temp1>largest){
                      largest=temp1;
                    //   printf("getting largest 1111\n");
                  } 

                    // printf("smalest%.2f\n",smallest);
                    // printf("largest%.2f\n",largest);
                    // printf("temp1%.2f\n",temp1);
                y1++; 
             }
              printf("helo 1\n");
             return (largest-smallest);
             
        }else if( y2<y1){
                 smallest=atof(grid[x1-1][y2-1]);
                 largest=atof(grid[x1-1][y2-1]);

            while (y2<y1)
             {
                 temp1=atof(grid[x1-1][y2]);
                  if (temp1<smallest)
                  {
                    smallest=temp1;
                    
                  }else if(temp1>largest){
                    largest=temp1;
                     
                  }              
                y2++;
             }
             
             return (largest-smallest);

        }else{
             
            return atof(grid[x1-1][y2-1]);

            
        }
        
        
    }else if (y2==y1)
    {
         if(x1<x2){
                 smallest=atof(grid[x1-1][y1-1]);
                 largest=atof(grid[x1-1][y1-1]);
             while (x1<x2)
             {
                 temp1=atof(grid[x1][y1-1]);
                  if (temp1<smallest)
                  {
                    smallest=temp1;
                  }else if(temp1>largest){
                      largest=temp1;
                    //   printf("getting largest 1111\n");
                  } 

                    // printf("smalest%.2f\n",smallest);
                    // printf("largest%.2f\n",largest);
                    // printf("temp1%.2f\n",temp1);
                x1++; 
             }
              printf("helo 1\n");
             return (largest-smallest);
             
        }else if( x2<x1){
                 smallest=atof(grid[x2-1][y2-1]);
                 largest=atof(grid[x2-1][y2-1]);

            while (x2<x1)
             {
                 temp1=atof(grid[x2][y2-1]);
                  if (temp1<smallest)
                  {
                    smallest=temp1;
                    // printf("111getting smallest %.2f\n", smallest);
                  }else if(temp1>largest){
                    largest=temp1;
                    //  printf("222getting largest %.2f \n",largest);
                  }              
                x2++;
             }
            //  printf("helo 2\n");
             return (largest-smallest);

        }else{
            //  printf("getting same\n");
            return atof(grid[x1-1][y2-1]);

            
        }


        
    }
     


}

float sum(char *cord1, char *cord2){
    // this returns the cumulative total from cord1 to cord2
    int x1,y1,x2,y2;
    float total=0.0;
    x1=fcoodtonum(cord1);
    y1=scoodtonum(cord1);
    x2=fcoodtonum(cord2);
    y2=scoodtonum(cord2);

    if (x1==x2)
    {
    //    y1,y2//2,5
        if (y1<y2){
            while (y1<=y2)
            {
                // printf(" sum1 ttteest %f",atof(grid[x1-1][y1-1]));
                total=total+atof(grid[x1-1][y1-1]);
                y1++;
            }
            return total;
            /* code */
        }else{
            while (y2<=y1)
            {
                // printf(" sum2 ttteest %f",atof(grid[x1-1][y2-1]));
                total=total +atof(grid[x1-1][y2-1]);
                y2++;
            }
            return total;
        }       
       
    }else if (y2==y1)
    {
       if (x1<x2){
            while (x1<=x2)
            {
                // printf(" sum3 ttteest %f",atof(grid[x1-1][y1-1]));
                total=total+atof(grid[x1-1][y1-1]);
                x1++;
            }
            return total;
            /* code */
        }else{
            while (x2<=x1)
            {
                // printf(" sum4 ttteest %f",atof(grid[x2-1][y2-1]));
                total=total+atof(grid[x2-1][y2-1]);
                x2++;
            }
            return total;
        }       
    }else{
        return 0.0;
        
        }
    
    }
float average(char *cord1, char *cord2){
    // this  returns  the average value  from cord1 tp cord2
    float s_sum;
    int  r_range,rr_range;
    s_sum= sum(cord1,cord2);
    r_range=range(cord1,cord2);
    rr_range= r_range+1;
    return (s_sum/rr_range);
}

void playpadding(){
    //  this adds white space to the values in the cell 
    // so that the grid looks sexy.
        while (strlen(play)<=4)
        {
        play[strlen(play)]=' ';
            /* code */
        }           
        play[5]='\0';
        // this truncates the values 
}
    


void * socketthread(void *sck){
    // this is the thread that runs each time a client connects to the server. 
    int newSocket = *((int *)sck);
    int get;
    char delim[2]="(";
    char delim2[2]=",";
    char *formulaname;
    char *formulabody;
    char *c1,*c2;
    char client_message[BUF_SIZE];
    char t_counter[10];


    THREAD_LOG[THREAD_COUNTER-1]=pthread_self();
    while (1){
        
        get=recv(newSocket,client_message,BUF_SIZE,0);
        if(get<0){
            printf("Unable to recieve data.\n");
            exit(0);
        }
        
        client_message[get]=0;
        printf("%d clients connected  \n",THREAD_COUNTER);
        // printf("messaage from client is %s\n",client_message);
        //Evaluate kill command
        if (strcasecmp(client_message,"kill")==0)
        {   // ensures that  kill command comes from first client 
            if (THREAD_LOG[0]==pthread_self())
            {
                // checking to see if this is the first client
                printf(" The First client has closed the connection. ");

                
                close(newSocket);
                break;
                
            }// closing thread for all clients that is not first client 
            pthread_exit(NULL);
            // break;
        }

        //save function gets called here
         if (strcasecmp(client_message,"save")==0||strcasecmp(client_message,"SAVE")==0){
             if (THREAD_LOG[0]==pthread_self())
        {
                printf("SAVING...\n");
                
                saveWorksheet();
                char tempmsg[BUF_SIZE];
                strcpy(tempmsg,"GRID SAVED SUCESFULLY");
                send(newSocket,tempmsg,sizeof(tempmsg),0);
                 printf("SAVED.\n");

            }else{
                char tempmsg[BUF_SIZE];
                strcpy(tempmsg,"ONLY FIRST CLIENT CAN SAVE GRID");
                send(newSocket,tempmsg,sizeof(tempmsg),0);

                printf("ONLY FIRST CLIENT CAN SAVE GRID\n");
            }


           


         }

        // split message 
        spliter(client_message);
        // spliter function splits the message from the client into three parts

        // THIS SET OF IF ELSE BLOCKS CHECKS WHAT TYPE OF INPUT WAS RECIEVED THEN PROCESS ACCORDINGLY
        // ---------------Start of processing input type--------------------
        if (strcasecmp(TYPE,"NUMBER")==0) 
        {
            printf("INPUT IS A NUMBER\n");
            strcpy(play,DATUM);
            play[5]='\0';
            makePlay(fcoodtonum(CADDR),scoodtonum(CADDR),play);
           
        } else if (strcasecmp(TYPE,"FORMULA")==0){
            printf("INPUT IS A FORMULA\n");           
            formulaname = strtok(DATUM, delim);
            formulabody = strtok(NULL, delim);
            c1=strtok(formulabody,delim2);
            c2=strtok(NULL,delim2);
            
            //------ Processing individual formulas---------------------------
            if(strcasecmp(formulaname,"=sum")==0||strcasecmp(formulaname,"=SUM")==0){
                // call sum function then make play
                printf("SUM FORMULA DETECTED \n");
                sprintf(play, "%.2f", sum(c1,c2));
                playpadding();
                makePlay(fcoodtonum(CADDR),scoodtonum(CADDR),play);

            }
            else if(strcasecmp(formulaname,"=average")==0||strcasecmp(formulaname,"=AVERAGE")==0){
                // call average function then make paly 
                printf("AVERAGE FORMULA DETECTED. \n");

                sprintf(play, "%.2f", average(c1,c2));
                playpadding();
                makePlay(fcoodtonum(CADDR),scoodtonum(CADDR),play);

            }
            else if (strcasecmp(formulaname,"=range")==0||strcasecmp(formulaname,"=range")==0){
            // Processing the Range formula  
                printf("RANGE FORMULA DETECTED \n");
                sprintf(play, "%f", theRange(c1,c2));
                playpadding();
                makePlay(fcoodtonum(CADDR),scoodtonum(CADDR),play);


            }
            //----------------End of processing formulas--------------------------  



        }else if (strcasecmp(TYPE,"TEXT")==0)
        // Processing all text input except for quit and save        
        {
            strcpy(play,DATUM);
            playpadding();
            makePlay(fcoodtonum(CADDR),scoodtonum(CADDR),play);

            
        }
        // ---------------End of processing input type--------------------
        // Clearing out Play
        memset(play,0,strlen(play));
        // sending updated grid to client 
        send(newSocket,grid,sizeof(grid),0);

        
        sprintf(t_counter, "%d", THREAD_COUNTER);
        // Sending the total amount of connected clients to each clients
        send(newSocket,t_counter,sizeof(t_counter),0);
        
       
    }


printf("closing socket and thread\n");
exit(0);
return NULL;
}
//--------------------------MAIN PROGRAM--------------------
int main(int argc, char const *argv[])
{
    
    pthread_t tid[MAXCONNECTION];
    int server_socket,new_socket[MAXCONNECTION],adsize, binded,get, listening=0;
    struct sockaddr_in server_addres,getaddr;
    struct sockaddr_storage serverStorage;

//--------------------------------------------------------
    getNewBoard();
    // creating server socket
    while (1)
    {

        server_socket = socket(PF_INET, SOCK_STREAM,0);
        if (server_socket<0)
        {
            printf("Error while Creating Socket.\n");
            exit(0);
        }
        // configure  settings for the server address struncture 
        memset(&server_addres, 0, sizeof (server_addres));
        server_addres.sin_family = AF_INET;
        server_addres.sin_addr.s_addr = htonl(INADDR_ANY);
        server_addres.sin_port = htons((unsigned short)SERVER_PORT);

        binded=bind(server_socket,(struct sockaddr *)&server_addres, sizeof(server_addres));
        if (binded<0){
            printf("There was an issue binding the Socket.\n");
            exit(0);
        }
        if (listen(server_socket,MAXCONNECTION)>=0){
            printf("Listening...\n");
            listening = 1;
        }
        else{
            printf("Unable to Listen for connections.\n ");
            exit(0);
        }

        while (1){
            adsize = sizeof(serverStorage);
            // accept incoming socket connection and pass to thread
            new_socket[THREAD_COUNTER] = accept(server_socket,(struct sockaddr *) &serverStorage, &adsize );
            printf("accepted connection\n");


            pthread_create(&tid[THREAD_COUNTER++],NULL,socketthread, &new_socket[THREAD_COUNTER]);
            // pthread_join(tid[THREAD_COUNTER], NULL);
            // pthread_create(&tid[thread_count],NULL,socketthread, &new_socket);
                
            
            
        // THREAD_COUNTER=THREAD_COUNTER+1;
        }
        
    }
return 0;
}
