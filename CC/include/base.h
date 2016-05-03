#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include <Riostream.h>
#include <TROOT.h>
#include <TFile.h>
#include <TObject.h>
#include <TMath.h>
#include <TSystem.h>
#include <TChain.h>
#include <TKey.h>
#include <TIterator.h>
#include <TMacro.h>
#include <TClass.h>
#include <TString.h>
#include <TGeoManager.h>
#include <TGeoNode.h>
#include <TGeoVolume.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TH2.h>
#include <TCanvas.h>
#include <TStyle.h>

#define x2(x) (x * x)
#define x3(x) (x2 * x)

class TFile;
class TGeoVolume;

class point3D {
  public:
    double x, y, z;
};

class line3D {
  public:
    point3D P1, P2;
    double len2 = x2(P2.x - P1.x) + x2(P2.y - P1.y) + x2(P2.z - P1.z);
};

TString blow = "b_";
TString modT = "Module";
TString lech = "_LE_CH";
TString hpc = "HITS_PER_CHANNEL";
TString noc = "_NUMBER_OF_CHANNEL";

typedef std::vector<unsigned int> Channel;
typedef std::vector<int> EventList;
typedef std::vector<Channel> Module;
typedef std::vector<Module> RPClist;
typedef std::vector<Channel> Scint;

void setEnv(void)
{
    gROOT->Reset();
    gSystem->Load("libRIO");
    gSystem->Load("libGeom");
    gSystem->Load("libHist");
    gSystem->Load("libGraf");
    gSystem->Load("libMathMore");
}

void strcpVega(std::string& s1, std::string s2)
{
    for(int i = 0; i < s2.size(); i++)
        s1.push_back(s2[i]);
}

TTree* getData(TString fileName)
{
    TFile* file;
    file = TFile::Open(fileName);
    TTree* fVolume;

    if(!file || file->IsZombie()) {
        std::cout << "Error: TFile :: Cannot open file " << fileName << std::endl;
    }
    else {
        std::cout << " The Code has opened " << fileName << " successfully....." << std::endl;
        TKey* rkey = (TKey*)file->GetListOfKeys()->First();
        fVolume = (TTree*)rkey->ReadObj();
        std::cout << "Root Data Tree " << fVolume->GetName()
                  << " loaded with total number of entries = " << fVolume->GetEntries() << std::endl;
    }
    return fVolume;
}

void fixfilename(int argc, char** argv, TString& configFileName, TString& dataFileName)
{
    if(argc) {
        if(argc < 3) {
            exit(0);
        }
        else {
            configFileName = argv[1];
            dataFileName = argv[2];
        }
    }
    else {
        exit(0);
    }
}
