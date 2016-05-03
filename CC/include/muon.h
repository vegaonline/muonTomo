#ifndef MUON_H
#define MUON_H

class track {
  public:
    line3D trackLine;
    double theta, phi;
};
typedef std::vector<track> trackSet;

class voxel {
  public:
    std::string eventID;
    unsigned int serialNum;
    point3D dRVoxel;
    point3D origin;
    double thetaVoxel, phiVoxel;
};
typedef std::vector<voxel> VoxelList;

class muon {
  public:
    std::string eventID;
    unsigned int serialNum;
    unsigned int numMuons;
    unsigned numVoxel;
    trackSet muonTracks;
    VoxelList memberOfVoxel;
    void makeTracks()
    {
        muonTracks.resize(numMuons);
    };
    void makeVoxels()
    {
        memberOfVoxel.resize(numVoxel);
    };
};
typedef std::vector<muon> muonGroup;

#endif /* MUON_H */