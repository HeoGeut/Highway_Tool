#pragma link "AdvGrid"
#pragma link "AdvGridWorkbook"
#pragma link "AdvObj"
#pragma link "AdvUtil"
#pragma link "BaseGrid"
#pragma link "tmsAdvGridExcel"
#include <vcl.h>
#pragma hdrstop

#include "./RAD/Cru_HEADER.h"
// ���������������������������������������.
//����������������������������������������
// ���������������������������������������.
#pragma package(smart_init)
#pragma link "AdvGlowButton"
#pragma resource "*.dfm"
//==============================================================================
TpEXCEL_export *pEXCEL_export;
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
__fastcall TpEXCEL_export::TpEXCEL_export(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TpEXCEL_export::uBTN_XLS_export_SaveClick(TObject *Sender)
{
    int n,p,k;
    int x,y,Jx,Jy;
    int chk,cnt,COLcnt,ROWcnt;
    int zSEL;

    UnicodeString dSTR, fSTR;
    //                                                                         .
    // ���� �ͽ����� - �������� ���̾�α� ����
    pEXCEL_export->uDLG_XLS_export->Execute(NULL);

    COLcnt = PGM->uDB_main->ColCount;


        switch(pEXCEL_export->uOPT_XLS_export_Type->ItemIndex)
        {
        // ���õ� �Ǽ����
        case 000: zSEL=0x1; ROWcnt = Export_SELcnt; break;
        // �˻��� ��ü�Ǽ����
        case 001: zSEL=0x0; ROWcnt = Export_ALLcnt; break;
        }


// ���� �������̺� ����״�� �����Ѵ�
PGM->uEXCEL_wb->Grid->ColCount = COLcnt;
PGM->uEXCEL_wb->Grid->RowCount = ROWcnt+2;


    // �� ����ʵ� ����
    // �ʵ��̸� / �ʵ������� ����
    for(x=1;x<=COLcnt-1;x++)
    {
        PGM->uEXCEL_wb->Grid->Cells[x-1][000] = Main_TBL_NMEs[x+1];
        PGM->uEXCEL_wb->Grid->Cells[x-1][001] = Main_TBL_FLDs[x+1];
        PGM->uEXCEL_wb->Grid->ColWidths[x-1]  = Main_TBL_CLWs[x+1];
    }

    // �� ����Ÿ ����
    cnt = Export_ALLcnt;

    y = 000;
    for(n=1;n<=cnt;n++)
    {
        chk = PGM->uDB_main->IsChecked(0, n);
        if(zSEL==0x0 || (zSEL==0x1 && chk))
        {
            ++y;

            x = 000;
            for(p=1;p<=COLcnt;p++)
            {
                if(1<p)
                {
                    ++x;
                    PGM->uEXCEL_wb->Grid->Cells[x-1][y+1] = PGM->uDB_main->Cells[p-1][n];
                }
            }
        }
    }
    //                                                                         .
    // �� ������������
    dSTR = xSYS.runDiR;
    dSTR += "/OUT";
    PGM->uSaveFiLE->InitialDir = dSTR;

    fSTR = pEXCEL_export->uDLG_XLS_export->FileName;

    pEXCEL_export->uEXCEL->XLSExport(fSTR, "�˻����");
    //                                                                         .
    pEXCEL_export->Close();
}
//---------------------------------------------------------------------------
void __fastcall TpEXCEL_export::uBTN_XLS_export_CloseClick(TObject *Sender)
{
    pEXCEL_export->Close();
}
//---------------------------------------------------------------------------
