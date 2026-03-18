#include <thread>
#include <QueryManager.h>

class ExecutionEngine
{
private:
    std::thread m_thdExecution;
    std::thread m_thdResponse;
    bool m_bRunning;
public:
    void Start();
    void Stop();
    void Execute(bool &bRunning);
    void ProcessResponses(bool &bRunning);
};