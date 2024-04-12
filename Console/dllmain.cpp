// dllmain.cpp : DLL アプリケーションのエントリ ポイントを定義します。
#include "pch.h"

namespace Offsets
{
    constexpr int StaticFindObject = 0x1520080; // 29.20

    constexpr int ConsoleClass = 0x00F0; // UEngine
    constexpr int GameViewport = 0x0910; // UEngine

    constexpr int ViewportConsole = 0x0040; // UGameViewportClient
}

static void* (*StaticFindObject)(void* Class, void* InOuter, const wchar_t* Name, bool ExactClass) = decltype(StaticFindObject)(__int64(GetModuleHandle(0)) + Offsets::StaticFindObject);

DWORD WINAPI MainThread(HMODULE hModule)
{
    static void* GEngine = StaticFindObject(nullptr, nullptr, L"/Engine/Transient.FortEngine_2147482646", false);

    if (GEngine != nullptr)
    {
        void** VTable = *reinterpret_cast<void***>(const_cast<void*>(GEngine));

        void* ConsoleClass = *reinterpret_cast<void**>(__int64(GEngine) + Offsets::ConsoleClass);
        void* GameViewport = *reinterpret_cast<void**>(__int64(GEngine) + Offsets::GameViewport);

        if (ConsoleClass && GameViewport)
        {
            void* GameplayStatics = StaticFindObject(nullptr, nullptr, L"/Script/Engine.Default__GameplayStatics", false);
            void* Function = StaticFindObject(nullptr, nullptr, L"/Script/Engine.GameplayStatics.SpawnObject", false);

            struct GameplayStatics_SpawnObject
            {
                void* ObjectClass;
                void* Param_Outer;
                void* ReturnValue;
            };

            GameplayStatics_SpawnObject Params{ ConsoleClass, GameViewport };

            reinterpret_cast<void(*)(void*, void*, void*)>(VTable[0x4D])(GameplayStatics, Function, &Params);

            if (Params.ReturnValue != nullptr)
            {
                *reinterpret_cast<void**>(__int64(GameViewport) + Offsets::ViewportConsole) = Params.ReturnValue;
            }
        }
    }

    return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)MainThread, hModule, 0, 0);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

