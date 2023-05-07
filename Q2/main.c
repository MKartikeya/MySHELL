#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include "myheader.h"
#define MAX_SPACES 100
#define MAX_LEN 100

char *splits[100];
int split(char *splits[], unsigned char *command)
{
    char *token = strtok(command, " ");
    int a = 0;
    while (token != NULL)
    {
        splits[a++] = token;
        token = strtok(NULL, " ");
    }
    return a;
}

void print_file(char *filename){
    FILE *fp = fopen(filename, "r");
            if (fp == NULL)
            {
                perror("Unable to open file!");
                exit(1);
            }
            char chunk[128];

            while (fgets(chunk, sizeof(chunk), fp) != NULL)
            {
                fputs(chunk, stdout);
            }

            fclose(fp);
}
void display_welcome()
{
    printf("\033[36;1m");
    // printf("<<<<<<<<<<<<<''''''''''''''''''''''''''''''''''>>>>>>>>>>>>\n");
    // printf("|********-----------Welcome to MyShell----------**********|\n");
    printf("                  ___________________________________     \n");                            
    printf("                 /                                   \\  \n");                          
    printf("                |             !!!WELCOME!!!           |  \n");          
    printf("                |            This is MyShell          |  \n");              
    printf("                |        Start out by seeing help     |  \n");                 
    printf("                 \\___________________________________/  \n\n");                           
    printf("\033[0m");
}
void display_exit(){
    printf("  Exiting the program.....\n");
    printf("                 _______       ___   ___     _______\n");
    printf("                |   __  \\      \\  \\_/  /    |   ____|\n");
    printf("                |  |__|  |      \\     /     |  |____\n");
    printf("                |   __   |       |   |      |   ____|\n");
    printf("                |  |__|  |       |   |      |  |____\n");
    printf("                |_______/        |___|      |_______|\n\n");
}
int main()
{
    display_welcome();
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

    while (1)
    {
        int split_count = 0;
        char final[300] = "";
        strcat(final, string);
        strcat(final, "\033[34;1m");
        char cur_dir[200];
        getcwd(cur_dir, 200);
        strcat(final, cur_dir);
        strcat(final, "\033[0m");
        strcat(final, "$ ");
        command = readline(final);
        if (strlen(command) > 0)
            add_history(command);
        char copy[1000] = "Please work";
        int a = split(splits, copy);
        strcpy(copy, command);
        a = split(splits, copy);
        if (!strcmp(splits[0], "ls"))
        {
            myls(splits, a);
        }
        else if (!strcmp(splits[0], "cp"))
        {
            mycp(splits, a);
        }
        else if (!strcmp(splits[0], "mv"))
        {
            mymv(splits, a);
        }
        else if (!strcmp(splits[0], "grep"))
        {
            mygrep(splits, a);
        }
        else if (!strcmp(splits[0], "ps"))
        {
            myps(splits, a);
        }
        else if (!strcmp(splits[0], "exit") || !strcmp(splits[0], "quit") || !strcmp(splits[0], "e") || !strcmp(splits[0], "q"))
        {
            // printf("Exiting program....\n");
            display_exit();
            break;
        }
        else if (!strcmp(splits[0], "clear"))
            system("clear");
        else if (!strcmp(splits[0], "cd") && a == 2)
        {
            chdir(splits[1]);
        }
        else if (!strcmp(splits[0], "help") && a == 1)
        {
            printf("I'm Fetching help.Hold your breathe...\n");
            print_file("help.txt");
        }
        else if (!strcmp(splits[0], "man") && a == 2 && !strcmp(splits[1],"ls"))
        {
            print_file("myls_help.txt");
        }
        else if (!strcmp(splits[0], "man") && a == 2 && !strcmp(splits[1],"cp"))
        {
            print_file("mycp_help.txt");
        }else if (!strcmp(splits[0], "man") && a == 2 && !strcmp(splits[1],"mv"))
        {
            print_file("mymv_help.txt");
        }else if (!strcmp(splits[0], "man") && a == 2 && !strcmp(splits[1],"grep"))
        {
            print_file("mygrep_help.txt");
        }else if (!strcmp(splits[0], "man") && a == 2 && !strcmp(splits[1],"ps"))
        {
            print_file("myps_help.txt");
        }
        else if ((!strcmp(splits[0], "hi") || !strcmp(splits[0], "hello")) && a == 1)
            printf("I'm Fetching help..Hold your breathe...\n");
        else if (strlen(splits[0]) != 0)
            printf("Invalid command. Please refer 'help'.\n");
    }
    return 0;
}
