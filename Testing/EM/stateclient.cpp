#include "ara/exec/exec_error_domain.hpp"
#include "ara/exec/function_group.hpp"
#include "ara/exec/function_group_state.hpp"
#include "ara/exec/state_client.hpp"

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <gtest/gtest.h>
#include <boost/variant2/variant.hpp>
extern int fg_num;
using namespace boost::variant2;
#define FIFO_NAME "state_client_fifo"
namespace ara
{
    namespace exec
    {
        TEST(StateClientTest, setState)
        {
            mkfifo(FIFO_NAME, 0666);
            int fd = open(FIFO_NAME, O_RDWR);
            StateClient sc;
            fg_num = 0;
            std::string msg;
            msg.resize(150);
            const std::string cShortnamePath{"../App/manifest_samples/machine_manifest.json"};
            
            variant<ara::exec::ExecErrc, FunctionGroup::CtorToken> _functionGroup = FunctionGroup::Preconstruct(cShortnamePath);
            FunctionGroup FG(std::move(get<1>(_functionGroup)));

            variant<ara::exec::ExecErrc, FunctionGroupState::CtorToken> _functionGroupState = FunctionGroupState::Preconstruct(FG, FG.get_FGname() + "/" + FG.get_states()[0]);
            
            FunctionGroupState functionGroupState(std::move(get<1>(_functionGroupState)));

            std::future<boost::variant2::variant<boost::variant2::monostate, ara::exec::ExecErrc>> var0 =sc.SetState(functionGroupState);
            boost::variant2::variant<boost::variant2::monostate, ara::exec::ExecErrc> var = var0.get();
            EXPECT_TRUE(var.index()==0);
            // get<1>(var).get();
            int n = read(fd,&msg[0],150);
            msg[n] = '\0';

            //std::cout<<"Received From SM : "<<msg<<std::endl;
            close(fd);
            unlink(FIFO_NAME);
            EXPECT_TRUE(FG.get_FGname()+"/"+FG.get_states()[0] == msg.substr(0,n));

        }
    } // namespace exec
    
} // namespace ara