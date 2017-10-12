#include "StatementAggregator.h"

StatementAggregator::StatementAggregator(const std::string filename):input(filename.c_str()), isInitState(true)
{ }

StatementAggregator::~StatementAggregator()
{
    // not required, but we can handle errors on closing here
    input.close();
}

StatementAggregator& StatementAggregator::operator>>(AggregatedRecord& record) {
    if (isInitState) {
        // first invocation, skip headers line
        std::string headers;
        std::getline(input, headers);
        // preload first row from csv
        input >> lastRead;
        isInitState = false;
    }

    // init the aggregated record from the last read but unused csv line
    record = AggregatedRecord(lastRead.getDate(), lastRead.getAmount());

    while (input >> lastRead && lastRead.getDate() == record.getDate()) {
        record.addAmount(lastRead.getAmount());
    }
    // we have read one more row in the end of the while loop, which should remain cached until the next invocation
    return *this;
}

StatementAggregator::operator bool() const {
    // the state of the aggregator is the same as the underlying stream
    return (bool)input;
}
