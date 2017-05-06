// /*
// * @Author: han
// * @Date:   2017-05-04 9:07
// * @Last Modified by:   han
// * @Last Modified time: 2017-05-06 9:35
// */

#include <stdio.h>
#include <stdlib.h>

/*****************************************************************/
/*
*function:对于给定矩阵,生成十字链表,并将十字链表打印出来
*原理:在边结构体中存储了行和列的相应的头地址,该头地址分别指向每行或每列的非零的下一个元素的地址.
*(firstOut是存储每一行的头地址的数组,firstIn是存储每一列的头地址的数组,
*数组中的每一个元素即为一条单链表,
*即相同的弧尾顶点在同一条单链表上,相同的弧头顶点在同一条单链表上),
*十字链表是邻接表和逆邻接表的结合体
*/
/*****************************************************************/

/**
 * 边结构体
 *
 */
typedef struct LinkNode
{
	int tailVex, headVex;/*弧尾顶点,弧头顶点*/
	int data; /*边权值*/
	struct LinkNode* tailLink;/*由弧尾顶点指向的下一条边*/
	struct LinkNode* headLink;/*由弧头顶点指向的下一条边*/
} LinkNode, *LinkPtr;

/**
 * 顶点结构体
 */
typedef struct VexNode
{
	int m, n;		/*矩阵的行和列的值*/
	LinkPtr* firstOut;/*指向每一行的头地址的数组*/
	LinkPtr* firstIn;/*指向每一列的头地址的数组*/
} VexNode;

/**
 * [OrthogonalList 十字链表生成函数]
 * @param Vex [顶点结构体]
 * @param m   [信息矩阵]
 */

void OrthogonalList(VexNode* Vex, int* m)
{
	LinkPtr p = NULL, q = NULL;
	q = malloc(sizeof(LinkNode));
	q->headLink = NULL;
	q->tailLink = NULL;
	q->headVex = -1;
	q->tailVex = -1;
	for (int i = 0; i < Vex->m; i++)
	{
		for (int j = 0; j < Vex->n; j++)
		{
			if (*(m + (Vex->m) * i + j) != 0)
			{
				p = malloc(sizeof(LinkNode));
				p->tailVex = i;
				p->headVex = j;
				p->tailLink = NULL;
				p->headLink = NULL;
				p->data = *(m + (Vex->m) * i + j);
				/*出度*/
				if (*(Vex->firstOut + i) == NULL)
				{
					/*每一行的头地址*/
					*(Vex->firstOut + i) = p;
				}
				else
				{
					/*寻找插入的位置*/
					for (q = *(Vex->firstOut + i); q->headLink && q->headLink->headVex < j; q = q->headLink);
					/*完成插入*/
					p->headLink = q->headLink;
					q->headLink = p;
				}

				/*入度*/
				if (*(Vex->firstIn + j) == NULL)
				{
					/*每一列的头地址*/
					*(Vex->firstIn + j) = p;
				}
				else
				{
					/*寻找插入的位置*/
					for (q = *(Vex->firstIn + j); q->tailLink && q->tailLink->tailVex < i; q = q->tailLink);
					/*完成插入*/
					p->tailLink = q->tailLink;
					q->tailLink = p;
				}
			}
		}
	}
}

/**
 * [printOrList 打印十字链表]
 * @param Vex [十字链表]
 */
void printOrList(VexNode* Vex)
{
	LinkPtr q = NULL;
	q = malloc(sizeof(LinkNode));
	for (int i = 0; i < Vex->m; i++)
	{
		printf("%d", i);
		/*遍历单链表*/
		for (q = *(Vex->firstOut + i); q; q = (*q).headLink)
		{
			printf(" -> %d", (*q).headVex);
		}
		printf("\n");
	}
	printf("\n\n");

	for (int i = 0; i < Vex->n; i++)
	{
		printf("%d", i);
		/*遍历单链表*/
		for (q = *(Vex->firstIn + i); q; q = (*q).tailLink)
		{
			printf(" <- %d", (*q).tailVex);
		}
		printf("\n");
	}
}

int main()
{
	char Vex[4] = {'A','B','C','D'};
	/*矩阵*/
	int matrix[4][4] = {
		{0,1,2,1},
		{0,0,1,1},
		{1,0,0,0},
		{0,0,1,0}
	};
	int m = sizeof(matrix) / sizeof(matrix[0]);		/*矩阵的行数*/
	int n = sizeof(matrix) / sizeof(*matrix[0]) / m;/*矩阵的列数*/
	VexNode* mVex = malloc(sizeof(VexNode));/*顶点*/
	(*mVex).m = m;
	(*mVex).n = n;
	(*mVex).firstIn = malloc((*mVex).n * sizeof(LinkPtr));
	(*mVex).firstOut = malloc((*mVex).m * sizeof(LinkPtr));
	for (int i = 0; i < (*mVex).n; i++)
		(*mVex).firstIn[i] = NULL;
	for (int i = 0; i < (*mVex).m; i++)
		(*mVex).firstOut[i] = NULL;
	OrthogonalList(mVex, matrix);
	printOrList(mVex);
	return 0;
}
