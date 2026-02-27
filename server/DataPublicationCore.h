#include <variant>
#include <map>
#include <string>
#include <set>



enum class DataPublicationCoreError
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
    DataPublicationCoreError AddDataList(const std::string& strPublisher, const std::string& strDlName) noexcept;
    DataPublicationCoreError RemoveDataList(const std::string& strDlName) noexcept;

    DataPublicationCoreError AddDataToList(const std::string& strDlName, const std::string& strDataName, const VarType& data) noexcept;
    DataPublicationCoreError RemoveDataFromList(const std::string& strDlName, const std::string& strDataName) noexcept;

    DataPublicationCoreError UpdateData(const std::string& strDlName, const std::string& strDataName, const VarType& newData) noexcept;
    DataPublicationCoreError Subscribe(const std::string& strSubscriber, const std::string& strDlName) noexcept;
    DataPublicationCoreError Unsubscribe(const std::string& strSubscriber, const std::string& strDlName) noexcept;

    DataPublicationCoreError GetPublication(const std::string& strSubscriber, std::map<std::string,std::map<std::string, VarType>>& publication) noexcept;

};