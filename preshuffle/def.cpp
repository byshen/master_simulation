#include "def.h"

void simulator::init()
{
        mbox[1][6].setVal(2,3,3);
        mbox[1][5].setVal(5,2,3);
        mbox[1][4].setVal(3,3,2);
        mbox[2][6].setVal(1,2,1);
        mbox[2][5].setVal(4,2,2);
        mbox[2][4].setVal(5,3,2);
        mbox[3][6].setVal(3,1,1);
        mbox[3][5].setVal(4,2,1);
        mbox[3][4].setVal(2,1,3);
        mbox[3][3].setVal(4,3,1);
        mbox[3][2].setVal(3,2,3);
        mbox[4][6].setVal(2,1,2);
        mbox[4][5].setVal(2,2,2);
        mbox[5][6].setVal(3,3,2);
        mbox[5][5].setVal(2,1,1);
        mbox[5][4].setVal(2,2,1);
        mbox[5][3].setVal(1,1,3);
        mbox[6][6].setVal(3,3,1);
        mbox[6][5].setVal(1,2,3);
        mbox[6][4].setVal(4,3,1);
        mbox[6][3].setVal(2,3,3);
        mbox[6][2].setVal(5,2,3);
        mbox[7][6].setVal(2,1,1);
        mbox[7][5].setVal(3,2,1);
        mbox[7][4].setVal(4,2,2);
        mbox[7][3].setVal(2,1,1);
        mbox[7][2].setVal(4,2,2);
        mbox[8][6].setVal(2,3,1);
        mbox[8][5].setVal(4,3,1);
        mbox[8][4].setVal(3,2,3);
        mbox[8][3].setVal(5,2,3);
        mbox[8][2].setVal(5,2,3);
        mbox[9][6].setVal(5,3,3);
        mbox[9][5].setVal(4,1,2);
        mbox[9][4].setVal(4,2,2);
        mbox[9][3].setVal(2,1,1);
        mbox[10][6].setVal(4,3,2);
        mbox[10][5].setVal(3,1,1);
        mbox[10][4].setVal(2,3,3);
        mbox[10][3].setVal(1,1,3);
        mbox[10][2].setVal(3,3,1);
        mbox[10][1].setVal(2,1,3);
}

void simulator::print()
{
        for(int j=1;j<D+1;++j)
        {
                for (int i=1;i<N+1;++i)
                {
                        if(mbox[i][j].v == MAXNUM)
                        {
                                cout << " " << "\t";
                        }
                        else
                                cout << mbox[i][j].v <<"\t";
                }
                cout << "\n";
        }
        getHeight();

        for(int i=1;i<N+1;++i)
               cout<< height[i]<<"\t";
        cout <<endl;

        check_state();

        cout << "A: ";
        for(size_t i =0;i <A.size();++i)
        {
                cout << A[i] <<"\t";
        }
        cout <<endl;
        cout << "B: ";
        for(size_t i =0;i <B.size();++i)
        {
                cout << B[i] <<"\t";
        }
        cout <<endl;

}

int simulator::getMinHeight()
{
        int minv = 1000000000;
        vector<int> res;
        for(int i=1;i<N+1;++i)
        {
                if(height[i]!=0 && height[i] < minv )
                {
                        minv = height[i];
                        res.clear();
                        res.push_back(i);
                        continue;
                }
                if(height[i] == minv)
                {
                        res.push_back(i);
                }
        }

        return res[0];
}
int simulator::getMinHeightMaxBottom()
{
        int minv = 1000000000;
        vector<int> res;
        for(int i=1;i<N+1;++i)
        {
                if(height[i]!=0 && height[i] < minv )
                {
                        minv = height[i];
                        res.clear();
                        res.push_back(i);
                        continue;
                }
                if(height[i] == minv)
                {
                        res.push_back(i);
                }
        }

        if (res.size() == 1)
        {
                return res[0];
        }
        else // choose the biggest c of the min height
        {
                int big = -1;
                int z = -1;
                for (size_t i=0;i<res.size();++i)
                {
                        if(mbox[res[i]][D].v  > big)
                        {
                                big = mbox[res[i]][D].v;
                                z = res[i];
                        }
                }
                return z;
        }
}
void simulator::eraseVecItem(vector<int>& Ans, int elem)
{
       vector<int>::iterator it;
        for (it= Ans.begin();it!=Ans.end();)
        {
                if(*it == elem)
                        it = Ans.erase(it);
                else
                        ++it;
        }
}
int simulator::getMinTopMinHeightMaxBottom(int start)
{
        //去除start已选出和满栈的栈
        // 从压栈的栈中选啊啊啊啊啊
        vector<int> res(A);

        eraseVecItem(res, start);

        if (!FullStack.empty())
        {
                for(size_t i = 0;i<res.size();++i)
                {
                        if(FullStack.find(res[i]) != FullStack.end())
                        {
                                eraseVecItem(res, res[i]);
                        }
                }
        }

        if (res.size() == 0)
        {
                cout <<FullStack.size();
                cout << "Error\n";
                return -1;
        }
        if (res.size() == 1)
                return res[0];

       // cout <<"1 res " << res.size() << endl;
        int mint = 1000000000;
        vector<int> res1;
        for(size_t i=0;i<res.size();++i)
        {
                if(getTopVal(res[i]) < mint)
                {
                        mint = getTopVal(res[i]);
                        res1.clear();
                        res1.push_back(res[i]);
                        continue;
                }
                if(getTopVal(res[i]) == mint)
                {
                        res1.push_back(res[i]);
                }
        }
     //   cout <<"1 res " << res1.size() << endl;
        if(res1.size() == 1)
                return res1[0];
        else
        {
                int minh = 1000000000;
                vector<int> res2;
                for(size_t i=0;i<res1.size();++i)
                {
                        if(height[res1[i]] < minh)
                        {
                                minh = height[res1[i]];
                                res2.clear();
                                res2.push_back(res1[i]);
                                continue;
                        }
                        if(height[res1[i]] == minh)
                        {
                                res2.push_back(res1[i]);
                        }
                }
       // cout <<"1 res " << res2.size() << endl;
                if (res2.size() == 1)
                {
                        return res2[0];
                }
                else // choose the biggest c of the min height
                {
                        int big = -1;
                        int z = -1;
                        for (size_t i=0;i<res2.size();++i)
                        {
                                if(mbox[res2[i]][D].v  > big)
                                {
                                        big = mbox[res2[i]][D].v;
                                        z = res2[i];
                                }
                        }
                        return z;
                }

        }
}
int simulator::getMinTopMaxHeightMinBottom(int start)
{
        //去除start已选出和满栈的栈
        // 从不压栈的栈中选啊啊啊啊啊
        // 还需要大于start啊
        vector<int> res(B);

        eraseVecItem(res, start);

        if (!FullStack.empty())
        {
                for(size_t i = 0;i<res.size();++i)
                {
                        if(FullStack.find(res[i]) != FullStack.end())
                        {
                                eraseVecItem(res, res[i]);
                        }
                }
        }
    //    cout <<"1 end res " << res.size() <<endl;


        if (res.size() == 0)
        {
                cout << "Error\n";
                return -1;
        }
        if (res.size() == 1)
                return res[0];

        int mint = 1000000000;

        for(size_t i=0;i<res.size();++i)
        {
                if (height[res[i]]==0)
                        return res[i];
        }
        vector<int> res1;
        for(size_t i=0;i<res.size();++i)
        {
                if(getTopVal(res[i]) < mint)
                {
                        mint = getTopVal(res[i]);
                        res1.clear();
                        res1.push_back(res[i]);
                        continue;
                }
                if(getTopVal(res[i]) == mint)
                {
                        res1.push_back(res[i]);
                }
        }
    //    cout <<"1 end res " << res1.size() << res1[0]<<endl;
        if(res1.size() == 1)
                return res1[0];
        else
        {
                int maxh = -1;
                vector<int> res2;
                for(size_t i=0;i<res1.size();++i)
                {
                        if(height[res1[i]] > maxh)
                        {
                                maxh = height[res1[i]];
                                res2.clear();
                                res2.push_back(res1[i]);
                                continue;
                        }
                        if(height[res1[i]] == maxh)
                        {
                                res2.push_back(res1[i]);
                        }
                }
     //           cout <<"1 end res " << res2.size() <<endl;
                if (res2.size() == 1)
                {
                        return res2[0];
                }
                else // choose the smallest c of the max height
                {
                        int small = 1000000000;
                        int z = -1;
                        for (size_t i=0;i<res2.size();++i)
                        {
                                if(mbox[res2[i]][D].v  < small)
                                {
                                        small = mbox[res2[i]][D].v;
                                        z = res2[i];
                                }
                        }
                        return z;
                }
        }
}
int simulator::getMaxTopMinHeightMaxBottom()
{
        // 从压栈的栈中选啊
        vector<int> res(A);

        if (res.size() == 1)
                return res[0];

        int maxt = -1;
        vector<int> res1;
        for(size_t i=0;i<res.size();++i)
        {
                if(getTopVal(res[i]) > maxt)
                {
                        maxt = getTopVal(res[i]);
                        res1.clear();
                        res1.push_back(res[i]);
                        continue;
                }
                if(getTopVal(res[i]) == maxt)
                {
                        res1.push_back(res[i]);
                }
        }
       // cout <<"1 choose start: " << res1[0] <<endl;
        if(res1.size() == 1)
                return res1[0];
        else
        {
                int minh = 1000000000;
                vector<int> res2;
                for(size_t i=0;i<res1.size();++i)
                {
                        if(height[res1[i]] < minh)
                        {
                                minh = height[res1[i]];
                                res2.clear();
                                res2.push_back(res1[i]);
                                continue;
                        }
                        if(height[res1[i]] == minh)
                        {
                                res2.push_back(res1[i]);
                        }
                }

                if (res2.size() == 1)
                {
                        return res2[0];
                }
                else // choose the biggest c of the min height
                {
                        int big = -1;
                        int z = -1;
                        for (size_t i=0;i<res2.size();++i)
                        {
                                if(mbox[res2[i]][D].v  > big)
                                {
                                        big = mbox[res2[i]][D].v;
                                        z = res2[i];
                                }
                        }
                        return z;
                }

        }
}
int simulator::chooseStart(int cs)
{
        switch(cs)
        {
        case 1:
                return getMaxTopMinHeightMaxBottom();
                break;
        case 2:
                return getMinHeightMaxBottom();
                break;
        case 3:
                return getMinHeightMaxBottom();
                break;
        default:
                cout << "fuck ur mother!!!!!!!!!!\n";
                return -1;
        }
}
int simulator::chooseEnd(int cs, int start)
{
        set<int>::iterator its;
        bool CASE2B;
        bool CASE2A;
        switch(cs)
        {
        case 1:
                return getMinTopMaxHeightMinBottom(start);
                break;

        case 2:
                // A压箱，B不压箱
                // 看看是不是有未达到最大高度的不压箱栈
                // 使用一个小技巧，只有当不压箱个数为1 且 为start时 或者 所有的不压箱栈都是在FULLSTACK
                // 需要从压箱的栈中进行选取
                // 而如果有不压箱栈且高度允许，可以选，就可以用getMinTopMaxHeightMinBottom()
                CASE2A = true;
                if (B.size() == 1 && B[0] == start)
                        CASE2A = false;

                CASE2B = false;

                for(size_t i=0;i<B.size();++i)
                {
                        if(FullStack.find(B[i]) == FullStack.end())
                        {
                                CASE2B = true;
                        }
                }
   //             cout << "case2 " << CASE2A << " " <<CASE2B << endl;
                if (CASE2A == false || CASE2B == false)
                {
                        return getMinTopMinHeightMaxBottom(start);
                }
                else
                {
                        return getMinTopMaxHeightMinBottom(start);
                }
                break;
        case 3:
                return getMinTopMinHeightMaxBottom(start);
                break;
        }
}
void simulator::run()
{
        int cs;
        int start = -1;
        int end = -1;
        int last_s;
        int last_e;

        while(!check_state() && currentStep != 50)
        {
                cout <<"----------------------------------------------------------\n";
                last_e = end;
                last_s = start;

                currentStep++;
                if(B.empty()) // the third state
                {
                        cs = 3;
                        cout << currentStep << " + method 3"<< endl;
                }
                else
                {
                        // first state, exist a
                        // A is ya xiang zhan, B is bu ya xiang zhan
                        // exist i in A , j in B, b(i) <= b(j)

                       // priority_queue<int,vector<int>, greater<int> > ba;// min heap
                       // priority_queue<int> bb;// max heap
                        priority_queue<node*, vector<node*>, cmp1> q; // min for A
                        priority_queue<node*, vector<node*>, cmp2> p; // max for B

                        for(size_t i=0;i<A.size();++i)
                        {
                                q.push(new node(A[i],getTopVal(A[i]) ) );
                        }
                        for(size_t i=0;i<B.size();++i)
                        {
                                p.push(new node(B[i],getTopVal(B[i]) ) );
                        }
              //          cout << q.top()->val << "**" << p.top()->val <<endl;
                        if (q.top()->val <= p.top()->val )
                        {
                                cs = 1;
                                cout << currentStep << " + method 1"<< endl;

                                stack<node* > s;
                                while(1)
                                {
                                        if(q.empty())
                                                break;

                                        s.push(q.top()); q.pop();
                                        if(s.top()->val > p.top()->val)
                                        {
                                                s.pop();
                                                break;
                                        }
                                }
     //                           cout << s.size() << " sdfdsafsadf\n";

                                stack<node* > e;
                                while(1)
                                {
                                        if(p.empty())
                                                break;
                                        int tmp = p.top()->idx;



                                        e.push(p.top()); p.pop();

                                        if(e.top()->val < s.top()->val)
                                        {
                                                e.pop();
                                                break;
                                        }
                                }
    //                            cout << e.size() << " sdfdsafsadf\n";


    //                            cout << s.top()->val<< " " << e.top()->val<<endl;
                                start = s.top()->idx;
                                end = e.top()->idx;


                        }
                        else{
                                cs = 2;
                                cout << currentStep << " + method 2"<< endl;
                        }
                }
                if(cs!= 1)
                {
                        start = chooseStart(cs);
                        end = chooseEnd(cs,start);

                        if(start == last_e && end == last_s)
                        {
                                ///
                                cout << "fuck !!!!!!!!!!!!!!!!!\n";
                                start = getMinHeight();
                                end = chooseEnd(3, start);
                        }

                }
                cout <<"start" << start <<"end"<<end<<endl;
                updateMbox(start, end);
                print();

                cout <<"----------------------------------------------------------\n";
        }
        cout<< "Total steps: " << currentStep << endl;
}
void simulator::updateMbox(int start, int end)
{
        int x = mbox[start][D+1-height[start]].x;
        int y = mbox[start][D+1-height[start]].y;
        int z = mbox[start][D+1-height[start]].z;

        mbox[start][D+ 1 -height[start]].clear();
        mbox[end][D-height[end]].setVal(x,y,z);

}
