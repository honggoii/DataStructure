void DeleteTree(BTreeNode* bt)
{
	if (bt == NULL)
		return;

	DeleteTree(bt->left);
	DeleteTree(bt->right);

	printf("del tree data: %d \n", bt->data);
	free(bt);
}