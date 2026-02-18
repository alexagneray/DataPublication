#include <list>
#include <variant>
#include <map>
#include <string>



enum class DataPublicationError
{
    Success,
    AlreadyExists,
    AddingIssue,
    NotFound
};

class DataPublicationServer
{
    private:
    struct Info
    {
        std::list<std::string> _lstPublishers;
        std::list<std::string> _lstSubscribers;
    };

    using VarType = std::variant<std::string, double, long, bool>; // type générique
    std::map<std::string, std::map<std::string,VarType>> m_dlData; // data list
    std::map<std::string, Info> m_dlInfo; // data list info

    public:
    DataPublicationError AddDataList(const std::string& strPublisher, const std::string& strDlName) noexcept;
    DataPublicationError RemoveDataList(const std::string& strDlName) noexcept;

    DataPublicationError AddDataToList(const std::string& strDlName, const std::string& strDataName, const VarType& data) noexcept;
    DataPublicationError RemoveDataFromList(const std::string& strDlName, const std::string& strDataName) noexcept;
    
};