#include "base.h"

class sensor {
  public:
    double length;
    double breadth;
    double height;
    int eventNo;
    int totEventNum;
    std::string lenUnit;
    std::string channelName;
    Channel* sensorVal = 0;
    EventList* eventNumber = 0;
    void setName(std::string scint)
    {
        strcpVega(this->channelName, scint);
    };
    void setParam(std::string lUni, double l, double w, double h)
    {
        this->length = l;
        this->breadth = w;
        this->height = h;
        strcpVega(this->lenUnit, lUni);
    }
};

typedef std::vector<sensor> SensorList;

class trigger {
  public:
    std::string nameTrig;
    int numSensor;
    SensorList trigger;

    void setName(std::string nameIn)
    {
        strcpVega(this->nameTrig, nameIn);
    };
    void makeTrigger()
    {
        trigger.resize(numSensor);
    };
};

class scintillator {
  public:
    std::string nameScint;
    int tag;
    int isData;
    int numSensor;
    int scintUP;
    int scintDN;
    double sensorLen;
    double sensorWid;
    double sensorHt;
    SensorList scintill;

    void setName(std::string nameIn)
    {
        strcpVega(this->nameScint, nameIn);
    };
    void makeScintill()
    {
        scintill.resize(numSensor);
    };
};

class RPCdet {
  public:
    std::string nameDET;
    int tag;
    int isData;
    int numStrips;
    SensorList stripLine;

    void setName(std::string nameIn)
    {
        strcpVega(this->nameDET, nameIn);
    };
    void makeStripLine()
    {
        stripLine.resize(numStrips);
    };
};
