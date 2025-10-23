#include <windows.h>
#include <commdlg.h>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

#define ID_TITLEBOX     101
#define ID_OPENBUTTON   102
#define ID_PATCHBUTTON  103

std::wstring selectedFilePath;
std::wstring titleId;

std::vector<uint8_t> hexStringToBytes(const std::wstring& hex) {
    std::vector<uint8_t> bytes;
    for (size_t i = 0; i < hex.length(); i += 2) {
        std::wstring byteString = hex.substr(i, 2);
        uint8_t byte = static_cast<uint8_t>(std::stoi(byteString, nullptr, 16));
        bytes.push_back(byte);
    }
    return bytes;
}

std::wstring openFileDialog(HWND hwnd) {
    wchar_t fileName[MAX_PATH] = L"";

    OPENFILENAMEW ofn = {};
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFilter = L"Binary Files (*.bin)\0*.bin\0All Files (*.*)\0*.*\0";
    ofn.lpstrFile = fileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
    ofn.lpstrTitle = L"Select versions.bin";

    if (GetOpenFileNameW(&ofn)) {
        return std::wstring(fileName);
    }
    return L"";
}

void patchFile(HWND hwnd) {
    if (selectedFilePath.empty() || titleId.length() != 16) {
        MessageBoxW(hwnd, L"Please enter a valid Title ID and select a file.", L"Error", MB_OK | MB_ICONERROR);
        return;
    }

    std::ifstream inFile(selectedFilePath, std::ios::binary);
    if (!inFile) {
        MessageBoxW(hwnd, L"Failed to open file.", L"Error", MB_OK | MB_ICONERROR);
        return;
    }

    std::vector<uint8_t> buffer((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
    inFile.close();

    std::vector<uint8_t> titleBytes = hexStringToBytes(titleId);
    auto it = std::search(buffer.begin(), buffer.end(), titleBytes.begin(), titleBytes.end());

    if (it != buffer.end()) {
        size_t offset = std::distance(buffer.begin(), it);
        if (offset + 0x0F < buffer.size()) {
            buffer[offset + 0x0C] = 0x00;
            buffer[offset + 0x0D] = 0x00;
            buffer[offset + 0x0E] = 0x00;
            buffer[offset + 0x0F] = 0x00;

            std::ofstream outFile(selectedFilePath, std::ios::binary);
            outFile.write(reinterpret_cast<const char*>(buffer.data()), buffer.size());
            outFile.close();

            MessageBoxW(hwnd, L"Patch applied successfully!", L"Success", MB_OK | MB_ICONINFORMATION);
        } else {
            MessageBoxW(hwnd, L"File too short to patch.", L"Error", MB_OK | MB_ICONERROR);
        }
    } else {
        MessageBoxW(hwnd, L"Title ID not found in file.", L"Error", MB_OK | MB_ICONERROR);
    }
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE:
        CreateWindowW(L"STATIC", L"Enter Title ID:", WS_VISIBLE | WS_CHILD,
            20, 20, 100, 20, hwnd, NULL, NULL, NULL);
        CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER,
            130, 20, 150, 20, hwnd, (HMENU)ID_TITLEBOX, NULL, NULL);
        CreateWindowW(L"BUTTON", L"Open File", WS_VISIBLE | WS_CHILD,
            20, 60, 100, 30, hwnd, (HMENU)ID_OPENBUTTON, NULL, NULL);
        CreateWindowW(L"BUTTON", L"Patch", WS_VISIBLE | WS_CHILD,
            130, 60, 100, 30, hwnd, (HMENU)ID_PATCHBUTTON, NULL, NULL);
        return 0;

    case WM_COMMAND:
        if (LOWORD(wParam) == ID_OPENBUTTON) {
            selectedFilePath = openFileDialog(hwnd);
        }
        else if (LOWORD(wParam) == ID_PATCHBUTTON) {
            wchar_t buffer[17] = {};
            GetWindowTextW(GetDlgItem(hwnd, ID_TITLEBOX), buffer, 17);
            titleId = std::wstring(buffer);
            patchFile(hwnd);
        }
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"WiiUPatcherWindow";

    WNDCLASSW wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClassW(&wc);

    HWND hwnd = CreateWindowExW(0, CLASS_NAME, L"WiiU Title ID Patcher",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 320, 160,
        NULL, NULL, hInstance, NULL);

    if (hwnd == NULL) return 0;

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg = {};
    while (GetMessageW(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    return 0;
}