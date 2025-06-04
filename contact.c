#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MAX_SEARCH_LEN 100
#define MAX_LINE_LEN 200


int main(int argc, char const *argv[])
{	
	Label1:
	printf("*********************\nContact List:\n\n");
	printf("1: List contacts\n"); 
	printf("2: Add contact\n");
	printf("3: Search contacts\n");
	printf("4: Delete contact\n*********************\n");


	
	int operator;
	scanf("%1d", &operator);
	switch (operator) {
		case 1: 
			FILE *fptr;
			char line[MAX_LINE_LEN];
			fptr = fopen("saved_contacts.txt", "r");
			printf("*********************\n");
			if (fptr != NULL) {
				while (fgets(line, sizeof(line), fptr)) {
					printf("%s", line);
				}
				printf("\n*********************\n");
				fclose(fptr);
			} else 
				printf("*********************\nError opening file.");
				break;

		case 2:
			char fName[30];
			char lName[30];
			char pNum[15];

			printf("*********************\nEnter first name:\n");
			scanf("%s", &fName);
			printf("*********************\nEnter last name:\n");
			scanf("%s", &lName);
			printf("*********************\nEnter Phone number:\n"); 
			scanf("%s", &pNum);
			fptr = fopen("saved_contacts.txt", "a");
			fprintf(fptr, "\n%s, %s, #%s", &fName, &lName, &pNum);
			fclose(fptr); 
			break;

		case 3:
			char search[MAX_SEARCH_LEN];
			printf("*********************\nSearch by name or number: **Enter 0 to exit**\n");
			while (1) 
			{
				printf("Enter search term: ");
				scanf("%99s", search);
				if (search[0] == '0' && search[1] == '\0')
					break;

				FILE *in_file = fopen("saved_contacts.txt", "r");
				if (in_file == NULL) {
					printf("Error. File missing!\n");
					exit(-1);
				}
				
				char line[MAX_LINE_LEN];
				int found = 0;
				while (fgets(line, sizeof(line), in_file)) {
					if (strcasestr(line, search)) {
						printf("*********************%s\n", line);
						found = 1;
					}
				}
				if (!found) {
					printf("No match found.\n");
				}
				fclose(in_file);
			}
			break;

		case 4:
			FILE *in_file, *out_file;
			char delete[MAX_SEARCH_LEN];
			int found = 0;
			printf("Search for contact to delete: **Enter 0 to exit**\n");
			printf("Enter search term: ");
			scanf("%99s", delete);
			if (delete[0] == '0' && delete[1] == '\0')
				break;

			in_file = fopen("saved_contacts.txt", "r");
			out_file = fopen("temp_file.txt", "w");
			if (in_file == NULL || out_file == NULL ) {
				printf("*********************\nError. File missing!\n");
				exit (-1);
			}
			char dLine[MAX_LINE_LEN];
			char answer[2];
			while (fgets(dLine, sizeof(dLine), in_file)) {
				if (strcasestr(dLine, delete)) {
					found = 1;
					printf("*********************\nIs this the contact you wish to delete? **Y/N**\n%s\n*********************\n", dLine);
					scanf("%1s", answer);
					if (answer[0] == 'Y' || answer[0] == 'y') {
						printf("********************\nContact deleted.\n");
						continue;
					}
				}
				fputs(dLine, out_file);
			}
			
			fclose(in_file); 
			fclose(out_file);

			remove("saved_contacts.txt");
			rename("temp_file.txt", "saved_contacts.txt");

			out_file = fopen("saved_contacts.txt", "r+");
			if (out_file) {
				fseek(out_file, -1, SEEK_END);
				char ch;
				fread(&ch, 1, 1, out_file);
				if (ch == '\n') {
					fseek(out_file, -1, SEEK_END);
					long pos = ftell(out_file);
					ftruncate(fileno(out_file), pos);
				}
				fclose(out_file);
			}

			if (!found)
				printf("*********************\nNo matching contact found.\n");
			break;
		default:
			printf("Navigate menu by entering the number that corresponds to the action you wish to take.\n"); 
			if (operator == 0) {
				break;	
			} else { 
				goto Label1;
			}	
	}
		return 0;
}
