#include <stdlib.h>
#include "tree.h"

#ifndef STRING_H
#define STRING_H
#ifndef STDIO_H
#define STDIO_H

void prune(struct node *branch)
{
	if (branch != 0)
	{
		prune(branch->left);
		prune(branch->right);
		free(branch);
	}
}

void insert(char *new, struct node **branch)
{
	if (*branch == 0)
	{
		*branch = (struct node*) malloc(sizeof(struct node));
		(*branch)->word = new;
		(*branch)->word_count = 1;
		(*branch)->left = 0;
		(*branch)->right = 0;
	}
	else
	{
		int result = strcmp((*branch)->word, new);
		if (result == 0)
		{
			(*branch)->word_count = (*branch)->word_count + 1;
		}
		else if (result < 0)
		{
			insert(new, &(*branch)->right);
		}
		else if (result > 0)
		{
			insert(new, &(*branch)->left);
		}
	}
}

int print_tree(struct node **tree, FILE *file)
{
	if (*tree != 0)
	{
		int a = print_tree(&(*tree)->left, file);
		fprintf(file, "%6i    %s\n",(*tree)->word_count, (*tree)->word);
		a += print_tree(&(*tree)->right, file);
		return a+1;
	}
	return 0;
}

#endif /* STRNG_H */
#endif /* STDIO_H */