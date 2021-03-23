#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "filesys.h"

int main(void)
{
	char command[100];
	char c1[100];
	char *token;
	struct Directory *root;

	do {
		fgets(command, 100, stdin);
		strcpy(c1, command);
		token = strtok(c1, " ");

		if (strcmp(command, "create fs\n") == 0)
			createRoot(&root);

		else if (strcmp(token, "touch") == 0)
			touch(&root, command);

		else if (strcmp(token, "mkdir") == 0) {
			token = strtok(NULL, " "); //dirname
			token[strlen(token)-1] = 0;
			mkdir(&root, token);
		}

		else if (strcmp(command, "ls\n") == 0) {
			print_list(root->files);
			if (root->files)
				printf(" ");
			print_list(root->directories);
			printf("\n");
		}

		else if (strcmp(command, "pwd\n") == 0) {
			pwd(root);
			printf("\n");
		}

		else if (strcmp(token, "cd") == 0) {
			token = strtok(NULL, " ");
			token[strlen(token)-1] = 0;
			cd(&root, token);
		}

		else if (strcmp(command, "tree\n") == 0) {
			printf("%s\n", root->name);
			tree(root, 0);
		} else
			continue;
	} while (strcmp(command, "delete fs\n") != 0);

	return 0;
}
