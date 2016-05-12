#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int hashRange = 131072;
int hashtable[4][256], shuffleArr[hashRange], ref[hashRange];
void buildHashTable() {
	memset(ref, -1, sizeof(ref));
	for(int i = 0; i < hashRange; i++)
		shuffleArr[i] = i;
	for(int i = 0; i < 4; i++) {
		random_shuffle(shuffleArr, shuffleArr + hashRange);
		for(int j = 0; j < 256; j++)
			hashtable[i][j] = shuffleArr[j];
	}
}
int myhash(int input) {
	int x[4];
	for(int i = 0; i < 4; i++)
		x[i] = hashtable[i][(input >> (i*8)) & (0xff)];
	int k = x[0] ^ x[1] ^ x[2] ^ x[3];
	if(ref[k] != input)
		for(int i = k; ; i = (i+1)%hashRange)
			if(ref[i] == -1 || ref[i] == input) {
				ref[i] = input;
				return i;
			}
	return k;
}
