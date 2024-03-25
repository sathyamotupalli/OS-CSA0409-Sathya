#include <stdio.h>
#include <windows.h>

#define MAX_MSG_SIZE 256
#define MSG_QUEUE_NAME L"Local\\MyMessageQueue"

int main() {
    HANDLE hQueue;
    DWORD dwBytesWritten;
    WCHAR msgBuffer[MAX_MSG_SIZE];

    // Create a message queue
    hQueue = CreateFileW(
        MSG_QUEUE_NAME,
        GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        0,
        NULL);

    if (hQueue == INVALID_HANDLE_VALUE) {
        wprintf(L"Inter process communication message queue %d\n", GetLastError());
        return 1;
    }

    // Prompt user to enter a message
    wprintf(L"Enter a message to be sent through the message queue: ");
    fgetws(msgBuffer, MAX_MSG_SIZE, stdin);

    // Send the message to the message queue
    if (!WriteFile(hQueue, msgBuffer, (wcslen(msgBuffer) + 1) * sizeof(WCHAR), &dwBytesWritten, NULL)) {
        wprintf(L"Failed to write to the message queue. Error code: %d\n", GetLastError());
        CloseHandle(hQueue);
        return 1;
    }

    wprintf(L"Message sent to message queue: %ls", msgBuffer);

    CloseHandle(hQueue);

    return 0;
}

