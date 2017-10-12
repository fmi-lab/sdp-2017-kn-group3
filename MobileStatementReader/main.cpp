#include <iostream>
#include <string>
#include "StatementAggregator.h"
using namespace std;

int main()
{
    string statementFile = "statement.csv";
    AggregatedRecord record;
    StatementAggregator statementAggregator(statementFile);

    while(statementAggregator >> record) {
        cout << record << endl;
    }
    return 0;
}
