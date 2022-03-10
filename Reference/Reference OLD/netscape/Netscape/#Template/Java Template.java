import java.io.IOException;
import java.math.*;
import java.util.*;

public class main {

	public static void main(String[] args)throws IOException{
		//FileReader rd = new FileReader("a.in");
		Scanner cin = new Scanner(System.in);
		
                 while( cin.hasNext() )
			int y = cin.nextInt();		 
		List<Integer> B = new ArrayList<Integer>();
		
		int [] C = new int[10];
		
		for( int i = 1; i <= 100; i += 5 ) B.add(i);
		
		Collections.sort(B);
		int a = Collections.binarySearch(B, 7);
		
		B.set(2, 7);
		BigInteger d = cin.nextBigInteger();
		
		System.out.println(B.get(2));
		System.out.printf("%d", 5);
		cin.close();
	}
}