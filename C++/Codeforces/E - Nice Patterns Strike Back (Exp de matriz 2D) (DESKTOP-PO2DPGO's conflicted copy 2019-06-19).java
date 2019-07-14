//~ http://codeforces.com/gym/100199

import java.util.*;
import java.math.*;
import java.io.*;

public class Main{
	
	public static class mat{
		int v[][];
		int m;
		mat(int mm){
			m = mm;
			v = new int[(1 << m)][(1 << m)];
			for (int i = 0; i < (1 << m); i++)
				for (int j = 0; j < (1 << m); j++)
					v[i][j] = 0;
		}
		
		
	}
	
	static mat multiplica(mat a, mat b, int MOD){
		mat ans = new mat(a.m);
		for (int i = 0; i < (1 << a.m); i++)
		{
			for (int j = 0; j < (1 << a.m); j++)
			{
				for (int k = 0; k < (1 << a.m); k++)
				{
					ans.v[i][j] += a.v[i][k] * b.v[k][j];
					ans.v[i][j] %= MOD;
				}
			}
		}
		return ans;
	}
	
	static int pode(int i, int j, int m){
		if(j == (1 << m)) return 1;
		
		int a, b, c, d;
		for (int k = 0; k < m - 1; k++)
		{
			a = ((i & (1 << k)) > 0) ? 1 : 0;
			b = ((i & (1 << (k + 1))) > 0) ? 1 : 0;
			c = ((j & (1 << k)) > 0) ? 1 : 0;
			d = ((j & (1 << (k + 1))) > 0) ? 1 : 0;
			
			if(a == b && b == c && c == d) return 0;
		}
		return 1;
	}
	
	//~ static mat id, g;
	
	static mat exponencia(BigInteger exp, mat id, mat g, int MOD){
		if(exp.equals(BigInteger.ZERO)) return id;
		
		BigInteger t = new BigInteger("2");
		mat aux = exponencia(exp.divide(t), id, g, MOD);
		aux = multiplica(aux, aux, MOD);

		if(!(exp.mod(t)).equals(BigInteger.ZERO))
			aux = multiplica(aux, g, MOD);
		
		return aux;
	}
	
	static final String FILE_NAME = "nice";
	public static void main(String[] args) throws IOException{
		FastScanner sc = new FastScanner(System.in);
		PrintWriter out = new PrintWriter(System.out);
		//~ if(ONLINE) {
			sc = new FastScanner(new FileInputStream(FILE_NAME + ".in"));
			out = new PrintWriter(new FileOutputStream(FILE_NAME + ".out"));
		//~ }
		BigInteger n;
		int m, MOD;
		String s;
		s = sc.next();
		m = sc.nextInt();
		MOD = sc.nextInt();
		n = new BigInteger(s);
		mat id = new mat(m);
		mat g = new mat(m);
		for (int i = 0; i < (1 << m); i++)
			id.v[i][i] = 1;
		for (int i = 0; i < (1 << m); i++)
			for (int j = 0; j < (1 << m); j++)
				g.v[i][j] = pode(i, j, m);
				
		n = n.subtract(BigInteger.ONE);
		mat aux = exponencia(n, id, g, MOD);
		
		int ans = 0;
		for (int i = 0; i < (1 << m); i++)
		{
			for (int j = 0; j < (1 << m); j++){
				ans += (aux.v[i][j]);
				ans %= MOD;
			}
		}
		out.println(ans);
		out.flush();
		out.close();
	}
	
	static class FastScanner {
		BufferedReader br;
		StringTokenizer st;
		public FastScanner(InputStream in) {
			br = new BufferedReader(new InputStreamReader(in));
			st = new StringTokenizer("");
		}
		public String next() throws IOException {
			while(!st.hasMoreTokens()) st = new StringTokenizer(br.readLine());
			return st.nextToken();
		}
		public int nextInt() throws IOException {
			return Integer.parseInt(next());
		}
	}
	
}
