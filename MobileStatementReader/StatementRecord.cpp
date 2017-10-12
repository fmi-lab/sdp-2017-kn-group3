#include "StatementRecord.h"
#include <sstream>

StatementRecord::StatementRecord(std::string date, std::string number, std::string service, int amount)
:date(date), number(number), service(service), amount(amount)
{ }

int StatementRecord::getAmount() const {
    return amount;
}

std::string StatementRecord::getDate() const {
    return date;
}

std::istream& operator>>(std::istream& in, StatementRecord& st) {
    // Each statement is a separate line in the csv, read it
    std::string line;
    std::getline(in, line);

    // now use a stringstream to split the line in csv columns
    std::stringstream ss(line);
    std::getline(ss, st.date, ',');
    std::getline(ss, st.number, ',');
    std::getline(ss, st.service, ',');
    ss >> st.amount;
    return in;
}

std::ostream& operator<<(std::ostream& out, const StatementRecord& st) {
    out << st.service << " from number " << st.number
        << " on date " << st.date
        << " with amount " << st.amount;
    return out;
}
