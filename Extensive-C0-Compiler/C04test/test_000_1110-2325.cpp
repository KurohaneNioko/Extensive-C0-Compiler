#define _CRT_SECURE_NO_WARNINGS

#include<cstdio>

const int zero = 0;
const int one = 1, minus_two = -0002;
const char renn = '0';
const char first_alpha = 'a', first_captical = 'A';
int x;

int fact(int t)
{
	if(t < 3)
		return(t);
	else
		return(fact(t-1)*t);
}

int rt15()
{
	return(3*5);
}

void fun2()
{
	printf("114514");
	return;
}

void main()
{
	const int b = +01, c = 2, d = 3, e = 4;
	char ar[2];
	int r, m1[8];
	int aa, a;
	
	x = -1;
	r = -4;
	aa = 6;
	printf("!@#$%%abcdABCD963287~;: %d", aa);
	printf("%d", fact(aa));
	fun2();
	ar[1] = '0'+rt15();
	aa = -b * ar[1] + (c - e * 9) + 2 * 'm';
	printf("%d", aa);
	a = aa;
	scanf("%d%d", &a, &x);
	if (a > 0)
	{
		printf("\narea 1 hit\n");
		if (x <= 0) {
			r = a / x * a;
			printf("\narea 2 hit\n");
		}
		r = r + aa;
	}
	if (x != 0)
	{
		printf("3 hit");
		if (a == -4)
		{
			r = r + 1;
			printf("\narea 4 hit\n");
		}
	}
	if (a < 0)
	{
		printf("5 hit ");
		if (x >= 0)
		{
			r = r + a;
			printf("\narea 6 hit\n");
		}
	}
	else
	{
		r = r * -1;
		printf("%d", r);
	}
	for(a = -2; a<d; a = a+1)
	{
		x = x + e;
	}
	while (x > 0)
	{
		x = x - c;
	}
	printf("%d", x);
}