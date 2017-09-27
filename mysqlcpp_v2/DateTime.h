#ifndef _MYSQLCPP_DATETIME_H
#define _MYSQLCPP_DATETIME_H

#include <mysql.h>
#include <array>
#include <vector>
#include <string>

#include <boost/date_time/posix_time/ptime.hpp>

#include "Types.h"

namespace mysqlcpp {

class DateTime
{
public:
    DateTime();
    explicit DateTime(time_t t);
    explicit DateTime(const timeval& t);
    explicit DateTime(const MYSQL_TIME& mysql_time);
    explicit DateTime(const boost::posix_time::ptime& pt);

    DateTime(const DateTime& rhs);
    DateTime& operator=(const DateTime& rhs);

    DateTime(DateTime&& rhs);
    DateTime& operator=(DateTime&& rhs);

    ~DateTime();

public:
    std::vector<uint8> getBinary() const;
    const MYSQL_TIME&  getMYSQL_TIME() const;
    MYSQL_TIME&        getMYSQL_TIME();
    std::string        getString() const;
    time_t             getTime() const;

private:
    void set_Y_m_d_H_M_S(const struct tm& t);
    static boost::posix_time::ptime timevalToPtime(const struct timeval& tv);

    bool isNull() const;
private:
    MYSQL_TIME m_mysql_time;
};

}

#endif
