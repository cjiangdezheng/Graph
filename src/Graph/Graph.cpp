#include "stdafx.h"
#include <iostream>
#include <string>
#include <math.h>
#include <queue>

using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////


#define MAXVEX 1000				//最大顶点数

typedef struct EdgeNode         //边表结点
{
	int adjvex;					//邻接点域，存储该顶点对应的下标
	struct EdgeNode *next;      //链域，指向下一个邻接点
}EdgeNode;

typedef struct VertexNode       //顶点表结构
{
	char data;                  //顶点域，存储顶点信息
	EdgeNode *firstedge;        //边表头指针
}VertexNode, AdjList[MAXVEX];

typedef struct					//图结点
{
	AdjList adjList;
	int numVertexes;			//图中当前顶点数
	int numEdges;				//图中当前边数
}GraphList;




int Locate(GraphList *g, char ch)
{
	int i;
	for (i = 0; i < MAXVEX; i++)
	{
		if (ch == g->adjList[i].data)
		{
			break;
		}
	}
	if (i >= MAXVEX)
	{
		cout << "there is no vertex" << endl;;
		return -1;
	}
	return i;
}

//
void CreateGraph(GraphList *g)
{
	int i, k;
	EdgeNode *e;
	EdgeNode *f;
	g->numVertexes = 3;//顶点数
	g->numEdges = 3;   //边数


	for (i = 0; i < g->numVertexes; i++)//输入顶点信息
	{
		printf("请输入顶点%d的标识(字符):\n", i);
		cin >> g->adjList[i].data;        //输入顶点信息
		g->adjList[i].firstedge = NULL;   //将边表置为空表
	}
	//建立边表
	for (k = 0; k < g->numEdges; k++)
	{
		cout << "输入边(vi,vj)上的起始、结束顶点标识(字符):" << endl;
		char cBegin, cEnd;
		cin >> cBegin;
		cin >> cEnd;

		int iBeginIndex, iEndIndex;
		iBeginIndex = Locate(g, cBegin);
		iEndIndex = Locate(g, cEnd);
		if (iBeginIndex == -1 || iEndIndex == -1)
		{
			return;
		}

		printf("cBegin = %c\n", cBegin);
		printf("cEnd = %c\n", cEnd);
		printf("iBeginIndex = %d\n", iBeginIndex);
		printf("iEndIndex = %d\n", iEndIndex);

		//向内存申请空间，生成边表结点
		e = (EdgeNode *)malloc(sizeof(EdgeNode));
		if (e == NULL)
		{
			cout << "malloc() error" << endl;
			return;
		}
		//邻接序号为j
		e->adjvex = iEndIndex;
		//将e指针指向当前顶点指向的结构
		e->next = g->adjList[iBeginIndex].firstedge;
		//将当前顶点的指针指向e
		g->adjList[iBeginIndex].firstedge = e;

		f = (EdgeNode *)malloc(sizeof(EdgeNode));
		if (f == NULL)
		{
			cout << "malloc() error" << endl;
			return;
		}
		f->adjvex = iBeginIndex;
		f->next = g->adjList[iEndIndex].firstedge;
		g->adjList[iEndIndex].firstedge = f;
	}
}

void printGraph(GraphList *g)
{
	int i = 0;

	while (g->adjList[i].firstedge != NULL && i < MAXVEX)
	{
		cout << "顶点:" << g->adjList[i].data << "的邻接点序号为:";
		EdgeNode *e = NULL;
		e = g->adjList[i].firstedge;
		while (e != NULL)
		{
			cout << e->adjvex << "  ";
			e = e->next;
		}
		i++;
		cout << endl;
	}
}
void Bfs(GraphList G)
{
	VertexNode v;
	EdgeNode *t = NULL;
	int i, j;
	int visited[MAXVEX];
	memset(visited, 0, sizeof(visited));

	deque<VertexNode> dequeVNode;
	for (i = 0; i < G.numVertexes; i++)
	{
		if (!visited[i])    //如果顶点i未被访问过    
		{
			dequeVNode.push_back(G.adjList[i]);
			cout << G.adjList[i].data << endl;
			visited[i] = 1;

			while (dequeVNode.size())
			{
				v = dequeVNode.front();
				dequeVNode.pop_front();

				t = v.firstedge;
				while (t)   //检查所有与顶点i相邻接的顶点
				{
					j = t->adjvex;    //顶点j是顶点i的一个邻接顶点
					if (visited[j] == 0) //若顶点j未被访问过，将j加入队列
					{
						dequeVNode.push_back(G.adjList[j]);
						cout << G.adjList[j].data << endl;
						visited[j] = 1;
					}
					t = t->next;
				}
			}
		}
	}
}

int visited[MAXVEX] = { 0 };
void Dfs(GraphList G, int i)
{
	EdgeNode *t;
	int j;
	printf("%d", i);   //访问序号为i的顶点
	visited[i] = 1;   //序号为i的顶点已被访问过
	t = G.adjList[i].firstedge; //取顶点i的第一个邻接顶点
	while (t != NULL)  //检查所有与顶点i相邻接的顶点
	{
		j = t->adjvex;   //顶点j为顶点i的一个邻接顶点
		if (visited[j] == 0)//若顶点j未被访问过
			Dfs(G, j); //从顶点j出发进行深度优先搜索
		t = t->next; //取顶点i的下一个邻接顶点
	}
}


int main()
{
	int a[2][2][2] = {0};
	return 0;
	GraphList g;
	memset(&g, 0, sizeof(GraphList));
	CreateGraph(&g);
	printGraph(&g);
	cout << "---------------------" << endl;
	//Bfs2(g);
}
	/*	int a[] = {5,4,3,2,1,9,10,8,7,6};
	int len = sizeof(a) / sizeof(int);
	RadixSort(a, len);

	for (int i = 0; i < len; i++)
	cout << a[i] << " ";
	cout << endl;
	*/
	//return 0;
//}