// define BinaryTree

void writeBinaryTree(mytree* root, fstream &fd)
{
	if (!root)
		fd<<"#";
	else
	{
		fd<<root->data<<" ";
		writeBinaryTree(root->left);
		writeBinaryTree(root->right);
	}
}


// unget(): Attempts to decrease the current location in the stream by one character
// get(): Extracts a single character from the stream.

bool getNextToken(string &token, fstream &fd, bool &isNumber)
{
    if (getline(fd, token, ' '))
    {
        if(fd.unget().get() == '\n')
            return false;

        if (token.compare("#") == 0)
            isNumber = false;
        else
            isNumber = true;
        return true;
    }
    //return false;
}

void readBinaryTree(mytree *&root, fstream &fd)
{
	string token;
	bool isNumber;

	if (!getNextToken(token, fd, isNumber))
		return;

	if (isNumber)
	{
		root = new BinaryTree(stoi(token));
		readBinaryTree(root->left, fd);
		readBinaryTree(root->right, fd);
	}
}
