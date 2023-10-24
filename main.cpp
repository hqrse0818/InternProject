
#include    "main.h"
#include    "System/Application.h"

#if defined(DEBUG) || defined(_DEBUG)
int wmain(int argc, wchar_t** argv, wchar_t** evnp){


   _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);


    // �A�v���P�[�V�������s
    Application app(SCREEN_WIDTH, SCREEN_HEIGHT);
    app.Run();

    return 0;
}

#else

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow) {


    // ���s����R�[�h���L�q

     // �A�v���P�[�V�������s
    Application app(SCREEN_WIDTH, SCREEN_HEIGHT);
    app.Run();


    return 0;

}

#endif//defined(DEBUG) || defined(_DEBUG)