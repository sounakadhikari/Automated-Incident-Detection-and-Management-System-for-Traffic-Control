#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_DOCS 100
#define MAX_LENGTH 1000

typedef struct {
    char title[100];
    char content[MAX_LENGTH];
    char category[50];
    char metadata[100];
} Document;

Document docs[MAX_DOCS];
int doc_count = 0;

void categorizeDocument(Document *doc) {
    if (strstr(doc->content, "legal") != NULL) {
        strcpy(doc->category, "Legal");
    } else if (strstr(doc->content, "tax") != NULL) {
        strcpy(doc->category, "Tax");
    } else if (strstr(doc->content, "personnel") != NULL) {
        strcpy(doc->category, "Personnel");
    } else if (strstr(doc->content, "finance") != NULL) {
        strcpy(doc->category, "Finance");
    } else {
        strcpy(doc->category, "General");
    }
}

void addMetadata(Document *doc, const char *metadata) {
    strcpy(doc->metadata, metadata);
}

void addDocument(const char *title, const char *content, const char *metadata) {
    if (doc_count >= MAX_DOCS) {
        printf("Document storage is full! Unable to add more documents.\n");
        return;
    }
    
    strcpy(docs[doc_count].title, title);
    strcpy(docs[doc_count].content, content);
    categorizeDocument(&docs[doc_count]);
    addMetadata(&docs[doc_count], metadata);
    doc_count++;
    
    printf("Document '%s' added successfully!\n", title);
}

void searchDocuments(const char *keyword) {
    int found = 0;
    printf("\nSearch Results for '%s':\n", keyword);
    
    for (int i = 0; i < doc_count; i++) {
        if (strstr(docs[i].content, keyword) != NULL || strstr(docs[i].metadata, keyword) != NULL) {
            printf("\nDocument Title: %s\n", docs[i].title);
            printf("Category: %s\n", docs[i].category);
            printf("Metadata: %s\n", docs[i].metadata);
            printf("Content Preview: %.50s...\n", docs[i].content);
            found = 1;
        }
    }

    if (!found) {
        printf("No documents found with the keyword '%s'.\n", keyword);
    }
}

void displayAllDocuments() {
    printf("\nList of All Documents:\n");
    for (int i = 0; i < doc_count; i++) {
        printf("\nDocument #%d\n", i + 1);
        printf("Title: %s\n", docs[i].title);
        printf("Category: %s\n", docs[i].category);
        printf("Metadata: %s\n", docs[i].metadata);
        printf("Content: %.100s...\n", docs[i].content);
    }
}

int main() {
    int choice;
    char title[100], content[MAX_LENGTH], metadata[100], keyword[50];

    printf("Welcome to the AI-powered Document Management System (Simplified Version)\n");

    while (1) {
        printf("\n1. Add Document\n2. Search Documents\n3. Display All Documents\n4. Exit\nEnter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("\nEnter document title: ");
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = 0;

                printf("Enter document content: ");
                fgets(content, sizeof(content), stdin);
                content[strcspn(content, "\n")] = 0;

                printf("Enter document metadata (e.g., Department, Date): ");
                fgets(metadata, sizeof(metadata), stdin);
                metadata[strcspn(metadata, "\n")] = 0; 

                addDocument(title, content, metadata);
                break;

            case 2:
                printf("Enter keyword to search: ");
                fgets(keyword, sizeof(keyword), stdin);
                keyword[strcspn(keyword, "\n")] = 0;

                searchDocuments(keyword);
                break;

            case 3:
                displayAllDocuments(); 
                break;

            case 4:
                printf("Exiting the system. Thank you!\n");
                printf("\nTeam: AlgoRhythm\n");
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
