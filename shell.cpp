#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 


void dir() 
{ 
   char cwd[1024]; 
    getcwd(cwd, sizeof(cwd)); 
    printf("\nDir: %s", cwd);
   // printf("\n\n"); 
} 



void type_prompt()
{
static int ftime=1;
if(ftime)
{
//clear screen for first time
const char* CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
write(STDOUT_FILENO,CLEAR_SCREEN_ANSI,12);
ftime=0;
}

printf("\nnewshell_@_own>>> ");

}


int main()
{ 
 printf("\nMY NEW SHELL");
 dir();
 
 char line[200];

 char *cmd[100];


while(1)           //repeat forever
{
    pid_t pid=fork(); 
    if(pid == 0)
    {
       type_prompt();    //display prompt on screen

        scanf("%[^\n]%*c",line);
        cmd[0]=strtok(line," ");
        int i=0;


        while(cmd[i] != NULL)
        {
		i++;       
	    cmd[i]=strtok(NULL," ");
	
        }  
char *cd=cmd[0];
	 if(strncmp(cd,"cd",2)==0)
    		{
       			 if(cmd[1] == "~") chdir("/home");
       			 else chdir(cmd[1]);
        		//continue;
   		 }
		
			/*if (execvp(cmd[0], cmd) < 0) 
			{ 
				  printf("\nCould not execute command.."); 
			}*/
			else execvp(cmd[0],cmd);
		}
    	
    else
    {

        //printf("\nfailed");
        wait(0);
	}
}
 return 0;
}


