//*****************************************************//
//                                                     //
//      ALTiKToK                                       //
//                                                     //
//      Copyright (C) 2020 Aloe Luigi                  //
//                                                     //
//*****************************************************//

//---------------------------------------------------------------------------

#include <vcl.h>
#include <System.SysUtils.hpp>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
 String __fastcall TForm1::sEstraiDati( const String s, const String ultimo, const String primo )
{
  String result;
  int pultimo=0, pprimo=0, psuccessivo=0;
  pprimo=s.Pos(primo);
  pultimo=s.Pos(ultimo);
  while ((pultimo>0) && (pprimo>0))
  {
    if (pprimo>pultimo)
	  pultimo=PosEx(ultimo,s,pultimo+ultimo.Length());
    else
    {
	  psuccessivo=PosEx(primo,s,pprimo+primo.Length());
      if ((psuccessivo==0) || (psuccessivo>pultimo))
      {
        result=Trim(s.SubString(pprimo,pultimo-pprimo+ultimo.Length()));
        return result;
      }
      else
        pprimo = psuccessivo;
    }
  }
  result = "";
  return result;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::NetHTTPClient2ReceiveData(TObject * const Sender, __int64 AContentLength,
		  __int64 AReadCount, bool &AAbort)
{
ProgressBar1->Max=AContentLength;
ProgressBar1->Position=AReadCount;
Application->ProcessMessages();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
  String s, urlc, nomefile, sitoweb;
  TMemoryStream * tm;
  TBase64Encoding * cod;
  cod=new TBase64Encoding();
  sitoweb = cod->Decode(sito);
  TReplaceFlags rf = TReplaceFlags()<<rfReplaceAll;
  nomefile = StringReplace(Edit1->Text, "https://www.tiktok.com/@", "",rf);
  nomefile = nomefile.SubString(1, nomefile.Pos( "/" ) - 1 );
  urlc = StringReplace( Edit1->Text, "https://www.tiktok.com/@", "", rf);
  urlc = StringReplace( urlc, "/video", "", rf);
  urlc = sitoweb + urlc;
  Memo1->Lines->Text=(NetHTTPClient1->Get(urlc)->ContentAsString());
  ProgressBar1->Position = 0;
  s = (sEstraiDati(Memo1->Text, "\" type=\"video/mp4\"", "<source src=\"" ) );
  s = StringReplace( s, "<source src=\"", "", rf);
  s = StringReplace( s, "\" type=\"video/mp4\"", "", rf);
  if (s=="")
  {
	ShowMessage( "Video non disponibile per il download" );
	return;
  }
  else
  {
	Memo1->Lines->Clear();
	Memo1->Lines->Add(s);
	tm=new TMemoryStream();
	try
	{
	  NetHTTPClient2->Get(Memo1->Text,tm);
	  tm->Position = 0;
	  tm->SaveToFile(nomefile+".mp4");
	}
	__finally
	{
	  tm->DisposeOf();
	  Edit1->Clear();
	  Label1->Caption = "Video scaricato con successo!!!";
	}
  }
}
//---------------------------------------------------------------------------
