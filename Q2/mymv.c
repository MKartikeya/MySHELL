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
int isDir(const char *);

void myMv1(char *source, char *dest)
{
    int i, fd1, fd2;
    char *file1, *file2, buf[2];
    file1 = source;
    file2 = dest;
    fd1 = open(file1, O_RDONLY, 0777);
    fd2 = creat(file2, 0777);
    while (i = read(fd1, buf, 1) > 0)
        write(fd2, buf, 1);
    remove(file1);
    close(fd1);
    close(fd2);
}
void smyMv1(char *source, char *dest, int flag)
{
    int isitDir = isDir(dest);
    if (isitDir)
    {
        char buffer[1024];
        int files[2];
        ssize_t count;

        /* Check for insufficient parameters */
        files[0] = open(source, O_RDONLY);
        if (files[0] == -1)
        { /* Check if file opened */
            printf("%s: No file or directory found.\n", source);
            return;
        }
        chdir(dest);
        files[1] = open(source, O_WRONLY | O_CREAT, S_IRUSR);
        if (files[1] == -1) /* Check if file opened (permissions problems ...) */
        {
            close(files[0]);
            printf("%s: File couldn't br created.\n", dest);
            return;
        }

        while ((count = read(files[0], buffer, sizeof(buffer))) != 0)
            write(files[1], buffer, count);
        close(files[0]);
        close(files[1]);
        chdir("..");
        remove(source);
    }
    else
    {
        char buffer[1024];
        int files[2];
        ssize_t count;

        /* Check for insufficient parameters */
        files[0] = open(source, O_RDONLY);
        if (files[0] == -1)
        { /* Check if file opened */
            printf("%s: No file or directory found.\n", source);
            return;
        }
        files[1] = open(dest, O_WRONLY | O_CREAT, S_IRUSR);
        if (files[1] == -1) /* Check if file opened (permissions problems ...) */
        {
            close(files[0]);
            printf("%s: File couldn't be created or Permissions not allowed.\n", dest);
            return;
        }

        while ((count = read(files[0], buffer, sizeof(buffer))) != 0)
            write(files[1], buffer, count);
        close(files[0]);
        close(files[1]);
        remove(source);
    }
    if (flag)
        printf("'%s' -> '%s'\n", source, dest);
}

void myMv2(char *splits[], int len)
{
    int i, fd1, fd2;
    char *file1, *file2, buf[2];
    file1 = splits[2];
    file2 = splits[3];
    remove(file2);
    fd1 = open(file1, O_RDONLY, 0777);
    fd2 = creat(file2, 0777);
    while (i = read(fd1, buf, 1) > 0)
        write(fd2, buf, 1);
    remove(file1);
    close(fd1);
    close(fd2);
}
void smyMv2(char *splits[], int len)
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
        if (files[0] == -1)
        { /* Check if file opened */
            printf("%s: No file or directory found.\n", splits[i]);
            return;
        }
        if (!chdir(splits[len - 1]))
        {
            files[1] = open(splits[i], O_WRONLY | O_CREAT, S_IRUSR);
            if (files[1] == -1) /* Check if file opened (permissions problems ...) */
            {
                close(files[0]);
                printf("%s: File couldn't be created or Permissions not allowed.\n", splits[len - 1]);
                return;
            }
            while ((count = read(files[0], buffer, sizeof(buffer))) != 0)
            {
                write(files[1], buffer, count);
            }
            close(files[0]);
            close(files[1]);
            chdir("..");
            remove(splits[i]);
        }
    }
}
void myMv3(char *splits[], int len)
{
    int i, fd1, fd2;
    char *file1, *file2, buf[2];
    file1 = splits[2];
    file2 = splits[3];
    int fd3 = open(splits[3], O_RDONLY);
    if (fd3 == -1)
    {
        fd1 = open(file1, O_RDONLY, 0777);
        fd2 = creat(file2, 0777);
        while (i = read(fd1, buf, 1) > 0)
            write(fd2, buf, 1);
        remove(file1);
        close(fd1);
        close(fd2);
    }
    else
    {
        return;
    }
}


void smyMv3(char *splits[], int len)
{
    int files[2];
    files[0] = open(splits[2], O_RDONLY|O_WRONLY);
    if (files[0] == -1)
    { /* Check if file opened */
        printf("%s: No file or directory found.\n", splits[2]);
        return;
    }

    close(files[0]);
    remove(splits[len - 1]);
    smyMv1(splits[2], splits[len - 1], 0);
    remove(splits[2]);
}
void myMv4(char *splits[], int len)
{
    int i, fd1, fd2;
    char *file1, *file2, buf[2];
    file1 = splits[2];
    file2 = splits[3];
    int fd3 = open(splits[3], O_RDONLY);
    if (fd3 == -1)
    {
        fd1 = open(file1, O_RDONLY, 0777);
        fd2 = creat(file2, 0777);
        while (i = read(fd1, buf, 1) > 0)
            write(fd2, buf, 1);
        remove(file1);
        close(fd1);
        close(fd2);
    }
    else
    {
        char *dest = "random.txt";
        myMv1(splits[3], dest);
        myMv1(splits[2], splits[3]);
        rename(dest, strcat(splits[3], "~"));
    }
}

void myMv5(char *source, char *dest)
{
    printf("'%s' -> '%s'\n", source, dest);
    myMv1(source, dest);
}

void myMv6(char *splits[], int len)
{
    if (!chdir(splits[len - 1]))
    {
        chdir("..");
    }

    else
    {
        if (mkdir(splits[len - 1], 0777))
        {
            printf("couldn't make such directory\n");
            return;
        }
    }
    for (int i = 1; i < len - 1; i++)
    {
        char buffer[1024];
        int files[2];
        ssize_t count;
        files[0] = open(splits[i], O_RDONLY);
        if (files[0] == -1) /* Check if file opened */
            return;
        if (!chdir(splits[len - 1]))
        {
            chdir(splits[len - 1]);
            files[1] = open(splits[i], O_WRONLY | O_CREAT, S_IRUSR);
            if (files[1] == -1) /* Check if file opened (permissions problems ...) */
            {
                close(files[0]);
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
        remove(splits[i]);
    }
}

void mymv(char *splits[], int i)
{
    if (!strcmp(splits[0], "mv") && i == 3)
    {
        smyMv1(splits[1], splits[2], 0);
    }
    else if (!strcmp(splits[0], "mv") && i == 4 && !strcmp(splits[1], "-f"))
    {
        smyMv3(splits, i);
    }
    else if (!strcmp(splits[0], "mv") && i == 4 && !strcmp(splits[1], "-n"))
    {
        myMv3(splits, i);
    }
    else if (!strcmp(splits[0], "mv") && i == 4 && !strcmp(splits[1], "-b"))
    {
        myMv4(splits, i);
    }
    else if (!strcmp(splits[0], "mv") && i == 4 && !strcmp(splits[1], "-v"))
    {
        smyMv1(splits[2], splits[3],1);
    }
    else if (!strcmp(splits[0], "mv") && i >= 4)
        smyMv2(splits, i);
    else printf("Invalid command. Please refer 'man mv'.\n");
}
