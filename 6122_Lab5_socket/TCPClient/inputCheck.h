/*
Author: Jiahao Sun
Class: ECE 6122 QSZ
Last Modified Date: 11/20/2022

Discription:
This function is to check if command line argument is valid or not
Input: string inputString, unsigned long inputNumber
*/

#pragma once

// System includes
#include <assert.h>
#include <math.h>
#include <fstream>
#include <string>
#include <cstring>
#include <iomanip> 
#include <algorithm>

using namespace std;

bool inputCheck(const string& inputString, unsigned long& inputNumber);
