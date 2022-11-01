#include <string>
using namespace std;

namespace billow
{
    const int MAX_SPRITES = 100000;
    const int MAX_SPRITE_COSTUMES = 100000;
    /*
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
    };
    */

    struct renderMap
    {
        renderTarget target;
        renderMonitor monitors[];
    };

    struct renderTarget
    {
        renderSprite sprite[MAX_SPRITES];
    };
    
    struct renderSprite
    {
        int currentCostume;
        renderSpriteCostume costumes[MAX_SPRITE_COSTUMES];
        //TODO: 添加声音播放
        int layerOrder;
        bool visible;
        int x;
        int y;
        int size;
        int direction;
        //设定旋转方式，传入编号
        int rotationStyle;
    };
    
    struct renderMonitor
    {
        //监视器指令编号
        int opcode;
        //显示类型编号
        int mode;
        //TODO: params
        double value;
        int width;
        int height;
        int x;
        int y;
        bool visible;
        float sliderMin;
        float sliderMax;
    };
    
    struct renderSpriteCostume
    {
        //造型图片路径
        string md5ext;
        //svg,png,jpg...
        int dataFormat;
        int bitmapResolution;
        double rotationCenterX;
        double rotationCenterY;
    };
}
