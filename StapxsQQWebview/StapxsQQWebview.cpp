#include "Common.h"
#include "webview/webview.h"

#ifdef _WIN_PLATFORM_
int wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
{
#else
int main(int argc, char **argv)
{
#endif
    webview_t w = webview_create(0, NULL);
    webview_set_title(w, "Basic Example");
    webview_set_size(w, 480, 320, WEBVIEW_HINT_NONE);
    webview_set_html(w, "Thanks for using webview!");
    webview_run(w);
    webview_destroy(w);
    return 0;
}