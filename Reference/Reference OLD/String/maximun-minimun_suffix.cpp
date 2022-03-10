//Dada una string s devuelve un array m[0:n] tal que m[i] contine el mximo sufijo de
//s[0:i+1].
void maximumSuffixArray (char* s, int* res)
{
    int i = 0, n = strlen(s), j, k;
    forn(l, n) res[l] = -1;
    while (i < n)
    {
        j = i + 1;
        k = i;
        if (res[i] == -1) res[i] = i;
        while (j < n and s[k] >= s[j])
        {
            if (s[k] > s[j]) k = i;
            else k++;
            if (res[j] == -1) res[j] = i;
            j++;
        }
        while (i <= k) i += j - k;
    }
}
Dada una string s devuelve un array m[0:n] tal que m[i] contine el mnimo sufijo de
s[0:i+1].
void minimumSuffixArray (char* s, int* res)
{
    int i = 0, n = strlen(s), j, k;
    while (i < n)
    {
        j = i + 1;
        k = i;
        res[i] = i;
        while (j < n and s[k] <= s[j])
        {
            if (s[k] < s[j]) res[j] = k = i;
            else res[j] = j - k + res[k], k++;
            j++;
        }
        while (i <= k) i += j - k;
    }
}