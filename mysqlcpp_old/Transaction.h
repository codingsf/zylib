#ifndef _MYSQLCPP_TRANSACTION_H
#define _MYSQLCPP_TRANSACTION_H

#include <memory>
#include <mysql.h>

#include "Types.h"

namespace mysqlcpp {

class Connection;

class Transaction
{
public:
    Transaction(Connection& conn);
    ~Transaction();
    Transaction(const Transaction& rhs) = delete;
    Transaction& operator=(const Transaction& rhs) = delete;

    void commit();
private:
    Connection&  m_conn;
    StatementPtr m_stmt;
    bool         m_rollback;
};

}

#endif

