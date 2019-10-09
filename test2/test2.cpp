#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

typedef void (*CALLBACK)(int,int);

static void process_byte(string sFilePathIn,string sFilePathOut,int line,CALLBACK cb)
{
	char * pData;
	ifstream fin(sFilePathIn,ios::binary|ios::in|ios::ate);
	cout<<sFilePathOut<<endl;
	ofstream fout(sFilePathOut,ios::binary|ios::out);
    if(!fout){cout<<"open failed"<<endl;return;}
	int nFileLength =fin.tellg();
	fin.seekg(0);
	pData = new  char [nFileLength];
	memset(pData,0,nFileLength*sizeof( char));
	fin.read(pData,nFileLength);
	
	int nCount =0;
	printf("nFileLength = %d\n",nFileLength);

	while(nCount < nFileLength)
	{
		ostringstream stream;
		unsigned char tempData ;
		string baseStr ="0x";
		string result;
		tempData =pData[nCount];
			
		stream<<hex<<(int)tempData;
		result =stream.str();

		if(tempData<=15)
			result.insert(0,"0");

		baseStr.append(result);
		baseStr.append(",");
		fout.write(baseStr.c_str(),baseStr.size());

		stream.clear();
		nCount++;

		if(nCount%16==0)
			fout<<"\r\n";
        if(nCount %1024 == 0)
            cb(nCount*100/nFileLength,line);
	}
    cb(nCount*100/nFileLength,line);

    delete pData;
	fin.close();
	fout.close();
}

static void process_short(string sFilePathIn,string sFilePathOut)
{
	char * pData;
	ifstream fin(sFilePathIn,ios::binary|ios::in|ios::ate);
	ofstream fout(sFilePathOut,ios::binary|ios::out);

	int nFileLength =fin.tellg()/sizeof(char);
	fin.seekg(0);
	pData = new  char [nFileLength];
	memset(pData,0,nFileLength*sizeof( char));
	fin.read(pData,nFileLength);
	
	int nCount =0;
	
	short * p =(short *)pData;

	const int nMinShortVal = 10000;
	const int nMaxShortVal = 20000;

	while(nCount < nFileLength)
	{
		//ostringstream stream;
		short tempData ;
		string baseStr ="0x";
		string result;
		tempData =*p;
		//stream<<hex<<(short)tempData;
#if 0	
		result =stream.str();
		if(result.size()<4)
			result.insert(0,4-result.size(),'0');
		baseStr.append(result);
		baseStr.append(",");
		fout.write(baseStr.c_str(),baseStr.size());
		stream.clear();
		nCount+=sizeof(short);
		if(nCount%(16*sizeof(short))==0)
			fout<<"\r\n";
		p++
#else
		tempData = tempData<nMinShortVal?nMinShortVal:tempData;
		tempData = tempData>nMaxShortVal?nMaxShortVal:tempData;
		
		
		fout.write((const char *)&tempData,sizeof(short));

		p++;
		nCount += sizeof(short);
#endif		
	}
	fin.close();
	fout.close();
}


void process(string strFileName,int line,CALLBACK cb)
{
#if 1    
    char strFileOut[128];
    int nArgInputLen = strlen(strFileName.c_str());
    memcpy(strFileOut,strFileName.c_str(),nArgInputLen);
    strFileOut[nArgInputLen]='\0';
	strcat(strFileOut,".txt");
    process_byte(strFileName,strFileOut,line,cb);
#endif	
}


