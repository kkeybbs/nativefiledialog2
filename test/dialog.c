#include "nfd.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CMD_SIZE 20

char* prefix = NULL;

void dialog_send(nfdresult_t result, nfdchar_t *path)
{
	if (result == NFD_OKAY)
	{
		if (path != NULL)
		{
			printf("%s1\n", prefix);
			printf("%s%s\n", prefix, path);
			free(path);
		}
	}
	else if (result == NFD_CANCEL)
	{
		printf("%s0\n", prefix);
	}
	else
	{
		printf("%s-1\n", prefix);
		printf("%s%s\n", prefix, NFD_GetError());
	}
}

void dialog_opens()
{
	nfdpathset_t pathSet;
	const char* defaultName = "select this folder";
	nfdresult_t result = NFD_OpenDialogMultiple(NULL, defaultName, &pathSet);
	if (result == NFD_OKAY)
	{
		size_t i;
		size_t count = NFD_PathSet_GetCount(&pathSet);
		printf("%s%d\n", prefix, (int)count);
		for (i = 0; i < count; ++i)
		{
			nfdchar_t *path = NFD_PathSet_GetPath(&pathSet, i);
			printf("%s%s\n", prefix, path);
		}
		NFD_PathSet_Free(&pathSet);
	}
	else 
	{
		dialog_send(result, NULL);
	}
}

void dialog_open()
{
	nfdchar_t *path = NULL;
	nfdresult_t result = NFD_OpenDialog(NULL, NULL, &path);
	dialog_send(result, path);
}

void dialog_save()
{
	nfdchar_t *savePath = NULL;
	nfdresult_t result = NFD_SaveDialog(NULL, NULL, &savePath);
	dialog_send(result, savePath);
}

void dialog_browser()
{
	nfdchar_t *path = NULL;
	nfdresult_t result = NFD_PickFolder(NULL, &path);
	dialog_send(result, path);
}

int main( void )
{
	char cmd[CMD_SIZE];
	
	prefix = getenv("OUTPUT_PREFIX");
	if(prefix == NULL) prefix = "";

	while (1)
	{
		fgets(cmd, CMD_SIZE , stdin);
		if (cmd[strlen(cmd) - 1] != '\n') 
		{
			do
			{
				fgets(cmd, CMD_SIZE, stdin);
			} while (cmd[strlen(cmd) - 1] != '\n');
			printf("%sinvalid\n", prefix);
			continue;			
		}
		*(cmd + strlen(cmd) - 1) = 0;
		if (strcmp(cmd, "exit") == 0 || strcmp(cmd, "q") == 0)
		{
			break;
		}
		else if (strcmp(cmd, "open") == 0)
		{
			dialog_open();
		}
		else if (strcmp(cmd, "opens") == 0)
		{
			dialog_opens();
		}
		else if (strcmp(cmd, "save") == 0)
		{
			dialog_save();
		}
		else if (strcmp(cmd, "browser") == 0)
		{
			dialog_browser();
		}
		else
		{
			printf("%sinvalid\n", prefix);
		}

	}
    return 0;
}
