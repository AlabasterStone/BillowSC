#include "runtime.hpp"
using namespace billow;

int main()
{
    thread renderThread(canvasRender, canvasInit());
    cout<<"thread create"<<endl;
    renderThread.join();
    cout<<"thread join"<<endl;
    return 0;
}