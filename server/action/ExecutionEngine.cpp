#include "ExecutionEngine.h"

void ExecutionEngine::Start()
{
    m_bRunning = true;
    m_thdExecution = std::thread(&ExecutionEngine::Execute, this, std::ref(m_bRunning));
    m_thdResponse = std::thread(&ExecutionEngine::ProcessResponses, this, std::ref(m_bRunning));
}

void ExecutionEngine::Stop()
{
    m_bRunning = false;
    if (m_thdExecution.joinable())
        m_thdExecution.join();
    if (m_thdResponse.joinable())
        m_thdResponse.join();
}

void ExecutionEngine::Execute(bool& bRunning)
{
    while (bRunning)
    {
        QueryPacket packet;
        if (QueryManagerInstance.GetNextQuery(packet))
        {
            
        }
    }
}

void ExecutionEngine::ProcessResponses(bool& bRunning)
{
    while (bRunning)
    {
        QueryResponse response;
        if (QueryManagerInstance.GetNextResponse(response))
        {
        }
    }
}