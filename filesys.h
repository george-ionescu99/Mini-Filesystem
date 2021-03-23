#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "list.h"

void createRoot(struct Directory **root)
{
	*root = (struct Directory *)calloc(1, sizeof(struct Directory *));
	(*root)->name = (char *)calloc(1, sizeof(char *));
	(*root)->name = "/";
	(*root)->files = NULL;
	(*root)->directories = NULL;
	(*root)->parentDir = NULL;
}

void touch(struct Directory **dir, char *command)
{
	char *token = strtok(command, " "); //scapam de "touch"
	struct File *f = (struct File *)calloc(1, sizeof(struct File *));

	token = strtok(NULL, " "); //filename

	f->name = (char *)calloc(strlen(token)+1, sizeof(char *));
	strcpy(f->name, token);

	token = strtok(NULL, " "); //data
	token[strlen(token)-1] = 0;

	f->data = (char *)calloc(strlen(token)+1, sizeof(char *));
	strcpy(f->data, token);

	f->size = sizeof(token);

	f->dir = *dir;//memdup(*dir, sizeof(*dir));

	push_back(&(*dir)->files, f);
}

void mkdir(struct Directory **dir, char *name)
{
	struct Directory *dir1 =
	(struct Directory *)calloc(1, sizeof(struct Directory *));

	dir1->name = (char *)calloc(strlen(name)+1, sizeof(char *));
	strcpy(dir1->name, name);

	dir1->files = NULL;
	dir1->directories = NULL;

	dir1->parentDir = *dir;// memdup(*dir, sizeof(*dir));
	//printf("Am creat directorul. Parinte: %s\n", dir1->parentDir->name);

	push_back(&(*dir)->directories, dir1);
}

void pwd(struct Directory *dir)
{
	if (!dir)
		return;
	if (!dir->parentDir) {
		printf("/");
		return;
	}

	pwd(dir->parentDir);

	if (dir->parentDir->parentDir)
		printf("/");
	printf("%s", dir->name);
}

void cd(struct Directory **current, char *dest)
{
	if (strcmp(dest, "..") == 0) {
		if  (!(*current)->parentDir) {
			printf("We are at root\n");
			return;
		}
		*current = (*current)->parentDir;
		return;
	}

	struct Directory *mouse = (struct Directory *)

	calloc(1, sizeof(struct Directory *));

	for (struct Node *iterator = (*current)->directories; iterator != NULL;
	iterator = iterator->next) {
		mouse = iterator->data;
		mouse->parentDir = *current;
		if (strcmp(mouse->name, dest) == 0) {
			*current = mouse;
			return;
		}
	}

		printf("Cannot move to '%s': No such directory!\n", dest);
		return;

}

void print_tree(struct Node *node, int spaces)
{
	for (struct Node *iterator = node; iterator != NULL;
	iterator = iterator->next) {
		for (int i = 0; i < spaces+4; i++)
			printf(" ");

		printf("%s", *(char **)iterator->data);
		printf("\n");
	}
}

void tree(struct Directory *root, int spaces)
{
	if (!root)
		return;

	print_tree(root->files, spaces);
	for (struct Node *iter = root->directories;
		iter != NULL; iter = iter->next) {
		for (int i = 0; i  < spaces+4; i++)
			printf(" ");
		struct Directory *aux = iter->data;

		printf("%s", aux->name);
		printf("\n");
		tree(aux, spaces+4);
	}
}
