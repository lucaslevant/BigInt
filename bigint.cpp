#include "bigint.h"
#include <iostream>
#include <string>
#include <climits>
#include <cmath>
using namespace std;

//******************************************************************
//START OF THE CONSTRUCTORS SECTION
//******************************************************************

/*
// Create a default BigInt with base 10.
// This function is complete. You do not have to add anything.
*/
BigInt::BigInt(){
  base = 10;
  isPositive = true;
}

/*
// Create a BigInt with a specified base.
// This function is complete. You do not have to add anything.
*/
BigInt::BigInt(int setbase){
    if(setbase < 2 || setbase > 36){
        throw InvalidBaseException();
    }
    base = setbase;
    isPositive = true;
}

/*
// Destructure. You do not have to add anything.
// This function is complete
*/
BigInt::~BigInt(){}

/*
//  Create a BigInt from string.
//  Don't forget to set the base accordingly
//  The input string will contain
//      - numbers (0-9) and/or 
//      - uppercase letters (A-Z) [A=10, B=11, ... , Z=35]
//  The input string may contain
//      - a negative sign ('-') to signify that the number is negative.
//  Note: char '0' = int 48 (see ASCII table)
//  Note: char 'A' = int 65
*/
BigInt::BigInt(const string &s, int setbase){
    if(setbase < 2 || setbase > 36){
        throw InvalidBaseException();
    }

    base = setbase;
    
    if(s[0] == '-')

    {
        isPositive = false;
    }
   

  
		if(isPositive == true)
		{
    for (int i = s.size() - 1; i >= 0; i--)
		{
        
        if( isdigit(s[i]) )
        {
            int c = (int)(s[i])-48;
            vec.push_back(c);
        }
        else if( !isdigit(s[i]) )
        {
            int c = (int)(s[i])-55;
            vec.push_back(c);
        }
		}
		}
        
		
		else if(isPositive == false)
		{
    for (int i = s.size() - 1; i > 0; i--)
        {

        if( isdigit(s[i]) )
        {
            int c = (int)(s[i])-48;
            vec.push_back(c);
        }
        else if( !isdigit(s[i]) )
        {
					
            int c = (int)(s[i])-55;
            vec.push_back(c);
        }
        }

		}
	
}


/*
//  Create a BigInt from int (base 10).
//  - Convert the int (base 10) input into a specified base (setbase).
//  - Don't forget to set the base accordingly
//  For example:
//     BigInt k(6,2) <- int 6 base 10 to BigInt base 2
//          - Result:  BigInt k with value 110 (base 2)
//     BigInt k(154,16) <- 154 base 10 to BigInt base 16
//          - Result: BigInt k with value 9A (base 16)
// 9 x 16 + 10 = 154
*/
BigInt::BigInt(int input,int setbase){
    if(setbase < 2 || setbase > 36){
        throw InvalidBaseException();
    }

  base = setbase;
	isPositive = true;

	if(input == 0)
	{
		vec.push_back(0);
	}
	else
	{
		if(input < 0)
		{
			isPositive = false;
			input = input * -1;
		}
while (input > 0)
{
	vec.push_back(input%base);
	input/=base;
}
	}

}

/*
//  Create a BigInt from another BigInt.
//  This is a copy constructor.
//  Simply call the assignment operator (=) below.
// (You can also think of this function as the same as the assignment operator (=))
// (but without a return statement because you are overriding the current object)
*/
BigInt::BigInt(const BigInt &b){
    base = b.base;
    isPositive = b.isPositive;
    vec = b.vec;
}
/*
//  Assignment operator. (i.e., BigInt a = b;)
//  OVERRIDING a's data with BigInt b's data
//       - vec
//       - isPositive
//       - base
*/
BigInt & BigInt::operator = (const BigInt &b){
    base = b.base;
    isPositive = b.isPositive;
    vec = b.vec;
    return *this; 
}


//******************************************************************
//END OF THE CONSTRUCTORS SECTION
//******************************************************************

//******************************************************************
//START OF THE DISPLAYS SECTION
//******************************************************************

/*
// Convert to string and return the string
// Display it in its corresponding base
//  Note: char '0' = int 48 (see the ASCII table)
//  Note: char 'A' = int 65
*/
string BigInt::to_string(){

string number = "";



if (isPositive == true)
{

for (int i = vec.size() - 1; i >= 0; i--)
{
	if(vec[i] < 10)
	{
	char c = vec[i]+'0'; 
	number += c;
	}

	else
	{
	char c = (char)vec[i] + 55; 
	number += c;
	}
}
}

else if (isPositive == false)
{
	char neg = '-';
	number += neg;

for (int i = vec.size()-1; i >= 0; i--)
{
	if(vec[i] < 10)
	{
	char c = vec[i]+'0'; 
	number += c;
	}

	else
	{

	char c = (char)vec[i] + 55; 
	number += c;


	}
}
}


return number;

}

/*
//  Convert BigInt to integer base 10 and return that int
//    If BigInt >= INT_MAX, return INT_MAX.
//    If BigInt =< INT_MIN, return INT_MIN.
//  Note: 1. INT_MAX and INT_MIN are already defined for you
//           in the 'climits' library.
//        2. INT_MAX = 2147483647, INT_MIN = -2147483648
//           therefore, INT_MIN does not equal to (-INT_MAX)
*/


int BigInt::to_int() const{

long long int sum = 0;
long long int size = vec.size();

		
for(long long int i = 0; i < size; i++)
{
	sum += (vec[i]) * pow(base,i);
	if(sum>=INT_MAX)
	{
		if(isPositive == false)
		{
			return INT_MIN;
		}
		return INT_MAX;
	}
}
	

if(isPositive == false)
{ 
	sum = sum * -1;
}

	if(sum >= INT_MAX )
	{
		return INT_MAX;
	}
 else if(sum <= INT_MIN )
		{
			return INT_MIN;
		}
		return sum;
}

//******************************************************************
//END OF THE DISPLAYS SECTION
//******************************************************************

//******************************************************************
//START OF THE EQUALITY CHECK OPERATORS SECTION
//******************************************************************

/*
//  Compare a and b.
//     If a = b, return 0.
//     If a < b, return -1.
//     If a > b, return 1.
//  See the HINT below
*/
int BigInt::compare(const BigInt &b) const{
    if(base != b.base){
        throw DiffBaseException();
    }


		if(isPositive == false && b.isPositive == true)
		{
			return -1;
		}

		else if(isPositive == true && b.isPositive == false)
		{
			return 1;
		}

		else if (isPositive == b.isPositive)//signs are the same
		{
			if(isPositive == true)
			{
			if(vec.size() > b.vec.size()) //compare vec sizes
			{
				return 1;
			}

			else if( vec.size() < b.vec.size() )
			{
				return -1;
			}
			}

			else
			{
			if(vec.size() < b.vec.size()) //compare vec sizes
			{
				return 1;
			}

			else if( vec.size() > b.vec.size() )
			{
				return -1;
			}
			}

			
		}

		if( vec.size() == b.vec.size() && isPositive == b.isPositive )
		{
			if(isPositive == true)
			{
			for(int i = vec.size() - 1; i >= 0; i--) //loop and compare each digit
			{
				if(vec[i] > b.vec[i])
				{
					return 1;
				}
				else if (vec[i] < b.vec[i])
				{
					return -1;
				}
			}
			}

			else if(isPositive == false)
			{
			for(int i = vec.size() - 1; i >= 0; i--) //loop and compare each digit
			{
				if(vec[i] < b.vec[i])
				{
					return 1;
				}
				else if (vec[i] > b.vec[i])
				{
					return -1;
				}
			}
			}
		}

		


    return 0;
}


//Call the compare function above to check if a == b
bool operator == (const BigInt &a, const BigInt &b){
    
		int x = a.compare(b);
		if (x == 0)
		{
			return true;
		}
		 return false;

}

//Call the compare function above to check if a != b
bool operator != (const BigInt &a, const BigInt &b){
  
	int x = a.compare(b);
	if (x == 0)
		{
			return false;
		}
		 return true;
}

//Call the compare function above to check if a <= b
bool operator <= (const BigInt &a, const BigInt &b){
  	int x = a.compare(b);
    if (x == 0 || x == -1)
		{
			return true;
		}
		
		 return false;
}

//Call the compare function above to check if a >= b
bool operator >= (const BigInt &a, const BigInt &b){
  
		int x = a.compare(b);
    if (x == 0 || x == 1)
		{
			return true;
		}
		return false;
}
  
  


//Call the compare function above to check if a > b
bool operator > (const BigInt &a, const BigInt &b){
  
		int x = a.compare(b);
    if (x == 1)
		{
			return true;
		}
		return false;
}

//Call the compare function above to check if a < b
bool operator < (const BigInt &a, const BigInt &b){
		int x = a.compare(b);
  if (x == -1)
		{
			return true;
		}
		return false;
}

//******************************************************************
//END OF THE EQUALITY CHECK OPERATORS SECTION
//******************************************************************

//******************************************************************
//START OF THE ARITHMETIC OPERATORS SECTION
//******************************************************************

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call += operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator + (const  BigInt &a, const BigInt &b){

BigInt copy = a;
copy += b;
return copy;
 

}

/*
//==================
// MEMBER function
//==================
//  Addition assignment operator.
//    i.e., a += b
*/
const BigInt & BigInt::operator += (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    

	vector<int>greater;
	vector<int> sum;
	int carry = 0;
  int holder = 0;
	int c;
	int a = vec.size();
	int e = b.vec.size();
	int max;
	BigInt copya;
	BigInt copyb;
	copya.base = base;
	copya.isPositive = isPositive;
	copya.vec = vec;
	copyb.base = b.base;
	copyb.isPositive = b.isPositive;
	copyb.vec = b.vec;



	if(a>=e){
		c = e;
		max = a;
		greater = vec;
	}
	else{
		c = a;
		max = e;
		greater = b.vec;

	}

	if(isPositive == b.isPositive)
	{
	carry = 0;
	for(int i = 0; i < c ; i++)
	{
		int p = 0;
		int o = 0;
    if(i<(int)vec.size())
    {
      p = vec[i];
    }
    if(i<(int)b.vec.size())
    {
      o = b.vec[i];
    }
		holder = carry + p + o;
		if(holder>=base) // not on last digit
		{
			carry = holder/base;
			holder = holder%base;
		}
		
		else{
			carry = 0;
		}
		sum.push_back(holder);
	}

	if (a==e)
	{
		if (carry!=0)
		{
			sum.push_back(carry);
		}
	}

	else
	{
		for (int i = c; i < max; i++)
		{
		holder = carry + greater[i];
		if(holder>=base) // not on last digit
		{
			carry = holder/base;
			holder = holder%base;
		}
		
		else{
			carry = 0;
		}
		sum.push_back(holder);

		}
	  if (carry!=0)
		{
			sum.push_back(carry);
		}
	}

	vec.clear();
  vec = sum;
	// if(isPositive == true)
	// {
	//   vec = sum;
	// }
	// else
	// {
	// 	int s = sum.size()-1;
	// 	sum[s] = sum[s] * -1;
	// 	vec = sum;
	// }


	}

	else{

	
	 if(copya.isPositive == false && copyb.isPositive == true)
	{
		copya.isPositive = true;
		copyb.isPositive = true;
		if(copya > copyb)
		{
			isPositive = false;

		}
		else
		{
			isPositive = true;
		}
		copya -= copyb;
		vec = copya.vec;

		
		
	}
	else if(copya.isPositive == true && copyb.isPositive == false)
	{
	copyb.isPositive = true;
	copya.isPositive = true;
	if(copya > copyb)
	{
	isPositive = true;
	}
	else
	{
		isPositive = false;
	}
	copya -= copyb;
	vec = copya.vec;
	
	}
	}
int sizec = vec.size() - 1;
	if(vec[sizec] == 0)
	{
		isPositive = true;
	}

  return *this;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call -= operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator - (const  BigInt &a, const BigInt & b){

		BigInt copy = a;
		copy -= b;
		return copy;
 
}


/*
//==================
// MEMBER function
//==================
//  Subtraction assignment operator.
//    i.e., a -= b
//  Note: Think of base cases (e.g., subtract by itself)
*/
const BigInt & BigInt::operator -= (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }

		
		vector<int> greater;
		vector<int> smaller;
		vector<int> sub;
		int limit;
		BigInt ahold;
		ahold.vec = vec;
		ahold.base = base;
		ahold.isPositive = isPositive;
		vec.clear();
		int holder = 0;
		

		if(ahold >= b)
			{
				greater = ahold.vec;
				smaller = b.vec;
				limit = b.vec.size();
			}

		else
			{
				greater = b.vec;
				smaller = ahold.vec;
				limit = ahold.vec.size();
			} 

		if(isPositive == false && b.isPositive == false)
			{
				if(ahold >= b)
			{
				greater = ahold.vec;
				smaller = b.vec;
				limit = ahold.vec.size();
			}

			else if (ahold < b)
			{
				greater = b.vec;
				smaller = ahold.vec;
				limit = b.vec.size();
			} 

			}


		 if(isPositive == true && b.isPositive == true)
		{
			int count = 0;
			int sizeg = greater.size();
			for(int i = 0; i < limit; i++)
			{
			
				if(greater[i] < smaller[i])
				{
					greater[i+1]--;
					greater[i] += base;
				}
				holder = greater[i] - smaller[i];
				sub.push_back(holder);
				count++;

			}

			for(int j = count; j < sizeg; j++ )
			{
				if(greater[j] >=0)
				{
				sub.push_back(greater[j]);
				}
				else
				{
				if(j+1 < sizeg)
				{
					greater[j+1]--;
				}
					greater[j] += base;
					sub.push_back(greater[j]);
				}
				
			}
		
			if(ahold < b)
			{
				isPositive = false;
			}
			vec.clear();
			vec = sub;
			
		}


		else if(isPositive == true && b.isPositive == false)
		{
			BigInt btemp = b;
			btemp.isPositive = true;
			ahold += btemp;
			vec = ahold.vec;
		}

		else if(isPositive == false && b.isPositive == true)
		{
			ahold.isPositive = true;
			 ahold += b;
		  isPositive = false;
			vec = ahold.vec;

		}

		else if(isPositive == false && b.isPositive == false)
			{
				
					int count = 0;
					int sizes = smaller.size();
			for(int i = 0; i < limit; i++)
			{
			
				if(smaller[i] < greater[i])
				{
					smaller[i+1]--;
					smaller[i] += base;
				}
				holder = smaller[i] - greater[i];
				sub.push_back(holder);
				count++;
			} 
		
			for(int j = count; j < sizes; j++)
			{
				if(smaller[j] >= 0)
				{
					sub.push_back(smaller[j]);
				}
				else
				{
					if(j+1 < sizes)
					{
						smaller[j+1]--;
					}
					smaller[j] += base;
					sub.push_back(smaller[j]);
				}
			}
			

			vec.clear();
			vec = sub;
			if (ahold < b)
			{
				isPositive = false;
			}	
			else
			{
				isPositive = true;
			}
				
			}


			if(vec[vec.size() - 1] == 0)
			{
				int i = vec.size() - 1;
				while(vec[i] == 0 && i > 0)
				{
					vec.pop_back();
					i--;
				}
			} 
			
			

			
		return *this;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call *= operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator * (const  BigInt &a, const BigInt & b){

    BigInt copya = a;
		copya *= b;
		return copya;

	
}



/*
//==================
// MEMBER function
//==================
//  Multiplication assignment operator.
//    i.e., a *= b
//  Implement Long Multiplication
//  Note: What are the base cases?? (e.g., multiply by 0)
*/
const BigInt & BigInt::operator *= (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    
	/*	BigInt copya;
		copya.base = base;
		copya.vec = vec;
		copya.isPositive = isPositive;
		vector<int> greater;
		vector<int> smaller;
		int ss, bs;
		int carry = 0;
		int holder = 0;
		BigInt mult;
		BigInt multsum;
		*/
		int sizevec = vec.size() - 1;
		int sizebvec = b.vec.size() - 1;	
		BigInt total(base);
		int carry = 0;
		int bsize = b.vec.size();
		int asize = vec.size();
		int product;
		BigInt temp(base);

			if(vec[sizevec] == 0 || b.vec[sizebvec] == 0) //is either num is 0
			{
				int i = vec.size() - 1;
				while(i>0)
				{
					vec.pop_back();
					i--;
				}
				vec[0] = 0;
				isPositive = true;
				return *this;
			} 

for(int i = 0; i < bsize; i++)
		{
			for(int k = 0; k < i; k++)
			{
			temp.vec.push_back(0);
			}
		
		for(int j = 0; j < asize; j++)
		{
			product = (b.vec[i] * vec[j]) + carry;
			//carry /= product;
				/*if(carry != 0)
				{	
					product %= 10;
				}*/
				temp.vec.push_back(product);
		}
			if(carry != 0)
			{
				temp.vec.push_back(carry);
			}
				carry = 0;
				total += temp;
				temp.vec.clear();
			
		}
			vec = total.vec;
		

		if(isPositive != b.isPositive)
		{
			isPositive = false;
		}
		else
		{
			isPositive = true;
		}
		

return *this;
		}
		 

		

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call /= operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator / (const  BigInt &a, const BigInt & b){

    BigInt copya = a;
		copya /= b;
		return copya;
  
}


/*
//==================
// MEMBER function
//==================
//  Division assignment operator.
//    - Call 'divisionMain' to get the quotient;
*/
const BigInt & BigInt::operator /= (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    if(b.vec.size() == 1 && b.vec[0] == 0){
        throw DivByZeroException();
    }

		BigInt quotient(base);
		BigInt remainder(base);
		divisionMain(b, quotient, remainder);
		*this = quotient;
		return *this;

}


/*
//==================
// MEMBER function
//==================
//  Modulus assignment operator.
//    - Call 'divisionMain' to get the remainder;
//    - Note: remainder takes the sign of the dividend.
*/
const BigInt & BigInt::operator %= (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    if(b.vec.size() == 1 && b.vec[0] == 0){
        throw DivByZeroException();//divide by zero.
    }
    
		BigInt quotient;
		quotient.base = base;
		BigInt remainder;
		remainder.base = base;
		divisionMain(b, quotient, remainder);
		*this = remainder;
    return *this;
}

/*
//  Main function for the Division (/=) and Modulus (%=) operators.
//     - Compute (q)uotient and (r)emainder
//     - Implement Long Division
//  Note: 1. This should behave like integer division
//        2. What are the base cases?? (e.g., div by itself)
*/
void BigInt::divisionMain(const BigInt &b, BigInt &quotient, BigInt &remainder){

 		BigInt copya(base);
		copya.vec = vec;
		copya.isPositive = true;
		BigInt copyb(base);
		copyb.vec = b.vec;
		copyb.isPositive = true;
		int pos = vec.size() - 1;
	
		BigInt acheck(base);
		acheck.vec = vec;
		acheck.isPositive = true;
		BigInt bcheck(base);
		bcheck.vec = b.vec;
		bcheck.isPositive = true;
		BigInt asign(base);
		asign.isPositive = isPositive;
	
    //determine the sign of the result
    bool resultedSign;
    bool thistempsign = isPositive;//Holds a sign of dividend for remainder
    if(isPositive!=b.isPositive){
        //different signs give negative.
        resultedSign = false;
    }else{
        //same signs give positive.
        resultedSign = true;
    }
		int cpr = compare(copyb);//avoid calling two times.
    //------------------------------------
    //divide by number > a (like 2/10 = 0, remainder = dividend)
    if(cpr < 0){
        //q = 0, r = a
        //remainder = dividend, use the temp sign
        remainder = *this;
        remainder.isPositive = thistempsign;
				BigInt zero(0,base);
				quotient = zero;
        return;
    }
    //------------------------------------
    //Divide by itself, give 1, sign may change.
    if(cpr == 0){
        //remainder is still 0.
        BigInt one(1,base);
				BigInt zero(0,base);
				remainder = zero;
        quotient = one;
        quotient.isPositive = resultedSign;
        return;   
    }
    //------------------------------------
    //may not need to do the following two lines (depending on what students pass as an argument)
    quotient.vec.clear();
    remainder.vec.clear();
    //Normal case - Long Division



		
	
			if(isPositive != b.isPositive)
			{
				quotient.isPositive = false;
			}
			
		BigInt dseq(vec[pos],base);
		// dseq.vec.push_back();
		while(dseq < copyb) //creating first digits of dseq
		{
			pos--;
			dseq.vec.insert(dseq.vec.begin(), vec[pos]);
		}

		while(pos >= 0)
		{
			int times = 0;
			while(dseq >= copyb)
			{
				dseq -= copyb;
				times += 1;
			}
			
			quotient.vec.insert(quotient.vec.begin(),times);
			if(dseq.vec.size() == 1 && dseq.vec[0] == 0)
			{
				dseq.vec.clear();
			}
			if(pos > 0) //fix
			{
				
				dseq.vec.insert(dseq.vec.begin(), vec[pos-1]);
				
			}
				pos--;//fix
		}

		if(dseq.vec.empty())
		{
			remainder.vec.clear();
			remainder.vec.push_back(0);
			remainder.isPositive = true;
		}
		else if(acheck <= bcheck)
		{
			remainder.vec.clear(); 
			remainder = acheck;
			if(asign.isPositive == true)
			{
				remainder.isPositive = true;
			}
			else
			{
				remainder.isPositive = false;
			}
		}
	
		else
		{
		remainder = dseq;
		remainder.isPositive = isPositive;
		} 
	
		if(acheck < bcheck)
		{
			int i = quotient.vec.size() - 1;
			while(i>1)
			{
				quotient.vec.pop_back();
				i--;
			}
			quotient.vec.push_back(0);
			quotient.isPositive = true;
		}

	/*	if(acheck.vec[0] == 0)
		{
			int i = remainder.vec.size() - 1;
			while(i>0)
			{
				remainder.vec.pop_back();
				i--;
			}
			remainder.vec[0] = 0;
			remainder.isPositive = true;
			} */ 
}
			

		 
	
/*
		if(copya.vec[empty] == 0) 
			{
				int i = quotient.vec.size() - 1;
				while(i>0)
				{
					quotient.vec.pop_back();
					i--;
				}
				quotient.vec[0] = 0;
				isPositive = true;
			} */
		
		
/*if(isPositive != b.isPositive)
{
	quotient.isPositive = false;
}*/
		
/*if(remainder.vec.empty())
		{
			remainder = 0;
			remainder.isPositive = true;
		}
		else
		{
			remainder.isPositive = isPositive;
		}

		if(isPositive != b.isPositive)
		{
			quotient.isPositive = false;
		}
		else
		{
			quotient.isPositive = true;
		} */


/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call %= operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator % (const  BigInt &a, const BigInt & b){

    BigInt copya = a;
		copya %= b;
		return copya;

}



/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call the 'exponentiation' function on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt pow(const  BigInt &a, const BigInt & b){

    BigInt copya = a;
	  copya.exponentiation(b);
		return copya;

	

  

}

/*
//==================
// MEMBER function
//==================
//  Exponentiation assignment function.
//     - i.e., a.exponentiation(b);
// Note: 1. implement Exponentiation by Squaring (see the writeup)
//       2. b should be treated as BigInt, not int or other data type.
*/
const BigInt & BigInt::exponentiation(const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    if(!b.isPositive){
        throw ExpByNegativeException();
    }
 		BigInt copya(base);
		copya.vec = vec;
		copya.isPositive = true;
		BigInt copyb(base);
		copyb.vec = b.vec;
		copyb.isPositive = true;
		BigInt two(base);
		two.vec.push_back(2);
		BigInt one(base);
		one.vec.push_back(1);
		BigInt bases(base);
		int count = 0;
		

		while(copyb > one)
		{

			if(copyb.vec[0] % 2 == 0)
			{
			
				copyb/=two;
			}
			else
			{
				count++;
				if(count == 1)
				{
						bases.vec = copya.vec;
				}
				else if (count > 1)
				{
						bases *= copya;
				}
				copyb /= two;
			}
			copya*=copya;
		}
		 if(count>0)
    {
        copya*=bases;
    }
		if(isPositive == false && (b.vec[0] %2 == 0) )
		{
			isPositive = true;
		}
		else if(isPositive == true && (b.vec[0] % 1 == 1))
		{
			isPositive = false;
		}
		

		vec = copya.vec;
		int x = b.vec.size()-1;
		if(b.vec[x] == 0)
		{
			vec.clear();
			vec.push_back(1);
		}
	
		
		return *this;
	


}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call the 'modulusExp' function on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt modPow(const BigInt &a, const BigInt &b, const BigInt &m){

    BigInt copya = a;
		copya.modulusExp(b, m);
		return copya;
}


/*
//==================
// MEMBER function
//==================
//  Modulus Exponentiation assignment function.
//     - i.e., a.modulusExp(b)
// Note: 1. implement Modulus Exponentiation (see the writeup)
//       2. b should be treated as BigInt, not int or other data type.
// Hint: same implementation as exponentiation, but take modulus 
//          after every call to the *= operator.
*/
const BigInt & BigInt::modulusExp(const BigInt &b, const BigInt &m){
    if(base != b.base || base != m.base){
        throw DiffBaseException();
    }
    if(!b.isPositive){
        throw ExpByNegativeException();
    }

    BigInt copya = *this;
    BigInt copyac = *this;
    BigInt copym = m;
    BigInt copyb = b;
		BigInt two(base);
		two.vec.push_back(2);
		BigInt one(base);
		one.vec.push_back(1);
		BigInt bases(base);
    bases.isPositive = isPositive;
		int count = 0;
		BigInt zero(base);
		zero.vec.push_back(0);

		while(copyb >= one)
		{
			if(copyb.vec[0] % 2 == 0)
			{
				copyb/=two;
			}
			else 
			{
				count++;
				if(count == 1)
				{
					copyac%=copym;
					bases.vec = copyac.vec;
				}
				else if (count > 1)
				{
						bases *= copya;
						bases %= copym;
				}
				 copyb -= one;
				 copyb /=two;
			}
			
			copya*=copya;
			copya%=copym;
			copyac*=copyac;
			copyac%=copym;
		}
  
		if(isPositive == false && (b.vec[0] %2 == 0) )
		{
			isPositive = true;
		}
		else if(isPositive == true && (b.vec[0] % 1 == 1))
		{
			isPositive = false;
		}

		vec.clear();
		vec = bases.vec;
		return *this;
	

}

//******************************************************************
//END OF THE ARITHMETIC OPERATORS SECTION
//******************************************************************

//******************************************************************
//START OF SANITY CHECK FUNCTIONS
//YOU CAN USE THEM, BUT DO NOT CHANGE ANYTHING
//THESE FUNCTIONS ARE COMPLETE.
//******************************************************************
void BigInt::printVecItems(){
  cout<<"[";
  for(size_t i = 0;i<vec.size();i++){
    cout<<vec[i];
    if(i < vec.size()-1){
      cout<<",";
    }
  }
  cout<<"]"<<endl;
}

bool BigInt::getSign(){
	return isPositive;
}

int BigInt::getBase(){
	return base;
}
//******************************************************************
//END OF SANITY CHECKS SECTION
//******************************************************************