// PFC.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "C:\Users\Administrator\Documents\Visual Studio 2015\Projects\BinaryTree\BinaryTree\BinTree.h"


int main(int argc,char* argv[])//PFC���롢����ͳһ�������
{
	PFCForest* forest = initForest();
	PFCTree* tree = generateTree(forest); release(forest);
	PFCTable* table = generateTable(tree);//��PFC������ת��Ϊ�����
	for (int i = 1; i < argc; i++) {
		Bitmap codeString;
		int n = encode(table, codeString, argv[i]);
		decode(tree, codeString, n);
	}
	release(table); release(tree);
    return 0;
}

