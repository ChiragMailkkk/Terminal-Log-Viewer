/*
 * Terminal Log Viewer
 * A beginner-friendly C command-line application.
 *
 * Features:
 * 1. Display all log entries
 * 2. Search entries using a keyword
 * 3. Filter entries by log level (INFO, WARNING, ERROR)
 * 4. Count total entries and entries by level
 *
 * Compile: gcc main.c -o logviewer
 * Run:     ./logviewer
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE 512
#define MAX_FILE_NAME 256

void remove_newline(char *text) {
    text[strcspn(text, "\n")] = '\0';
}

void to_lowercase(char *text) {
    int i;
    for (i = 0; text[i] != '\0'; i++) {
        text[i] = (char)tolower((unsigned char)text[i]);
    }
}

int contains_word(const char *line, const char *keyword) {
    char line_copy[MAX_LINE];
    char keyword_copy[MAX_LINE];

    snprintf(line_copy, sizeof(line_copy), "%s", line);
    snprintf(keyword_copy, sizeof(keyword_copy), "%s", keyword);

    to_lowercase(line_copy);
    to_lowercase(keyword_copy);

    return strstr(line_copy, keyword_copy) != NULL;
}

void display_logs(const char *filename) {
    FILE *file = fopen(filename, "r");
    char line[MAX_LINE];
    int line_number = 0;

    if (file == NULL) {
        printf("\nError: Could not open '%s'. Check that the file exists.\n", filename);
        return;
    }

    printf("\n========== LOG ENTRIES ==========\n");
    while (fgets(line, sizeof(line), file) != NULL) {
        line_number++;
        printf("%3d | %s", line_number, line);
        if (strchr(line, '\n') == NULL) {
            printf("\n");
        }
    }

    if (line_number == 0) {
        printf("The log file is empty.\n");
    }

    printf("=================================\n");
    printf("Total lines displayed: %d\n", line_number);
    fclose(file);
}

void search_logs(const char *filename) {
    FILE *file = fopen(filename, "r");
    char line[MAX_LINE];
    char keyword[MAX_LINE];
    int line_number = 0;
    int matches = 0;

    if (file == NULL) {
        printf("\nError: Could not open '%s'.\n", filename);
        return;
    }

    printf("\nEnter keyword to search: ");
    if (fgets(keyword, sizeof(keyword), stdin) == NULL) {
        fclose(file);
        return;
    }
    remove_newline(keyword);

    if (keyword[0] == '\0') {
        printf("Search keyword cannot be empty.\n");
        fclose(file);
        return;
    }

    printf("\n========== SEARCH RESULTS ==========\n");
    while (fgets(line, sizeof(line), file) != NULL) {
        line_number++;
        if (contains_word(line, keyword)) {
            printf("%3d | %s", line_number, line);
            if (strchr(line, '\n') == NULL) {
                printf("\n");
            }
            matches++;
        }
    }

    if (matches == 0) {
        printf("No matching entries found.\n");
    } else {
        printf("Matching entries: %d\n", matches);
    }
    printf("====================================\n");
    fclose(file);
}

void filter_logs(const char *filename) {
    FILE *file = fopen(filename, "r");
    char line[MAX_LINE];
    char level[20];
    int line_number = 0;
    int matches = 0;

    if (file == NULL) {
        printf("\nError: Could not open '%s'.\n", filename);
        return;
    }

    printf("\nChoose log level (INFO / WARNING / ERROR): ");
    if (fgets(level, sizeof(level), stdin) == NULL) {
        fclose(file);
        return;
    }
    remove_newline(level);

    if (level[0] == '\0') {
        printf("Log level cannot be empty.\n");
        fclose(file);
        return;
    }

    printf("\n========== %s LOGS ==========\n", level);
    while (fgets(line, sizeof(line), file) != NULL) {
        line_number++;
        if (contains_word(line, level)) {
            printf("%3d | %s", line_number, line);
            if (strchr(line, '\n') == NULL) {
                printf("\n");
            }
            matches++;
        }
    }

    if (matches == 0) {
        printf("No entries found for this level.\n");
    } else {
        printf("Entries found: %d\n", matches);
    }
    printf("==============================\n");
    fclose(file);
}

void show_statistics(const char *filename) {
    FILE *file = fopen(filename, "r");
    char line[MAX_LINE];
    int total = 0;
    int info = 0;
    int warning = 0;
    int error = 0;

    if (file == NULL) {
        printf("\nError: Could not open '%s'.\n", filename);
        return;
    }

    while (fgets(line, sizeof(line), file) != NULL) {
        total++;
        if (contains_word(line, "INFO")) {
            info++;
        } else if (contains_word(line, "WARNING")) {
            warning++;
        } else if (contains_word(line, "ERROR")) {
            error++;
        }
    }

    printf("\n========== LOG STATISTICS ==========\n");
    printf("Total log entries : %d\n", total);
    printf("INFO entries      : %d\n", info);
    printf("WARNING entries   : %d\n", warning);
    printf("ERROR entries     : %d\n", error);
    printf("====================================\n");

    fclose(file);
}

int main(int argc, char *argv[]) {
    char filename[MAX_FILE_NAME] = "sample.log";
    char input[20];
    int choice;

    if (argc >= 2) {
        snprintf(filename, sizeof(filename), "%s", argv[1]);
    }

    printf("====================================\n");
    printf("          TERMINAL LOG VIEWER       \n");
    printf("====================================\n");
    printf("Log file: %s\n", filename);

    do {
        printf("\n--------------- MENU ---------------\n");
        printf("1. View all logs\n");
        printf("2. Search logs by keyword\n");
        printf("3. Filter logs by level\n");
        printf("4. View log statistics\n");
        printf("5. Exit\n");
        printf("------------------------------------\n");
        printf("Enter your choice: ");

        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("\nInput ended. Exiting...\n");
            break;
        }

        if (sscanf(input, "%d", &choice) != 1) {
            printf("Invalid input. Please enter a number from 1 to 5.\n");
            continue;
        }

        switch (choice) {
            case 1:
                display_logs(filename);
                break;
            case 2:
                search_logs(filename);
                break;
            case 3:
                filter_logs(filename);
                break;
            case 4:
                show_statistics(filename);
                break;
            case 5:
                printf("\nThank you for using Terminal Log Viewer!\n");
                break;
            default:
                printf("Invalid choice. Please select between 1 and 5.\n");
        }
    } while (choice != 5);

    return 0;
}
