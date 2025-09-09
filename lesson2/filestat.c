#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <time.h>

const char *epoch_to_date(struct stat st)
{
    static char timebuf[64];
    struct tm *tm_info = localtime(&st.st_mtime);
    strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M:%S", tm_info);
    return timebuf;
}

void list_files(const char *dirpath) {
    DIR *dir;
    struct dirent *entry;
    struct stat st;
    char fullpath[1024];

    dir = opendir(dirpath);
    if (!dir) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        // Skip . and ..
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(fullpath, sizeof(fullpath), "%s/%s", dirpath, entry->d_name);

        if (lstat(fullpath, &st) == -1) {
            perror("lstat");
            continue;
        }

        printf("%s: ", fullpath);

        if (S_ISREG(st.st_mode)) {
            printf("regular file, file size: %ld bytes, last modified: %s\n",st.st_size, epoch_to_date(st));
        } else if (S_ISDIR(st.st_mode)) {
            printf("directory, file size: %ld bytes, last modified: %s\n",st.st_size, epoch_to_date(st));
        } else if (S_ISLNK(st.st_mode)) {
            printf("symlink, file size: %ld bytes, last modified: %s\n",st.st_size, epoch_to_date(st));
        } else if (S_ISCHR(st.st_mode)) {
            printf("character device, file size: %ld bytes, last modified: %s\n",st.st_size, epoch_to_date(st));
        } else if (S_ISBLK(st.st_mode)) {
            printf("block device, file size: %ld bytes, last modified: %s\n",st.st_size, epoch_to_date(st));
        } else if (S_ISFIFO(st.st_mode)) {
            printf("FIFO/pipe, file size: %ld bytes, last modified: %s\n",st.st_size, epoch_to_date(st));
        } else if (S_ISSOCK(st.st_mode)) {
            printf("socket, file size: %ld bytes, last modified: %s\n",st.st_size, epoch_to_date(st));
        } else {
            printf("unknown\n");
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <directory_path>\n", argv[0]);
        return EXIT_FAILURE;
    }

    list_files(argv[1]);
    return EXIT_SUCCESS;
}
