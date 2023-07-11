#include <stdio.h>
#include "mshell.h"

typedef struct tet
{
	int good;
	struct tet *next;
}test;

void updatePointer(int** ptr) {
    *ptr = malloc(sizeof(int));
    **ptr = 42;
}

int main() {

    int i  = 0;
    t_lexer *cmd;
	t_file *ptr;
   // t_file **file;

	cmd = creat_cmd(4);
   // while (cmd)
   // {
        //new_file(cmd->file);
		new_file(&cmd->file, i);
		ptr = cmd->file;
		while (ptr)
		{
			printf("%s\n",ptr->limeter);
			new_file(&cmd->file, i);
			ptr =ptr->next;
		}
		
		//printf(".	%s\n", cmd->cmd);
		//cmd = cmd->next;
		// file = cmd->file;
        // while (*file)
        // {
		// 	printf("			%s\n",(*file)->limeter);
        //     *file = (*file)->next;
        // }
        i++;
   // }
// int z = 45;
// int	*ptr = &z;
// updatePointer(&ptr);
// 	if (*ptr == 45)
// 		printf("dvsd\n");

    return 0;
}

