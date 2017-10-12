#ifndef STATEMENTRECORD_H
#define STATEMENTRECORD_H

#include <string>
#include <istream>
#include <ostream>
class StatementRecord
{
    public:
        StatementRecord(std::string="", std::string="", std::string="", int=0);
        int getAmount() const;
        std::string getDate() const;
        friend std::istream& operator>>(std::istream&, StatementRecord&);
        friend std::ostream& operator<<(std::ostream&, const StatementRecord&);
    private:
        std::string date;
        std::string number;
        std::string service;
        int amount;
};

#endif // STATEMENTRECORD_H
