#include "UserInfo.h"
#include <list>
#include <string>
#include <boost/json.hpp>


class UserInfoParser
{
    public:
    void ConvertUserInfoToJsonArray(const std::list<UserInfo>& lstUserInfo, boost::json::array& arr) const noexcept;
    void ConvertJsonArrayToUserInfo(const boost::json::array& arr, std::list<UserInfo>& lstUserInfo) noexcept;
};