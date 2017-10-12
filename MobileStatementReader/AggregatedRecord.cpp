#include "AggregatedRecord.h"

AggregatedRecord::AggregatedRecord(std::string date, int amount):date(date), amount(amount)
{
    //ctor
}

void AggregatedRecord::addAmount(int amount) {
    this->amount += amount;
}

std::string AggregatedRecord::getDate() const {
    return date;
}

std::ostream& operator<<(std::ostream& out, const AggregatedRecord& record) {
    out << record.amount << " seconds used on " << record.date;
    return out;
}
