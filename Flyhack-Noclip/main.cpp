#include <iostream>
#include "stdafx.h"
#include <vector>
#include <Windows.h>
#include "proc.h"
#include "Console.h"
namespace con = JadedHoboConsole;

int main()
{
    SetConsoleTitleA("Ice droppin', red bottom sky");

    //Get ProcID of the target process
    DWORD procId = GetProcId(L"ac_client.exe");

    //Getmodulebaseaddress
    uintptr_t moduleBase = GetModuleBaseAddress(procId, L"ac_client.exe");

    //Get handle to process
    HANDLE hProcess = 0;
    hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);

    //resolve base address of the pointer chain
    uintptr_t dynamicPtrBaseAddr = moduleBase + 0x10f4f4;

    std::cout << "[" << con::fg_green << "+" << con::fg_white << "]" << con::fg_magenta << " Ice on my feet, I keep slippin'\n\n" << con::fg_white;

    std::cout << "[" << con::fg_green << "F1" << con::fg_white << "]" << con::fg_magenta << " Flyhack\n" << con::fg_white;
    std::cout << "[" << con::fg_green << "F2" << con::fg_white << "]" << con::fg_magenta << " NoClip\n\n" << con::fg_white;

    std::cout << "[" << con::fg_green << "+" << con::fg_white << "]" << con::fg_magenta << " Build: 19 June\n" << con::fg_white;
    std::cout << "[" << con::fg_green << "+" << con::fg_white << "]" << con::fg_magenta << " Made by hj.#0010\n" << con::fg_white;

    //Hack vars
    bool bFlyHack = false;
    bool bNoClip = false;
    BYTE spectateOn = 5;
    BYTE spectateOff = 0;
    BYTE invisibleOn = 4;
    BYTE invisibleOff = 0;

    uintptr_t entAddr = 0;
    uintptr_t spectateAddr = 0;
    uintptr_t invisibleAddr = 0;

    while (1)
    {
        if (GetAsyncKeyState(VK_F1) & 1)
        {
            bFlyHack = !bFlyHack;
            ReadProcessMemory(hProcess, (BYTE*)dynamicPtrBaseAddr, &entAddr, sizeof(entAddr), nullptr);
            spectateAddr = entAddr + 0x338;
            //FlyHack code
            if (bFlyHack)
            {
                WriteProcessMemory(hProcess, (BYTE*)spectateAddr, &spectateOn, sizeof(spectateOn), nullptr);
            }
            else
            {
                WriteProcessMemory(hProcess, (BYTE*)spectateAddr, &spectateOff, sizeof(spectateOff), nullptr);
            }
        }
        if (GetAsyncKeyState(VK_F2) &1)
        {
            bNoClip = !bNoClip;
            ReadProcessMemory(hProcess, (BYTE*)dynamicPtrBaseAddr, &entAddr, sizeof(entAddr), nullptr);
            invisibleAddr = entAddr + 0x82;
            //Invisible code
            if (bNoClip)
            {
                WriteProcessMemory(hProcess, (BYTE*)invisibleAddr, &invisibleOn, sizeof(invisibleOn), nullptr);
            }
            else
            {
                WriteProcessMemory(hProcess, (BYTE*)invisibleAddr, &spectateOff, sizeof(spectateOff), nullptr);
            }
        }
    }
    return 0;
}