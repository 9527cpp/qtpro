#include <iostream>
#include <iterator>
#include <functional>

using namespace std;


bool binarysearch_re(int * p,int len,int val)
{
    function<bool(int *,int,int,int)> binarysearch_re_lambda = [&binarysearch_re_lambda](int*p,int l,int h,int val)
    {
        if(l>=h)return false;
        int m = (l+h)/2;
        if(p[m] == val){printf("the val:[%d]'s index is[%d]\r\n",val,m);return true;}
        else if(p[m] > val)binarysearch_re_lambda(p,l,m,val);
        else if(p[m] < val)binarysearch_re_lambda(p,m,h,val);
    };
    bool bFind = binarysearch_re_lambda(p,0,len-1,val);
    return bFind;
}


bool binarysearch(int * p,int len,int val)
{
    bool bFind = false;
    int l = 0;
    int h = len;
    int m = (l+h)/2;
    while(l<h)
    {
        m = (l+h)/2;
        if(p[m] < val)l = m+1;
        else if(p[m] > val)h = m;
        else if(p[m] == val)
        {
            bFind = true;
            printf("the val:[%d]'s index is[%d]\r\n",val,m);
            break;
        }
    }
    return bFind;
}



int main()
{
    int array[] = {1,2,3,4,5,6,7,8,9};
    int len = sizeof(array)/sizeof(array[0]);
    int bFind = binarysearch(array,len,4);
    //int bFind = binarysearch_re(array,len,4);
    printf("bFind = %d",bFind);
    return 0;
}