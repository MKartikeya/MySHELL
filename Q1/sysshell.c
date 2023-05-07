#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<readline/readline.h>
#include<readline/history.h>
#include<unistd.h>

void exit_dis(){
printf("Exiting the program..\n");
exit(0);
}
void display_welcome(){
//color change to cyan
printf("\033[36;1m");
printf("WELCOME!!\nThis custom terminal run by a program in C.\nTryout `help` to get to know some commands that are available ^_^\n");
//reset
printf("\033[0m");
}

int main(){
char *input;
char *command;
    char string[300] = "";
    strcat(string, "\033[32;1m");
    char username[200];
    getlogin_r(username, 200);
    printf("%s", string);
    strcat(string, username);
    strcat(string, "@");
    gethostname(username, 200);
    strcat(string, username);
    strcat(string, ":");
    strcat(string, "\033[0m");
    printf("\033[0m");
while(1){
char cwd[300],final[300]="";
strcat(final,string);
getcwd(cwd,300);
strcat(final,"\033[34;1m");
strcat(final,cwd);
strcat(final,"\033[0m");
strcat(final,"$ ");
input=readline(final);
if(strlen(input)>0) add_history(input);
if(!strcmp(input,"help")) system("bash -c help");
else if(!strcmp(input,"hi") || !strcmp(input,"hello")) display_welcome();
else if(!strcmp(input,"exit") || !strcmp(input,"quit") || !strcmp(input,"e") || !strcmp(input,"q")) exit_dis();
else system(input);
}
return 0;
}

