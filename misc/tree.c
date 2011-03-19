#include <stdio.h>
#include <stdlib.h>

typedef struct tree_node *position;
typedef struct tree_node *search_tree;
struct tree_node{
	int item;
	search_tree left;
	search_tree right;
};

search_tree
make_empty(search_tree t)
{
	if (t != NULL) {
		make_empty(t->left);
		make_empty(t->right);
		free(t);
	}
	return NULL;
}

position
find(int x, search_tree t)
{
	if (t == NULL)
		return NULL;
	if (x < t->item)
		return find(x, t->left);
	else if (x > t->item)
		return find(x, t->right);
	else
		return t;
}

position
find_min(search_tree t)
{
	if (t == NULL)
		return NULL;
	else if (t->left == NULL)
		return t;
	else
		return find_min(t->left);
}

position
find_max(search_tree t)
{
	if (t != NULL)
		while(t->right != NULL)
			t = t->right;
	return t;
}

search_tree
insert(int x, search_tree t)
{
	if (t == NULL) {
		t = malloc(sizeof(struct tree_node));
		if (t == NULL)
			printf("Malloc error");
		else {
			t->item = x;
			t->left = t->right = NULL;
		}
	} else if (x < t->item) {
		t->left = insert(x, t->left);
	} else if (x > t->item) {
		t->right = insert(x, t->right);
	}
	return t;
}

search_tree
delete(int x, search_tree t)
{
	position tmp;
	if (t == NULL)
		printf("Error\n");
	else if (x < t->item)
		t->left = delete(x, t->left);
	else if (x > t->item)
		t->right = delete(x, t->right);
	else if (t->left && t->right) {
		tmp = find_min(t->right);
		t->item = tmp->item;
		t->right = delete(t->item, t->right);
	} else {
		tmp = t;
		if (t->left == NULL) {
			t = t->right;
		} else if (t->right == NULL) {
			t = t->left;
		}
		free(tmp);
	}
	return t;
}

int main(int argc, char *argv[])
{
	int i;
	search_tree tree = NULL;
	position tmp;
	char input[10];
	FILE *fd;
	
	fd = fopen("./data", "r");
	while (fgets(input, 9, fd) != 0) {
		tree = insert(atoi(input), tree);
	}
	
	printf("max = %d\n", find_max(tree)->item);
	
	tree = insert(1000, tree);
	printf("max = %d\n", find_max(tree)->item);

	tree = delete(100, tree);
	tree = delete(1000, tree);
	printf("max = %d\n", find_max(tree)->item);
	return 0;
}
