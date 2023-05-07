//done
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
#include <fcntl.h>
#include <grp.h>
#include <ctype.h>
#define MAX_SPACES 100

void myPs1()
{
    char dir[256];
    sprintf(dir, "/proc");
    DIR *f = opendir(dir);
    struct dirent *entry;
    while ((entry = readdir(f)) != NULL)
    {
        char *pid = entry->d_name;
        char file_name[256];
        int fd;
        sprintf(file_name, "/proc/%ld/stat", atol(pid));
        char path[256];
        char cur_tty[100];
        sprintf(path, "/proc/self/fd/0");
        int f1 = open(path, O_RDONLY);
        sprintf(cur_tty, "%s", ttyname(f1));
        close(f1);
        sprintf(path, "/proc/%ld/fd/0", atol(pid));
        if (access(path, F_OK))
            continue;
        if (fd = open(path, O_RDONLY) < 0)
            continue;
        if (ttyname(fd) == NULL)
        {
            close(fd);
            continue;
        }
        FILE *data = fopen(file_name, "r");
        char name[256];
        unsigned pi, ppid, psr, sid;
        unsigned long size, rss, utime, stime, c;
        unsigned long long start_time;
        char state, tty[20];
        f1 = open(path, O_RDONLY);
        sprintf(tty, "%s", ttyname(f1));
        close(f1);
        fscanf(data, "%u %s %c %u %*u %u %*u %*u %*s %*s %*s %*s %*s %lu %lu %*s %*s %*s %*s %*s %*s %llu %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %u %lu ", &pi, name, &state, &ppid, &sid, &utime, &stime, &start_time, &psr, &c);
        fclose(data);
        char file_name2[256];
        sprintf(file_name2, "/proc/%u/statm", atoi(pid));
        FILE *stat = fopen(file_name2, "r");
        fscanf(stat, "%lu %lu", &size, &rss);
        fclose(stat);
        stat = fopen("/proc/uptime", "r");
        double uptime;
        fscanf(stat, "%lf", &uptime);
        fclose(stat);
        name[strlen(name) - 1] = '\0';
        char buf[200];
        utime=(int)(double)(utime+stime)/sysconf(_SC_CLK_TCK);
        sprintf(buf,"%02lu:%02lu:%02lu",(utime/3600)%3600,(utime/60)%60,utime%60);
        if (!strcmp(cur_tty, tty))
        {
            printf("%6u %6s %9s %6s\n", pi, tty + 5, buf, name + 1);
        }
    }
}
void myPs2()
{
    char dir[256];
    sprintf(dir, "/proc");
    DIR *f = opendir(dir);
    struct dirent *entry;
    while ((entry = readdir(f)) != NULL)
    {
        char *pid = entry->d_name;
        char file_name[256];
        int fd;
        sprintf(file_name, "/proc/%ld/stat", atol(pid));
        char path[256];
        char cur_tty[100];
        sprintf(path, "/proc/self/fd/0");
        int f1 = open(path, O_RDONLY);
        sprintf(cur_tty, "%s", ttyname(f1));
        close(f1);
        sprintf(path, "/proc/%ld/fd/0", atol(pid));
        if (access(path, F_OK))
            continue;
        if (fd = open(path, O_RDONLY) < 0)
            continue;
        if (ttyname(fd) == NULL)
        {
            close(fd);
            continue;
        }
        FILE *data = fopen(file_name, "r");
        char name[256];
        unsigned pi, ppid, psr, sid, uid;
        unsigned long size, rss, utime, stime, c;
        unsigned long long start_time;
        char state, tty[20];
        f1 = open(path, O_RDONLY);
        sprintf(tty, "%s", ttyname(f1));
        close(f1);
        fscanf(data, "%u %s %c %u %*u %u %*u %*u %*s %*s %*s %*s %*s %lu %lu %*s %*s %*s %*s %*s %*s %llu %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %u %lu", &pi, name, &state, &ppid, &sid, &utime, &stime, &start_time, &psr, &c);
        fclose(data);
        char file_status[100], line[1024];
        sprintf(file_status, "/proc/%d/status", pi);
        FILE *tempfile = fopen(file_status, "r");
        while (fgets(line, sizeof(line), tempfile))
        {
            if (!strncmp(line, "Uid:", 4))
            {
                sscanf(line, "Uid:\t%d", &uid);
                break;
            }
        }
        struct passwd *pw = getpwuid(uid);
        char *temp = pw->pw_name;
        fclose(tempfile);
        char file_name2[256];
        sprintf(file_name2, "/proc/%u/statm", atoi(pid));
        FILE *stat = fopen(file_name2, "r");
        fscanf(stat, "%lu %lu", &size, &rss);
        fclose(stat);
        stat = fopen("/proc/uptime", "r");
        double uptime;
        fscanf(stat, "%lf", &uptime);
        fclose(stat);
        name[strlen(name) - 1] = '\0';
        char buf[200];
        utime=(int)(double)(utime+stime)/sysconf(_SC_CLK_TCK);
        sprintf(buf,"%02lu:%02lu:%02lu",(utime/3600)%3600,(utime/60)%60,utime%60);
        if (!strcmp(cur_tty, tty))
        {
            if (pi == sid)
            {
                continue;
            }
            else
                printf("%6u %6s %9s %6s\n", pi, tty + 5,buf, name + 1);
        }
    }
}
void myPs3()
{
    char dir[256];
    sprintf(dir, "/proc");
    DIR *f = opendir(dir);
    struct dirent *entry;
    while ((entry = readdir(f)) != NULL)
    {
        char *pid = entry->d_name;
        char file_name[256];
        int fd;
        sprintf(file_name, "/proc/%ld/stat", atol(pid));
        char path[256];
        char cur_tty[100];
        sprintf(path, "/proc/self/fd/0");
        int f1 = open(path, O_RDONLY);
        sprintf(cur_tty, "%s", ttyname(f1));
        close(f1);
        sprintf(path, "/proc/%ld/fd/0", atol(pid));
        if (access(path, F_OK))
            continue;
        if (fd = open(path, O_RDONLY) < 0)
            continue;
        if (ttyname(fd) == NULL)
        {
            close(fd);
            continue;
        }
        FILE *data = fopen(file_name, "r");
        char name[256];
        unsigned pi, ppid, psr, sid;
        unsigned long size, rss, utime, stime, c;
        unsigned long long start_time;
        char state, tty[20];
        f1 = open(path, O_RDONLY);
        sprintf(tty, "%s", ttyname(f1));
        close(f1);
        fscanf(data, "%u %s %c %u %*u %u %*u %*u %*s %*s %*s %*s %*s %lu %lu %*s %*s %*s %*s %*s %*s %llu %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %u %lu", &pi, name, &state, &ppid, &sid, &utime, &stime, &start_time, &psr, &c);
        fclose(data);
        char file_name2[256];
        sprintf(file_name2, "/proc/%u/statm", atoi(pid));
        FILE *stat = fopen(file_name2, "r");
        fscanf(stat, "%lu %lu", &size, &rss);
        fclose(stat);
        stat = fopen("/proc/uptime", "r");
        double uptime;
        fscanf(stat, "%lf", &uptime);
        fclose(stat);
        name[strlen(name) - 1] = '\0';
        char buf[200];
        utime=(int)(double)(utime+stime)/sysconf(_SC_CLK_TCK);
        sprintf(buf,"%02lu:%02lu:%02lu",(utime/3600)%3600,(utime/60)%60,utime%60);
        if (!strcmp(cur_tty, tty))
        {
            printf("%6u %6s %9s %s\n", pi, tty + 5,buf, name + 1);
        }
        else
            printf("%6u %6s %9s %s\n", pi,"?", buf,name + 1);
    }
}
void myPs4()
{
    char dir[256];
    sprintf(dir, "/proc");
    DIR *f = opendir(dir);
    struct dirent *entry;
    while ((entry = readdir(f)) != NULL)
    {
        char *pid = entry->d_name;
        char file_name[256];
        int fd;
        sprintf(file_name, "/proc/%ld/stat", atol(pid));
        char path[256];
        char cur_tty[100];
        sprintf(path, "/proc/self/fd/0");
        int f1 = open(path, O_RDONLY);
        sprintf(cur_tty, "%s", ttyname(f1));
        close(f1);
        sprintf(path, "/proc/%ld/fd/0", atol(pid));
        if (access(path, F_OK))
            continue;
        if (fd = open(path, O_RDONLY) < 0)
            continue;
        if (ttyname(fd) == NULL)
        {
            close(fd);
            continue;
        }
        FILE *data = fopen(file_name, "r");
        char name[256];
        unsigned pi, ppid, psr, sid, uid;
        unsigned long size, rss, utime, stime, c;
        unsigned long long start_time;
        char state, tty[20];
        f1 = open(path, O_RDONLY);
        sprintf(tty, "%s", ttyname(f1));
        close(f1);
        fscanf(data, "%u %s %c %u %*u %u %*u %*u %*s %*s %*s %*s %*s %lu %lu %*s %*s %*s %*s %*s %*s %llu %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %u %lu", &pi, name, &state, &ppid, &sid, &utime, &stime, &start_time, &psr, &c);
        fclose(data);
        char file_status[100], line[1024];
        sprintf(file_status, "/proc/%d/status", pi);
        FILE *tempfile = fopen(file_status, "r");
        while (fgets(line, sizeof(line), tempfile))
        {
            if (!strncmp(line, "Uid:", 4))
            {
                sscanf(line, "Uid:\t%d", &uid);
                break;
            }
        }
        struct passwd *pw = getpwuid(uid);
        char *temp = pw->pw_name;
        fclose(tempfile);
        char file_name2[256];
        sprintf(file_name2, "/proc/%u/statm", atoi(pid));
        FILE *stat = fopen(file_name2, "r");
        fscanf(stat, "%lu %lu", &size, &rss);
        fclose(stat);
        stat = fopen("/proc/uptime", "r");
        double uptime;
        fscanf(stat, "%lf", &uptime);
        fclose(stat);
        name[strlen(name) - 1] = '\0';
        time_t t = stime;
        struct tm *tme;
        char buf[200];
        tme = localtime(&t);
        strftime(buf, 200, "%H:%M:%S", tme);
        char buf2[200];
        utime=(int)(double)(utime+stime)/sysconf(_SC_CLK_TCK);
        sprintf(buf2,"%02lu:%02lu:%02lu",(utime/3600)%3600,(utime/60)%60,utime%60);
        if (!strcmp(cur_tty, tty))
        {
            if (pi == sid)
            {
                continue;
            }
            else
                printf("%6s %5u %5u %lu %7lu %6lu %8s %8s %4u %6s %6s\n", temp, pi, ppid, c, size, rss, buf,buf2, psr, tty + 5, name + 1);
        }
    }
}
void myPs5()
{
    char dir[256];
    sprintf(dir, "/proc");
    DIR *f = opendir(dir);
    struct dirent *entry;
    while ((entry = readdir(f)) != NULL)
    {
        char *pid = entry->d_name;
        char file_name[256];
        int fd;
        sprintf(file_name, "/proc/%ld/stat", atol(pid));
        char path[256];
        char cur_tty[100];
        sprintf(path, "/proc/self/fd/0");
        int f1 = open(path, O_RDONLY);
        sprintf(cur_tty, "%s", ttyname(f1));
        close(f1);
        sprintf(path, "/proc/%ld/fd/0", atol(pid));
        if (access(path, F_OK))
            continue;
        if (fd = open(path, O_RDONLY) < 0)
            continue;
        if (ttyname(fd) == NULL)
        {
            close(fd);
            continue;
        }
        FILE *data = fopen(file_name, "r");
        char name[256];
        unsigned pi, ppid, psr, sid, uid;
        unsigned long size, rss, utime, stime, c;
        unsigned long long start_time;
        char state, tty[20];
        f1 = open(path, O_RDONLY);
        sprintf(tty, "%s", ttyname(f1));
        close(f1);
        fscanf(data, "%u %s %c %u %*u %u %*u %*u %*s %*s %*s %*s %*s %lu %lu %*s %*s %*s %*s %*s %*s %llu %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %u %lu", &pi, name, &state, &ppid, &sid, &utime, &stime, &start_time, &psr, &c);
        fclose(data);
        char file_status[100], line[1024];
        sprintf(file_status, "/proc/%d/status", pi);
        FILE *tempfile = fopen(file_status, "r");
        while (fgets(line, sizeof(line), tempfile))
        {
            if (!strncmp(line, "Uid:", 4))
            {
                sscanf(line, "Uid:\t%d", &uid);
                break;
            }
        }
        struct passwd *pw = getpwuid(uid);
        char *temp = pw->pw_name;
        fclose(tempfile);
        char file_name2[256];
        sprintf(file_name2, "/proc/%u/statm", atoi(pid));
        FILE *stat = fopen(file_name2, "r");
        fscanf(stat, "%lu %lu", &size, &rss);
        fclose(stat);
        stat = fopen("/proc/uptime", "r");
        double uptime;
        fscanf(stat, "%lf", &uptime);
        fclose(stat);
        name[strlen(name) - 1] = '\0';
        time_t t = stime;
        struct tm *tme;
        char buf[200];
        tme = localtime(&t);
        strftime(buf, 200, "%H:%M:%S", tme);
        char buf2[200];
        utime=(int)(double)(utime+stime)/sysconf(_SC_CLK_TCK);
        sprintf(buf2,"%02lu:%02lu:%02lu",(utime/3600)%3600,(utime/60)%60,utime%60);
        if (!strcmp(cur_tty, tty))
        {
            printf("%6s %5u %5u %lu %7lu %6lu %8s %8s %4u %6s %6s\n", temp, pi, ppid, c, size, rss, buf,buf2, psr, tty + 5, name + 1);
        }
        else
            printf("%6s %5u %5u %lu %7lu %6lu %8s %8s %4u %6s %6s\n", temp, pi, ppid, c, size, rss, buf,buf2, psr, "?", name + 1);
    }
}

void myps(char *splits[],int i)
{
        if (!strcmp(splits[0], "ps"))
        {
            if (i == 1)
            {
                printf("%6s %6s %9s %6s\n", "PID", "TTY","TIME", "CMD");
                myPs1();
            }
            else if(i==2)
            {

                if (!strcmp(splits[0], "ps") && !strcmp(splits[1], "-a"))
                {
                    printf("%6s %6s %9s %6s\n", "PID", "TTY","TIME", "CMD");
                    myPs2();
                }
                else if (!strcmp(splits[0], "ps") && !strcmp(splits[1], "-e"))
                {
                    printf("%6s %6s %9s %6s\n", "PID", "TTY","TIME", "CMD");
                    myPs3();
                }
                else if (!strcmp(splits[0], "ps") && !strcmp(splits[1], "-aF"))
                {
                    printf("%9s %5s %5s %s %7s %6s %8s %8s %4s %6s %6s\n", "UID", "PID", "PPID", "C", "SZ", "RSS", "STIME","TIME", "PSR", "TTY", "CMD");
                    myPs4();
                }
                else if (!strcmp(splits[0], "ps") && !strcmp(splits[1], "-eF"))
                {
                    printf("%9s %5s %5s %s %7s %6s %8s %8s %4s %6s %6s\n", "UID", "PID", "PPID", "C", "SZ", "RSS", "STIME","TIME", "PSR", "TTY", "CMD");
                    myPs5();
                }
                else printf("Invalid command. Please refer 'man ps'.\n");
            }
            else printf("Invalid command. Please refer 'man ps'.\n");
        }
}
