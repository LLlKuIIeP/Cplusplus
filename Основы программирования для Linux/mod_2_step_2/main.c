#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

int main(int argc, char *argv[])
{
        printf("Hello\n");

        DIR *dir = opendir("/home/");
        struct dirent *entry;

        while((entry = readdir(dir)) != NULL) {
                // действия со структурой dirent
                printf("Name: %s\n\tType: %d\n\tNode: %u\n",
                entry->d_name, entry->d_type, entry->d_ino);
        }

        closedir(dir);
        return 0;
}
