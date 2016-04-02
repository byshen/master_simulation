#ifndef DEF_H_INCLUDED
#define DEF_H_INCLUDED
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
struct Box
{
        int val;
        int x;
        int y;
        bool operator <(const Box &other)const   //降序排序
        {
                return val>other.val;
        }
};

class simulator
{
public:
        void run();
        // get a_n's xy
        void getXY(int n, int& x, int& y);

        bool isTop(int x, int y);

        int getTop(int i);
        void updateMinList();

        void move(int target)
        {
                int xt, yt; // target's coordinate
                getXY(target, xt, yt);

                while(!isTop(xt,yt)) // deal with the boxes on the target
                {
                        int ytop = getTop(xt);
                        updateMinList();
                        int tmpTarget = box[xt][ytop];
                        int ptr = 0;
                        while(minList[ptr].val == B+1) ptr++;
                        if(ptr <N-1 && minList[ptr].val > tmpTarget) // 有不压箱的
                        {
                                while(minList[ptr].val > tmpTarget) ptr++;
                                ptr--;

                                int movToX = minList[ptr].x;
                                int movToY = getTop(movToX)-1;

                                int movToVal = box[movToX][movToY+1];
                                if(movToVal == tmpTarget + 1)
                                {

                                }
                                else
                                {
                                        if(movToVal > 5 + tmpTarget)
                                        {// 且不能超过最高的顶啊！！！留下一个位置！！ 先不管了 ==
                                                for(int ii = movToVal-1; ii >= movToVal -5; --ii)
                                                {
                                                        int xii, yii;
                                                        getXY(ii, xii, yii);
                                                        if(isTop(xii,yii))
                                                        {
                                                                box[xii][yii] = B+1;
                                                                box[movToX][movToY] = ii;
                                                                movToY--;
                                                        }
                                                        print();
                                                }
                                        }
                                        else
                                        {
                                                for(int ii = movToVal-1; ii > tmpTarget; --ii)
                                                {
                                                        int xii, yii;
                                                        getXY(ii, xii, yii);
                                                        if(isTop(xii,yii))
                                                        {
                                                                box[xii][yii] = B+1;
                                                                box[movToX][movToY] = ii;
                                                                movToY--;
                                                        }
                                                        print();
                                                }
                                        }
                                }

                                // 将本来的那个移入
                                box[xt][ytop] = B+1;
                                box[movToX][movToY] = tmpTarget;

                        }
                        else // 没有不压箱的
                        {
                                if(ptr<N-2)
                                {
                                        int movToX = minList[ptr].x;
                                        int movToY = getTop(movToX)-1;
                                        box[xt][ytop] = B+1;
                                        box[movToX][movToY] = tmpTarget;

                                }
                                else
                                {
                                        int movToX = minList[0].x;
                                        int movToY = D;
                                        box[xt][ytop] = B+1;
                                        box[movToX][movToY] = tmpTarget;
                                }
                        }
                        currentStep++;
                        print();
                }
                if(isTop(xt,yt)) { // find it !!! and move !!
                        currentStep++;
                        box[xt][yt] = B+1;
                        print();
                }
        }

        void print();

        simulator();

private:
        const int N = 6; // NUM OF STACKS
        const int D = 9; // DEPTH OF STACK
        const int B = 12;// TOTAL NUMBER OF BOXES TO BE MOVED

        int currentStep;
        int** box;


        Box* minList;
        // initial the boxes as the graph init.png
        void setValue();
};

#endif // DEF_H_INCLUDED
