#pragma link "tmsAdvGridExcel"
#pragma link "AdvGrid"
#pragma link "AdvGridWorkbook"
#pragma link "AdvObj"
#pragma link "AdvUtil"
#pragma link "BaseGrid"
#include <vcl.h>
#pragma hdrstop

#include "./RAD/Cru_HEADER.h"
// ���������������������������������������.
//����������������������������������������
// ���������������������������������������.
#pragma package(smart_init)
#pragma link "AdvEdit"
#pragma link "AdvGlowButton"
#pragma link "CloudImage"
#pragma resource "*.dfm"
//==============================================================================
TpEXCEL_import *pEXCEL_import;
// ���������������������������������������.
//����������������������������������������
// ���������������������������������������.
// �ܺ����� / ��������

Cru_SYSTEM xSYS;                                 // �ý��� ��ü                .

Cru_SCRiPT xSCR;                                 // ��ũ��Ʈ ��ü              .

//�̢̢̢̢̢̢̢̢̢�
extern int  Main_TBL_FNOs[1000];                       // �������̺� �ʵ��ȣ ����Ʈ
extern int  Main_TBL_AVLs[1000];                       // �������̺� ǥ�ÿ��� ����Ʈ
extern int  Main_TBL_CLWs[1000];                       // �������̺� ������ ����Ʈ
extern char Main_TBL_FLDs[1000][64];                   // �������̺� �����ʵ��̸�
extern char Main_TBL_NMEs[1000][64];                   // �������̺� �ѱ��ʵ��̸�
extern int  Main_TBL_Field_CNT;                        // �������̺� �ʵ尳��
///////
extern int  Main_TBL_DEFAULTs[1000];                   // �������̺� ����Ʈ�ʵ� �ʵ��ȣ ����Ʈ
extern int  Main_TBL_DEFAULTs_FLDcnt;                  // �������̺� ����Ʈ�ʵ� ����
///////
extern int  Main_TBL_SAVEs[1000];                      // �������̺� �����ʵ� �ʵ��ȣ ����Ʈ
extern int  Main_TBL_SaveCLWs[1000];                   // �������̺� ���� ������ ����Ʈ
extern int  Main_TBL_SAVEs_FLDcnt;                     // �������̺� �����ʵ� ����
//�̢̢̢̢̢̢̢̢̢�

extern int Export_SELcnt;
extern int Export_ALLcnt;
// ���������������������������������������.
//����������������������������������������
// ���������������������������������������.
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
    // ���� ������ - ���Ϸε� ���̾�α� ����
//    pEXCEL_import->uDLG_XLS_import->Execute(NULL);

//PGM->uEXCEL->XLSExport(fSTR, "�˻����");

//PGM->uEXCEL->XLSImport(fSTR, "������");
}
//---------------------------------------------------------------------------
void __fastcall TpEXCEL_import::AdvGlowButton2Click(TObject *Sender)
{
    UnicodeString dSTR, fSTR;

    int n;

    // ���� ������ - ����üũ
    dSTR = xSYS.runDiR;
    dSTR += "/iN";
    PGM->uLoadFiLE->InitialDir = dSTR;

    fSTR = pEXCEL_import->uEXCEL_import_File->Text;

    if(fSTR=="")
    {
        okMSG("���� �����ư���� ���������� �ҷ�������");
    }
    else
    {

pEXCEL_import->uEXCEL->XLSImport(fSTR, "������");

n = 777;

    }
}
//---------------------------------------------------------------------------
