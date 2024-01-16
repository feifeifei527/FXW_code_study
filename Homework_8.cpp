#include <iostream>
#define OK 0
#define ERROR -1
#define MVNum 100
using namespace std;

//数据结构定义
typedef struct VNode
{
    int data;
    struct VNode *next;
} VNode, *NodeList;
typedef struct
{
    NodeList V[MVNum];
    int vexnum, arcnum;
} ALGraph;

//创建图表
int CreateUDG(ALGraph &G, int vexnum, int arcnum)
{
    G.vexnum = vexnum;
    G.arcnum = arcnum;
    for (int i = 1; i <= vexnum; i++)
    {
        G.V[i] = new VNode;
        G.V[i]->next = NULL;
        G.V[i]->data = i;
    }
    for (int i = 0; i < arcnum; i++)
    {
        int v1, v2;
        cin >> v1 >> v2;
        NodeList p1 = new VNode;
        p1->data = v2;
        p1->next = G.V[v1]->next;
        G.V[v1]->next = p1;
        NodeList p2 = new VNode;
        p2->data = v1;
        p2->next = G.V[v2]->next;
        G.V[v2]->next = p2;
    }
    return OK;
}

//深度优先遍历
int DFS(ALGraph G)
{
    int v;
    cin >> v;
    cout << v;
    int top = 0, visited[MVNum], Stack[MVNum];
    for (int i = 0; i < MVNum; i++)
        visited[i] = 0;
    Stack[top++] = v;
    visited[v] = 1;
    while (top > 0)
    {
        int flag = 0;
        NodeList p = G.V[Stack[top - 1]];
        while (p)
        {
            if (!visited[p->data])
                flag = p->data;
            p = p->next;
        }
        if (flag == 0)
            top--;
        else
        {
            cout << " " << flag;
            Stack[top++] = flag;
            visited[flag] = 1;
        }
    }
    cout << endl;
    return OK;
}

//删除图表，释放内存
void DeleteGraph(ALGraph &G)
{
    for (int i = 1; i <= G.vexnum; i++)
    {
        NodeList p = G.V[i];
        while (p)
        {
            NodeList q = p;
            p = p->next;
            delete q;
        }
    }
}

int main()
{

    int vexnum, arcnum;
    //当都为0 时跳出
    while (cin >> vexnum >> arcnum && vexnum != 0 && arcnum != 0)
    {
        ALGraph G;
        CreateUDG(G, vexnum, arcnum);
        DFS(G);
        DeleteGraph(G);
    }
    return 0;
}