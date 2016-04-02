#ifndef DEF_H_INCLUDED
#define DEF_H_INCLUDED
#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <stack>
using namespace std;
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
                x = y = z =  v = 0;
        }
        void clear() {x = y = z = v =0;}
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
                                if(mbox[i][j].v != 0)
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
                        for(j=D;j>1;--j)
                        {
                                if(mbox[i][j]<mbox[i][j-1])
                                {
                                        A.push_back(i);
                                        break;
                                }
                                if(mbox[i][j-1].v == 0)
                                {
                                        B.push_back(i);
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
        // for start
        int getMinHeightMaxBottom();
        int getMaxTopMinHeightMaxBottom();
        // for end
        int getMinTopMaxHeightMinBottom(int s);
        int getMinTopMinHeightMaxBottom(int s);

        void updateMbox(int start, int end);
        void eraseVecItem(vector<int>& Ans, int elem);
};

#endif // DEF_H_INCLUDED
