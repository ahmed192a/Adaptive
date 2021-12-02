#include "execution_client.h"
#include "sys/stat.h"
#include "sys/types.h"
#include "errno.h"
#include <fcntl.h>

namespace ara
{
    namespace exec
    {
        ExecutionClient::ExecutionClient()
        {
            // opens the Execution Management communication channel for reporting the Execution State
            if (mkfifo(fifo_l, 0777) == -1)
            {
                if (errno != EEXIST)
                {
                    // TO DO
                    // Log Error : coundn't create fifo
                }
            }
            // get file discreptor
            fd = open(fifo_l, O_WRONLY);
        }
        ExecutionClient::~ExecutionClient()
        {
            // close file descriptor
            close(fd);
        }
        void ExecutionClient::ReportExecutionState(ara::exec::ExecutionState state) const
        {
            if (write(fd, &state, sizeof(state)) == -1)
            {
                // TO DO
                // Log Error : counldn't send the state to fifo
            }
        }

    }
}