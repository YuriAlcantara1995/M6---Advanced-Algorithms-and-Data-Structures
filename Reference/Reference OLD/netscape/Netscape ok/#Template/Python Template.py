import string
import math
import fractions

@memoize
def funcion( s ):
    print s[0:5]
    s = sorted( s )
    return s

arr = []
arr.append( 5 )
arr.append( 1 )
arr.append( 6 )
arr.append( 10 )
arr.append( 4 )
arr = funcion(arr)
print arr[0:5]
for x in range(0, 10):
   arr.append( x )
gg = fractions.gcd(10, 65)
   
while True:
    try:
        n, c, d  = raw_input().split()
        import math
        print pow( long(c), long(n), long(d) )
    except EOFError:
        break