#include "def.h"
simulator::simulator()
{
        currentStep = 0;
        box = new int*[N+1];
        for(int i = 0; i < N+1; ++i)
        {
                box[i] = new int[D+1];
                for(int j = 0; j < D+1; ++j)
                {
                        box[i][j] = B+1;
                }
        }
        setValue();
        minList = new Box[N];
}
void simulator::run()
{
        move(1);
        move(2);
        move(3);
        move(4);
        move(5);
        move(6);
        move(7);
        move(8);
        move(9);
        move(10);
        move(11);
        move(12);
}
int simulator::getTop(int i)
{
        int j = 0;
        while(box[i][j] == B+1)
        {
                j++;
        }
        if(j > D)
                return -1;// all is empty
        else
                return j;
}

void simulator::setValue()
{
        box[1][9] = 9;
        box[1][8] = 12;
        box[1][7] = 1;
        box[2][9] = 5;
        box[2][8] = 2;
        box[2][7] = 6;
        box[3][9] = 4;
        box[3][8] = 7;
        box[4][9] = 10;
        box[5][9] = 3;
        box[5][8] = 11;
        box[6][9] = 8;
}

void simulator::getXY(int n, int& x, int& y)
{
        for (int i=1 ; i<N+1; ++i)
        {
                for (int j=1; j<D+1; ++j)
                {
                        if(box[i][j] == n)
                        {
                                x = i;
                                y = j;
                        }
                }
        }
}

bool simulator::isTop(int x, int y)
{
        if(box[x][y] != B+1 && box[x][y-1] == B+1)
        {
                return true;
        }
        return false;
}

void simulator::updateMinList()
{
        for (int i =1;i <N+1; ++i)
        {
                int min = B+1;
                int minj = -1;
                for (int j=1; j<D+1;++j)
                {
                         if(box[i][j]<min){
                                min = box[i][j];
                                minj = j;
                        }
                }
                minList[i-1].val = min;
                minList[i-1].x = i;
                minList[i-1].y = minj;
        }
        sort(minList,minList+N);
}

void simulator::print()
{
        for (int j=1;j<D+1;++j)
        {
                for (int i = 1;i<N+1;++i)
                {
                        if(box[i][j] == B+1)
                        {
                                cout << " "<<"\t";
                        }
                        else
                                cout << box[i][j] << "\t";
                }
                cout << "\n";
        }

        cout << "=========================================\n";

        updateMinList();

        for (int j=0;j<N;++j)
        {
                cout << minList[j].val << "\t";
        }
}
