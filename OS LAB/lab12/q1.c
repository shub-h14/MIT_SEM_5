// Credits - Komal Mathur

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>

void list_files(const char *path) {
    struct dirent *entry;
    struct stat file_stat;
    DIR *dp = opendir(path);

    if (!dp) return;

    while ((entry = readdir(dp)) != NULL) {
        if (strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..")) {
            char full_path[1024];
            snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
            if (stat(full_path, &file_stat) == 0) {
                char time_buf[80];
                strftime(time_buf, sizeof(time_buf), "%b %d %H:%M", localtime(&file_stat.st_mtime));
                printf("%c%s%s %lu %s %s %lld %s %s\n",
                       (S_ISDIR(file_stat.st_mode)) ? 'd' : '-',
                       (file_stat.st_mode & S_IRUSR) ? "r" : "-",
                       (file_stat.st_mode & S_IWUSR) ? "w" : "-",
                       file_stat.st_nlink,
                       getpwuid(file_stat.st_uid)->pw_name,
                       getgrgid(file_stat.st_gid)->gr_name,
                       (long long)file_stat.st_size,
                       time_buf,
                       entry->d_name);
            }
        }
    }
    closedir(dp);
}

int main() {
    list_files(".");
    return 0;
}
