//Usage getsize(1,0)
//sack(1,0,0)
//col[] has the node values.
//sbsz[] has the subtree size
//cnt[] has the count of occurence of col[i] in subtree of u.
//O(nlogn)

vector<int> adjlst[MAX];
int n,cnt[MAX],big[MAX],sbsz[MAX]={0},col[MAX];

void getsize(int u,int p){
	sbsz[u]=1;
	for(auto v:adjlst[u])
		if(v!=p){
			getsize(v,u);
			sbsz[u]+=sbsz[v];
		}
}

void add(int u,int p,int vl){
	cnt[col[u]]+=vl;
	for(auto v:adjlst[u])
		if(v!=p && !big[v])
			add(v,u,vl);
}

void sack(int u,int p,bool kp){
	int bigc=-1,mx=-1;
	for(auto v:adjlst[u]){
		if(v!=p && mx<sbsz[v]){
			mx=sbsz[v];
			bigc=v;
		}
	}
	for(auto v:adjlst[u])
		if(v!=p && bigc!=v)
			sack(v,u,0);
	if(bigc!=-1){
		sack(bigc,u,1);
		big[bigc]=1;
	}
	add(u,p,1);
	
	//Now cnt has the value for subtree of x
	// so now compute answer

	if(bigc!=-1)
		big[bigc]=0;
	
	if(!kp)
		add(u,p,-1);
}