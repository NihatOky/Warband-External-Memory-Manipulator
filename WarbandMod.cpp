
#include "proc.h"
#include <iostream>
#include <vector>
#include <windows.h>
#include <chrono>
#include <thread>

using namespace std;


uintptr_t FindDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets)
{
    uintptr_t addr = ptr;
    for (unsigned int i = 0; i < offsets.size(); ++i)
    {
        if (!ReadProcessMemory(hProc, (BYTE*)addr, &addr, sizeof(addr), 0))
        {
            std::cerr << "Failed to read memory at offset " << i << std::endl;
            return 0;
        }
        addr += offsets[i];
    }
    return addr;
}

void RightClick() {
    INPUT input = { 0 };

    input.type = INPUT_MOUSE;
    input.mi.dx = 0;
    input.mi.dy = 0;
    input.mi.mouseData = 0;
    input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
    input.mi.time = 0;
    input.mi.dwExtraInfo = 0;
    SendInput(1, &input, sizeof(INPUT));

    // Fare sağ tuş bırakma
    input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
    SendInput(1, &input, sizeof(INPUT));
}

int main()
{
    cout << "Nihat Okyar Tarafından hazırlandı" << endl;

    DWORD modulebase, Pid;
    HANDLE handle;

    // Proses ID'sini alıyoruz
    Pid = getprocid(L"mb_Warband.exe");

    // Modülün taban adresini alıyoruz
    modulebase = getmodulebaseaddres(Pid, L"mb_Warband.exe");

    // Warband işlemine erişim sağlıyoruz
    handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, Pid);
    if (Pid == 0)
    {
        cout << "Warband bulunamadı" << endl;
    }
    else
    {
        cout << "warband bulundu" << endl;
    }

    if (modulebase == 0)
    {
        cout << "Modül bulunamadı" << endl;
    }
    else
    {
        cout << "Modül bulundu" << endl;
    }

    if (!handle)
    {
        cout << "Couldn't handle to Warband" << endl;
    }
    else
    {
        cout << "Lütfen  oyuna enjekte edin... Devam etmek için Enter tuşuna basın." << endl;
        cout << "Enjeksiyon Başarılı!" << endl;
    }

    cout << "Nihat Okyar Tarafından hazırlandı" << endl;

    // Entity Offset listesi (oyundaki karakterlerin listesine erişim için)
    vector<unsigned int> EntityOffset{ 0x4, 0x2B0, 0x134, 0x110, 0xC };
    vector<unsigned int> healthoffset{ 0x4, 0x2B0, 0x134, 0x110, 0xC, 0x6000 };
    vector<unsigned int> offsetX{ 0x4, 0x2B0, 0x134, 0x110, 0xC, 0x40 };
    vector<unsigned int> offsetY{ 0x4, 0x2B0, 0x134, 0x110, 0xC, 0x44 };
    vector<unsigned int> offsetZ{ 0x4, 0x2B0, 0x134, 0x110, 0xC, 0x48 };
    vector<unsigned int> matrix3B0offset{ 0x3B0 };
    vector<unsigned int> matrix3ACoffset{ 0x3AC };

    uintptr_t addres = 0x02D5484C;
    uintptr_t entityaddres = modulebase + addres;
    uintptr_t EntityList = FindDMAAddy(handle, addres, EntityOffset);

    uintptr_t healthaddres = modulebase + addres;
    uintptr_t healthoffsetT = FindDMAAddy(handle, addres, healthoffset);

    uintptr_t Xaddres = modulebase + addres;
    uintptr_t xoffsetT = FindDMAAddy(handle, addres, offsetX);

    uintptr_t Yaddres = modulebase + addres;
    uintptr_t YoffsetT = FindDMAAddy(handle, addres, offsetY);

    uintptr_t Zaddres = modulebase + addres;
    uintptr_t ZoffsetT = FindDMAAddy(handle, addres, offsetZ);

    uintptr_t matrixaddr = modulebase + 0x009D9B18; //3B0 offseti
    uintptr_t matrixtotaladdr = FindDMAAddy(handle, matrixaddr, matrix3B0offset);

    uintptr_t matrix3AC = modulebase + 0x009D9B18;
    uintptr_t matrix3ACaddr = FindDMAAddy(handle, matrix3AC, matrix3ACoffset);

    uintptr_t zoomnopOffset = modulebase + 0x1B270B;

   


  
    unsigned char nops[]{ 0x90,0x90,0x90 };
    unsigned char RealBytes[]{ 0x8B,0x43,0x08 };

   
    float heal = 0.0f;
    float matrix3b0deger = -1;
    float matrix3ACdeger = 0;
    float zoomDeger = 0;
    float zoom3ACdeger = 0;

    bool wasInsertPressed = false;
    bool wasEndPressed = false;
    bool end = false;
    bool insert = false;
    bool f1key = false;
    bool ctrlPressed;
    bool qkey = false;
    bool tabPressed = false;
    bool capspressed = false;
    bool altPressed = false; 

    bool zoomToggled = false; 
    bool oWasPressed = false; 


    while (true)
    {
       
        
        if (GetAsyncKeyState(VK_CONTROL) & 0x8000) {
            if (!ctrlPressed) { ctrlPressed = true; }
        }
        else {
            if (ctrlPressed) { ctrlPressed = false; }
        }

        if (ctrlPressed) {
            // 0 değeri
            matrix3b0deger = 0;
            if (!WriteProcessMemory(handle, (LPVOID)matrixtotaladdr, &matrix3b0deger, sizeof(matrix3b0deger), nullptr)) {
               
            }
            else {
                
            }
            this_thread::sleep_for(chrono::milliseconds(220));

            // 1 değeri
            matrix3b0deger = 1;
            if (!WriteProcessMemory(handle, (LPVOID)matrixtotaladdr, &matrix3b0deger, sizeof(matrix3b0deger), nullptr)) {
              
            }
            else {
              
            }
            this_thread::sleep_for(chrono::milliseconds(220));

            matrix3b0deger = -1;
            if (!WriteProcessMemory(handle, (LPVOID)matrixtotaladdr, &matrix3b0deger, sizeof(matrix3b0deger), nullptr)) {
              
            }
            else {
               
            }
            this_thread::sleep_for(chrono::milliseconds(220));

            matrix3ACdeger = 0;
            if (!WriteProcessMemory(handle, (LPVOID)matrix3ACaddr, &matrix3ACdeger, sizeof(matrix3ACdeger), nullptr)) {
               
            }
            else {
                
            }
            this_thread::sleep_for(chrono::milliseconds(220));

            matrix3ACdeger = 1;
            if (!WriteProcessMemory(handle, (LPVOID)matrix3ACaddr, &matrix3ACdeger, sizeof(matrix3ACdeger), nullptr)) {

            }
            else {
              
            }
            this_thread::sleep_for(chrono::milliseconds(220));

            matrix3ACdeger = -1;
            if (!WriteProcessMemory(handle, (LPVOID)matrix3ACaddr, &matrix3ACdeger, sizeof(matrix3ACdeger), nullptr)) {
                
            }
            else {
               
            }
            this_thread::sleep_for(chrono::milliseconds(220));

          
        }
        else {
            this_thread::sleep_for(chrono::milliseconds(40));
        }

        






        if (GetAsyncKeyState(VK_F1)) {
            Sleep(300);
            //mb_warband.exe+BE677 - 8B 43 08 - mov eax,[ebx+08]
            unsigned char nops[]{ 0x90, 0x90, 0x90 };
            DWORD targetoffset = 0xBE677;
            DWORD targetaddres = modulebase + targetoffset;
            if (WriteProcessMemory(handle, (LPVOID)targetaddres, nops, sizeof(nops), 0)) {
                cout << "yer altına inildi" << endl;
            }
        }

        if (GetAsyncKeyState(VK_F2)) {
            Sleep(300);
            unsigned char bytes[]{ 0x8B, 0x43 , 0x08 };
            DWORD targetoffset = 0xBE677;
            DWORD targetaddresr = modulebase + targetoffset;
            if (WriteProcessMemory(handle, (LPVOID)targetaddresr, bytes, sizeof(bytes), 0)) {
                cout << "yer altından çıkıldı! " << endl;
            }
        }


        float girişdegeri;

        if (GetAsyncKeyState(VK_END) & 0x8000) {
            if (!wasEndPressed) {
                wasEndPressed = true;
                if (!end) {
                    unsigned char realbyte5[] = { 0x89, 0x53, 0x48 };
                    DWORD hedefoffset = 0xEAB26;
                    DWORD hedefaddres = modulebase + hedefoffset;
                    DWORD hedefoffset2 = 0xBE67A;
                    DWORD hedefaddres2 = modulebase + hedefoffset2;
                    unsigned char nopsfornoclip[] = { 0x90, 0x90, 0x90 };
                    unsigned char nopsfornoclip2[] = { 0x90, 0x90, 0x90 };
                    if (WriteProcessMemory(handle, (LPVOID)hedefaddres, nopsfornoclip, sizeof(nopsfornoclip), 0)) {
                        cout << "deger gırınız:  " << endl;
                    }
                    if (WriteProcessMemory(handle, (LPVOID)hedefaddres2, nopsfornoclip2, sizeof(nopsfornoclip2), 0)) {
                        cout << "deger gırınız:  " << endl;
                    }

                    vector<unsigned> zaddronlineoffset{ 0x48 };
                    float readprocesdeger = 0.0f;
                    uintptr_t zaddr = 0x0314E9E8 + 0x550;
                    uintptr_t ztotaladdr = FindDMAAddy(handle, zaddr, zaddronlineoffset);
                    ReadProcessMemory(handle, (LPCVOID)ztotaladdr, &readprocesdeger, sizeof(readprocesdeger), 0);
                    cout << "readprocesdeger: " << readprocesdeger << endl;
                    cout << "No clip açıldı. Lütfen değer girin: ";
                    cin >> girişdegeri;
                    if (WriteProcessMemory(handle, (LPVOID)ztotaladdr, &girişdegeri, sizeof(girişdegeri), 0)) {
                        cout << "Girdiğiniz değer ile no clip açılmıştır!" << endl;
                    }
                    end = true;
                }
                else {
                    unsigned char BE67Abyte[] = { 0x89, 0x46, 0x48 };
                    unsigned char EAB26byte[] = { 0x89, 0x53, 0x48 };
                    DWORD hedefoffset2 = 0xBE67A;
                    DWORD hedefaddres2 = modulebase + hedefoffset2;
                    DWORD hedefoffset = 0xEAB26;
                    DWORD hedefaddres = modulebase + hedefoffset;
                    // No clip kapama
                    if (WriteProcessMemory(handle, (LPVOID)hedefaddres2, BE67Abyte, sizeof(BE67Abyte), 0)) {
                        cout << "No clip kapandı!" << endl;
                    }
                    if (WriteProcessMemory(handle, (LPVOID)hedefaddres, EAB26byte, sizeof(EAB26byte), 0)) {
                    }
                    end = false;
                }
            }
        }
        else {
            wasEndPressed = false;
        }
    }

    return 0;
}
