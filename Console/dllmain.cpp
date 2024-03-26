﻿// dllmain.cpp : DLL アプリケーションのエントリ ポイントを定義します。
#include "pch.h"

namespace Offsets
{
    constexpr int StaticFindObject = 0x17A803C;

    constexpr int ConsoleClass = 0x00F0;
    constexpr int GameViewport = 0x0910;

    constexpr int ViewportConsole = 0x0040;
}

static void* (*StaticFindObject)(void* Class, void* InOuter, const wchar_t* Name, bool ExactClass);

DWORD WINAPI MainThread(HMODULE hModule)
{
    if (StaticFindObject = decltype(StaticFindObject)(__int64(GetModuleHandle(0)) + Offsets::StaticFindObject))
    {
        void* GEngine = StaticFindObject(nullptr, nullptr, L"/Engine/Transient.FortEngine_2147482646", false);

        if (GEngine != nullptr)
        {
            void** VTable = *reinterpret_cast<void***>(const_cast<void*>(GEngine));

            void* ConsoleClass = *reinterpret_cast<void**>(__int64(GEngine) + Offsets::ConsoleClass);
            void* GameViewport = *reinterpret_cast<void**>(__int64(GEngine) + Offsets::GameViewport);

            void* GameplayStatics = StaticFindObject(nullptr, nullptr, L"/Script/Engine.Default__GameplayStatics", false);
            void* SpawnObject = StaticFindObject(nullptr, nullptr, L"/Script/Engine.GameplayStatics.SpawnObject", false);

            struct GameplayStatics_SpawnObject
            {
                void* ObjectClass;
                void* Param_Outer;
                void* ReturnValue;
            };

            GameplayStatics_SpawnObject Params{ ConsoleClass, GameViewport };

            reinterpret_cast<void(*)(void* Object, void* Function, void* Parms)>(VTable[0x4D])(GameplayStatics, SpawnObject, &Params);

            if (Params.ReturnValue != nullptr)
                *reinterpret_cast<void**>(__int64(GameViewport) + Offsets::ViewportConsole) = Params.ReturnValue;
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

