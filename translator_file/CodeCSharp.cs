using System;

 namespace from_C_to_C_Sharp
{
	class Program
	{
			//#include "stdio.h" 
		//#include <malloc.h> 
		static int sizeNumber(int num)
		{
			int count = 0;
			while(num != 0)
			{
			num = num / 10;
				count++ ;
			}
			return count;
		}
/*test comment*/ 
		static int[] setDigitNumber(int num)
		{
			int size = sizeNumber(num);
			int[] digits = new int[size];
			int index = 0;
			while(num != 0)
			{
			digits[index] = num % 10;
			num /= 10;
				index++ ;
			}
			return digits;
		}
// Main 
/* double
comment
*/ 
		static void Main(string[] args)
		{
			int size = sizeNumber(36);
			int[] digitsNumber = setDigitNumber(36);
			int sum7Digit7 = 0;
			for(int i = 0 ;i < size ;i++)
			{
			if(i < 100 && i > 0)
			{
				Console.WriteLine("array[{0}] = {1} \n",i,digitsNumber[i]) ;
			}
				sum7Digit7 += digitsNumber[i] ;
			}
			Console.WriteLine("Summa digit: {0}",sum7Digit7);

		}
	}
}