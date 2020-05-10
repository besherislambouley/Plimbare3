/*
 * after removing an edge we will have two trees , the answer for this edge is the sum of diameters of the two trees + 1 
 * we use dp to know for every node the diameter in it's subtree & the tree without this current subtree 
*/
#define fast ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <bits/stdc++.h>
using namespace std;
#define sqr 547
//#define mp make_pair
#define mid (l+r)/2
#define pb push_back
#define ppb pop_back
#define fi first
#define se second
#define lb lower_bound
#define ub upper_bound
#define ins insert
#define era erase
#define C continue
#define mem(dp,i) memset(dp,i,sizeof(dp))
#define mset multiset
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef short int si;
typedef long double ld;
typedef pair<int,int> pi;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pi> vpi;
typedef vector<pll> vpll;
const ll inf=1e18;
const ll mod=1e9+7;
const ld pai=acos(-1);
int N ;
vi v [200009] ;
pi E [200009] ;
int Ord [200009] , DpDn [200009] , DpUp [200009] , MxDn [200009] , MxUp [200009] ; 
void Dfs1 ( int Node , int P ) {
	Ord [Node] = Ord [P] + 1 ;
	for ( auto u : v [Node] ) {
		if ( u == P ) C ;
		Dfs1 ( u , Node ) ;
		DpDn [Node] = max ( DpDn [Node] , max ( DpDn [u]  , MxDn [u] + MxDn [Node] + 1 ) ) ;
		MxDn [Node] = max ( MxDn [Node] , MxDn [u] + 1 ) ;
	}
}
void Dfs2 ( int Node , int P ) {
	pi MxMx1 , MxMx2 , MxMx3 , MxDp1 , MxDp2 ;
	MxDp1 = MxDp2 = MxMx1 = MxMx2 = MxMx3 = { 0 , -1 } ; 
	for ( auto u : v [Node] ) {
		if ( u == P ) C ;
		pi CrntDp = { DpDn [u] , u } ;
		pi CrntMx = { MxDn [u] , u } ; 
		if ( max ( MxDp1 , CrntDp ) == CrntDp ) {
			MxDp2 = CrntDp ;
			swap ( MxDp1 , MxDp2 ) ;
		}
		else MxDp2 = max ( MxDp2 , CrntDp ) ;
		if ( max ( MxMx1 , CrntMx ) == CrntMx ) {
			MxMx3 = CrntMx ;
			swap ( MxMx3 , MxMx2 ) ;
			swap ( MxMx2 , MxMx1 ) ;
		}
		else if ( max ( MxMx2 , CrntMx ) == CrntMx ) {
			MxMx3 = CrntMx ;
			swap ( MxMx2 , MxMx3 ) ;
		}
		else MxMx3 = max ( MxMx3 , CrntMx ) ;
	}
	for ( auto u : v [Node] ) {
		if ( u == P ) C ;
		int CrntMxDp = MxDp1 .fi ;
		if ( MxDp1 .se == u ) CrntMxDp = MxDp2 .fi ;
		pi CrntMxMx1 , CrntMxMx2 ;
		if ( u == MxMx1.se ) {
			CrntMxMx1 = MxMx2 ;
			CrntMxMx2 = MxMx3 ;
		}
		else if ( u == MxMx2.se ) {
			CrntMxMx1 = MxMx1 ;
			CrntMxMx2 = MxMx3 ;	
		}
		else {
			CrntMxMx1 = MxMx1 ;
			CrntMxMx2 = MxMx2 ;
		}
		int Merge1 = 0 ;
		if ( CrntMxMx1 .se != -1 && CrntMxMx2 .se != -1 ) Merge1 = CrntMxMx1.fi + CrntMxMx2.fi + 2 ;
		int Merge2 = 0 ;
		if ( CrntMxMx1 .se != -1 ) Merge2 = MxUp [Node] + CrntMxMx1.fi + 1 ;
		DpUp [u] = max ( max ( DpUp [Node] , CrntMxDp ) , max ( Merge1 , Merge2 ) ) ;
		DpUp [u] = max ( DpUp [u] , MxUp [Node] ) ; 
		int Merge3 = 0 ;
		if ( CrntMxMx1 .se != -1 ) Merge3 = CrntMxMx1.fi + 2 ;
		MxUp [u] = max ( MxUp [Node] + 1 , Merge3 ) ;
		Dfs2 ( u , Node ) ;
	}	
}
int main () {
	freopen ( "plimbare3.in" , "r" , stdin ) ;
	freopen ( "plimbare3.out", "w" , stdout) ;
	scanf("%d",&N);
	for ( int i = 0 ; i < N - 1 ; i ++ ) {
		int A , B ;
		scanf("%d%d",&A,&B);
		A -- , B -- ;
		v [A] .pb ( B ) ;
		v [B] .pb ( A ) ;
		E [i] = { A , B } ; 
	}
	Dfs1 ( 0 , 0 ) ; 
	Dfs2 ( 0 , 0 ) ; 
	for ( int i = 0 ; i < N - 1 ; i ++ ) {
		int A = E [i] .fi , B = E [i] .se ;
		if ( Ord [A] < Ord [B] ) swap ( A , B ) ;
		printf ("%d\n", DpDn [A] + DpUp [A] + 1 ) ; 
	}	
}
