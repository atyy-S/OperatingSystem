#include <stdio.h>
#include "Aty_libFS.h"

int main() {
    int choice;
    char filename[111];
    char buffer[1024];
    int index = -1;   // no file open initially

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
        getchar();

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
                if (index < 0) printf("Failed to open file.\n");
                break;

            case 3:
                if (index < 0) {
                    printf("No file is open.\n");
                    break;
                }
                printf("Enter text: ");
                getchar();
                fgets(buffer, sizeof(buffer), stdin);
                fileWrite(index, buffer);
                fileClose(index);   // required by assignment
                index = -1;
                break;

            case 4:
                if (index < 0) {
                    printf("Enter filename: ");
                    scanf("%s", filename);
                    index = fileOpen(filename);
                    if (index < 0) break;
                }
                int n = fileRead(index, buffer, sizeof(buffer)-1);
                if (n > 0) {
                    buffer[n] = '\0';
                    printf("File contents:\n%s\n", buffer);
                }
                fileClose(index);
                index = -1;
                break;

            case 5:
                if (index >= 0) {
                    fileClose(index);
                    index = -1;
                } else {
                    printf("No file is open.\n");
                }
                break;

            case 6:
                printf("Enter filename: ");
                scanf("%s", filename);
                fileDelete(filename);
                break;

            case 7:
                printf("Byeee..bye... 🥲 \n");
                return 0;
        }
    }
}
