#pragma link "tmsAdvGridExcel"
#pragma link "AdvGrid"
#pragma link "AdvGridWorkbook"
#pragma link "AdvObj"
#pragma link "AdvUtil"
#pragma link "BaseGrid"
#include <vcl.h>
#pragma hdrstop

#include "./RAD/Cru_HEADER.h"
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
#pragma package(smart_init)
#pragma link "AdvEdit"
#pragma link "AdvGlowButton"
#pragma link "CloudImage"
#pragma resource "*.dfm"
//==============================================================================
TpEXCEL_import *pEXCEL_import;
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
// 외부참조 / 전역변수

Cru_SYSTEM xSYS;                                 // 시스템 개체                .

Cru_SCRiPT xSCR;                                 // 스크립트 개체              .

//▩▩▩▩▩▩▩▩▩▩
extern int  Main_TBL_FNOs[1000];                       // 메인테이블 필드번호 리스트
extern int  Main_TBL_AVLs[1000];                       // 메인테이블 표시여부 리스트
extern int  Main_TBL_CLWs[1000];                       // 메인테이블 폭길이 리스트
extern char Main_TBL_FLDs[1000][64];                   // 메인테이블 영문필드이름
extern char Main_TBL_NMEs[1000][64];                   // 메인테이블 한글필드이름
extern int  Main_TBL_Field_CNT;                        // 메인테이블 필드개수
///////
extern int  Main_TBL_DEFAULTs[1000];                   // 메인테이블 디폴트필드 필드번호 리스트
extern int  Main_TBL_DEFAULTs_FLDcnt;                  // 메인테이블 디폴트필드 개수
///////
extern int  Main_TBL_SAVEs[1000];                      // 메인테이블 저장필드 필드번호 리스트
extern int  Main_TBL_SaveCLWs[1000];                   // 메인테이블 저장 폭길이 리스트
extern int  Main_TBL_SAVEs_FLDcnt;                     // 메인테이블 저장필드 개수
//▩▩▩▩▩▩▩▩▩▩

extern int Export_SELcnt;
extern int Export_ALLcnt;
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
__fastcall TpEXCEL_import::TpEXCEL_import(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TpEXCEL_import::uBTN_XLS_import_CloseClick(TObject *Sender)
{
    pEXCEL_import->Close();
}
//---------------------------------------------------------------------------
void __fastcall TpEXCEL_import::AdvGlowButton1Click(TObject *Sender)
{
    pEXCEL_import->uDLG_XLS_import->Execute(NULL);

    pEXCEL_import->uEXCEL_import_File->Text = pEXCEL_import->uDLG_XLS_import->FileName;

//PGM->uEXCEL_wb->Grid->

//    pEXCEL_import->Close();
}
//---------------------------------------------------------------------------
void __fastcall TpEXCEL_import::uBTN_XLS_import_UploadClick(TObject *Sender)
{
    // 엑셀 임포팅 - 파일로딩 다이얼로그 실행
//    pEXCEL_import->uDLG_XLS_import->Execute(NULL);

//PGM->uEXCEL->XLSExport(fSTR, "검색결과");

//PGM->uEXCEL->XLSImport(fSTR, "임포팅");
}
//---------------------------------------------------------------------------
void __fastcall TpEXCEL_import::AdvGlowButton2Click(TObject *Sender)
{
    UnicodeString dSTR, fSTR;

    int n;

    // 엑셀 임포팅 - 파일체크
    dSTR = xSYS.runDiR;
    dSTR += "/iN";
    PGM->uLoadFiLE->InitialDir = dSTR;

    fSTR = pEXCEL_import->uEXCEL_import_File->Text;

    if(fSTR=="")
    {
        okMSG("먼저 열기버튼으로 엑셀파일을 불러오세요");
    }
    else
    {

pEXCEL_import->uEXCEL->XLSImport(fSTR, "임포팅");

n = 777;

    }
}
//---------------------------------------------------------------------------

