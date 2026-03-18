#include "DataPublicationAction.h"
#include <DataPublicationCore.h>
#include <DataPublication.h>
#include <boost/json.hpp>


void DataPublicationActionPublish::Execute()
{
    std::string strPublisher, strDataList;

    boost::json::object obj = boost::json::parse(m_payload).as_object();
    if(obj.contains("Publisher") && obj["Publisher"].is_string()
       && obj.contains("DataList") && obj["DataList"].is_string())
    {
        strPublisher = obj["Publisher"].as_string().c_str();
        strDataList = obj["DataList"].as_string().c_str();
    }
    else
    {
        // Handle error: Publisher or DataList field is missing or not a string
        return;
    }

    DataPublicationCoreError error = DataPublicationCoreInstance.AddDataList(strPublisher, strDataList);
    if(error != DataPublicationCoreError::Success)
    {
        // Handle error: Log the error or take appropriate action
    }
}