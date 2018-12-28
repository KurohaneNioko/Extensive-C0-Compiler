const int MAX_NUM = 1024 ;

int factorial(int n){
   if(n<=1) 
	   return (1);
   else
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
  do
  {
    n = -1;
    s = j;
	i=1;
    do
    {
      x1 = (j/i) * i ;
      if( mod(j,i) == 0 )
      {
        n = n + 1;
        s = s - i;
	   if (n >= 128)
		  printf(" OVERFLOW!          ") ;
       else
		  k[n] = i;
      }
	  else
		  ;
	  i=i+1;
    }while(i<j)

    if(s==0)
    {
      printf(" complete number: ",j);
	  i=0;
	  do
	  {
      	printf("  ",k[i]);
		i=i+1;
	  }while(i<=n)
      printf("          ") ;
    }
	else
		;
    j=j+1;
  }while(j< MAX_NUM)

  printf(" ---------------------------------------------------------------          ");
  a = 0 ;
  i=0;
  do{
    b = a *i ;
    c = j * n ;
    a = a *i ;
    a = a + b + c;
	i=i+1;
  }while(i< MAX_NUM )

  b = a ;
  i=0;
  do{
    b = b + i ;
	i=i+1;
  }while( i < MAX_NUM )

  printf(" b = ", b) ;



  printf(" ---------------------------------------------------------------          ");
  h = 0 ;
  leap = 1 ;
  m = 2;
  do
  {
    k2 = m / 2;
	i = 2;
    do{
      x2 = (m/i)*i ;
      if( mod(m,i) == 0)
      {
        leap=0;
      }
	  else
		  ;
	  i=i+1;
    }while( i<=k2 )
    if(leap == 1)
    {
      printf(" ",m);
      h = h +1;

      x2 = (h/10)*10 ;
      if( x2 == h )
        printf("          ");
	  else
		  ;
     }
	 else
		 ;
     leap=1;
	 m=m+1;
  }while( m <= MAX_NUM )

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
