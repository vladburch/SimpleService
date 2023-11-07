#include <windows.h>
#include <stdio.h>

#define SLEEP_TIME 5000

SERVICE_STATUS serviceStatus;
SERVICE_STATUS_HANDLE hStatus;

void ServiceMain(int argc, char** argv);
void ControlHandler(DWORD request);

wchar_t ServiceName[] = L"WKSService";

int DoStaff() {
    
    Sleep(SLEEP_TIME);

    return 0;
}

int main() {
    SERVICE_TABLE_ENTRY ServiceTable[] = {
      {ServiceName, (LPSERVICE_MAIN_FUNCTION)ServiceMain},
      {NULL, NULL}
    };

    StartServiceCtrlDispatcher(ServiceTable);
    return 0;
}

void ServiceMain(int argc, char** argv) {
    serviceStatus.dwServiceType = SERVICE_WIN32;
    serviceStatus.dwCurrentState = SERVICE_START_PENDING;
    serviceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN;
    serviceStatus.dwWin32ExitCode = 0;
    serviceStatus.dwServiceSpecificExitCode = 0;
    serviceStatus.dwCheckPoint = 0;
    serviceStatus.dwWaitHint = 0;

    hStatus = RegisterServiceCtrlHandler(ServiceName, (LPHANDLER_FUNCTION)ControlHandler);
    DoStaff();

    serviceStatus.dwCurrentState = SERVICE_RUNNING;
    SetServiceStatus(hStatus, &serviceStatus);

    while (serviceStatus.dwCurrentState == SERVICE_RUNNING) {
        Sleep(SLEEP_TIME);
    }
    return;
}

void ControlHandler(DWORD request) {
    switch (request) {
    case SERVICE_CONTROL_STOP:
        serviceStatus.dwWin32ExitCode = 0;
        serviceStatus.dwCurrentState = SERVICE_STOPPED;
        SetServiceStatus(hStatus, &serviceStatus);
        return;

    case SERVICE_CONTROL_SHUTDOWN:
        serviceStatus.dwWin32ExitCode = 0;
        serviceStatus.dwCurrentState = SERVICE_STOPPED;
        SetServiceStatus(hStatus, &serviceStatus);
        return;

    default:
        break;
    }
    SetServiceStatus(hStatus, &serviceStatus);
    return;
}
