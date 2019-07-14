import java.util.*;
import java.math.*;

public class Main{
	static char memo[][] = new char[201][201];
	static BigInteger dp[][] = new BigInteger[201][201];
	static int n, k, len[] = new int[201];
	
	//~ static BigInteger
	static BigInteger solve(int posn, int posk){
		if(posk == k-1) return posn + len[posk]-1 < n ? BigInteger.ONE : BigInteger.ZERO;
		if(posn >= n) return BigInteger.ZERO;
		
		//~ System.out.println("estou em " + posn + " " + posk + " " + memo[posn][posk]);
		if(memo[posn][posk] == 1) return dp[posn][posk];
		memo[posn][posk] = 1;
		
		BigInteger ans = new BigInteger("0");
		
		
		for (int i = posn + len[posk] + 1; i < n; i++)
		{
			ans = ans.add(solve(i, posk+1));
		}
			
		dp[posn][posk] = new BigInteger("0");
		return dp[posn][posk] = ans;
	}
	
	public static void main(String args[]){
		Scanner sc = new Scanner(System.in);
		int tc;
		tc = sc.nextInt();
		while (tc-- > 0)
		{
			n = sc.nextInt();
			k = sc.nextInt();
			for (int i = 0; i < k; i++)
				len[i] = sc.nextInt();
			
			if(k == 0){
				System.out.println("1");
				continue;
			}
			for (int i = 0; i <= n; i++)
				for (int j = 0; j <= k; j++)
					memo[i][j] = 0;
			
			//~ System.out.println("oi");
			BigInteger ans = new BigInteger("0");
			for (int i = 0; i < n; i++)
				ans = ans.add(solve(i, 0));
			System.out.println(ans);
		}
	
	}
	
}
