#include "UserInfoParser.h"
#include <list>
#include <string>
#include <boost/json.hpp>
#include <boost/uuid/uuid.hpp>


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
    bool LoadUserInfoFile();
    bool SaveUserInfoFile() const;

    
public:
    void Run() noexcept;
};