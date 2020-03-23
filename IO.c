#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "LinkedList.h"

#define MAX_LINE_LENGTH 100

#define STRINGS_ARE_EQUAL( Str1, Str2 ) ( strcmp( (Str1), (Str2) ) == 0 )

typedef struct user_instruction {
	char command[MAX_LINE_LENGTH];
	int argument_1;
	int argument_2;
} instruction;


void GetUserInput(char* destination);

int ParseUserInput(char* user_input, instruction* user_instruction);

bool DoCommand(Node** head, instruction* user_instruction);

void ConvertToLowercase(char* str);

void UsageGuide();

int main() {
	
	char user_input[MAX_LINE_LENGTH];	
	Node* head = NULL;
	bool stop_input_loop = false;

	instruction user_instruction;

	while (!stop_input_loop) {

		GetUserInput(user_input);

		int num_of_arguments = ParseUserInput(user_input, &user_instruction);
		if (num_of_arguments == -1) {
			printf("Empty string received\n");
			break;
		}
		stop_input_loop = DoCommand(&head, &user_instruction);
		
	}
	TerminateList(head);

	return 0;
}

void GetUserInput(char* destination)
{
	fgets(destination, MAX_LINE_LENGTH, stdin);
}

void RemoveTrailingNewline(char* string) {
	int last_character_position = strlen(string) - 1;
		if (string[last_character_position] == '\n') {
			string[last_character_position] = '\0';
	}

}
int ParseUserInput(char* user_input, instruction* user_instruction) {

	RemoveTrailingNewline(user_input);

	ConvertToLowercase(user_input);

	int num_of_arguments = sscanf(user_input, "%s %d %d",
		user_instruction->command,
		&user_instruction->argument_1,
		&user_instruction->argument_2);

	return num_of_arguments;
}



bool DoCommand(Node** start, instruction* user_instruction) {
	bool got_exit_indication = false;
	if (STRINGS_ARE_EQUAL(user_instruction->command, "add_end")){
		InsertEndOfList(start, user_instruction->argument_1);
	}
	else if (STRINGS_ARE_EQUAL(user_instruction->command, "add_start")) {
		InsertStartOfList(start, user_instruction->argument_1);
	}
	else if (STRINGS_ARE_EQUAL(user_instruction->command, "add_after")) {
		got_exit_indication = (bool)InsertAfterElement(start,
							  user_instruction->argument_1,
							  user_instruction->argument_2);
	}
	else if (STRINGS_ARE_EQUAL(user_instruction->command, "index")) {
		SearchForElement(*start, user_instruction->argument_1, true);
	}
	else if (STRINGS_ARE_EQUAL(user_instruction->command, "del")) {
		got_exit_indication = (bool)RemoveIndex(start, user_instruction->argument_1);
	}
	else if (STRINGS_ARE_EQUAL(user_instruction->command, "print")) {
		PrintList(*start);
	}
	else if (STRINGS_ARE_EQUAL(user_instruction->command, "exit")) {
		got_exit_indication = true;
	}
	else {
		printf("Unrecognized command\n");
		UsageGuide();
	}
	return got_exit_indication;
}

void ConvertToLowercase(char* str) {
	if (NULL == str) {
		printf("ConvertToLowercase received a NULL string\n");
		return;
	}
	else {
		int i = 0;
		for (i = 0; str[i] != '\0'; i++) {
			str[i] = tolower(str[i]);
		}
	}
}

void UsageGuide() {

	printf(	"\nPlease use one of the following allowed commands:\n\n"
			"add_end i:		add item i to the end of the list\n"
			"add_start i:		add item i to the start of the list\n"
			"add_after j i:		add item j after item i, if existing. If i not found, exit\n"
			"del i:			remove item i from the list, if found. If i not found, exit\n"
			"index i:		return the index of first occurence of item i\n"
			"print:			print the linked list in the following format : [i, j, k, ..]\n"
			"exit:			free the linked list and exit the program\n");
}