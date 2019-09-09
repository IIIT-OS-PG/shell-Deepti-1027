#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "pipe.h"





int i;


void dir() 
{ 
   char cwd[1000]; 
    getcwd(cwd, sizeof(cwd)); 
    printf("\nDir: %s", cwd);
} 


void print()
{
static int ftime=1;
if(ftime)
{
//clear screen for first time
const char* CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
write(STDOUT_FILENO,CLEAR_SCREEN_ANSI,12);
ftime=0;
}
//setenv("PS1", "my_new_shell>", 1);
//execlp("bash", "bash", (char*)NULL);

char* prompt = getenv("HOME"); 
printf("\n\n\nmy_new_shell:@%s:", prompt); 

//printf("\nnewshell_@_own>>> ");
}


void redirect(char **cmd)
{
  int in,out;

  if(i > 2)
  {  
     char *re=cmd[i-2];
     char *output=cmd[i-1];

     if(strcmp(re,">") == 0)
     {
     out = open(output, O_CREAT | O_WRONLY | O_TRUNC );
     }
     else if(strcmp(re,">>")==0)
     {
      out=open(output, O_CREAT | O_APPEND | O_WRONLY);
     }

     cmd[i-1]=NULL;
     cmd[i-2]=NULL;

    dup2(out, 1);

    execvp(cmd[0], cmd);
  }
}





int main()
{ 
 printf("\nMY NEW SHELL");
 dir();
 
 
char line[200];
char *cmd[100];
FILE *fptr;

 


while(1)           //repeat forever
{   

    bool present = false;
    pid_t pid=fork(); 
    if(pid == 0)
    {
        print();    //display prompt on screen
        
        fptr = fopen("history.txt", "w");
        scanf("%[^\n]%*c",line);
        if(fptr == NULL)
       {
          printf("Error!");
          exit(1);
       }
       fprintf(fptr,"%s",line);
       fclose(fptr);
        
        
        
        

        char duplicate[100];

        strcpy(duplicate,line);

        


        cmd[0]=strtok(line," ");
        i=0;


        while(cmd[i] != NULL)
        {
         i++;       
         cmd[i]=strtok(NULL," ");
  
        }  
    
//printf("%d\n",i);

if(i > 3)
{
  //printf("askdfjlia");
  pipe(duplicate);
  
  continue;
}

else{
char *cd=cmd[0];
char *w=cmd[i-2];
//printf("%s\n",cd);
//printf("%s\n",w);

if((strcmp(w,">>") == 0)||(strcmp(w,">") == 0))
{
  redirect(cmd);
}


else
{
   if(strcmp(cd,"cd") == 0)
        {
             if(cmd[1] == "~") chdir("/home");
             else chdir(cmd[1]);
       }
    
      else execvp(cmd[0],cmd);
}
}
}

   
    else
     {
        wait(0);
     }
     

}
 return 0;
}


