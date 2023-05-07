#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#define MAX_SPACES 100
#define MAX_LEN 100
struct data
{
        char perms[10];
        int link;
        char *owner;
        char *group;
        long long int size;
        char *time;
        char *file_name;
        long long int raw_time;
        int inode;
};
struct data modData[100];
int count_check()
{
        int file_count = 0;
        DIR *dirp;
        struct dirent *entry;

        dirp = opendir(".");
        while ((entry = readdir(dirp)) != NULL)
        {
                struct stat cur_fil;
                stat(entry->d_name, &cur_fil);
                if (S_ISREG(cur_fil.st_mode) || S_ISDIR(cur_fil.st_mode))
                {
                        file_count++;
                }
        }
        closedir(dirp);
        return file_count;
}
int comparator(const void *p, const void *q)
{
        if (((struct data *)p)->size == ((struct data *)q)->size)
                return 0;
        else if (((struct data *)p)->size > ((struct data *)q)->size)
                return 1;
        else
                return -1;
}
int comparator2(const void *p, const void *q)
{
        if (((struct data *)p)->raw_time == ((struct data *)q)->raw_time)
                return 0;
        else if (((struct data *)p)->raw_time < ((struct data *)q)->raw_time)
                return 1;
        else
                return -1;
}
int comparator3(const void *p, const void *q)
{
        return strcmp(((struct data *)p)->file_name,((struct data *)q)->file_name);
}
void myLs1(int data_count)
{
        for (int i = 0; i < data_count; i++)
        {
                printf("%-12s", modData[i].file_name);
        }
        printf("\n");
}
void myLs2(int count)
{
        for (int i = 0; i < count; i++)
        {
                // print_perm(modData);
                printf("%c%c%c%c%c%c%c%c%c%c ", modData[i].perms[0], modData[i].perms[1], modData[i].perms[2], modData[i].perms[3], modData[i].perms[4], modData[i].perms[5], modData[i].perms[6], modData[i].perms[7], modData[i].perms[8], modData[i].perms[9]);
                // print_link(modData);
                printf("%d ", modData[i].link);
                // print_owner(modData);
                printf("%s ", modData[i].owner);
                // print_grp(modData);
                printf("%s ", modData[i].group);
                // print_size(modData);
                printf("%8lld ", modData[i].size);
                // print_time(modData);
                time_t t = modData[i].raw_time;
                struct tm *tm;
                char buf[200];
                tm = localtime(&t);
                strftime(buf, sizeof(buf), "%b %d %H:%M", tm);
                modData[i].time = buf;
                printf("%s ", buf);
                // print_name(modData);
                printf("%s ", modData[i].file_name);
                printf("\n");
        }
}
void myLs3(int data_count)
{
        qsort(modData, data_count, sizeof(struct data), comparator);
        for (int i = 0; i < data_count; i++)
        {
                // print_name(modData);
                printf("%s ", modData[i].file_name);
                printf(" ");
        }
        printf("\n");
}
void myLs4(int data_count)
{
        qsort(modData, data_count, sizeof(struct data), comparator2);
        for (int i = 0; i < data_count; i++)
        {
                // print_name(modData);
                printf("%s ", modData[i].file_name);
        }
        printf("\n");
}
void myLs5(int data_count)
{
        qsort(modData, data_count, sizeof(struct data), comparator2);
        myLs2(data_count);
}
void myLs6(int data_count)
{
        for (int i = 0; i < data_count; i++)
        {
                // print_inode(modData);
                printf("%d ", modData[i].inode);
                // print_name(modData);
                printf("%s ", modData[i].file_name);
                printf(" ");
        }
        printf("\n");
}
void myLs7(int data_count)
{
        for (int i = 0; i < data_count; i++)
        {
                // print_perm(modData);
                printf("%c%c%c%c%c%c%c%c%c%c ", modData[i].perms[0], modData[i].perms[1], modData[i].perms[2], modData[i].perms[3], modData[i].perms[4], modData[i].perms[5], modData[i].perms[6], modData[i].perms[7], modData[i].perms[8], modData[i].perms[9]);
                // print_link(modData);
                printf("%d ", modData[i].link);
                // print_owner(modData);
                printf("%s ", modData[i].owner);
                // print_size(modData);
                printf("%8lld ", modData[i].size);
                // print_time(modData);
                time_t t = modData[i].raw_time;
                struct tm *tm;
                char buf[200];
                tm = localtime(&t);
                strftime(buf, sizeof(buf), "%b %d %H:%M", tm);
                modData[i].time = buf;
                printf("%s ", buf);
                // print_name(modData);
                printf("%s ", modData[i].file_name);
                printf("\n");
        }
}
void myLs8(int data_count)
{
        for (int i = 0; i < data_count; i++)
        {
                printf("\"%s\" ", modData[i].file_name);
        }
        printf("\n");
}

void myls(char *splits[], int j)
{        
        int i = 0;
        DIR *dir;
        struct dirent *ent;
        dir = opendir(".");
        char fil_name[100];
        while ((ent = readdir(dir)) != NULL)
        {
                if(ent->d_name[0]!='.'){
                struct stat cur;
                struct passwd *pw;
                struct group *grp;
                // strcpy(modData[i].file_name, ent->d_name);
                modData[i].file_name= ent->d_name;
                stat(modData[i].file_name, &cur);
                modData[i].inode = cur.st_ino;
                modData[i].perms[0] = (S_ISDIR(cur.st_mode)) ? 'd' : '-';
                modData[i].perms[1] = (cur.st_mode & S_IRUSR) ? 'r' : '-';
                modData[i].perms[2] = (cur.st_mode & S_IWUSR) ? 'w' : '-';
                modData[i].perms[3] = (cur.st_mode & S_IXUSR) ? 'x' : '-';
                modData[i].perms[4] = (cur.st_mode & S_IRGRP) ? 'r' : '-';
                modData[i].perms[5] = (cur.st_mode & S_IWGRP) ? 'w' : '-';
                modData[i].perms[6] = (cur.st_mode & S_IXGRP) ? 'x' : '-';
                modData[i].perms[7] = (cur.st_mode & S_IROTH) ? 'r' : '-';
                modData[i].perms[8] = (cur.st_mode & S_IWOTH) ? 'w' : '-';
                modData[i].perms[9] = (cur.st_mode & S_IXOTH) ? 'x' : '-';
                modData[i].size = cur.st_size;
                pw = getpwuid(cur.st_uid);

                modData[i].owner = pw->pw_name;
                grp = getgrgid(cur.st_gid);
                modData[i].group = grp->gr_name;
                modData[i].link = cur.st_nlink;
                modData[i].raw_time = cur.st_mtime;
                time_t t = modData[i].raw_time;
                struct tm *tm;
                char buf[200];
                tm = localtime(&t);
                strftime(buf, sizeof(buf), "%b %d %H:%M", tm);
                modData[i].time=buf;
                i++;
                }
        }
        int count=i;
        closedir(dir);
        qsort(modData, count, sizeof(struct data), comparator3);
        if (j == 1)
        {
                myLs1(i);
        }
        else if (j == 2)
        {
                if (!strcmp(splits[1], "-l"))
                {
                        myLs2(i);
                }
                else if (!strcmp(splits[1], "-s"))
                {
                        myLs3(i);
                }
                else if (!strcmp(splits[1], "-t"))
                        myLs4(i);
                else if (!strcmp(splits[1], "-lt"))
                        myLs5(i);
                else if (!strcmp(splits[1], "-i"))
                        myLs6(i);
                else if (!strcmp(splits[1], "-g"))
                        myLs7(i);
                else if (!strcmp(splits[1], "-q"))
                        myLs8(i);
                else printf("Invalid command. Please refer 'man ls'.\n");

        }
        else printf("Invalid command. Please refer 'man ls'.\n");
}