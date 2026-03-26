#include <windows.h>

// Функция обработки сообщений окна
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        // --- СЕКЦИЯ ГРАФИКИ (GDI) ---
        Rectangle(hdc, 50, 50, 200, 150); // Рисуем прямоугольник
        MoveToEx(hdc, 0, 0, NULL);
        LineTo(hdc, 300, 300); // Рисуем линию
        // ---------------------------
        EndPaint(hwnd, &ps);
    }
                 return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

// Точка входа
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // 1. Регистрация класса окна
    const char CLASS_NAME[] = "Sample Window Class";
    WNDCLASS wc = { };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    RegisterClass(&wc);

    // 2. Создание окна
    HWND hwnd = CreateWindowEx(
        0, CLASS_NAME, "Окно с графикой C++", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 400,
        NULL, NULL, hInstance, NULL
    );

    if (hwnd == NULL) return 0;

    // 3. Показ окна
    ShowWindow(hwnd, nCmdShow);

    // 4. Цикл сообщений
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}
