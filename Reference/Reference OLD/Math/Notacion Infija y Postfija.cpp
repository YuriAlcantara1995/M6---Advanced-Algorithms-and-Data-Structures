//En la expresion solo hay variables y signos
// luego se especifican los valores de las variables
using namespace std;

char E[1000], I[1000], x;
stack<char>S;
stack<double>P;
int v, V[30];

int val( char c )
{
    if( c == '+' || c == '-' )
        return 1;
    if( c == '*' || c == '/' )
        return 2;
    if( c == '^' )
        return 3;
    return 4;
}

int main()
{
    freopen("a.in","r",stdin);

    scanf("%s\n",E);
    int le = strlen(E);
    E[le] = ')';

    while( scanf("%c=%d\n",&x,&v) != EOF )
        V[x-'a'] = v;

    int pos = 0;
    S.push('(');
    for( int i = 0; i <= le; i++ )
    {
        if( E[i] >= 'a' && E[i] <= 'z' )
            I[pos++] = E[i];
        else if( E[i] == '(' )
            S.push(E[i]);
        else if( E[i] == ')' )
        {
            while( S.top() != '(' )
            {
                I[pos++] = S.top();
                S.pop();
            }
            S.pop();
        }
        else
        {
            while( !S.empty() && val(S.top()) >= val(E[i]) && val(S.top()) <= 3 )
            {
                I[pos++] = S.top();
                S.pop();
            }
            S.push(E[i]);
        }
    }

    printf("%s\n",I);

    double a,b,c;
    for( int i = 0; i < pos; i++ )
    {
        if( I[i] >= 'a' && I[i] <= 'z' )
            P.push(V[I[i]-'a']);
        else
        {
            b = P.top();
            P.pop();
            a = P.top();
            P.pop();
            if( I[i] == '+' )
                c = a+b;
            if( I[i] == '-' )
                c = a-b;
            if( I[i] == '*' )
                c = a*b;
            if( I[i] == '/' )
                c = a/b;
            if( I[i] == '^' )
                c = pow(a,b);
            P.push(c);
        }
    }
    double val=P.top();P.pop();

    printf("%.2f",val);

    return 0;
}
