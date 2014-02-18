#include "constraints.h"
#include <boost/asio/ip/address.hpp>
using namespace std;

bool is_not_invalid_doid(const doid_t& c)
{
	return c != INVALID_DO_ID;
}
bool is_not_reserved_doid(const doid_t& c)
{
	return (c < 1) || (c > 999); 
}
bool is_not_invalid_channel(const channel_t& c)
{
	return c != INVALID_CHANNEL;
}
bool is_not_reserved_channel(const channel_t& c)
{
	return (c < 1)
	    || ((c > 999) && (c < (channel_t(1) << ZONE_BITS)))
	    || (c > channel_t(999) << ZONE_BITS);
}
bool is_valid_ip_address(const string& host)
{
	using namespace boost::asio;
	using namespace boost::system;

	// Parse out port from address string
	string addr;
    int col_index = host.find_last_of(":");
    int sqr_index = host.find_last_of("]");
	if(col_index != (int)string::npos && col_index > sqr_index)
	{
		addr = host.substr(0, col_index);
	}
	else
	{
		addr = host;
	}


	error_code ec;
	ip::address::from_string(addr, ec);
	if(ec.value() != 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}
