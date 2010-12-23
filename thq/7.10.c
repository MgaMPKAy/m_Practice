#include <stdio.h>

int main(void)
{
    char article[3][80], ch;
    int i, j, up, low, num, space, other;
    
    up = low = num = space = other = 0;

    fgets(article[0], 80, stdin);
    fgets(article[1], 80, stdin);
    fgets(article[2], 80, stdin);

    for (i = 0; i < 3; i++){
	for(j = 0; j < 80; j++){
	    ch = article[i][j];
	    if (ch == '\0' || ch == '\n')
		break;
	    else if (ch >= 'A' && ch <= 'Z'){
		up++; continue;
	    }
	    else if (ch >= 'a' && ch <= 'z'){
		low++; continue;
	    }	
	    else if (ch >= '0' && ch <= '9'){
		num++; continue;
	    }
	    else if (ch == ' '){
		space++; continue;
	    }
	    else
		other++;
	}
    }

    printf("Up= %d, low= %d, num= %d, space=%d, other= %d\n",
	   up, low, num, space, other);
    return 0;
}
