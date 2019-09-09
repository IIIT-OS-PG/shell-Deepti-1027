#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
char *cmd[100];





using namespace std;

void pipe_line(char **cmd)
{
	

	 int fd[2];
	 pipe(fd);  

	 
	 char *new_cmd1[200];
	
    
    new_cmd1[0]=strtok(cmd[0]," ");
    int i=0;
    while(new_cmd1[i]!=NULL)
    {
    	i++;
    	new_cmd1[i]=strtok(NULL," ");
    }



    char *new_cmd2[100];
    new_cmd2[0]=strtok(cmd[1]," ");
    int j=0;
    while(new_cmd2[j]!=NULL)
    {
    	j++;
    	new_cmd2[j]=strtok(NULL," ");
    }

   

    


	 int pid2;
	 int pid1=fork();
	 if(pid1 == 0)
	 {
	 	//child procss

	 	close(fd[0]);             //read end of child process
	 	dup2(fd[1],1);
	 	execvp(new_cmd1[0],new_cmd1);

	 }
	 else    //second command..
	 {
           pid2=fork();
           if(pid2==0)
           {
           	//child process 2
           

           	close(fd[1]);
           	dup2(fd[0],0);
           	execvp(new_cmd2[0],new_cmd2);
           }
	 }
	
	
	 waitpid(pid1,nullptr,0);

	                             
	 close(fd[1]);   
	
	 waitpid(pid2,nullptr,0);

}


void pipe(char *line)

{
	
	cmd[0]=strtok(line,"|");
    int i=0;
	while(cmd[i] != NULL)
        {
         i++;       
         cmd[i]=strtok(NULL,"|");
        }  
        
        pipe_line(cmd);

}