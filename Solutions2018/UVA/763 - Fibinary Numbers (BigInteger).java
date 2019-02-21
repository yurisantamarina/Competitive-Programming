import java.util.*;
import java.math.*;

public class Main{
	
	public static void main(String args[]){
		Scanner sc = new Scanner(System.in);
		String s1, s2;
		
		boolean fst = true;
		BigInteger fib[] = new BigInteger[120];
		fib[0] = new BigInteger("1");
		fib[1] = new BigInteger("2");
		
		for (int i = 2; i < 120; i++)
		{
			fib[i] = fib[i-1].add(fib[i-2]);
			//~ System.out.println(fib[i]);
		}
		
		while (sc.hasNext())
		{
			if(!fst){
				sc.nextLine();
				System.out.println("");
			}
			fst = false;
			s1 = sc.nextLine();
			s2 = sc.nextLine();
			//~ System.out.println("s1 = " + s1);
			//~ System.out.println("s2 = " + s2);
			
			BigInteger sum1 = new BigInteger("0");
			BigInteger sum2 = new BigInteger("0");
			
			int cnt = 0;
			for (int i = s1.length()-1; i >= 0; i--, cnt++)
			{
				if(s1.charAt(i) == '1') sum1 = sum1.add(fib[cnt]);
			}
			cnt = 0;
			
			for (int i = s2.length()-1; i >= 0; i--, cnt++)
			{
				if(s2.charAt(i) == '1') sum2 = sum2.add(fib[cnt]);
			}
			
			//~ System.out.println(sum1);
			//~ System.out.println(sum2);
			
			String saida = new String("");
			//~ System.out.println(saida);
			
			BigInteger sum = new BigInteger(sum1.toString());
			sum = sum.add(sum2);
			boolean tem = false;
			
			//~ sum = BigInteger.ZERO;
			for (int i = 119; i >= 0; i--)
			{
				//~ if(sum.equals(BigInteger.ZERO)) break;
				//~ System.out.println("oi");
				if(sum.compareTo(fib[i]) == -1){
					if(tem) saida += '0';
					//~ saida += '0';
				}else{
					tem = true;
					saida += '1';
					sum = sum.subtract(fib[i]);
				}
					
			}
			
			//~ for(int i = saida.lenght() - 1; i >= 0; i--){
				//~ if()
			//~ }
			if(saida.length() == 0) saida += '0';
			System.out.println(saida);
		}
		
	}
	
}
