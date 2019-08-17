
import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
	static int len, base;
	static BigInteger dp[][][][] = new BigInteger[110][130][2][2];
	
	static void reset(){
		for (int i = 0; i < 110; i++)
		{
			for (int j = 0; j < 130; j++)
			{
				for (int k = 0; k < 2; k++)
				{
					for (int l = 0; l < 2; l++)
					{
						dp[i][j][k][l] = BigInteger.valueOf(-1);
					}
				}
				
				
				
				
			}
		}
	}
	
	static BigInteger solve(int pos, int base, int fst, int isUm){
		if(pos == -1) return BigInteger.valueOf(1);
		if(!dp[pos][base][fst][isUm].equals(BigInteger.valueOf(-1))) return dp[pos][base][fst][isUm];
		
		BigInteger ans = BigInteger.valueOf(0);
		
		if(fst==1){
			ans = solve(pos-1, base, 0, 1);
			ans = (ans.add(solve(pos-1, base, 0, 0).multiply(BigInteger.valueOf(base-2))));//tira 1 e 0
		}else{
			if(isUm==1){
				ans = solve(pos-1, base, 0, 1);
				ans = (ans.add(solve(pos-1, base, 0, 0).multiply(BigInteger.valueOf(base-2))));//tira 1 e 3
			}else{
				ans = solve(pos-1, base, 0, 1);
				ans = (ans.add(solve(pos-1, base, 0, 0).multiply(BigInteger.valueOf(base-1))));//tira 1
			}
		}
		
		return dp[pos][base][fst][isUm] = ans;
	}
	
	
	
	public static void main(String args[]){
		Scanner sc = new Scanner(System.in);
		
		reset();
		while (true)
		{
			
			base = sc.nextInt();
			len = sc.nextInt();
			if(base + len == 0) break;
			
			System.out.println(solve(len-1, base, 1, 0));
		}
		
		
	}
	
}
