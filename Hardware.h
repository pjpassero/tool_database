/*
 Hardware.h
 Tool Class
 Philip Passero
 May 07,2024

 Defines the Tool class

 */

#ifndef Hardware_h
#define Hardware_h

#include <string>

using namespace std;
class Tool
{

private:
    int toolID;
    string toolName;
    double toolCost;
    int toolQuantity;

public:
    Tool();
    Tool(int tID, string tName, double tCost, int tQuantity);
    friend ostream &operator<<(ostream &os, const Tool &tool);
    friend istream &operator>>(istream &is, Tool &tool);

    string getName() const;
    int getID() const;
    double getCost() const;
    int getQuantity() const;
};

#endif
