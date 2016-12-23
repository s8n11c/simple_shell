

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>


char line [2048];

char *argz[100];
 
pid_t pid;

static void exit_checker();

static void run_command();
static void cleanup(int n);
 
static char* skipwhite(char* s);
static void preparation(char * command);


void filler(int sig){
	printf("\n Enter exit to quit \n");
        
}

int main(){
	signal(SIGINT,filler);
	// start the shell by cleaning the screen 
	argz[0]="clear";
	run_command();
	cleanup(1);
	printf("\n \t \t [Custom Shell written in C] \t \n");
	// then loop to infinity to grap simple user command
	//Hint: there is no redirections - pipes - change current directory 
while(1){
	printf("\n \x1b[35m ---)>  \x1b[0m ");
	
	if (!fgets(line, 1024, stdin))
		return 0;

	exit_checker();
	char *pipe_checker=strchr(line,'|');

	char *redir_checker=strchr(line,'>');

	if(pipe_checker!=NULL){
		printf("\x1b[31m * it contains pipes will be implemented later * \x1b[0m \n" );
	}else if(redir_checker!=NULL){
		printf("\x1b[31m * it contains output redirection will be implemented later * \x1b[0m \n" );
		
	}else{

	preparation(line);

	run_command();
	cleanup(1);
}
}

	return 0;
}

static void run_command(){
	   pid = fork();
        int input=0;
        if (pid == 0) {
        
        		//child process 
                if (execvp(argz[0], argz) == -1)
                        _exit(EXIT_FAILURE); 

			}

}

static void exit_checker(){
		//check if the user type exit 
	int i=0;
	char e[]="exit";
	for( i=0;i<4;i++){
		if(e[i]==line[i]){
			continue;
		}else{
			return ;
		}
	}

	if(i==4){
		printf("good bye \n ");
		exit(0);
	}
}
 
static char* skipwhite(char* s)
{	//helper method	
	//ignore any white spaces 

        while (isspace(*s)) ++s;
        return s;
}
 

static void preparation(char *command){
	 command = skipwhite(command);

	 // ls -a -l 
	 //preparing the argz argument to our built-in command executor function

	 /*
	  *example: ls -l -l 
	  *next will point to the space between the command and the first argument
	  *making next = null , seperate the command from its arguments and return the rest to the loop of doing the same thing to 
	  *the rest of the second argument and the third one 
	  */ 
        char* next = strchr(command, ' ');
        int i = 0;
        while(next != NULL) {
                next[0] = '\0';
                argz[i] = command;
                ++i;
                command = skipwhite(next + 1);
                next = strchr(command, ' ');
        }
        if (command[0] != '\0') {
                argz[i] = command;
                next = strchr(command, '\n');
                next[0] = '\0';
                ++i; 
        }

        argz[i] = NULL;
}

static void cleanup(int n){
	//cleaning up the child process  to get rid of any additional zoobies process 
	wait(NULL);
}