// Credits - Komal Mathur

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void list_files(const char *base_path) {
    struct dirent *entry;
    char path[1024];
    DIR *dp = opendir(base_path);

    if (dp == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dp)) != NULL) {
        // Skip the current and parent directories
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Create the full path
        snprintf(path, sizeof(path), "%s/%s", base_path, entry->d_name);

        // Print the file name
        printf("%s\n", path);

        // If the entry is a directory, recursively call list_files
        if (entry->d_type == DT_DIR) {
            list_files(path);
        }
    }

    closedir(dp);
}

int main() {
    const char *path = "."; // Start from the current directory
    list_files(path);
    return 0;
}
