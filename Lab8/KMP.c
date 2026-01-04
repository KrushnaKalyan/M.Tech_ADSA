#include <stdio.h>
#include <string.h>
void computeLPS(char pattern[], int m, int lps[]) {
    int len = 0;   
    lps[0] = 0;   
    int i = 1;
    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0)
                len = lps[len - 1];
            else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

void KMPSearch(char text[], char pattern[]) {
    int n = strlen(text);
    int m = strlen(pattern);
    int lps[m];
    computeLPS(pattern, m, lps); 
    int i = 0;  // index for text
    int j = 0;  // index for pattern
    while (i < n) {
        if (text[i] == pattern[j]) {
            i++;
            j++;
        }
        if (j == m) {
            printf("Pattern found at index %d\n", i - j);
            j = lps[j - 1];
        }
        else if (i < n && text[i] != pattern[j]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }
}
int main() 
{
    char text[100], pattern[50];
    printf("Enter text: ");
    scanf("%[^\n]%*c", text);  
    printf("Enter pattern to search: ");
    scanf("%[^\n]%*c", pattern);
    KMPSearch(text, pattern);
    return 0;
}
