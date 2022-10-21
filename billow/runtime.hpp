#include <cheerp/client.h>
#include <cheerp/clientlib.h>
#include <string>
using namespace client;
using namespace std;

namespace billow
{
    class scMonitor
    {
        public:
            scMonitor(string id, string mode, string opcode, string param, double value, bool visible, int sliderMin, int sliderMax, bool isDiscrete);
        
        private:
            string monitor_mode_default = "default";
            string monitor_mode_large = "large";
            string monitor_mode_slider = "slider";
            string monitor_mode_list = "list";

            string monitor_opcode_loudness = "sensing_loudness";
            string monitor_opcode_list = "data_listcontents";
    }
}
