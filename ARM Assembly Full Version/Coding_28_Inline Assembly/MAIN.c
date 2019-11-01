

__inline int getSum(int a, int d)
{
	int sum;
	__asm
	{
		ADD sum,a,d
	}
	return sum;
}

//c=x+y 
//x=10
//y=20

int c;
int main()
{
	int x,y;
	x=10;
	y=20;
	c=getSum(x,y);
		while(1)
		{
			
		}
	
}
