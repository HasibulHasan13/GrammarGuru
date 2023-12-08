#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Define a structure to represent a node in the linked list
struct Node {
    char word[100];
    struct Node* next;
};

// Define a structure to represent a linked list
struct LinkedList {
    struct Node* head;
};

// Function to create an empty linked list
struct LinkedList* createLinkedList() {
    struct LinkedList* list = (struct LinkedList*)malloc(sizeof(struct LinkedList));
    list->head = NULL;
    return list;
}

// Function to insert a word into the linked list
void insert(struct LinkedList* list, const char* word) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->word, word);
    newNode->next = list->head;
    list->head = newNode;
}

// Function to check if a word is in the linked list
int contains(struct LinkedList* list, const char* word) {
    struct Node* current = list->head;
    while (current) {
        if (strcmp(current->word, word) == 0) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

// Function to display the words in the linked list
void display(struct LinkedList* list) {
    struct Node* current = list->head;
    while (current) {
        printf("\t\t\t\t%s\n", current->word);
        current = current->next;
    }
}

// Function to free the memory used by the linked list
void freeLinkedList(struct LinkedList* list) {
    struct Node* current = list->head;
    while (current) {
        struct Node* temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}

char lower_alpha[] = "abcdefghijklmnopqrstuvwxyz";

// Function to handle incorrect arrangement
int incorrectArrangement(const char* input, struct LinkedList* wordList) {
    char line[100];
    int found = 0;
    FILE* words = fopen("words.txt", "r");
    if (words) {
        while (fgets(line, sizeof(line), words) != NULL) {
            char Xinput[100], Ninput[100], Tinput[200], Tline[200], Nline[100], Xline[100];
            int len = strlen(input);
            int flen = strlen(line);
            if (len == flen) {
                for (int i = 1; i < len; i++) {
                    Ninput[i - 1] = input[i];
                }
                for (int i = 1; i < flen - 1; i++) {
                    Nline[i - 1] = line[i];
                }
                Ninput[len - 1] = '\0';
                Nline[flen - 1] = '\0';
                Xinput[0] = input[0];
                Xinput[1] = '\0';
                Xline[0] = line[0];
                Xline[1] = '\0';

                for (int i = 0; i < strlen(Nline); i++) {
                    for (int j = i + 1; j < strlen(Nline); j++) {
                        if (Nline[i] > Nline[j]) {
                            char temp = Nline[i];
                            Nline[i] = Nline[j];
                            Nline[j] = temp;
                        }
                    }
                }

                for (int i = 0; i < strlen(Ninput); i++) {
                    for (int j = i + 1; j < strlen(Ninput); j++) {
                        if (Ninput[i] > Ninput[j]) {
                            char temp = Ninput[i];
                            Ninput[i] = Ninput[j];
                            Ninput[j] = temp;
                        }
                    }
                }

                strcpy(Tinput, Xinput);
                strcat(Tinput, Ninput);
                strcpy(Tline, Xline);
                strcat(Tline, Nline);

                if (strcmp(Tinput, Tline) == 0) {
                    found = 1;
                    insert(wordList, line);
                }
            }
        }
        fclose(words);
    } else {
        printf("\nUnexpected error occurred.......\n");
    }
    return found;
}

// Function to handle exchanged characters
int exchangedCharacters(const char* input, struct LinkedList* wordList) {
    char line[100], Xinput[100];
    int found = 0;
    FILE* words = fopen("words.txt", "r");
    if (words) {
        while (fgets(line, sizeof(line), words) != NULL) {
            int len = strlen(input);
            int flen = strlen(line);
            if (len == flen) {
                for (int i = len - 1; i >= 0; i--) {
                    strcpy(Xinput, input);
                    Xinput[i] = lower_alpha[0];
                    for (int j = 0; j < 26; j++) {
                        if (strcmp(Xinput, line) == 0) {
                            found = 1;
                            insert(wordList, line);
                            break;
                        }
                        Xinput[i] = lower_alpha[j];
                    }
                    if (found == 1)
                        break;
                    else
                        continue;
                }
            }
        }
        fclose(words);
    } else {
        printf("\nUnexpected error occurred\n");
    }
    return found;
}

// Function to handle missing character
int missingCharacter(const char* input, struct LinkedList* wordList) {
    char Xinput[100], line[100], Tinput[200], Tline[200], Xline[100];
    int found = 0;
    FILE* words = fopen("words.txt", "r");
    if (words) {
        while (fgets(line, sizeof(line), words) != NULL) {
            for (int i = 0; i < 26; i++) {
                int len = strlen(input);
                int flen = strlen(line);
                strcpy(Xinput, input);
                strcpy(Xline, line);
                for (int j = len; j < len + 1; j++) {
                    Xinput[j] = 'a';
                }
                Xinput[len + 1] = lower_alpha[i];
                len = strlen(Xinput);
                char Ninput[100], Nline[100];
                if (len == flen) {
                    for (int j = 1; j <= len; j++) {
                        Ninput[j - 1] = Xinput[j];
                    }
                    for (int j = 1; j <= flen - 1; j++) {
                        Nline[j - 1] = Xline[j];
                    }
                    Ninput[len - 1] = '\0';
                    Nline[flen - 1] = '\0';
                    Xinput[1] = '\0';
                    Xline[1] = '\0';

                    for (int j = 0; j < strlen(Nline); j++) {
                        for (int k = j + 1; k < strlen(Nline); k++) {
                            if (Nline[j] > Nline[k]) {
                                char temp = Nline[j];
                                Nline[j] = Nline[k];
                                Nline[k] = temp;
                            }
                        }
                    }

                    for (int j = 0; j < strlen(Ninput); j++) {
                        for (int k = j + 1; k < strlen(Ninput); k++) {
                            if (Ninput[j] > Ninput[k]) {
                                char temp = Ninput[j];
                                Ninput[j] = Ninput[k];
                                Ninput[k] = temp;
                            }
                        }
                    }

                    strcpy(Tinput, Xinput);
                    strcat(Tinput, Ninput);
                    strcpy(Tline, Xline);
                    strcat(Tline, Nline);

                    if (strcmp(Tinput, Tline) == 0) {
                        found = 1;
                        insert(wordList, line);
                        break;
                    }
                }
                if (found == 1)
                    break;
            }
            if (found == 1)
                break;
        }
        fclose(words);
    } else {
        printf("\nUnexpected error occurred\n");
    }
    return found;
}

// Function to handle extra character
int extraCharacter(const char* input, struct LinkedList* wordList) {
    char Xinput[100], line[100], Ninput[100], Tinput[200];
    int found = 0;
    FILE* words = fopen("words.txt", "r");
    if (words) {
        while (fgets(line, sizeof(line), words) != NULL) {
            int len = strlen(input);
            int flen = strlen(line);
            if ((len - 1) == flen) {
                for (int i = 1; i < len; i++) {
                    strcpy(Xinput, input);
                    for (int j = i; j < len - 1; j++) {
                        Xinput[j - 1] = Xinput[j];
                    }
                    if (strcmp(Xinput, line) == 0) {
                        found = 1;
                        insert(wordList, line);
                        break;
                    }
                }
            }
        }
        fclose(words);
    } else {
        printf("\nUnexpected error occurred\n");
    }
    return found;
}

// Function to handle mixed extra/missing characters
int mixedExtraMissing(const char* input, struct LinkedList* wordList) {
    char Xinput[100], line[100], Xline[100];
    int found = 0;
    FILE* words = fopen("words.txt", "r");
    if (words) {
        while (fgets(line, sizeof(line), words) != NULL) {
            int len = strlen(input);
            int flen = strlen(line);
            if (len == flen) {
                for (int i = 1; i < len - 1; i++) {
                    for (int j = 0; j < 26; j++) {
                        strcpy(Xinput, input);
                        strcpy(Xline, line);
                        for (int k = i; k < len - 1; k++) {
                            Xinput[k - 1] = Xinput[k];
                        }
                        for (int k = len - 1; k < len - 1; k++) {
                            Xinput[k - 1] = 'a';
                        }
                        Xinput[len - 1] = lower_alpha[j];
                        for (int k = i; k < flen - 1; k++) {
                            Xline[k - 1] = Xline[k];
                        }
                        Xline[flen - 1] = lower_alpha[j];
                        for (int k = 1; k < len - 1; k++) {
                            for (int l = k + 1; l < len - 1; l++) {
                                if (Xinput[k] > Xinput[l]) {
                                    char temp = Xinput[k];
                                    Xinput[k] = Xinput[l];
                                    Xinput[l] = temp;
                                }
                            }
                        }
                        for (int k = 1; k < flen - 1; k++) {
                            for (int l = k + 1; l < flen - 1; l++) {
                                if (Xline[k] > Xline[l]) {
                                    char temp = Xline[k];
                                    Xline[k] = Xline[l];
                                    Xline[l] = temp;
                                }
                            }
                        }
                        if (strcmp(Xinput, Xline) == 0) {
                            found = 1;
                            insert(wordList, line);
                            break;
                        }
                    }
                    if (found == 1)
                        break;
                }
                if (found == 1)
                    break;
            }
        }
        fclose(words);
    }
    return found;
}

// ...
int main() {
    system("COLOR 7D");
    struct LinkedList* wordList = createLinkedList();
    #include <stdio.h>


    printf("\t\t\t\t\t      ___       __   __         ___    ___  __           \n");
    printf("\t\t\t\t\t|  | |__  |    /  ` /  \\  |\\/| |__      |  /  \\          \n");
    printf("\t\t\t\t\t|/\\| |___ |___ \\__, \\__/  |  | |___     |  \\__/          \n");
    printf("                                                        \n");
    printf("\t\t\t\t __   __                         __   __        __       \n");
    printf("\t\t\t\t/ _` |__)  /\\   |\\/|  |\\/|  /\\  |__) / _` |  | |__) |  |\n");
    printf("\t\t\t\t\\__> |  \\ /~~\\  |  |  |  | /~~\\ |  \\ \\__> \\__/ |  \\ \\__/ \n");
    printf("                                                        \n");
    printf("                                                        \n");
    printf("                                                        \n");
    printf("                                                        \n");



    while (1) {
        char input[100], line[100];
        int len, flen, correct = 0;

        // Clear the linked list before processing a new word
        while (wordList->head != NULL) {
            struct Node* current = wordList->head;
            wordList->head = current->next;
            free(current);
        }

        printf("\t\t\t\tPlese enter word to check: ");
        fgets(input, sizeof(input), stdin);
        len = strlen(input);
        for (int i = 0; i < len; i++) {
            input[i] = tolower(input[i]);
        }
        FILE* words = fopen("words.txt", "r");
        if (words) {
            while (fgets(line, sizeof(line), words) != NULL) {
                flen = strlen(line);
                if (len == flen) {
                    if (strcmp(line, input) == 0) {
                        correct = 1;
                    } else
                        continue;
                } else
                    continue;
            }
            fclose(words);
            if (correct == 1) {
                printf("\t\t\t\tThe Spelling is correct\n");
            }
            if (correct == 0) {
                printf("\n\t\t\t\tSorry! Your spelling is wrong. \n\t\t\t\tPossible right spellings are given below:\n\n");
                int missing = 0, extra = 0, mixed = 0, incorrect = 0, exchanged = 0;
                missing = missingCharacter(input, wordList);
                extra = extraCharacter(input, wordList);
                mixed = mixedExtraMissing(input, wordList);
                incorrect = incorrectArrangement(input, wordList);
                exchanged = exchangedCharacters(input, wordList);
                if (missing == 0 && extra == 0 && mixed == 0 && incorrect == 0 && exchanged == 0) {
                    printf("\n\t\t\t\tNo such word exists\n");
                } else {
                    printf("\n\t\t\t\tPossible suggestions:\n\n");
                    display(wordList);
                }
            }
        } else {
            printf("\t\t\t\tNot able to open words.txt\n");
        }
        printf("\t\t\t\t................Press Enter to continue................\n");
        getchar();
    }
    freeLinkedList(wordList);
    return 0;
}
