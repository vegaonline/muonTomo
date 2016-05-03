/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package tomography;

/**
 *
 * @author vega
 */
public class Detector {
    private double dim1;
    private double dim2;
    private double dim3;
    private double posX;
    private double posY;
    private double posZ;
    
    private int detTag; // Tag of each detector slab
    private int nStripsperDet; // number of strips per detector
    private double delXstrip; // spacing between two strips in a slab
    
    private final double halfDim1 = 0.5 * dim1;
    private final double halfDim2 = 0.5 * dim2;
    private final double halfDim3 = 0.5 * dim3;
    
    private Vector3D origin;
    private final Vector3D u = new Vector3D(dim1,   posY, posZ);
    private final Vector3D v  = new Vector3D(posX, dim2, posZ);
    private final Vector3D w   = new Vector3D(posX, posY, dim3);    
    private double tolerance;
    
    
    
}
