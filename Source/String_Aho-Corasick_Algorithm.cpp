#include <queue>
#include <cstdio>
#include <cstring>
using namespace std;
struct AC_algorithm {
	struct node {
		static const int signNum = 52;	//number of kind of character
		node *ch[signNum];
		node *suffix, *dict;			
		int index;
		node() {
			memset(ch, 0, sizeof(ch));
			suffix = dict = 0;
			index = -1;
		}
	};
	
	static const int stringNum = 100010;//number of pattern
	node *root;
	int occur[stringNum];				//string i occur occur[i] times
	int reflect[stringNum];				//string i is the same as string reflect[i];
	
	AC_algorithm() {
		root = new node();
		memset(occur, 0, sizeof(occur));
		memset(reflect, -1, sizeof(reflect)); 
	}
	
	int decode(char c) {				//decode char
		return c <= 'Z' ? (c - 'A') : (c - 'a' + 26);
	}
	
	void insert(char *s,int index) {	//add string to trie
		node *p = root;
		for(; *s; s++) {
			int code = decode(*s);
			if(p->ch[code] == NULL)
				p->ch[code] = new node();
			p = p->ch[code];
		}
		if(p->index == -1)
			p->index = index;
		else
			reflect[index] = p->index;
	}
	
	void build() {						//build machine
		queue<node*> q;
		q.push(root);
		while(!q.empty()) {
			node *p = q.front();
			for(int i = 0; i < node::signNum; i++)
				if(p->ch[i]) {
					node *tmp = p->suffix;
					while(tmp && !tmp->ch[i]) tmp = tmp->suffix;
					if(tmp)
						p->ch[i]->suffix = tmp->ch[i];
					else
						p->ch[i]->suffix = root;
					tmp = p->ch[i]->suffix;
					if(tmp->index != -1)
						p->ch[i]->dict = tmp;
					else
						p->ch[i]->dict = tmp->dict;
					q.push(p->ch[i]);
				}
			q.pop();
		}
	}
	
	void match(char *s) {				//match patterns with Text
		node *p = root;
		for(; *s; s++) {
			int code = decode(*s);
			while(p && !p->ch[code]) p = p->suffix;
			if(p)
				p = p->ch[code];
			else
				p = root;
			node *tmp = p;
			while(tmp) {
				if(tmp->index != -1)
					occur[tmp->index]++;
				tmp = tmp->dict;
			}
		}
	}
	
	~AC_algorithm() {
		queue<node*> q;
		q.push(root);
		while(!q.empty()) {
			node *p = q.front();
			q.pop();
			for(int i = 0; i < node::signNum; i++)
				if(p->ch[i])
					q.push(p->ch[i]);
			delete p;
		}
	}
};
