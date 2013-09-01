#include <string.h>
#include <stdio.h>

struct node
{
  int word_count;
  char *word;
  struct node *left;
  struct node *right;
};

void prune(struct node *branch);
void insert(char *word, struct node **branch);
int print_tree(struct node **tree, FILE *file);
