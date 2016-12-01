// PFC.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "C:\Users\Administrator\Documents\Visual Studio 2015\Projects\BinaryTree\BinaryTree\BinTree.h"


int main(int argc,char* argv[])//PFC编码、解码统一测试入口
{
	PFCForest* forest = initForest();
	PFCTree* tree = generateTree(forest); release(forest);
	PFCTable* table = generateTable(tree);//将PFC编码树转换为编码表
	for (int i = 1; i < argc; i++) {
		Bitmap codeString;
		int n = encode(table, codeString, argv[i]);
		decode(tree, codeString, n);
	}
	release(table); release(tree);
    return 0;
}

