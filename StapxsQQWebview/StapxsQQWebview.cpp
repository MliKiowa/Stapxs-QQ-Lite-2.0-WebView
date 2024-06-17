#include "Common.h"
#include "webview/webview.h"

#ifdef _WIN_PLATFORM_
int wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
{
#else
int main(int argc, char **argv)
{
#endif
    webview_t w;
    w = webview_create(false, nullptr);
    webview_set_size(w, 1000, 700, WEBVIEW_HINT_NONE);
    webview_set_title(w, "Test");
    webview_set_html(w, "set_html ok");
    webview_navigate(w, "https://stapxs.github.io/Stapxs-QQ-Lite-2.0/");
    webview_run(w);
    return 0;
}