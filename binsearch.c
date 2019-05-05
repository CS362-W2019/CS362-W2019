#include <stdio.h>
#include <assert.h>
int binsearch(int a[], int n, int x)
{
        int low = 0;
        int high = n-1;
        int mid;
        while(low <=  high)
        {
                mid = (low + high) / 2;
                if(a[mid] == x)
                {
                        return mid;
                }
                else if (x<a[mid])
                {
                        high = mid - 1;
                }
                else
                {
                        low = mid + 1;
                }
        }
        return -1;
}
void test()
{
        int a[7] = {2,4,6,8,10,12,14};
        int element_index = binsearch(a,7,4);
        assert(element_index == 1);
        element_index = binsearch(a,7,2);
        assert(element_index == 0);
        element_index = binsearch(a,7,10);
        assert(element_index == 4);
        element_index = binsearch(a,7,14);
        assert(element_index == 6);
        element_index = binsearch(a,7,28);
        assert(element_index == -1);
}
int main()
{
        test();
        return 0;
}
