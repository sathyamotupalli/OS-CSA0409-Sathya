#include <stdio.h>
#include <windows.h>

#define BUF_SIZE 256
#define SHARED_MEM_NAME "Local\\MySharedMemory"

int main() {
    HANDLE hMapFile;
    LPCTSTR pBuf;

    hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE,    // Use the page file
        NULL,                    // Default security
        PAGE_READWRITE,          // Read/write access
        0,                       // Maximum object size (high-order DWORD)
        BUF_SIZE,                // Maximum object size (low-order DWORD)
        SHARED_MEM_NAME);        // Name of the mapping object

    if (hMapFile == NULL) {
        printf("Could not create file mapping object (%d)\n", GetLastError());
        return 1;
    }

    pBuf = (LPTSTR)MapViewOfFile(
        hMapFile,            // Handle to the map object
        FILE_MAP_ALL_ACCESS, // Read/write permission
        0,
        0,
        BUF_SIZE);

    if (pBuf == NULL) {
        printf("Could not map view of file (%d)\n", GetLastError());
        CloseHandle(hMapFile);
        return 1;
    }

    printf("Enter a message to be written to shared memory: ");
    fgets((char*)pBuf, BUF_SIZE, stdin);

    printf("Message written to shared memory: %s\n", pBuf);

    UnmapViewOfFile(pBuf);
    CloseHandle(hMapFile);

    return 0;
}

