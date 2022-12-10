/*
Author: Jiahao Sun
Class: ECE 6122 QSZ
Last Modified Date: 11/20/2022

Discription:
This function is to check if command line argument is valid or not
Input: string inputString, unsigned long inputNumber
*/

#include <string>
#include <iostream>

#include "inputCheck.h"

using namespace std;

bool inputCheck(const string& inputString, unsigned long& inputNumber)
{
    int inputStringBitValid = 0;
    for (int i = 0; i < inputString.length(); i++) 
    {
        // this for loop is to check the every bit in the string.
        if(isdigit(inputString[i]))
        {
            // if one bit is valid then increment valid recording
            inputStringBitValid++;
        }
        else
        {
            return false;
        }
    }

    if (inputStringBitValid == inputString.length())
    {
        // if every bit is valid digit, then convert string to number
        inputNumber = stoul(inputString);
    }
    else
    {
        return false;
    }

    if ((inputNumber >= 61000) && (inputNumber <= 65535))
    {
        // input number also need to be in the range 61000 - 65535
        return true;
    }
    else
    {
        return false;
    }
}
