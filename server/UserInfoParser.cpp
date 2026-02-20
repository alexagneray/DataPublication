#include "UserInfoParser.h"

void UserInfoParser::ConvertUserInfoToJsonArray(const std::list<UserInfo>& lstUserInfo, boost::json::array& arr) const noexcept
{
    int i = 0;
    arr.resize(lstUserInfo.size());
    for(const auto& user: lstUserInfo)
    {
        boost::json::object& obj = arr.at(i).emplace_object();
        obj["name"] = user._name;
        obj["passwd"] = user._passwd;
        i++;
    }
}

void UserInfoParser::ConvertJsonArrayToUserInfo(const boost::json::array& arr, std::list<UserInfo>& lstUserInfo) noexcept
{
    for(const auto& user: arr)
    {
        UserInfo& info = lstUserInfo.emplace_back();
        info._name = user.at("name").as_string();
        info._passwd = user.at("passwd").as_string();
    }
}