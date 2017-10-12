#ifndef AGGREGATEDRECORD_H
#define AGGREGATEDRECORD_H

#include <ostream>
#include <string>
class AggregatedRecord
{
    public:
        AggregatedRecord(std::string="", int=0);
        void addAmount(int);
        std::string getDate() const;
        friend std::ostream& operator<<(std::ostream&, const AggregatedRecord&);
    protected:
    private:
        std::string date;
        int amount;
};

#endif // AGGREGATEDRECORD_H
