/*
 * File:   main.cpp
 * Author: vega
 *
 * Created on March 16, 2016, 12:06 AM
 */

#include "hodoscope.h"

void makeHodoscope(int ch,
                   TString& configFileName,
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

    doConfig(ch, configFileName, geoShape, enUnit, lenUnit, side1, side2, side3, side4, segNumPerDet, delSeg,
             stripsNumPerSeg, delStrips, numDETabove, numDETbelow, delDETht0, delDETht1, objLen, objWid, objHt,
             delObjDET, numTDC, numActiveTDC);

    NumDetectors = numDETabove + numDETbelow;
    NumChannels = segNumPerDet * stripsNumPerSeg;

    std::cout << "Number of detectors = " << NumDetectors << " Seg number / det " << segNumPerDet
              << "  Number of channels = " << NumChannels << std::endl;

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
 * Generate new data for the extended detectors to simulate the algorithm
 * when real life data is not ready. The data generated has mean value as
 * same as that of real data of reduced detector set obtained from NPD
 * LAB.
 */
void genNewData(int choice,
                Hodoscope& mt,
                Hodoscope& nt,
                int totData,
                TString dataFileName,

                int& NumDetN,
                int& NumChanN,
                std::string geo,
                std::string enU,
                std::string lenU,
                double& s1,
                double& s2,
                double& s3,
                double& s4,
                int& segN,
                double& delSegN,
                int& stripsN,
                double& delSN,
                int& detU,
                int& detD,
                double& delH0,
                double& delH1,
                double& oL,
                double& oW,
                double& oH,
                double& DobjDet,
                int& nTDC,
                int& nATDC,
                int nScintU,
                int nScintD,
                int scintSN,
                int scintNumN,
                int& totC,
                int detC0,
                double& stripL,
                double& stripW,
                double& stripH,
                int modu0,
                int TDCoff,
                double& scintMean,
                double& trigMean,
                double& sigMean,
                int& scintMax,
                int& trigMax,
                int& sigMax,
                int& scintMin,
                int& trigMin,
                int& sigMin)
{

    // TFile* file;

    TString NewConf = "../../data/NEWmuonSim6147.tom";
    TString fName_tmp = dataFileName;
    TString fileNameNew = fName_tmp.Replace(dataFileName.Length() - 5, 6, "_NEW.root");
    // file = new TFile(fileNameNew, "NEW");

    std::cout << " \n ---> Generating a new hodoscope for testing...." << std::endl;

    makeHodoscope(choice, NewConf, nt, NumDetN, NumChanN, geo, enU, lenU, s1, s2, s3, s4, segN, delSegN, stripsN, delSN,
                  detU, detD, delH0, delH1, oL, oW, oH, DobjDet, nTDC, nATDC, nScintU, nScintD, scintSN, scintNumN,
                  totC, detC0, stripL, stripW, stripH, modu0, TDCoff);

    std::cout << " Number of detectors = " << NumDetN << " each having number of channels " << NumChanN << " where "
              << NumChanN << " are active from  Channel #" << detC0 << "." << std::endl;
    std::cout << "  total number of scintillator = " << scintNumN
              << " total number of sensor in scintillator = " << scintSN << std::endl;

    std::cout << "....... Generating Numbers ..........." << std::endl;

    int numEnt = 0;
    int cnt = 0;
    scintMean = 0.0;
    trigMean = 0.0;
    sigMean = 0.0;
    scintMax = -9999999;
    trigMax = scintMax;
    sigMax = scintMax;
    scintMin = 99999999;
    trigMin = scintMin;
    sigMin = scintMin;

    // ********* determining Trigger Value mean ***********
    for(int ii = 0; ii < totData; ii++) {
        int mydata = mt.Trigger.trigger[0].sensorVal->at(0);
        std::cout << mydata << std::endl;
        trigMean += 1.0 * mydata;
        trigMin = std::min(trigMin, mydata);
        trigMax = std::max(trigMax, mydata);
        cnt++;
    }
    trigMean /= (cnt - 1);
    cnt = 0;

    // ********** determining scintillator data Mean **********
    for(int ii = 0; ii < totData; ii++) {
        for(int scintI = 0; scintI < (scintNumN - 1); scintI++) {
            for(int j1 = (scintI * scintSN); j1 < (scintI * scintSN + scintSN); j1++) {
                int j = j1 - scintI * scintSN;
                int mydata = 0;
                if(mt.ScintillatorArray[scintI].scintill[j].sensorVal->size()) {
                    mydata = mt.ScintillatorArray[scintI].scintill[j].sensorVal->at(0);
                    scintMean += 1.0 * mydata;
                    cnt++;
                    scintMax = std::max(scintMax, mydata);
                    scintMin = std::min(scintMin, mydata);
                }
            }
        }
    }
    scintMean /= (cnt - 1);

    // *********** determining detector data  Mean *********

    int totDET = (mt.numDetUP + mt.numDetDN);
    cnt = 0;
    for(int ii = 0; ii < totData; ii++) {
        for(int i1 = 0; i1 < totDET; i1++) {
            int idet = modu0 + TDCoff + i1;
            for(int j = detC0; j < (detC0 + mt.detEleNumX); j++) {
                if(mt.detectorArray[idet].stripLine[j].sensorVal->size()) {
                    int mydata = mt.detectorArray[idet].stripLine[j].sensorVal->at(0);
                    sigMean += 1.0 * mydata;
                    cnt++;
                    sigMax = std::max(sigMax, mydata);
                    sigMin = std::min(sigMin, mydata);
                }
            }
        }
    }
    sigMean /= (cnt - 1);
    std::cout << "Min trigger = " << trigMin << "  max Trigger = " << trigMax << " Mean Trigger = " << trigMean
              << "  Min Scint = " << scintMin << "  Max Scint = " << scintMax
              << "  Mean Scintilator data = " << scintMean << "  Max Sig = " << sigMax << "  Min Sig = " << sigMin
              << " Mean detector data = " << sigMean << std::endl;

    // ******** Now prepare the tree structure for the new file *********************
    // first kill old tomoscope.

    std::normal_distribution<> distTrig(trigMean, 0.1 * trigMean);
    std::normal_distribution<> distScint(scintMean, 0.1 * scintMean);
    std::normal_distribution<> distSig(sigMean, 0.2 * sigMean);
    /*
        scintMean = 0.0;
        trigMean = 0.0;
        sigMean = 0.0;

        // ****** for trigger *******
        int range = trigMax - trigMin;
        std::cout << " starting to create new tree.. " << std::endl;
        int mydata = 0;
        cnt = 0;
        // TBranch* myBranchTrig;
        for(int ii = 0; ii < totData; ii++) {
            mydata = 0;
            while(mydata < trigMin || mydata > trigMax) {
                mydata = distTrig(e2);
            }
            trigMean += 1.0 * mydata;
            cnt++;
            //std::cout << ii << "  " << mydata << std::endl;
            // myBranchTrig = newTree->Branch(newTomoScope.Trigger.trigger[0].channelName.c_str(), &mydata, "mydata/F");
            //  nt.Trigger.trigger[0].sensorVal->emplace_back(mydata);
            //std::cout << nt.Trigger.trigger[0].sensorVal->at(0) << std::endl;
        }
        trigMean /= (cnt - 1);
        std::cout << " Trigger data added in new file  Tree with mean = " << trigMean << std::endl;
        // myBranchTrig->SetFile(file);

        // ****** for scintillator *******
        // TBranch* myBranchScint;
        range = scintMax - scintMin;
        cnt = 0;
        for(int ii = 0; ii < totData; ii++) {
            for(int scI = 0; scI < (scintNumN - 1); scI++) {
                for(int j1 = (scI * scintSN); j1 < (scI * scintSN + scintSN); j1++) {
                    int j = j1 - scI * scintSN;
                    mydata = 0;
                    while(mydata < scintMin || mydata > scintMax) {
                        mydata = distScint(e2);
                    }
                    scintMean += mydata;
                    cnt++;
                    // std::cout << ii << "  " << scI << "  " << j << "   " << mydata << std::endl;
                    // myBranchScint =
                    //
       newTree->Branch(newTomoScope.ScintillatorArray[scI].scintill[j].channelName.c_str(),&mydata,"mydata/F");
                    nt.ScintillatorArray[scI].scintill[j].sensorVal->push_back(mydata);
                }
            }
        }
        scintMean /= (cnt - 1);
        std::cout << " Scintillation data added in new file Tree with mean = " << scintMean << std::endl;
        // myBranchScint->SetFile(file);
        // ********* for detector *******
        range = sigMax - sigMin;
        cnt = 0;
        // TBranch* myBranchSig;
        for(int ii = 0; ii < totData; ii++) {
            for(int i = 0; i < NumDetN; i++) {
                int idet = modu0 + TDCoff + i;
                for(int j = detC0; j < (detC0 + NumChanN); j++) {
                    mydata = 0;
                    while(mydata < sigMin || mydata > sigMax) {
                        mydata = distSig(e2);
                    }
                    sigMean += mydata;
                    cnt++;
                    // std::cout << ii << "   " << idet << "   " << j << "  " << mydata << std::endl;
                    // myBranchSig =
                    //
       newTree->Branch(newTomoScope.detectorArray[idet].stripLine[j].channelName.c_str(),&mydata,"mydata/F");
                    nt.detectorArray[idet].stripLine[j].sensorVal->push_back(mydata);
                }
            }
        }
        sigMean /= (cnt - 1);
        std::cout << " Detector data added in the new file Tree with mean = " << sigMean << std::endl;
        // myBranchSig->SetFile(file);
    */
    // exit(0);
}

void getStats(Hodoscope& mt,
              int totData,
              int& trigMax,
              int& trigMin,
              double& trigMean,
              int scintSN,
              int scintNumN,
              int& scintMin,
              int& scintMax,
              double& scintMean,
              int modu0,
              int TDCoff,
              int totDet,
              int detC0,
              int& sigMin,
              int& sigMax,
              double& sigMean)
{
    trigMin = 999999;
    scintMin = trigMin;
    sigMin = trigMin;
    trigMax = -trigMin;
    scintMax = trigMax;
    sigMax = trigMax;
    trigMean = 0.0;
    scintMean = 0.0;
    sigMean = 0.0;

    // Determine trigger stats
    int cnt = 0;
    for(int ii = 0; ii < totData; ii++) {
        int mydata = mt.Trigger.trigger[0].sensorVal->at(0);
        trigMean += 1.0 * mydata;
        trigMin = std::min(trigMin, mydata);
        trigMax = std::max(trigMax, mydata);
        cnt++;
    }
    trigMean /= (cnt - 1);
    cnt = 0;

    // Determine scintillator stats
    for(int ii = 0; ii < totData; ii++) {
        for(int scintI = 0; scintI < (scintNumN - 1); scintI++) {
            for(int j1 = (scintI * scintSN); j1 < (scintI * scintSN + scintSN); j1++) {
                int j = j1 - scintI * scintSN;
                int mydata = 0;
                if(mt.ScintillatorArray[scintI].scintill[j].sensorVal->size()) {
                    mydata = mt.ScintillatorArray[scintI].scintill[j].sensorVal->at(0);
                    scintMean += 1.0 * mydata;
                    scintMax = std::max(scintMax, mydata);
                    scintMin = std::min(scintMin, mydata);
                    cnt++;
                }
            }
        }
    }
    scintMean /= (cnt - 1);
    cnt = 0;

    // Determine Detector stats
    for(int ii = 0; ii < totData; ii++) {
        for(int i1 = 0; i1 < totDet; i1++) {
            int idet = modu0 + TDCoff + i1;
            for(int j = detC0; j < (detC0 + mt.detEleNumX); j++) {
                if(mt.detectorArray[idet].stripLine[j].sensorVal->size()) {
                    int mydata = mt.detectorArray[idet].stripLine[j].sensorVal->at(0);
                    sigMean += 1.0 * mydata;
                    sigMax = std::max(sigMax, mydata);
                    sigMin = std::min(sigMin, mydata);
                    cnt++;
                }
            }
        }
    }
    sigMean /= (cnt - 1);
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
    TString NewConf = "";
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

    double scintMean = 0.0, trigMean = 0.0, sigMean = 0.0;
    int scintMax, trigMax, sigMax, scintMin, trigMin, sigMin;

    // std::vector<std::vector<std::vector<std::vector<double>>>> DataMatrix;
    std::vector<std::vector<double>> DataMatrix;

    //******************** load ROOT libraries ***************
    setEnv(); // loading libRIO, libGEOM etc ROOT libraries

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
        /*
        std::cout << " PATH: ../../data/" << std::endl;
        system("ls -l ../../data");
        dataFileName = "";
        while(!dataFileName.Length()) {
            std::cout << " Enter datafile name to be edited:-> ";
            std::cin >> dataFileName;
        }
         */
    }

    //****************** Set the config file and data file Names **********
    fixfilename(argc, argv, configFileName, dataFileName, choice);
    if(configFileName = "") {
        configFileName = "../../data/muonSim6133.tom";
    }

    //******************* Read data Tree; ******************
    // myTree = getData(dataFileName, choice, );
    getData(dataFileName, myTree); // reading original root file
    treeName = myTree->GetName();
    totEventNum = myTree->GetEntries();

    //****************** Set configuration **************************
    std::cout << " Construction of the Hodoscope begins........" << std::endl;
    Hodoscope muonTomoScope;
    makeHodoscope(choice, configFileName, muonTomoScope, NumDetectors, NumChannels, geoShape, enUnit, lenUnit, side1,
                  side2, side3, side4, segNumPerDet, delSeg, stripsNumPerSeg, delStrips, numDETabove, numDETbelow,
                  delDETht0, delDETht1, objLen, objWid, objHt, delObjDET, numTDC, numActiveTDC, numScintUP, numScintDN,
                  scintSensorNum, numScintillator, totChannel, detChannelStart, stripLen, stripWid, stripHt,
                  startModuleNum, offTDC);

    std::cout << " Number of detectors = " << NumDetectors << " each having number of channels " << totChannel
              << " where " << NumChannels << " are active from  Channel #" << detChannelStart << "." << std::endl;
    std::cout << "  total number of scintillator = " << numScintillator
              << " total number of sensor in scintillator = " << scintSensorNum << std::endl;

    //******************** Set Branches with variables ************
    muonTomoScope.genLeaves(myTree, numScintillator, NumDetectors, startModuleNum, offTDC, detChannelStart);

    getStats(muonTomoScope, myTree->GetEntries(), trigMax, trigMin, trigMean, scintSensorNum, numScintillator, scintMin,
             scintMax, scintMean, startModuleNum, offTDC, numDETabove + numDETbelow, detChannelStart, sigMin, sigMax,
             sigMean);

    std::cout << " Total number of events : " << totEventNum << std::endl;
    std::cout << " Total valid data "
              << muonTomoScope.checkDataCount(totEventNum, NumDetectors, startModuleNum, offTDC, detChannelStart)
              << " \n Total valid Scintillator data " << muonTomoScope.checkScintCount(totEventNum, numScintillator)
              << std::endl;
    std::cout << "Signal Min = " << sigMin << "  signal Max = " << sigMax << "   signal Mean = " << sigMean
              << std::endl;

    // *********************** If ROOT file is edited do editing here ******************************
    if(choice == 1) {
        int NumDetN = 0;
        int NumChanN = 0;
        std::string geo = "";
        std::string enU = "";
        std::string lenU = "";
        double s1 = 0.0, s2 = 0.0, s3 = 0.0, s4 = 0.0, delSegN = 0.0, delSN = 0.0;
        double delH0 = 0.0, delH1 = 0.0, oL = 0.0, oW = 0.0, oH = 0.0, DobjDet = 0.0;
        int segN = 0, stripsN = 0, detU = 0, detD = 0, nTDC = 0, nATDC = 0;
        int nScintU = numScintUP, nScintD = numScintDN, scintSN = scintSensorNum, scintNumN = numScintillator, totC = 0;
        int detC0 = detChannelStart, modu0 = startModuleNum, TDCoff = offTDC;
        double stripL = 0.0, stripW = 0.0, stripH = 0.0;
        int totData = myTree->GetEntries();

        Hodoscope newTomoscope;
        if(choice == 1) {
            configFileName = "../../data/NEWmuonSim6147.tom";
        }

        doConfig(choice, configFileName, geo, enU, lenU, s1, s2, s3, s4, segN, delSegN, stripsN, delSN, detU, detD,
                 delH0, delH1, oL, oW, oH, DobjDet, nTDC, nATDC);

        NumDetN = detU + detD;
        NumChanN = segN * stripsN;

        // xx = (i1 < numDetUP) ? i1 * det2detGap : topbotDetGap + (i1 - 1) * det2detGap;

        muonTomoScope.assignXYZ(choice, totData, NumDetectors, NumDetN, NumChanN, modu0, TDCoff, detC0, sigMean, sigMax,
                                sigMin, delH1, delH0, detU, DataMatrix);
    }
    //********************* Assign #evt   #Ch   X   Y   Z    Time  for each data point ***********************
    else {
        muonTomoScope.assignXYZ(choice, totEventNum, NumDetectors, NumDetectors, NumChannels, startModuleNum, offTDC,
                                detChannelStart, sigMean, sigMax, sigMin, delDETht1, delDETht0, numDETabove,
                                DataMatrix);
    }

    for(std::vector<std::vector<double>>::iterator it1 = DataMatrix.begin(); it1 != DataMatrix.end(); ++it1) {
        for(std::vector<double>::iterator it2 = it1->begin(); it2 != it1->end(); ++it2) {
            std::cout << *it2 << "  ";
        }
        std::cout << std::endl;
    }

    //********************** Assign Muon to each point and find tracks
    //***********************************************
    muonGroup muons;
    muons.resize(DataMatrix.size());
    muonTomoScope.get_tracks(DataMatrix, NumDetectors, muons);
}
