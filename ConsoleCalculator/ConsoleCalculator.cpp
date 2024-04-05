// CalculatorTutorial.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

using namespace std;

double Solve(vector<double> variables, vector<char> operators);

int main()
{
	while (true)
	{
		// 2 vector arrays hold equation variables and operators
		vector<double> variables;
		vector<char> operators;

		//double temp_var;
		//char temp_oper;
		string temp = "";
		double result = 0.0;

		//populates arrays
		cout << "Enter equation: ";
		while (true)
		{
			cin >> temp;
			if (temp == "+" || temp == "-" || temp == "*" || temp == "/" || temp == "(" || temp == ")")
			{
				operators.push_back(temp[0]);
			}
			else if (temp == "=")
			{
				break;
			}
			else
			{
				variables.push_back(strtod(temp.c_str(), NULL));
			}
		}

		result = Solve(variables, operators);

		if (result == 0.12345)
		{
			cout << "Result: Undefined" << endl;
		}
		else
		{
			cout << "Result: " << result << endl;
		}
	}

	return 0;
}


//solves equation stored in variables and operator arrays
double Solve(vector<double> variables, vector<char> operators)
{
	int num_operators = operators.size(); //keeps track of how many operators are left

	for (int i = 0; i < 3; i++) //3 passes, 1st to solve all equations in parentheses, 2nd to solve multiplication and division, 3rd to solve addition and subtraction
	{

		for (int j = 0; j < num_operators; j++) //iterates over every operator
		{
			if (operators[j] == '(' && i == 0) //checks for "(", which denotes sub-equation that must be solved before main equation
			{
				vector<double> sub_variables; //stores variables in sub-equation
				vector<char> sub_operators; //stores operators in sub-equation
				int nested_parenthesis = 0; //keeps track of which ")" belongs to the first "(" in case of nested parentheses
				int num_parentheses_operators = 0; //keeps track of how many operators in sub_operators are parenthesis

				while (true) //iterates through sub-equation
				{
					if (operators[j + 1] == '(') //checks for start of nested sub-equation
					{
						nested_parenthesis++;
						num_parentheses_operators++;
					}
					if (operators[j + 1] == ')' && nested_parenthesis != 0) //checks for end of nested sub-equation
					{
						sub_operators.push_back(operators[j + 1]);
						operators.erase(operators.begin() + j + 1);
						num_operators--;
						nested_parenthesis--;
						num_parentheses_operators++;
					}
					else if (operators[j + 1] == ')' && nested_parenthesis == 0) //checks for end of sub-equation
					{
						if (sub_variables.size() <= (sub_operators.size() - num_parentheses_operators) && sub_operators.size() > 0) // checks if the number of sub variables is less than the number of sub operators
						{
							sub_variables.push_back(variables[j]);
							variables.erase(variables.begin() + j);
						}
						if (sub_variables.size() == 0) //checks if there is only one variable in parenthesis
						{
							operators.erase(operators.begin() + j + 1);
							operators.erase(operators.begin() + j);
							num_operators -= 2;
							break;
						}
						else
						{
							variables.insert(variables.begin() + j, Solve(sub_variables, sub_operators));
							if (variables[j] == 0.12345) //checks for undefined result
							{
								return 0.12345;
							}
						}
						operators.erase(operators.begin() + j + 1);
						operators.erase(operators.begin() + j);
						num_operators -= 2;
						break;
					}
					else //swaps 1 variable and 1 operator into sub_variables and sub_operators
					{
						sub_variables.push_back(variables[j]);
						sub_operators.push_back(operators[j + 1]);
						operators.erase(operators.begin() + j + 1);
						variables.erase(variables.begin() + j);
						num_operators--;
					}
				}
			}
			else if (i == 1 && (operators[j] == '*' || operators[j] == '/')) //checks if current operator is * or / during 2nd pass
			{
				if (operators[j] == '*')
				{
					variables[j + 1] = variables[j] * variables[j + 1];
					operators.erase(operators.begin() + j);
					variables.erase(variables.begin() + j);
					num_operators--;
					j--;
				}
				else if (operators[j] == '/')
				{
					if (variables[j + 1] == 0.0) //checks for divide by 0
					{
						return 0.12345; //placeholder for undefined
					}
					variables[j + 1] = variables[j] / variables[j + 1];
					operators.erase(operators.begin() + j);
					variables.erase(variables.begin() + j);
					num_operators--;
					j--;
				}
			}
			else if (i == 2 && (operators[j] == '+' || operators[j] == '-')) //checks if current operator is + or - during 3rd pass
			{
				if (operators[j] == '+')
				{
					variables[j + 1] = variables[j] + variables[j + 1];
					operators.erase(operators.begin() + j);
					variables.erase(variables.begin() + j);
					num_operators--;
					j--;
				}
				else if (operators[j] == '-')
				{
					variables[j + 1] = variables[j] - variables[j + 1];
					operators.erase(operators.begin() + j);
					variables.erase(variables.begin() + j);
					num_operators--;
					j--;
				}
			}
			if (operators.size() == 0) //returns last element of variables array as result
				return variables[0];

		}
	}
	return variables[0];
}