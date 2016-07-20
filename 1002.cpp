#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<string>
#include<vector>
#include<iostream>
#include<set>

using namespace std;

long long m;

struct matrix
{
	long long a[3][3];
	matrix()
	{
		memset( a , 0 , sizeof a );
	}
	friend matrix operator + ( const matrix &x , const matrix &y )
	{
		matrix ret;
		for( int i = 0 ; i < 2 ; i++ )
			for( int j = 0 ; j < 2 ; j++ )
				ret.a[i][j] = (x.a[i][j]+y.a[i][j])%m;
		return ret;
	}
	friend matrix operator * ( const matrix &x , const matrix &y )
	{
		matrix ret;
		for( int i = 0 ; i < 2 ; i++ )
			for( int j = 0 ; j < 2 ; j++ )
				for( int k = 0 ; k < 2 ; k++ )
					ret.a[i][j] = (ret.a[i][j]+x.a[i][k]*y.a[k][j])%m;
		return ret;
	}
	friend bool operator == ( const matrix &x , const matrix &y )
	{
		for( int i = 0 ; i < 2 ; i++ )
			for( int j = 0 ; j < 2 ; j++ )
				if( x.a[i][j] != y.a[i][j] )
					return 0;
		return 1;
	}
	friend bool operator < ( const matrix &x , const matrix &y )
	{
		for( int i = 0 ; i < 2 ; i++ )
			for( int j = 0 ; j < 2 ; j++ )
				if( x.a[i][j] < y.a[i][j] )
					return 1;
				else if( x.a[i][j] > y.a[i][j] )
					return 0;
		return 0;
	}
	void print()
	{
		for( int i = 0 ; i < 2 ; i++ )
		{
			for( int j = 0 ; j < 2 ; j++ )
				cout << a[i][j] << " ";
			cout << endl;
		}
	}
} I , x;
set < matrix > s;
long long tim;

matrix fast_pow( matrix x , int n )
{
	matrix ret = I;
	for( ; n ; n >>= 1 , x = x*x )
		if( n&1 )
			ret = ret*x;
	return ret;
}

long long fast_pow_int( int n )
{
	long long ret = 1 , x = 2;
	for( ; n ; n >>= 1 , x = (x*x)%tim )
		if( n&1 )
			ret = (ret*x)%tim;
	return ret;
}

bool check( int x )
{
	for( int i = 2 ; i*i <= x ; i++ )
		if( x % i == 0 )
			return 0;
	return 1;
}

long long get_tim( long long m )
{
	if( fast_pow( x , m-1 ) == I )
		return m-1;
	return m+1;
}

int main()
{
	I.a[0][0] = I.a[1][1] = 1;
	x.a[0][0] = 5;
	x.a[0][1] = 2;
	x.a[1][0] = 12;
	x.a[1][1] = 5;
	int t , n;
	scanf( "%d" , &t );
	for( int ca = 1 ; ca <= t ; ca++ )
	{
		scanf( "%d%lld" , &n , &m );
		if( m == 3 )
			tim = 6;
		else
			tim = get_tim( m );
		matrix x , ans;
		ans.a[0][0] = 5;
		ans.a[0][1] = 2;
		x.a[0][0] = 5;
		x.a[0][1] = 2;
		x.a[1][0] = 12;
		x.a[1][1] = 5;
		ans = ans*fast_pow( x , fast_pow_int( n ) );
		printf( "Case #%d: %lld\n" , ca , (2*ans.a[0][0]-1)%m );
	}
	return 0;
}
