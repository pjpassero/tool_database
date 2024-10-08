
/*
 Hardware.cpp
 Tool Class Implementation
 May 07, 2024

 Implements to Tool class found in Hardware.h


 */

#include "Hardware.h"

#include <iostream>
#include <string>
#include <iomanip>

Tool::Tool()
{
    toolName = "";
    toolCost = 0.0;
    toolQuantity = 0;
    toolID = -1;
}

Tool::Tool(int tID, string tName, double tCost, int tQuantity)
{
    toolName = tName;
    toolID = tID;
    toolCost = tCost;
    toolQuantity = tQuantity;
}

ostream &operator<<(ostream &os, const Tool &tool)
{
    os << left << setw(10) << tool.toolID << "\t" << setw(20) << left << tool.toolName << "\t" << setw(15) << tool.toolQuantity << "\t$" << setw(8) << tool.toolCost << fixed << setprecision(2);
    return os;
}




istream &operator>>(istream &is, Tool &tool)
{
    is >> tool.toolID >> tool.toolCost >> tool.toolQuantity;
    getline(is, tool.toolName);
    return is;
};

 
int Tool::getID() const
{
    return toolID;
}

double Tool::getCost() const
{
    return toolCost;
}

int Tool::getQuantity() const
{
    return toolQuantity;
}

string Tool::getName() const
{
    return toolName;
}
