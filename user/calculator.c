#include <inc/stdio.h>
#include <inc/string.h>
#include <inc/memlayout.h>
#include <inc/assert.h>
#include <inc/x86.h>
#include <inc/math.h>
#include <kern/console.h>
#include <kern/monitor.h>
#include <kern/kdebug.h>
#include <inc/calculator.h>

void Substract_List_Operation(operation op[])
{
    int i;
    for (i =0; i<6; i++){

        op[i].position = op[i].position - 1;
    }

    int Isoperation(char r)
{
	if (r == '+' || r == '-' || r == '*' || r == '/' || r == '%')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


int Isnumber(char r)
{
	if (r >= '0' && r <= '9')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int Isdot(char r)
{
	if (r == '.')
	{
		return 1;
	}
	else
	{
		return 0;
	}

}

// remove item
void removeItem(float str[], int location)
{
	int i;

	for (i = location; i < 6; i++)
	{
		str[i] = str[i + 1];
	}

	str[5] = 0;

}



Float Getnumber(char* str, int *i)
{   
	int x = 0;
	Float Value;
	int dot = 1;
	int y = 1;
	char number[100];
	for(x = 0 ;x < 100; x++)
	{
	number[x] = '0';
	}
	number[strlen(str)] = '\0';
	number[0] = str[*i];
	*i=*i+1;
	int j=*i;
	while (*i < strlen(str))
	{
		cprintf("I form inside Getnumber %d\n",*i);
		if (Isnumber(str[*i]))
		{
			number[y] = str[*i];
			y++;
			*i=*i+1;

		}
		else if (Isdot((str[*i])) && dot)
		{
			number[y] = str[*i];
			dot--;
			y++;
			*i=*i+1;
		}
		else if ( Isoperation(str[*i]) )
	        {
			if (dot)
		             {
	         	number[y] = '.';
		             }
		             break;
			}
		else
		{
			Value.error = 1;
			Value.number = 1;
			return Value;
		}
	}
	number[*i-j+1]='\0';
	int check ; 
	for (check=0 ; check < *i-j+1 ; check++)
	{
		cprintf("%c",number[check]);
	}
	cprintf("\n");
	cprintf("length %d",strlen(number));
	Value = char_to_float(number);
	return Value;
}

Char GetOperation(char* str, int i)
{
	Char operat;
	if (str[i] == '-' || str[i] == '+' || str[i] == '*' || str[i] == '/' || str[i] == '%')
	{
		operat.error = 0;
		operat.value = str[i];
		return operat;
	}
	else
	{
		operat.error = 1;
		operat.value = '0';
		return operat;
	}

}

void calc(float numbers[], operantion op[])
{
	int i;

	for (i = 0; i < 6; i++)
	{
		if (op[i].operant == '*')
		{
			numbers[op[i].position - 1] = numbers[op[i].position - 1] * numbers[op[i].position];

		}
		else if (op[i].operant == '/')
		{
			if (numbers[op[i].position ] == 0)
			{
				cprintf("error");
				return;
			}
			numbers[op[i].position - 1] = numbers[op[i].position - 1] / numbers[op[i].position];
		}
		else if (op[i].operant == '%')
		{
			if (numbers[op[i].position ] == 0)
			{
				cprintf("error");
				return;
			}
		int y = (int)(numbers[op[i].position - 1] / numbers[op[i].position]);
		numbers[op[i].position - 1] = numbers[op[i].position - 1] / numbers[op[i].position];
		}
		else{ break; }
		removeItem(numbers, op[i].position);
		subtract_List_Operation(op);
	}
	float result;
	result = 0;
	for (i = 0; i <6; i++)
	{
		result = result + numbers[i];
	}
	cprintf("%f", result);

}

int calculator()
{
	int numposition = 0;
	int Operation_Position = 1;
	int operantnum = 0;
	float A[6];
	int i = 0;

	operantion numericop[6];

	operantion oper;
	oper.operant = '0';
	oper.position = 0;

	for (i = 0; i < 6; i++)
	{
		numericop[i].operant ='0';
		numericop[i].position = 0 ;
		A[i] = 0;
	}
	cprintf("Expression:");
	char *op  = readline("");
	char number[100];
	for(i = 0 ; i < 100; i++)
	{
	number[i] = '0';	
	}
	number[strlen(op)] = '\0';
	i = 0;
	if (!(op[0] == '-' || Isnumber(op[0])))
	{
		cprintf("error");
		return -1;
	}
	if (!(Isnumber(op[strlen(op) - 1]) || Isdot(op[strlen(op) - 1])))
	{
		cprintf("error");
		return -1;
	}

	while (i < strlen(op))
	{
		cprintf("I form inside Calculator %d\n",i);
		Float answer_num = Getnumber(op, &i);
		if (answer_num.error)
		{
			cprintf("error number is wrong");
			return -1;
		}
		else
		{
			A[numposition] = answer_num.number;
			numposition++;
		}
		if (i == strlen(op))
		{
			break;
		}
		Char answer_char = GetOperation(op, i);
		if (answer_char.error)
		{
			cprintf("error operation is not true");
			return -1;
		}
		else
		{
			if (answer_char.value == '+')
			{
				i++;
			}
			else if (!(answer_char.value == '-'))
			{
				numericop[operantnum].operant = answer_char.value;
				numericop[operantnum].position = Operation_Position;
				operantnum++;
				i++;
			}
			Operation_Position++;
		}

	}
	int u=0;
	for(u;u<6;u++){
	cprintf("op %c pos %d",numericop[u].operant,numericop[u].position);	
	}
	
	cprintf(" float A array %f\n %f\n %f\n %f\n %f\n %f\n",A[0],A[1],A[2],A[3],A[4],A[5]);
	calc(A, numericop);
	return 0;
}