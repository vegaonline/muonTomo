/*
 * File:   main.cpp
 * Author: vega
 *
 * Created on March 16, 2016, 12:06 AM
 */

#include "hodoscope.h"

// using namespace std;

void makeHodoscope(TString& configFileName,
                   TTree* myTree,
                   Hodoscope& muonTomoScope,
                   int& NumDetectors,
                   int& NumChannels,
                   std::string geoShape,
                   std::string enUnit,
                   std::string lenUnit,
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
                   int& numActiveTDC,
                   int& numScintUP,
                   int& numScintDN,
                   int& scintSensorNum,
                   int& numScintillator,
                   int& totChannel,
                   int& detChannelStart,
                   double& stripLen,
                   double& stripWid,
                   double& stripHt,
                   int& startModuleNum,
                   int& offTDC)
{

    doConfig(configFileName, geoShape, enUnit, lenUnit, side1, side2, side3, side4, segNumPerDet, delSeg,
             stripsNumPerSeg, delStrips, numDETabove, numDETbelow, delDETht0, delDETht1, objLen, objWid, objHt,
             delObjDET, numTDC, numActiveTDC);

    NumDetectors = numDETabove + numDETbelow;
    NumChannels = segNumPerDet * stripsNumPerSeg;

    muonTomoScope.scintSide1 = side1;
    muonTomoScope.scintSide2 = side2;
    muonTomoScope.scintSide3 = side1;
    muonTomoScope.scintSide4 = side2;

    muonTomoScope.detSide1 = side1;
    muonTomoScope.detSide2 = side2;
    muonTomoScope.detSide3 = side3;
    muonTomoScope.detSide4 = side4;

    muonTomoScope.numScintUP = numScintUP;
    muonTomoScope.numScintDN = numScintDN;
    muonTomoScope.numDetUP = numDETabove;
    muonTomoScope.numDetDN = numDETbelow;
    muonTomoScope.scintEleNum = scintSensorNum;
    muonTomoScope.detEleNumX = segNumPerDet * stripsNumPerSeg;
    muonTomoScope.detEleNumY = 0;
    muonTomoScope.det2detGap = delDETht1;
    muonTomoScope.topbotDetGap = delDETht0;
    muonTomoScope.ScintillatorArray.resize(numScintillator);
    muonTomoScope.detectorArray.resize(numTDC);

    // Trigger
    std::string sensorName = "";
    sensorName = "trigger";
    muonTomoScope.Trigger.setName(sensorName);
    muonTomoScope.Trigger.numSensor = 1;
    muonTomoScope.Trigger.makeTrigger();
    sensorName = modT + "2" + lech + "31";
    muonTomoScope.Trigger.trigger[0].setName(sensorName);

    // Scintillator
    sensorName = "";
    for(int i = 0; i < numScintillator; i++) {
        muonTomoScope.ScintillatorArray[i].numSensor = muonTomoScope.scintEleNum;
        muonTomoScope.ScintillatorArray[i].makeScintill();
        for(int j1 = (i * muonTomoScope.scintEleNum); j1 < (i * muonTomoScope.scintEleNum + muonTomoScope.scintEleNum);
            j1++) {
            int j = j1 - i * muonTomoScope.scintEleNum;
            sensorName = modT + "2" + lech + std::to_string(j1);
            muonTomoScope.ScintillatorArray[i].scintill[j].setName(sensorName);
        }
        sensorName = "scint" + std::to_string(i);
        muonTomoScope.ScintillatorArray[i].setName(sensorName);
        muonTomoScope.ScintillatorArray[i].tag = i;
        muonTomoScope.ScintillatorArray[i].numSensor = scintSensorNum;
        muonTomoScope.ScintillatorArray[i].scintUP = (i < numScintUP) ? 1 : 0;
        muonTomoScope.ScintillatorArray[i].scintDN = (i > (numScintUP - 1)) ? 1 : 0;
        muonTomoScope.ScintillatorArray[i].sensorLen = muonTomoScope.scintSide1;
        muonTomoScope.ScintillatorArray[i].sensorWid =
            std::min(muonTomoScope.scintSide2, muonTomoScope.scintSide4) / scintSensorNum;
        muonTomoScope.ScintillatorArray[i].sensorHt = 0.001;
        muonTomoScope.ScintillatorArray[i].makeScintill();
        for(int j = 0; j < scintSensorNum; j++) {
            muonTomoScope.ScintillatorArray[i].scintill[j].setParam(
                lenUnit, muonTomoScope.ScintillatorArray[i].sensorLen, muonTomoScope.ScintillatorArray[i].sensorWid,
                muonTomoScope.ScintillatorArray[i].sensorHt);
        }
    }

    // Detector
    sensorName = "";
    bool exists = geoShape.find("trapez") != std::string::npos;
    totChannel = detChannelStart + muonTomoScope.detEleNumX;
    stripLen = (exists == 1) ? ((side1 - ((segNumPerDet - 1) * delSeg)) / segNumPerDet) : side1;
    stripWid = (exists == 1) ?
                   ((std::min(muonTomoScope.detSide2, muonTomoScope.detSide4) - stripsNumPerSeg * delStrips) /
                    stripsNumPerSeg) :
                   (side2 - stripsNumPerSeg * delStrips) / stripsNumPerSeg;
    stripHt = 0.001;
    for(int i = 0; i < NumDetectors; i++) {
        int idet = startModuleNum + offTDC + i;
        muonTomoScope.detectorArray[idet].numStrips = totChannel + 1;
        muonTomoScope.detectorArray[idet].makeStripLine();

        for(int j = detChannelStart; j < (detChannelStart + 1 + muonTomoScope.detEleNumX); j++) {
            sensorName = modT + std::to_string(idet) + lech + std::to_string(j);
            muonTomoScope.detectorArray[idet].stripLine[j].setName(sensorName);
            muonTomoScope.detectorArray[idet].stripLine[j].setParam(lenUnit, stripLen, stripWid, stripHt);
        }
    }
}

/*
 * This is main code for processing MuonTomography ROOT Data
 * obtained from RPC
 */

int main(int argc, char** argv)
{

    TTree* myTree;
    TString treeName = "";
    TString fileName = "";
    TString configFileName = "";
    TString dataFileName = "";

    int NumDetectors = 0;
    int NumChannels = 0;
    std::string geoShape = "";
    std::string enUnit = "";
    std::string lenUnit = "";
    double side1 = 0.0, side2 = 0.0, side3 = 0.0, side4 = 0.0;
    int segNumPerDet = 0;
    double delSeg = 0.0;
    int stripsNumPerSeg = 0;
    double delStrips = 0.0;
    double delDETht0 = 0.0;
    double delDETht1 = 0.0;
    double objLen = 0.0, objWid = 0.0, objHt = 0.0;
    double delObjDET = 0.0;
    int numDETabove = 0;
    int numDETbelow = 0;
    int startModuleNum = 2;

    int numTDC = 0;
    int numActiveTDC = 0;
    int numInactiveTDC = 0;
    int DETstartNum = 0;
    int offTDC = 1; // this is offset. starts from 0 and active starts from 3

    int numScintUP = 1;
    int numScintDN = 1;
    int numScintillator = numScintUP + numScintDN;
    int scintSensorNum = 8;
    int detChannelStart = 32; // channel number for data starts from 32 while 31 is trigger
    int totChannel = 0;
    int totEventNum = 0;

    double stripLen = 0.0;
    double stripWid = 0.0;
    double stripHt = 0.0;

    // std::vector<std::vector<std::vector<std::vector<double>>>> DataMatrix;
    std::vector<std::vector<double>> DataMatrix;

    //******************** load ROOT libraries ***************
    setEnv();

    //************************* check whether editing a file is required **************
    system("clear");
    std::cout << "\n";
    std::cout << " 1. Edit data file: \n";
    std::cout << " 2. Run Simulation with default data\n\n";
    std::cout << " Enter Choice: ";
    int choice = 0;
    while(choice < 1 || choice > 2) {
        std::cin >> choice;
    }

    if(choice == 1) {
        std::cout << " PATH: ../../data/" << std::endl;
        system("ls -l ../../data");
        dataFileName = "";
        while(!dataFileName.Length()) {
            std::cout << " Enter datafile name to be edited:-> ";
            std::cin >> dataFileName;
        }
    }

    //****************** Set the config file and data file Names **********
    fixfilename(argc, argv, configFileName, dataFileName, choice);

    //******************* Read data Tree; ******************
    myTree = getData(dataFileName, choice);
    treeName = myTree->GetName();
    totEventNum = myTree->GetEntries();

    //****************** Set configuration **************************
    std::cout << " Construction of the Hodoscope begins........" << std::endl;
    Hodoscope muonTomoScope;
    makeHodoscope(configFileName, myTree, muonTomoScope, NumDetectors, NumChannels, geoShape, enUnit, lenUnit, side1,
                  side2, side3, side4, segNumPerDet, delSeg, stripsNumPerSeg, delStrips, numDETabove, numDETbelow,
                  delDETht0, delDETht1, objLen, objWid, objHt, delObjDET, numTDC, numActiveTDC, numScintUP, numScintDN,
                  scintSensorNum, numScintillator, totChannel, detChannelStart, stripLen, stripWid, stripHt,
                  startModuleNum, offTDC);

    std::cout << " Number of detectors = " << NumDetectors << " each having number of channels " << totChannel
              << " where " << NumChannels << " are active from  Channel #" << detChannelStart << "." << std::endl;

    //******************** Set Branches with variables ************
    muonTomoScope.genLeaves(myTree, numScintillator, NumDetectors, startModuleNum, offTDC, detChannelStart);

    std::cout << " Total number of events : " << totEventNum << std::endl;
    std::cout << " Total valid data "
              << muonTomoScope.checkDataCount(totEventNum, NumDetectors, startModuleNum, offTDC, detChannelStart)
              << " \n Total valid Scintillator data " << muonTomoScope.checkScintCount(totEventNum, numScintillator)
              << std::endl;

    //********************* Assign X, Y, Z, Theta, Phi, T  for each data point ***********************
    muonTomoScope.assignXYZ(totEventNum, NumDetectors, startModuleNum, offTDC, detChannelStart, DataMatrix);
    /*
        for(std::vector<std::vector<double>>::iterator it1 = DataMatrix.begin(); it1 != DataMatrix.end(); ++it1) {
            for(std::vector<double>::iterator it2 = it1->begin(); it2 != it1->end(); ++it2) {
                std::cout << *it2 << "  ";
            }
            std::cout << std::endl;
        }
    */

    //********************** Assign Muon to each point and find tracks ***********************************************
    muonGroup muons;
    muons.resize(DataMatrix.size());
    muonTomoScope.get_tracks(DataMatrix, NumDetectors, muons);
}
