class kmp{
	private:
		int  prefix[maxLen];
		char pat[maxLen];
	public:
		void setPattern(const char *str){
			strcpy(pat, str);
			prefix[0] = -1;
			int i=1 , j=0;
			for( ; str[i]!='\0' ; ++i , ++j ){
				if( str[i]==str[j] )
					prefix[i] = prefix[j];
				else
					prefix[i] = j;
				while( j>=0 && str[j]!=str[i] )
					j = prefix[j];
			}
			prefix[i] = j;
		}
		int search(const char *str){
			// return index of str match pattern
			int i=0 , j=0;
			for( ; str[i]!='\0' && pat[j]!='\0' ; ++i,++j){
				while( j>=0 && pat[j]!=str[i] )
					j = prefix[j];
			}
			if( pat[j]=='\0' )
				return i-j;
			return -1;
		}
		int countMatched(const char *str){
			// return # of pattern in str
			int cnt = 0;
			int i=0 , j=0;
			while( true ){
				if( pat[j]=='\0' ) ++cnt;
				if( str[i]=='\0' ) break;
				while( j>=0 && pat[j]!=str[i] )
					j = prefix[j];
				++i , ++j;
			}
			return cnt;
		}
};
