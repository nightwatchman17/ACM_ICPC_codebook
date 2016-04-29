int lps(const char *str){
	// return len of longest palindrom substring
	static char emptyChar = '@';
	static char tmp[maxLen*2];
	static int lprb[maxLen*2];
	// [i-lprb[i], i+lprb[i]] is the lps when mid is i
	for(int i=0, j=-1; true; ++i){
		if( str[i]=='\0' ){
			tmp[++j] = emptyChar;
			tmp[++j] = '\0';
			break;
		}
		tmp[++j] = emptyChar;
		tmp[++j] = str[i];
	}
	lprb[0] = 0;
	int rightBorder = 0 , midId = 0;
	for(int i=1; tmp[i]!='\0'; ++i){
		if( i>rightBorder ){
			rightBorder = i;
			midId = i;
			lprb[i] = 0;
		}
		int mirId = midId - (i-midId);
		if( i+lprb[mirId] > rightBorder )
			lprb[i] = rightBorder - i;
		else if( i+lprb[mirId] < rightBorder )
			lprb[i] = lprb[mirId];
		else{
			int j=lprb[mirId];
			while( tmp[i+j]!='\0' && i-j>=0 && tmp[i+j]==tmp[i-j])
				++j;
			rightBorder = i+j-1;
			midId = i;
			lprb[i] = j-1;
		}
	}
	int ans = 1;
	for(int i=0 ; tmp[i]!='\0' ; ++i)
		if( lprb[i]>ans )
			ans = lprb[i];
	return ans;
}
