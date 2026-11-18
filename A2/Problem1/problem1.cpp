// File Name: problem1.cpp
// Project: CS221 Assignment 2, Problem 1
// Author: Gogi Benny
// Date: November 15, 2026
// Purpose: Evaluate integer expressions with named variables.
// Major Items:
// - Expression parsing and variable lookup
// - Spaces and tabs between expression tokens (EXTRA)
// - Evaluate multiple expressions in one run (EXTRA)
// - Version control using Git & GitHub:
// github.com/dozothebozo/CS221/blob/main/A2/Problem1/problem1.cpp

#include <cctype>
#include <iostream>
#include <limits>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>

using namespace std;

/**
   Evaluates the next expression, including addition and subtraction.
   @param expression the stream containing the expression
   @param variables the saved variable values
   @return the value of the expression
*/
int expression_value(istream& expression, map<string, int>& variables);

/**
   Evaluates the next term, including multiplication and division.
   @param expression the stream containing the expression
   @param variables the saved variable values
   @return the value of the term
*/
int term_value(istream& expression, map<string, int>& variables);

/**
   Evaluates a number, variable, or parenthesized expression.
   @param expression the stream containing the expression
   @param variables the saved variable values
   @return the value of the factor
*/
int factor_value(istream& expression, map<string, int>& variables);

/**
   Reads a variable name and prompts for its value if needed.
   @param expression the stream positioned at the start of the name
   @param variables the map used to look up and save values
   @return the value of the variable
*/
int variable_value(istream& expression, map<string, int>& variables);

/**
   Checks whether an arithmetic result fits in an int.
   @param result the result calculated as a long long
   @return the result converted to int
*/
int checked_value(long long result);

/**
   Asks whether to evaluate another expression.
   @return true to continue or false to finish
*/
bool evaluate_again();

/**
   Evaluates expressions until the user finishes.
   @return 0 on success or 1 if an expression could not be evaluated
*/
int main()
{
    int status = 0;
    do
    {
        cout << "Enter an expression: ";
        string input;
        if (!getline(cin, input))
        {
            break;
        }

        // Read variable answers separately from the expression.
        istringstream expression(input);
        map<string, int> variables;
        try
        {
            int result = expression_value(expression, variables);
            if ((expression >> ws).peek() != char_traits<char>::eof())
            {
                throw runtime_error("Unexpected text after the expression.");
            }

            cout << result << '\n';
        }
        catch (const runtime_error& error)
        {
            cerr << "Error: " << error.what() << '\n';
            status = 1;
        }
    } while (cin.good() && evaluate_again());

    return status;
}

bool evaluate_again()
{
    while (true)
    {
        cout << "Evaluate another expression? (y/n): ";
        char answer;
        if (!(cin >> answer))
        {
            return false;
        }

        string rest_of_line;
        getline(cin, rest_of_line);
        if (rest_of_line.find_first_not_of(" \t\r\f\v") == string::npos)
        {
            if (answer == 'y' || answer == 'Y')
            {
                return true;
            }
            if (answer == 'n' || answer == 'N')
            {
                return false;
            }
        }

        cout << "Please enter y or n.\n";
    }
}

int expression_value(istream& expression, map<string, int>& variables)
{
    int result = term_value(expression, variables);
    int operation = (expression >> ws).peek();
    while (operation == '+' || operation == '-')
    {
        expression.get();
        // Widen an operand before calculating so the result can be checked.
        long long value = term_value(expression, variables);
        if (operation == '+')
        {
            result = checked_value(result + value);
        }
        else
        {
            result = checked_value(result - value);
        }
        operation = (expression >> ws).peek();
    }
    return result;
}

int term_value(istream& expression, map<string, int>& variables)
{
    int result = factor_value(expression, variables);
    int operation = (expression >> ws).peek();
    while (operation == '*' || operation == '/')
    {
        expression.get();
        long long value = factor_value(expression, variables);
        if (operation == '*')
        {
            result = checked_value(result * value);
        }
        else
        {
            if (value == 0)
            {
                throw runtime_error("Division by zero.");
            }
            result = checked_value(result / value);
        }
        operation = (expression >> ws).peek();
    }
    return result;
}

int factor_value(istream& expression, map<string, int>& variables)
{
    int next_character = (expression >> ws).peek();
    if (next_character == '(')
    {
        expression.get();
        int result = expression_value(expression, variables);
        if ((expression >> ws).get() != ')')
        {
            throw runtime_error("Expected a closing parenthesis.");
        }
        return result;
    }

    if (isalpha(next_character) || next_character == '_')
    {
        return variable_value(expression, variables);
    }

    if (isdigit(next_character))
    {
        int number;
        if (!(expression >> number))
        {
            throw runtime_error("Integer overflow.");
        }
        return number;
    }

    throw runtime_error("Expected a number, variable, or opening parenthesis.");
}

int variable_value(istream& expression, map<string, int>& variables)
{
    string name;
    int next_character = expression.peek();
    while (isalnum(next_character) || next_character == '_')
    {
        name += static_cast<char>(expression.get());
        next_character = expression.peek();
    }

    map<string, int>::const_iterator found = variables.find(name);
    if (found != variables.end())
    {
        return found->second;
    }

    cout << "Enter a value for " << name << ": ";
    string answer;
    if (!(cin >> answer))
    {
        throw runtime_error("Expected an integer value for " + name + ".");
    }

    // Read the whole answer so that a something like 12abc is rejected.
    istringstream value_input(answer);
    int value;
    if (!(value_input >> value) || value_input.peek() != char_traits<char>::eof())
    {
        throw runtime_error("Expected an integer value for " + name + ".");
    }

    variables.emplace(name, value);
    return value;
}

int checked_value(long long result)
{
    if (result < numeric_limits<int>::min() || result > numeric_limits<int>::max())
    {
        throw runtime_error("Integer overflow.");
    }
    return static_cast<int>(result);
}
