#ifndef DEF_H_INCLUDED
#define DEF_H_INCLUDED
#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <stack>
#include <random>
#include <time.h>
using namespace std;

#define MAXNUM 1000000
//////////////////////////////////////////////////////////////////
// node is for method 1
/////////////////////////////////////////////////////////////////
struct node {
        int idx;
        int val;
        node(int i, int v):idx(i), val(v) {}
};
struct cmp1 {
        bool operator() (node* a, node* b) {
                return a->val > b->val;
        }
};
struct cmp2 {
        bool operator() (node* a, node* b) {
                return a->val < b->val;
        }
};

////////////////////////////////////////////////////////////////
struct box
{
        int v;
        int x;
        int y;
        int z;
        void setVal(int a,int b,int c = 0)
        {
                x = a;
                y = b;
                z = c;
                v = c *100 + a*10+b;
        }
        box()
        {
                x = y = z = 0;
                v = MAXNUM;
        }
        void clear() {x = y = z = 0; v = MAXNUM;}
        bool operator <(const box &other)const   //降序排序
        {
                return v<other.v;
        }
        bool operator ==(const box &other) const
        {
                return v == other.v;
        }
};
/////////////////////////////////////////////////////////////////////
class simulator
{
private:
        int N;
        int D;
        box** mbox;
        vector<int> A;
        vector<int> B;
        set<int> FullStack;
        int* height;
        int currentStep;

        void init();

        void getHeight()
        {
                int i,j;
                for(i=1;i<N+1;++i)
                {
                        for(j=1;j<D+1;++j)
                        {
                                if(mbox[i][j].v != MAXNUM)
                                {
                                        break;
                                }
                        }
                        height[i] = D-j+1;
                        if(height[i] == D)
                                FullStack.insert(i);
                }
        }
        bool check_state()
        {
                A.clear();
                B.clear();
                FullStack.clear();
                getHeight();
                for(int i=1;i<N+1;++i)
                {
                        int j;
                        if(height[i] == 0)
                        {
                                B.push_back(i);
                                continue;
                        }
                        for(j=D;j > 0;--j)
                        {
                                if(mbox[i][j].v == MAXNUM || mbox[i][j-1].v == MAXNUM)
                                {
                                        B.push_back(i);
                                        break;
                                }
                                if(mbox[i][j]<mbox[i][j-1])
                                {
                                        A.push_back(i);
                                        break;
                                }

                        }

                }

                return A.empty();
        }
public:
        simulator()
        {
                N = 6;
                D = 6;
//                cout << "number of stacks: ";
//                cin >> N;
//                cout << "number of depths: ";
//                cin >> D;

                currentStep = 0;

                height = new int[N+1];
                height[0] = -1;
                mbox = new box*[N+1];
                for(int i=1;i<N+1;++i) {mbox[i] = new box[D+1];}
                init();
        }
        void print();
        void run();
        int chooseStart(int c);
        int chooseEnd(int c, int s);

        int getTopVal(int x)
        {
                return mbox[x][D+1-height[x]].v;
        }
        void setTopVal(int s, int x, int y, int z)
        {
                mbox[s][D-height[s]].setVal(x,y,z);
        }

        int getMinHeight();


        // for start
        int getMinHeightMaxBottom();
        int getMinHeightMaxBottom_method2();
        int getMaxTopMinHeightMaxBottom();
        // for end
        int getMinTopMaxHeightMinBottom(int s);
        int getMinTopMinHeightMaxBottom(int s);

        void updateMbox(int start, int end);
        void eraseVecItem(vector<int>& Ans, int elem);
};

#endif // DEF_H_INCLUDED
