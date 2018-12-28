const int MAX_NUM = 1024 ;

int factorial(int n){
   if(n<=1) return (1);

   return(n*factorial(n-1)) ;
}

int mod(int x, int y){
   x=x-x/y*y;

   return (x) ;
}

void swap(int x, int y){
	int temp;

	printf(" x = ", x) ;
	printf(" y = ", y) ;
	temp = x;
	x=y;
	y=temp;
	printf(" SWAP x = ", x) ;
	printf(" SWAP y = ", y) ;
}


void complete_num(int val)
{
  int k[128];
  int i,j,n,s,x1;
  int m,k2,h,leap,x2;
  int a,b,c ;

  j=val;
  while(j< MAX_NUM)
  {
    n = -1;
    s = j;
	i=1;
    while(i<j)
    {
      x1 = (j/i) * i ;
      if( mod(j,i) == 0 )
      {
        n = n + 1;
        s = s - i;
	   if (n >= 128)
		  printf(" OVERFLOW!          ") ;
       if (n<128)
		  k[n] = i;
      }
	  i=i+1;
    }

    if(s==0)
    {
      printf(" complete number: ",j);
	  i=0;
	  while(i<=n)
	  {
      	printf("  ",k[i]);
		i=i+1;
	  }
      printf("          ") ;
    }
    j=j+1;
  }

  printf(" ---------------------------------------------------------------          ");
  a = 0 ;
  i=0;
  while(i< MAX_NUM ){
    b = a *i ;
    c = j * n ;
    a = a *i ;
    a = a + b + c;
	i=i+1;
  }

  b = a ;
  i=0;
  while( i < MAX_NUM ){
    b = b + i ;
	i=i+1;
  }

  printf(" b = ", b) ;



  printf(" ---------------------------------------------------------------          ");
  h = 0 ;
  leap = 1 ;
  m = 2;
  while( m <= MAX_NUM )
  {
    k2 = m / 2;
	i = 2;
    while( i<=k2 ){
      x2 = (m/i)*i ;
      if( mod(m,i) == 0)
      {
        leap=0;
      }
	  i=i+1;
     }
    if(leap == 1)
    {
      printf(" ",m);
      h = h +1;

      x2 = (h/10)*10 ;
      if( x2 == h )
        printf("          ");
     }
     leap=1;
	 m=m+1;
  }

  printf("          The total is ",h);

}


void main()
{
   int n ;

   n = factorial(10) ;
   printf(" 10! = ", n) ;

   swap(5,10) ;

   complete_num(2) ;
}
