#ifndef STATEMENTAGGREGATOR_H
#define STATEMENTAGGREGATOR_H

#include <string>
#include <fstream>
#include "StatementRecord.h"
#include "AggregatedRecord.h"

class StatementAggregator
{
    public:
        StatementAggregator(std::string);
        virtual ~StatementAggregator();
        StatementAggregator& operator>>(AggregatedRecord&);
        operator bool() const;
    protected:
    private:
        std::ifstream input;
        bool isInitState;
        StatementRecord lastRead;
};

#endif // STATEMENTAGGREGATOR_H
