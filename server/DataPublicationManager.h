#include "UserInfoParser.h"
#include <list>
#include <string>

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
 */
class DataPublicationManager
{
public:

private:
    std::list<UserInfo> m_lstUserInfo;


    
public:
    bool LoadUserInfoFile();
    bool SaveUserInfoFile() const;
    DataPublicationManagerError AddUser(const std::string& name, const std::string& passwd) noexcept;
    DataPublicationManagerError RemoveUser(const std::string& name) noexcept;
    DataPublicationManagerError UpdatePassword(const std::string& name, const std::string& passwd) noexcept;
    void Run() noexcept;
};