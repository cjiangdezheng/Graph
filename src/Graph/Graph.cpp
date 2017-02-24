#include "stdafx.h"
#include <iostream>
#include <string>
#include <math.h>
#include <queue>

using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////


#define MAXVEX 1000				//��󶥵���

typedef struct EdgeNode         //�߱����
{
	int adjvex;					//�ڽӵ��򣬴洢�ö����Ӧ���±�
	struct EdgeNode *next;      //����ָ����һ���ڽӵ�
}EdgeNode;

typedef struct VertexNode       //������ṹ
{
	char data;                  //�����򣬴洢������Ϣ
	EdgeNode *firstedge;        //�߱�ͷָ��
}VertexNode, AdjList[MAXVEX];

typedef struct					//ͼ���
{
	AdjList adjList;
	int numVertexes;			//ͼ�е�ǰ������
	int numEdges;				//ͼ�е�ǰ����
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
	g->numVertexes = 3;//������
	g->numEdges = 3;   //����


	for (i = 0; i < g->numVertexes; i++)//���붥����Ϣ
	{
		printf("�����붥��%d�ı�ʶ(�ַ�):\n", i);
		cin >> g->adjList[i].data;        //���붥����Ϣ
		g->adjList[i].firstedge = NULL;   //���߱���Ϊ�ձ�
	}
	//�����߱�
	for (k = 0; k < g->numEdges; k++)
	{
		cout << "�����(vi,vj)�ϵ���ʼ�����������ʶ(�ַ�):" << endl;
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

		//���ڴ�����ռ䣬���ɱ߱����
		e = (EdgeNode *)malloc(sizeof(EdgeNode));
		if (e == NULL)
		{
			cout << "malloc() error" << endl;
			return;
		}
		//�ڽ����Ϊj
		e->adjvex = iEndIndex;
		//��eָ��ָ��ǰ����ָ��Ľṹ
		e->next = g->adjList[iBeginIndex].firstedge;
		//����ǰ�����ָ��ָ��e
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
		cout << "����:" << g->adjList[i].data << "���ڽӵ����Ϊ:";
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
		if (!visited[i])    //�������iδ�����ʹ�    
		{
			dequeVNode.push_back(G.adjList[i]);
			cout << G.adjList[i].data << endl;
			visited[i] = 1;

			while (dequeVNode.size())
			{
				v = dequeVNode.front();
				dequeVNode.pop_front();

				t = v.firstedge;
				while (t)   //��������붥��i���ڽӵĶ���
				{
					j = t->adjvex;    //����j�Ƕ���i��һ���ڽӶ���
					if (visited[j] == 0) //������jδ�����ʹ�����j�������
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
	printf("%d", i);   //�������Ϊi�Ķ���
	visited[i] = 1;   //���Ϊi�Ķ����ѱ����ʹ�
	t = G.adjList[i].firstedge; //ȡ����i�ĵ�һ���ڽӶ���
	while (t != NULL)  //��������붥��i���ڽӵĶ���
	{
		j = t->adjvex;   //����jΪ����i��һ���ڽӶ���
		if (visited[j] == 0)//������jδ�����ʹ�
			Dfs(G, j); //�Ӷ���j�������������������
		t = t->next; //ȡ����i����һ���ڽӶ���
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