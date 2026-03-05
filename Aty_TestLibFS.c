#include <stdio.h>
#include "libFS.h"

int main() {
    int choice;
    char filename[111];
    char buffer[1024];
    int index;

    while (1) {
        printf("\n___ Menu ___\n");
        printf("1. Create a file 📁\n");
        printf("2. Open a file📂\n");
        printf("3. Write to a file📝\n");
        printf("4. Read from a file📖\n");
        printf("5. Close a file📕\n");
        printf("6. Delete a file\n");
        printf("7. Exit\n");
        printf("Enter any number gurllyyy: ");
        scanf("%d", &choice);
        getchar(); // clear newline

        switch (choice) {
            case 1:
                printf("Enter filename: ");
                scanf("%s", filename);
                fileCreate(filename);
                break;

            case 2:
                printf("Enter filename: ");
                scanf("%s", filename);
                index = fileOpen(filename);
                break;

            case 3:
                printf("Enter text: ");
                getchar();
                fgets(buffer, sizeof(buffer), stdin);
                fileWrite(index, buffer);
                break;

            case 4:
                index = fileOpen(filename);
                int n = fileRead(index, buffer, sizeof(buffer));
                buffer[n] = '\0';
                printf("File contents:\n%s\n", buffer);
                break;

            case 5:
                printf("Bye..byeeee👋🥲 ")
                fileClose(index);
                break;

            case 6:
                printf("Enter filename: ");
                scanf("%s", filename);
                fileDelate(filename);
                break;

            case 7:
                return 0;
        }
    }
}
