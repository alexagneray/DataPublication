#include <variant>
#include <map>
#include <string>
#include <set>



enum class DataPublicationError
{
    Success,
    AlreadyExists,
    AddingIssue,
    NotFound
};

class DataPublicationCore
{
    public:
    using VarType = std::variant<std::string, double, long, bool>;
    private:
    struct Info
    {
        std::set<std::string> _setPublishers;
        std::set<std::string> _setSubscribers;
    };

    
    std::map<std::string, std::map<std::string,VarType>> m_dlData;
    std::map<std::string, Info> m_dlInfo;

    public:
    DataPublicationError AddDataList(const std::string& strPublisher, const std::string& strDlName) noexcept;
    DataPublicationError RemoveDataList(const std::string& strDlName) noexcept;

    DataPublicationError AddDataToList(const std::string& strDlName, const std::string& strDataName, const VarType& data) noexcept;
    DataPublicationError RemoveDataFromList(const std::string& strDlName, const std::string& strDataName) noexcept;

    DataPublicationError UpdateData(const std::string& strDlName, const std::string& strDataName, const VarType& newData) noexcept;
    DataPublicationError Subscribe(const std::string& strSubscriber, const std::string& strDlName) noexcept;
    DataPublicationError Unsubscribe(const std::string& strSubscriber, const std::string& strDlName) noexcept;

    DataPublicationError GetPublication(const std::string& strSubscriber, std::map<std::string,std::map<std::string, VarType>>& publication) noexcept;

};