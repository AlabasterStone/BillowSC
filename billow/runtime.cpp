#include <emscripten/val.h>

auto main() -> int
{
    const auto document = emscripten::val::global("document");
    const auto canvas =
        document.call<emscripten::val, std::string>("querySelector", "canvas");

    auto ctx = canvas.call<emscripten::val, std::string>("getContext", "2d");

    const auto width = canvas["width"].as<int>();
    const auto height = canvas["height"].as<int>();

    ctx.call<void>("clearRect", 0, 0, width, height);

    // rect
    ctx.set("fillStyle", "white");
    ctx.call<void>("fillRect", 0, 0, width, height);

    // line
    ctx.set("strokeStyle", "black");
    ctx.call<void>("moveTo", 0, 0);
    ctx.call<void>("lineTo", width, height);
    ctx.call<void>("stroke");

    // text
    ctx.set("fillStyle", "black");
    ctx.set("font", "bold 48px serif");
    ctx.call<void, std::string>("fillText", "Hello World!", width / 2,
                                height / 2);

    return 0;
}