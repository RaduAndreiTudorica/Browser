// Copyright 2025 <Tudorica Radu Andrei>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "web_struct.h"

const char functions[][50] = {
    "NEW_TAB",        // 0
    "CLOSE",          // 1
    "NEXT",           // 2
    "PREV",           // 3
    "BACKWARD",       // 4
    "FORWARD",        // 5
    "PRINT",          // 6
    "PRINT_HISTORY",  // 7
    "OPEN",           // 8
    "PAGE",           // 9
};

int main() {
    FILE *file = fopen("tema1.in", "r");
    if (!file) {
        printf("Failed to open file\n");
        return 1;
    }
    // am pus chestia asta pentru ca nu stiam ce face in general checker-ul
    FILE *clean = fopen("tema1.out", "w");
    fclose(clean);

    BrowserNode browser = init_browser();
    if (!browser) {
        fclose(file);
        return 1;
    }

    int index = 0;
    char line[256];

    fgets(line, sizeof(line), file);
    sscanf(line, "%d", &index);

    Stack pages = init_stack();
    if (!pages) {
        fclose(file);
        return 1;
    }

    while (index--) {
        int id = 0;
        char url[50];
        char *description;

        fgets(line, sizeof(line), file);
        sscanf(line, "%d", &id);
        fgets(url, sizeof(url), file);

        url[strcspn(url, "\n")] = 0;
        fgets(line, sizeof(line), file);
        description = malloc(strlen(line) + 1);
        if (!description) {
            printf("Memory allocation failed for description\n");
            fclose(file);
            return 1;
        }

        strncpy(description, line, strlen(line) + 1);
        description[strcspn(description, "\n")] = 0;

        PageNode page = create_page(id, url, description);

        if (!page) {
            free(description);
            fclose(file);
            return 1;
        }
        free(description);
        pages = insert_page(pages, page);
    }
    char command[50];
    int id_tab = 0;

    fscanf(file, "%d", &index);
    fgets(command, sizeof(command), file);

    while (index--) {
        fgets(command, sizeof(command), file);
        command[strcspn(command, "\n")] = 0;
        for (int i = 0; i < 10; i++) {
            if (i < 6 && strstr(command, functions[i])) {
                if (i == 0) {
                    id_tab += 1;
                    new_tab(browser, id_tab);
                } else if (i == 1) {
                    close(browser);
                } else if (i == 2) {
                    next(browser);
                } else if (i == 3) {
                    prev(browser);
                } else if (i == 4) {
                    backward(browser);
                } else if (i == 5) {
                    forward(browser);
                }
                break;
            } else if (i == 6 && strcmp(command, "PRINT") == 0) {
                print(browser);
            } else if (i >= 7 && strstr(command, functions[i])) {
                char *p = strstr(command, " ");
                int id = atoi(p + 1);

                if (i == 7) {
                    print_history(browser, id);
                } else if (i == 8) {
                    open(browser, id);
                } else if (i == 9) {
                    page(browser, id, pages);
                }
            }
        }
    }

    pages = free_stack(pages);
    browser = free_browser(browser);
    fclose(file);
}
