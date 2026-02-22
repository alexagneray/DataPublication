#include "UserInfoParser.h"
#include <list>
#include <string>
#include <mutex>


enum class DataPublicationManagerError
{
    Success,
    AlreadyExists,
    NotFound
};

/**
 * Gestion de l'authentification des utilisateurs. 
 * Gestion des interactions avec le Core : couche sécurisée interagissant avec le Core, assure la cohérence des interactions,
 * et le refus de certaines opérations si l'utilisateur impliqué n'est pas autorisé. 
 * La classe est thread safe.
 */
class DataPublicationManager
{
public:

private:
    static const std::string UserInfoFilename;
    static const std::string KeyFilename;
    static const std::string IvFilename;

    std::list<UserInfo> m_lstUserInfo;
    std::mutex m_mutUserInfo;


    
public:
    bool LoadUserInfoFile();
    bool SaveUserInfoFile();
    DataPublicationManagerError AddUser(const std::string& name, const std::string& passwd) noexcept;
    DataPublicationManagerError RemoveUser(const std::string& name) noexcept;
    DataPublicationManagerError UpdatePassword(const std::string& name, const std::string& passwd) noexcept;
    void Run() noexcept;
};