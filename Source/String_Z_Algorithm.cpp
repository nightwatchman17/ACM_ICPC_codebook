#include <cstring>
int z[length];
void z_function(char *str) {
	int len = strlen(str), L = 0, R = 1;
	z[0] = len;
	for(int i = 1; i <len; i++)
		if(R <= i || z[i-L] >= R-i) {
			int x = max(R, i);
			while(x < len && str[x] == str[x-i])
				x++;
			z[i] = x-i;
			L = i; R = x;
			//if(i < x) {L = i; R = x;}
		} else
			z[i] = z[i-L];
}
