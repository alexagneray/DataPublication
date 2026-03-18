#include <string>

class DataPublicationAction
{
    protected:
    std::string m_payload;
    virtual void Execute() = 0;
};

class DataPublicationActionPublish : public DataPublicationAction
{   
    void Execute() override;
};
