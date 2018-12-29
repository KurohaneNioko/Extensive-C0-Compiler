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

 10! = 3628800 x = 5 y = 10 SWAP x = 10 SWAP y = 5 complete number: 6  1  2  3
 complete number: 28  1  2  4  7  14           
 complete number: 496  1  2  4  8  16  31  62  124  248           
 --------------------------------------------------------------- 
 b = -1465899520 
 ---------------------------------------------------------------
 2 3 5 7 11 13 17 19 23 29           
 31 37 41 43 47 53 59 61 67 71           
 73 79 83 89 97 101 103 107 109 113           
 127 131 137 139 149 151 157 163 167 173           
 179 181 191 193 197 199 211 223 227 229           
 233 239 241 251 257 263 269 271 277 281           
 283 293 307 311 313 317 331 337 347 349           
 353 359 367 373 379 383 389 397 401 409           
 419 421 431 433 439 443 449 457 461 463           
 467 479 487 491 499 503 509 521 523 541           
 547 557 563 569 571 577 587 593 599 601           
 607 613 617 619 631 641 643 647 653 659           
 661 673 677 683 691 701 709 719 727 733           
 739 743 751 757 761 769 773 787 797 809           
 811 821 823 827 829 839 853 857 859 863           
 877 881 883 887 907 911 919 929 937 941           
 947 953 967 971 977 983 991 997 1009 1013           
 1019 1021          The total is 172
