//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("Main.cpp", PGM);
USEFORM("pXLS_import.cpp", pEXCEL_import);
USEFORM("pXLS_export.cpp", pEXCEL_export);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
    try
    {
         Application->Initialize();
         Application->MainFormOnTaskBar = true;
         Application->CreateForm(__classid(TPGM), &PGM);
         Application->CreateForm(__classid(TpEXCEL_import), &pEXCEL_import);
         Application->CreateForm(__classid(TpEXCEL_export), &pEXCEL_export);
         Application->Run();

         Application->HintPause = 000;
    }
    catch (Exception &exception)
    {
         Application->ShowException(&exception);
    }
    catch (...)
    {
         try
         {
             throw Exception("");
         }
         catch (Exception &exception)
         {
             Application->ShowException(&exception);
         }
    }
    return 0;
}
//---------------------------------------------------------------------------
