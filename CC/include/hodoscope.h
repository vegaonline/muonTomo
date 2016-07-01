/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   muonTomo.h
 * Author: vega
 *
 * Created on March 16, 2016, 12:10 AM
 */

#ifndef HODOSCOPE_H
#define HODOSCOPE_H

#include "sensor.h"
#include "muon.h"

class Hodoscope {
  public:
    int numScintUP;
    int numScintDN;
    int numDetUP;
    int numDetDN;
    int TOTDET = numDetUP + numDetDN;
    int TOTSCINT = numScintUP + numScintDN;
    int scintEleNum;
    int detEleNumX;
    int detEleNumY;

    double topbotDetGap;
    double det2detGap;

    double scintSide1;
    double scintSide2;
    double scintSide3;
    double scintSide4;
    double scintEleLen;
    double scintEleWid;
    double scintEleHt;

    double detSide1;
    double detSide2;
    double detSide3;
    double detSide4;

    std::vector<scintillator> ScintillatorArray;
    std::vector<RPCdet> detectorArray;
    trigger Trigger;

    void genLeaves(TTree* myTree,
                   int numScintillator,
                   int NumDetectors,
                   int startModuleNum,
                   int offTDC,
                   int detChannelStart);

    Channel* GetEntry(TTree* myTree, int i, int j, int event);
    int checkDataCount(int totEventNum, int NumDetectors, int startModuleNum, int offTDC, int detChannelStart);
    int checkScintCount(int totEventNum, int numScintillator);
    void assignXYZ(int totEventNum,
                   int NumDetectors,
                   int startModuleNum,
                   int offTDC,
                   int detChannelStart,
                   // std::vector<std::vector<std::vector<std::vector<double>>>>& dataMatrix);
                   std::vector<std::vector<double>>& dataMatrix);
    void get_tracks(std::vector<std::vector<double>>& dataMatrix, int NumDetectors, muonGroup& muons);
};

// *********************** Get data Entry from branch ******************
Channel* Hodoscope::GetEntry(TTree* myTree, int i, int j, int event)
{
    Channel* vpx = 0;
    TBranch* bvpx = 0;
    myTree->SetBranchAddress(detectorArray[i].stripLine[j].channelName.c_str(), &vpx, &bvpx);
    Long64_t tentry = myTree->LoadTree(event);
    bvpx->GetEntry(tentry);
    myTree->ResetBranchAddresses();
    return vpx;
}

//************************* Check Scintill **********************
int Hodoscope::checkScintCount(int totEventNum, int numScintillator)
{
    int countPlus = 0;

    for(int evt = 0; evt < totEventNum; evt++) {
        for(int i = 0; i < (numScintillator - 1); i++) {
            double mean = 0.0;
            for(int j1 = (i * scintEleNum); j1 < (i * scintEleNum + scintEleNum); j1++) {
                int j = j1 - i * scintEleNum;
                if(ScintillatorArray[i].scintill[j].sensorVal->size()) {
                    mean += ScintillatorArray[i].scintill[j].sensorVal->at(0);
                    countPlus++;
                }
            }
        }
    }
    return countPlus;
}

//********************** Assign Muon to each point and find tracks ***********************************************
void Hodoscope::get_tracks(std::vector<std::vector<double>>& dataMatrix, int NumDetectors, muonGroup& muons)
{
    int count = 0;
    std::vector<std::vector<double>> pointSet(NumDetectors, std::vector<double>());
    for(std::vector<std::vector<double>>::iterator it1 = dataMatrix.begin(); it1 != dataMatrix.end(); ++it1) {
        int event = 0, det = 0, chan = 0, time = 0;
        double xx = 0.0, yy = 0.0, zz = 0.0;
        std::vector<double>::iterator start = it1->begin();
        for(std::vector<double>::iterator it2 = it1->begin(); it2 != it1->end(); ++it2) {
            int dist = (int)std::distance(start, it2);
            switch(dist) {
            case 0:
                event = *it2;
            case 1:
                det = *it2;
            case 2:
                chan = *it2;
            case 3:
                xx = *it2;
            case 4:
                yy = *it2;
            case 5:
                zz = *it2;
            case 6:
                time = *it2;
            }
        }
        // muons[count].eventID = std::to_string(event) + "." + std::to_string(det) + "." + std::to_string(chan);
        // muons[count].serialNum = count;
        ++count;
    }
}

//******************** Assign X, Y, Z, Theta, Phi, T for detectors ************************
void Hodoscope::assignXYZ(int totEventNum,
                          int NumDetectors,
                          int startModuleNum,
                          int offTDC,
                          int detChannelStart,
                          std::vector<std::vector<double>>& dataMatrix)
{
    // event module channel x y z time, row = totEventNum * NumDetectors * delEleNumX, col = 7
    unsigned int cnt = 0;
    for(int evt = 0; evt < totEventNum; evt++) {
        for(int i1 = 0; i1 < NumDetectors; i1++) {
            int idet = startModuleNum + offTDC + i1;
            for(int j = detChannelStart; j < (detChannelStart + detEleNumX); j++) {
                if(detectorArray[idet].stripLine[j].sensorVal->size()) {
                    dataMatrix.push_back(std::vector<double>());
                    dataMatrix[cnt].push_back(evt);
                    dataMatrix[cnt].push_back(idet);
                    dataMatrix[cnt].push_back(j);
                    double xx = (j - detChannelStart) * detectorArray[idet].stripLine[j].length / (double)detEleNumX;
                    dataMatrix[cnt].push_back(xx); // X
                    xx = 0.0;
                    dataMatrix[cnt].push_back(xx); // Y
                    xx = (i1 < numDetUP) ? i1 * det2detGap : topbotDetGap + (i1 - 1) * det2detGap;
                    dataMatrix[cnt].push_back(xx); // Z
                    int time = detectorArray[idet].stripLine[j].sensorVal->at(0);
                    dataMatrix[cnt].push_back((double)time);
                    cnt++;
                }
            }
        }
    }
}

//************************* Check Data **********************
int Hodoscope::checkDataCount(int totEventNum, int NumDetectors, int startModuleNum, int offTDC, int detChannelStart)
{
    int countPlus = 0;

    for(int evt = 0; evt < totEventNum; evt++) {
        for(int i1 = 0; i1 < NumDetectors; i1++) {
            int idet = startModuleNum + offTDC + i1;
            int countChPlus = 0;
            double mean = 0.0;
            for(int j = detChannelStart; j < (detChannelStart + detEleNumX); j++) {
                if(detectorArray[idet].stripLine[j].sensorVal->size()) {
                    // std::cout << "Event " << evt << " Det # " << idet << "  Chan # " << j<< " Val = " <<
                    // detectorArray[idet].stripLine[j].sensorVal->at(0) << std::endl;
                    mean += detectorArray[idet].stripLine[j].sensorVal->at(0);
                    countPlus++;
                    countChPlus++;
                }
            }
            // std::cout << "Mean for Detector " << idet << "   " << mean / countChPlus << std::endl;
        }
    }
    return countPlus;
}

// **********************************   Generate leaves ********************8
void Hodoscope::genLeaves(TTree* myTree,
                          int numScintillator,
                          int NumDetectors,
                          int startModuleNum,
                          int offTDC,
                          int detChannelStart)
{

    // bool isScint = objectName.find("Scintillator") != std::string::npos;
    // bool isDetector = objectName.find("Detector") != std::string::npos;

    // Trigger
    for(Int_t evt = 0; evt < myTree->GetEntries(); evt++) {
        TBranch* myBranch = 0;
        myTree->SetBranchAddress(Trigger.trigger[0].channelName.c_str(), &Trigger.trigger[0].sensorVal, &myBranch);
        Long64_t tentry = myTree->LoadTree(evt);
        myBranch->GetEntry(tentry);
        // Raman Sehgal, NPD, BARC helped me to get this loop working
        // He told me use of SBA idea of LoadTree and GetEntry as I could
        // not make it working without his advice.
    }
    std::cout << " Trigger data Loaded.... " << std::endl;

    // Scintillator
    for(Int_t evt = 0; evt < myTree->GetEntries(); evt++) {
        for(int i = 0; i < (numScintillator - 1); i++) {
            for(int j1 = (i * scintEleNum); j1 < (i * scintEleNum + scintEleNum); j1++) {
                int j = j1 - i * scintEleNum;
                TBranch* myBranch = 0;
                myTree->SetBranchAddress(ScintillatorArray[i].scintill[j].channelName.c_str(),
                                         &ScintillatorArray[i].scintill[j].sensorVal, &myBranch);
                Long64_t tentry = myTree->LoadTree(evt);
                myBranch->GetEntry(tentry);
            }
        }
    }
    std::cout << " Scintilation data loaded....." << std::endl;

    // Detector
    for(Int_t evt = 0; evt < myTree->GetEntries(); evt++) {
        for(int i = 0; i < NumDetectors; i++) {
            int idet = startModuleNum + offTDC + i;
            for(int j = detChannelStart; j < (detChannelStart + detEleNumX); j++) {
                TBranch* myBranch = 0;
                myTree->SetBranchAddress(detectorArray[idet].stripLine[j].channelName.c_str(),
                                         &detectorArray[idet].stripLine[j].sensorVal, &myBranch);
                Long64_t tentry = myTree->LoadTree(evt);
                myBranch->GetEntry(tentry);
            }
        }
    }
    std::cout << " Detector data loaded....." << std::endl;
    myTree->ResetBranchAddresses();
}

// ********************* make configuration **********************88888
void doConfig(int ch,
              TString& configFileName,
              std::string& geoShape,
              std::string& enUnit,
              std::string& lenUnit,
              double& side1,
              double& side2,
              double& side3,
              double& side4,
              int& segNumPerDet,
              double& delSeg,
              int& stripsNumPerSeg,
              double& delStrips,
              int& numDETabove,
              int& numDETbelow,
              double& delDETht0,
              double& delDETht1,
              double& objLen,
              double& objWid,
              double& objHt,
              double& delObjDET,
              int& numTDC,
              int& numActiveTDC)
{
    std::string line;
    std::string key = "DET.png";
    std::ifstream conFile(configFileName, std::ios::in);
    int maxtot = 22, tot = maxtot;

    std::size_t found;
    std::string::size_type sz;

    if(conFile.is_open()) {
        while(std::getline(conFile, line)) {
            switch(tot) {
            case 22:
                found = line.rfind(key);
                if(found != std::string::npos)
                    line.replace(found, key.length(), "");
                strcpVega(geoShape, line);
                tot--;
                break;
            case 21:
                strcpVega(lenUnit, line);
                tot--;
                break;
            case 20:
                strcpVega(enUnit, line);
                tot--;
                break;
            case 19:
                side1 = std::stod(line, &sz);
                tot--;
                break;
            case 18:
                side2 = std::stod(line, &sz);
                tot--;
                break;
            case 17:
                side3 = std::stod(line, &sz);
                tot--;
                break;
            case 16:
                side4 = std::stod(line, &sz);
                tot--;
                break;
            case 15:
                segNumPerDet = std::stoi(line, &sz);
                tot--;
                break;
            case 14:
                delSeg = std::stod(line, &sz);
                tot--;
                break;
            case 13:
                stripsNumPerSeg = std::stoi(line, &sz);
                if(ch)
                    std::cout << " stripsNum/seg = " << stripsNumPerSeg << std::endl;
                tot--;
                break;
            case 12:
                delStrips = std::stod(line, &sz);
                tot--;
                break;
            case 11:
                numDETabove = std::stoi(line, &sz);
                tot--;
                break;
            case 10:
                numDETbelow = std::stoi(line, &sz);
                tot--;
                break;
            case 9:
                objLen = std::stod(line, &sz);
                tot--;
                break;
            case 8:
                objWid = std::stod(line, &sz);
                tot--;
                break;
            case 7:
                objHt = std::stod(line, &sz);
                tot--;
                break;
            case 6:
                delObjDET = std::stod(line, &sz);
                tot--;
                break;
            case 5:
                delDETht0 = std::stod(line, &sz);
                tot--;
                break;
            case 4:
                delDETht1 = std::stod(line, &sz);
                tot--;
                break;
            case 3:
                numTDC = std::stod(line, &sz);
                tot--;
                break;
            case 2:
                numActiveTDC = std::stod(line, &sz);
                tot--;
                break;
            }
        }
        conFile.close();
    }
    else {
        std::cout << "Unable to open file: " << configFileName << std::endl;
    }
}

#endif /* HODOSCOPE_H */
