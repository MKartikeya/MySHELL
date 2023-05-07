#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#define MAX_SPACES 10
#define MAX_LEN 100
// done
void myGrep1(char *name, char *word, int flag)
{
    int newline = 0;
    char line[1500];
    FILE *fp = fopen(name, "r");
    if (fp != NULL)
    {
        while (fgets(line, 1000, fp))
        {
            if (strstr(line, word))
            {
                if (flag)
                {
                    printf("\033[35;1m");
                    printf("%s:", name);
                    printf("\033[0m");
                }
                newline = 1;
                printf("%s", line);
            }
        }
        // while (!feof(fp))
        // {
        //     fgets(line, 1000, fp);
        //     if (strstr(line, word) != NULL)
        //     {
        //         // memset(line,1000,0);
        //     }
        // }
        fclose(fp);
        // if(newline) printf("\n");
    }
    else
    {
        // if (!flag)
        //     perror("grep()");
        printf("grep: %s: No such file or directory\n",name);
    }
}
//done
void myGrep2(char *name, char *word, int flag)
{
    long int count = 0;
    FILE *fp = fopen(name, "r");
    if (fp != NULL)
    {
        char temp, line[1000];
        while (fgets(line, 1000, fp))
        {
            if (strstr(line, word))
            {
                count++;
            }
        }
        if (flag)
        {
            printf("\033[35;1m");
            printf("%s:", name);
            printf("\033[0m");
            printf("%ld\n",count);
        }
        else
            printf("%ld\n", count);
            fclose(fp);
        
    }
    else
    {
        // if (!flag)
            // perror("grep(): %s ",name);
            printf("grep: %s: No such file or directory\n",name);
    }
}
//done
void myGrep3(char *name, char *word, int flag)
{
    long int count = 0;
    FILE *fp = fopen(name, "r");
    if (fp != NULL)
    {
        char temp, line[1000];
        while (fgets(line, 1000, fp))
        {
            if (strstr(line, word))
            {
                printf("\033[35;1m");
                printf("%s\n", name);
                printf("\033[0m");
                count++;
                break;
            }
        }
        fclose(fp);
    }
    else
    {
            printf("grep: %s: No such file or directory\n",name);
    }
}
//done
void myGrep4(char *name, char *word)
{
    char line[1500];
    FILE *fp = fopen(name, "r");
    if (fp != NULL)
    {   
        while (fgets(line, 1000, fp))
        {
            if (strstr(line, word))
            {
                printf("%s", line);
            }
        }
        // while (!feof(fp))
        // {
        //     fgets(line, 1000, fp);
        //     if (strstr(line, word) != NULL)
        //     {
        //     }
        // }
        fclose(fp);
    }
    else
    {
         printf("grep: %s: No such file or directory\n",name);
    }
}
///done
void myGrep5(char *name, char *word, int flag)
{
    char line[1500];
    int line_number = 1;
    FILE *fp = fopen(name, "r");
    if (fp != NULL)
    {
        while (fgets(line, 1000, fp))
        {
            if (strstr(line, word))
            {
                if (flag)
                {
                    printf("\033[35;1m");
                    printf("%s:", name);
                    printf("\033[0m");
                }
                printf("%s\n", word);
            }
        }
        fclose(fp);
    }
    else
    {
        printf("grep: %s: No such file or directory\n",name);
    }
}
//done
void myGrep6(char *name, char *word, int flag)
{
    char line[1500];
    long int line_number = 1;
    FILE *fp = fopen(name, "r");
    if (fp != NULL)
    {
        while (fgets(line, 1000, fp))
        {
            if (strstr(line, word))
            {
                if (flag)
                {
                    printf("\033[35;1m");
                    printf("%s:", name);
                    printf("\033[0m");
                }
                printf("%ld:%s", line_number, line);
            }
            line_number++;
        }
        fclose(fp);
    }
    else
    {
        printf("grep: %s: No such file or directory\n",name);
    }
}
void myGrep7(char *name, char *word, int flag)
{
    struct stat stt;
    if (stat(name, &stt) == 0)
    {
        int fd, r, j = 0;
        char temp, line[1000];
        if ((fd = open(name, O_RDONLY)) != -1)
        {
            while ((r = read(fd, &temp, sizeof(char))) != 0)
            {
                if (temp != '\n')
                {
                    line[j] = temp;
                    j++;
                }
                else
                {
                    if (!strcmp(strstr(line, word), word))
                    {

                        if (flag)
                        {
                            printf("%s:", name);
                        }
                        printf("%s\n", line);
                    }
                    memset(line, 0, sizeof(line));
                    j = 0;
                }
            }
        }
    }
    else
    {
        perror("stat()");
    }
}
//done
void myGrep8(char *name, char *word, int flag)
{
    char line[1500];
    FILE *fp = fopen(name, "r");
    if (fp != NULL)
    {
        while (fgets(line, 1000, fp))
        {
            if (!strstr(line, word) && strlen(line)>1)
            {
                if (flag)
                {
                    printf("\033[35;1m");
                    printf("%s:", name);
                    printf("\033[0m");
                }
                printf("%s", line);
            }
        }
        fclose(fp);
    }
    else
    {
        printf("grep: %s: No such file or directory\n",name);
    }
}

void mygrep(char *splits[], int i)
{
    if (!strcmp(splits[0], "grep") && !strcmp(splits[1], "-c") && i > 3)
    {
        int flag = 0;
        if (i > 4)
            flag = 1;
        for (int k = 3; k < i; k++)
        {
            myGrep2(splits[k], splits[2], flag);
        }
    }
    else if (!strcmp(splits[0], "grep") && !strcmp(splits[1], "-l") && i > 3)
    {
        int flag = 0;
        if (i > 4)
            flag = 1;
        for (int k = 3; k < i; k++)
        {
            myGrep3(splits[k], splits[2], flag);
        }
    }
    else if (!strcmp(splits[0], "grep") && !strcmp(splits[1], "-h") && i > 3)
    {
        for (int k = 3; k < i; k++)
        {
            myGrep4(splits[k], splits[2]);
        }
        printf("\n");
    }
    else if (!strcmp(splits[0], "grep") && !strcmp(splits[1], "-o") && i > 3)
    {
        int flag = 0;
        if (i > 4)
            flag = 1;
        for (int k = 3; k < i; k++)
        {
            myGrep5(splits[k], splits[2], flag);
        }
    }
    else if (!strcmp(splits[0], "grep") && !strcmp(splits[1], "-n") && i > 3)
    {
        int flag = 0;
        if (i > 4)
            flag = 1;
        for (int k = 3; k < i; k++)
        {
            myGrep6(splits[k], splits[2], flag);
        }
        printf("\n");
    }
    else if (!strcmp(splits[0], "grep") && !strcmp(splits[1], "-v") && i > 3)
    {
        int flag = 0;
        if (i > 4)
            flag = 1;
        for (int k = 3; k < i; k++)
        {
            myGrep8(splits[k], splits[2], flag);
        }
        printf("\n");
    }
    // done
    else if (!strcmp(splits[0], "grep") && i >= 3)
    {
        int flag = 0;
        if (i > 3)
            flag = 1;
        for (int k = 2; k < i; k++)
        {
            myGrep1(splits[k], splits[1], flag);
        }
        printf("\n");
    }
    else printf("Invalid command. Please refer 'man grep'.\n");
}
