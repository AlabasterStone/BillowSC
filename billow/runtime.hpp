#include <string>
#include <emscripten.h>
#include <emscripten/val.h>
#include <thread>
#include <iostream>
using namespace std;
using namespace emscripten;

namespace billow
{
    const int MAX_SPRITES = 1000;
    const int MAX_SPRITE_COSTUMES = 1000;
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

    struct renderSpriteCostume
    {
        // 造型图片路径
        string md5ext;
        // svg,png,jpg...
        int dataFormat;
        int bitmapResolution;
        double rotationCenterX;
        double rotationCenterY;
    };

    struct renderSprite
    {
        int currentCostume;
        renderSpriteCostume costumes[MAX_SPRITE_COSTUMES];
        // TODO: 添加声音播放
        int layerOrder;
        bool visible;
        int x;
        int y;
        int size;
        int direction;
        // 设定旋转方式，传入编号
        int rotationStyle;
    };

    struct renderTarget
    {
        renderSprite sprite[MAX_SPRITES];
    };

    struct renderMonitor
    {
        // 监视器指令编号
        int opcode;
        // 显示类型编号
        int mode;
        // TODO: params
        double value;
        int width;
        int height;
        int x;
        int y;
        bool visible;
        float sliderMin;
        float sliderMax;
    };

    struct renderMap
    {
        renderTarget target;
        renderMonitor monitors[];
    };

    val canvasInit()
    {
        val document = val::global("document");
        val canvasElement = document.call<val, string>("getElementById", "canvas");
        val canvasContext = canvasElement.call<val, string>("getContext", "2d");
        return canvasContext;
    }

    void canvasRender(val ctx)
    {
        ctx.set("fillStyle", "green");
        ctx.call<void>("fillRect", 0, 0, 150, 150);
    }
}
