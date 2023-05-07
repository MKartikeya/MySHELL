#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <ctype.h>
#define MAX_SPACES 100
#define MAX_LEN 100
int isDir(const char* fileName)
{
    struct stat path;

    stat(fileName, &path);

    return S_ISDIR(path.st_mode);
}
void myCp1(char *source, char *dest,int flag)
{
    int isitDir=isDir(dest);
    if(isitDir){
    char buffer[1024];
    int files[2];
    ssize_t count;

    /* Check for insufficient parameters */
    files[0] = open(source, O_RDONLY);
    if (files[0] == -1){ /* Check if file opened */
        printf("%s: No file or directory found.\n",source);
        return;}
    chdir(dest);
    files[1] = open(source, O_WRONLY | O_CREAT, S_IRUSR);
    if (files[1] == -1) /* Check if file opened (permissions problems ...) */
    {
        close(files[0]);
        printf("%s: File couldn't br created.\n",dest);
        return;
    }

    while ((count = read(files[0], buffer, sizeof(buffer))) != 0)
        write(files[1], buffer, count);
    close(files[0]);
    close(files[1]);
    chdir("..");
    }
    else{
    char buffer[1024];
    int files[2];
    ssize_t count;

    /* Check for insufficient parameters */
    files[0] = open(source, O_RDONLY);
    if (files[0] == -1){/* Check if file opened */
    printf("%s: No file or directory found.\n",source);
        return;}
    files[1] = open(dest, O_WRONLY | O_CREAT, S_IRUSR);
    if (files[1] == -1) /* Check if file opened (permissions problems ...) */
    {
        close(files[0]);
        printf("%s: File couldn't be created or Permissions not allowed.\n",dest);
        return;
    }

    while ((count = read(files[0], buffer, sizeof(buffer))) != 0)
        write(files[1], buffer, count);
    close(files[0]);
    close(files[1]);
    }
    if(flag) printf("'%s' -> '%s'\n",source,dest);
}
//done
void myCp2(char *splits[], int len)
{
    if (!chdir(splits[len - 1]))
    {
        chdir("..");
    }

    else
    {
        if (mkdir(splits[len - 1], 0777))
        {
            printf("coukdn't make such directory\n");
            return;
        }
    }
    for (int i = 1; i < len - 1; i++)
    {
        char buffer[1024];
        int files[2];
        ssize_t count;
        files[0] = open(splits[i], O_RDONLY);
        if (files[0] == -1){ /* Check if file opened */
            printf("%s: No file or directory found.\n",splits[i]);
            return;}
        if (!chdir(splits[len - 1]))
        {
            files[1] = open(splits[i], O_WRONLY | O_CREAT, S_IRUSR);
            if (files[1] == -1) /* Check if file opened (permissions problems ...) */
            {
                close(files[0]);
                printf("%s: File couldn't be created or Permissions not allowed.\n",splits[len-1]);
                return;
            }
            while ((count = read(files[0], buffer, sizeof(buffer))) != 0)
            {
                write(files[1], buffer, count);
            }
            close(files[0]);
            close(files[1]);
            chdir("..");
        }
    }
}
//done
void myCp3(char *splits[], int len)
{
    FILE *ptr=fopen(splits[3],"r");
    if(ptr!=NULL){
        fclose(ptr);
    printf("The file %s already exits.Do you want to overwrite [Y/N]?: ", splits[len - 1]);
    char proceed;
    scanf("%c", &proceed);
    if (proceed=='Y' || proceed=='y')
    {
        char buffer[1024];
        int files[2];
        ssize_t count;
        /*Check for insufficient parameters */
        files[0] = open(splits[2], O_RDONLY);
        if (files[0] == -1) /* Check if file opened */
            return;
            files[1] = open(splits[len-1], O_WRONLY );
            if (files[1] == -1) /* Check if file opened (permissions problems ...) */
            {
                close(files[0]);
                printf("Permission denied.It is not a writable file\n");
                return;
            }
            close(files[1]);
            fclose(fopen(splits[len-1], "w"));
            files[1] = open(splits[len-1], O_WRONLY );

            while ((count = read(files[0], buffer, sizeof(buffer))) != 0)
                write(files[1], buffer, count);
            close(files[0]);
            close(files[1]);
    }
    else return;
    }
    else myCp1(splits[2],splits[3],0);
}
//done
void myCp4(char *splits[], int len)
{
    myCp1(splits[3], "random",0);
    myCp1(splits[2],splits[3],0);
    char *dest = strcat(splits[len - 1], "~");
    rename("random",dest);

}
//done
void myCp5(char *splits[], int len)
{
    char buffer[1024];
    int files[2];
    ssize_t count;
    /* Check for insufficient parameters */
    files[0] = open(splits[2], O_RDONLY);
    if (files[0] == -1) /* Check if file opened */
        return;
    files[1] = open(splits[len - 1], O_WRONLY);
    if (files[1] == -1) /* Check if file opened (permissions problems ...) */
    {
        close(files[0]);
        remove(splits[len - 1]);
        myCp1(splits[2], splits[len - 1],0);
    }
    else
    {
        while ((count = read(files[0], buffer, sizeof(buffer))) != 0)
            write(files[1], buffer, count);
        close(files[0]);
        close(files[1]);
    }
}

void mycp(char *splits[],int i)
{
        if (!strcmp(splits[0], "cp") && i == 3)
        {
            myCp1(splits[1], splits[2],0);
        }
        else if (!strcmp(splits[0], "cp") && !strcmp(splits[1], "-i") && i == 4)
        {
            myCp3(splits, i);
        }
        else if (!strcmp(splits[0], "cp") && !strcmp(splits[1], "-b") && i == 4)
        {
            myCp4(splits, i);
        }
        else if (!strcmp(splits[0], "cp") && !strcmp(splits[1], "-f") && i == 4)
        {
            myCp5(splits, i);
        }
        else if (!strcmp(splits[0], "cp") && !strcmp(splits[1], "-v") && i == 4)
        {
            myCp1(splits[2],splits[3],1);
        }
        else if (!strcmp(splits[0], "cp") && i > 3)
        {
            myCp2(splits, i);
        }
        else printf("Invalid command. Please refer 'man cp'.\n");
    
}
