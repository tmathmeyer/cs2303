#include <stdio.h>
#include "tree.h"

int main(int argc, char*argv[])
{
	void fillTree(struct node **branch, char *filename);
	int write_tree(char *filename, struct node **tree);

	struct node *root = 0;

	int k;
	for(k = 2; k < argc; k++)
	{
		fillTree(&root, argv[k]);
	}
	
	write_tree(argv[1], &root);


	prune(root);
	return 0;
}

int read_words(char *filename, char *words[], int max_count)
{
	FILE *f = fopen(filename, "rt");
	int i = 0;
	char temp[100];
	while (fscanf(f, "%s", temp) != -1)
	{
		words[i] = strdup(temp);
		i++;
	}
	fclose(f);
	return i;
}


void fillTree(struct node **tree, char *filename)
{
	char *words[20000];
	int count = read_words(filename, words, 20000);
	int i;
	for (i = 0; i < count; i++)
	{
		insert(words[i], tree);
	}
}


int write_tree(char *filename, struct node **tree) {
	FILE *file;
	file = fopen(filename,"a+");
	int total = print_tree(tree, file);
	fprintf(file, "-------------\n%6i	Total number of different words\n",total);
	fclose(file);
	return 0;
}