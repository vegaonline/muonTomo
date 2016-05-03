/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package tomography;

import java.io.*;
import java.net.URL;
import java.util.ResourceBundle;
import java.util.logging.*;
import javafx.beans.value.*;
import javafx.event.ActionEvent;
import javafx.fxml.*;
import javafx.scene.control.*;
import javafx.scene.image.*;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.AnchorPane;
import javafx.stage.*;

/**
 * FXML Controller class
 *
 * @author vega
 */
public class SetParameterController implements Initializable {

    int maxItem2Edit = 20;
    int isEdit = maxItem2Edit; // total number units
    int isTrapez = 0;
    int isRect = 0;
    private String lenUnit = null;
    private String enUnit = null;
    private String detShape = null;
    private double detSide1 = 0.0, detSide2 = 0.0, detSide3 = 0.0, detSide4 = 0.0;
    private int segTrapezeNum = 0;
    private double gapSegment = 0.0;
    private int numStripsPerSeg = 0;
    private double gapStrips = 0.0;
    private int numDetAbove = 0, numDetBelow = 0;    
    private double objLen = 0.0, objWid = 0.0, objHt = 0.0;
    private double htObjLowDet = 0.0;
    private double detGap0 = 0.0;
    private double detGap1 = 0.0;
    private String imgVal1 = null;
    private String imgVal2 = null;    
    private String dataFName = null;
    private String configFName = null;
    private int TDCNum = 0;
    private int activeTDCNum = 0;
    
    private int isSaved = 0;

    private final ToggleGroup group = new ToggleGroup();
    /*
    private final Image image1 = new Image(getClass().getResourceAsStream(
            "/home/vega/NetBeansProjects/MuonTomography/src/muontomography/rectDET.png"
    ));
    private final Image image2 = new Image(getClass().getResourceAsStream(
            "/home/vega/NetBeansProjects/MuonTomography/src/muontomography/trapezDET.png"
    ));
     */
    @FXML
    private AnchorPane setParamAnchor;
    @FXML
    private RadioButton shapeRect;
    @FXML
    private RadioButton shapeTrapez;
    @FXML
    private TextField setParamdetSideA;
    @FXML
    private TextField setParamdetSideB;
    @FXML
    private TextField setParamdetSideC;
    @FXML
    private TextField setParamdetSideD;
    @FXML
    private TextField setParamdetsegNum;
    @FXML
    private TextField setParamdetstripNum;
    @FXML
    private TextField setParamdetstripGap;
    @FXML
    private ComboBox<String> setParamLenUnit;
    @FXML
    private ComboBox<String> setParamEnergyUnit;
    @FXML
    private TextField setParamdetsegGap;
    @FXML
    private Button setParamReset;
    @FXML
    private Button setParamSave;
    @FXML
    private Button setParamLoad;
    @FXML
    private TextField setParamdetstripNumUP;
    private TextField setParamdetVertGap;
    @FXML
    private TextField setParamdetstripNumDN;
    @FXML
    private TextField setParamObjLen;
    @FXML
    private TextField setParamObjwid;
    @FXML
    private TextField setParamObjHt;
    @FXML
    private TextField setParamObjLowDet;
    @FXML
    private ImageView detImage;
    @FXML
    private Label trapSegLab;
    @FXML
    private Label gapSegLab;
    @FXML
    private TextField dataFileName;
    @FXML
    private Button acceptParam;
    @FXML
    private TextField setParamdetGap0;
    @FXML
    private TextField setParamdetGap1;
    @FXML
    private ImageView detImage1;
    @FXML
    private ImageView detImage2;
    @FXML
    private TextField setParamTDCNum;
    @FXML
    private TextField setParamTDCActiveNum;    
    
    private Tomography myGUI;        

    public void setMainApp(Tomography myGUI) {
        this.myGUI = myGUI;
    }

    private Stage myStage;

    public void setMyStage(Stage myStage) {
        this.myStage = myStage;
    }

    /**
     * Initializes the controller class.
     */
    @Override
    public void initialize(URL url, ResourceBundle rb) {
        detImage1 = new ImageView();
        detImage2 = new ImageView();
        //detImage.setPreserveRatio(true);
        detImage1.setLayoutX(280);
        detImage1.setLayoutY(280);
        detImage1.setScaleX(0.5);
        detImage1.setScaleY(0.5);

        detImage2.setLayoutX(420);
        detImage2.setLayoutY(280);
        detImage2.setScaleX(0.5);
        detImage2.setScaleY(0.5);        
        

        shapeRect.setToggleGroup(group);
        shapeTrapez.setToggleGroup(group);
        shapeTrapez.setSelected(true);
        shapeRect.setUserData("rectDET");
        shapeTrapez.setUserData("trapezDET");

        group.selectedToggleProperty().addListener(new ChangeListener<Toggle>() {
            public void changed(ObservableValue<? extends Toggle> ov,
                    Toggle old_toggle, Toggle new_toggle) {
                imgVal1 = group.getSelectedToggle().getUserData().toString() + ".png";

                if (group.getSelectedToggle() != null) {
                    final Image image1 = new Image(
                            getClass().getResourceAsStream(imgVal1)
                    );
                    detImage1.setImage(image1);
                    final Image image2 = new Image(
                            getClass().getResourceAsStream("series.png"));
                    detImage2.setImage(image2);
                }
            }
        });
        setParamAnchor.getChildren().addAll(detImage1, detImage2);
        setParamLenUnit.getItems().setAll("cms", "mm");
        setParamLenUnit.setValue("cms");
        setParamEnergyUnit.getItems().setAll("eV", "MeV", "GeV");
        setParamEnergyUnit.setValue("MeV");
        // TODO
    }

    private void setupParam() {
        lenUnit = setParamLenUnit.getValue();
        isEdit--; 
        enUnit = setParamEnergyUnit.getValue();
        isEdit--; 
        
        detShape = imgVal1;
        if (detShape.contains("rectDET") == true) {
            isRect = 1; isTrapez = 0;
        } else if (detShape.contains("trapezDET") == true) {
            isRect = 0; isTrapez = 1;
        }
        if (setParamdetSideA.getText() != null) {
            detSide1 = Double.parseDouble(setParamdetSideA.getText());
            if (isRect == 1) {
                setParamdetSideC.setText(setParamdetSideA.getText());
            }
            isEdit--; 
        }
        if (setParamdetSideB.getText() != null) {
            detSide2 = Double.parseDouble(setParamdetSideB.getText());
            if (isRect == 1) {
                setParamdetSideD.setText(setParamdetSideB.getText());
            }
            isEdit--; 
        }
        if (setParamdetSideC.getText() != null) {
            detSide3 = Double.parseDouble(setParamdetSideC.getText());
            isEdit--; 
        }
        if (setParamdetSideD.getText() != null) {
            detSide4 = Double.parseDouble(setParamdetSideD.getText());
            isEdit--; 
        }
        if (isTrapez == 1) {
            segTrapezeNum = Integer.parseInt(setParamdetsegNum.getText());
            isEdit--; 
            gapSegment = Double.parseDouble(setParamdetsegGap.getText());
            isEdit--; 
        } else {
            setParamdetsegNum.setVisible(false);
            setParamdetsegGap.setVisible(false);
            trapSegLab.setVisible(false);
            gapSegLab.setVisible(false);
            segTrapezeNum = 0;
            isEdit--; 
            gapSegment = 0.0;
            isEdit--; 
        }
        numStripsPerSeg = Integer.parseInt(setParamdetstripNum.getText());
        isEdit--; 
        gapStrips = Double.parseDouble(setParamdetstripGap.getText());
        isEdit--; 
        numDetAbove = Integer.parseInt(setParamdetstripNumUP.getText());
        isEdit--; 
        numDetBelow = Integer.parseInt(setParamdetstripNumDN.getText());
        isEdit--; 
        objLen = Double.parseDouble(setParamObjLen.getText());
        isEdit--; 
        objWid = Double.parseDouble(setParamObjwid.getText());
        isEdit--;
        objHt = Double.parseDouble(setParamObjHt.getText());
        isEdit--;
        htObjLowDet = Double.parseDouble(setParamObjLowDet.getText());
        isEdit--;
        detGap0 = Double.parseDouble(setParamdetGap0.getText());
        isEdit--;
        detGap1 = Double.parseDouble(setParamdetGap1.getText());
        isEdit--;
        TDCNum = Integer.parseInt(setParamTDCNum.getText());
        isEdit--;
        activeTDCNum = Integer.parseInt(setParamTDCActiveNum.getText());
        isEdit--;
    }

    private void resetIt() {
        lenUnit = null;
        enUnit = null;
        setParamdetSideA.clear();
        setParamdetSideB.clear();
        setParamdetSideC.clear();
        setParamdetSideD.clear();
        segTrapezeNum = 0;
        setParamdetsegNum.clear();
        gapSegment = 0;
        setParamdetsegGap.clear();
        numStripsPerSeg = 0;
        setParamdetstripNum.clear();
        gapStrips = 0.0;
        setParamdetstripGap.clear();
        numDetAbove = 0;
        setParamdetstripNumUP.clear();
        numDetBelow = 0;
        setParamdetstripNumDN.clear();
        objLen = 0.0;
        setParamObjLen.clear();
        objWid = 0.0;
        setParamObjwid.clear();
        objHt = 0.0;
        setParamObjHt.clear();
        htObjLowDet = 0.0;
        setParamObjLowDet.clear();
        dataFileName.clear();
        setParamdetGap0.clear();
        detGap0 = 0.0;
        setParamdetGap1.clear();
        detGap1 = 0.0;        
        setParamTDCNum.clear();
        TDCNum = 0;
        setParamTDCActiveNum.clear();
        activeTDCNum = 0;
        isEdit = maxItem2Edit;
    }

    @FXML
    private void doReset(ActionEvent event) {
        resetIt();
    }

    @FXML
    private void doSaveParam(ActionEvent event) {
        while (isEdit != 0) {
            setupParam();  // Accept Values finally just before saving
        }
        FileChooser filechooser = new FileChooser();
        File recordsDir = new File("data");
        if (!recordsDir.exists()) {
            recordsDir.mkdirs();
        }
        filechooser.setInitialDirectory(recordsDir);

        // Set extension filter
        FileChooser.ExtensionFilter extFilter
                = new FileChooser.ExtensionFilter("Tomography (CONFIG) files (*.tom)", "*.tom");
        filechooser.getExtensionFilters().add(extFilter);
        filechooser.setTitle("Save the Configuration for the Muon Tomography");
        configFName = filechooser.showSaveDialog(myStage).getPath();
        File file = new File(configFName);
        try (FileWriter fw = new FileWriter(file)) {
            fw.write(detShape);
            fw.write("\n");
            fw.write(lenUnit);
            fw.write("\n");
            fw.write(enUnit);
            fw.write("\n");
            fw.write(String.valueOf(detSide1));
            fw.write("\n");
            fw.write(String.valueOf(detSide2));
            fw.write("\n");
            fw.write(String.valueOf(detSide3));
            fw.write("\n");
            fw.write(String.valueOf(detSide4));
            fw.write("\n");
            fw.write(Integer.toString(segTrapezeNum));
            fw.write("\n");
            fw.write(String.valueOf(gapSegment));
            fw.write("\n");
            fw.write(Integer.toString(numStripsPerSeg));
            fw.write("\n");
            fw.write(String.valueOf(gapStrips));
            fw.write("\n");
            fw.write(Integer.toString(numDetAbove));
            fw.write("\n");
            fw.write(Integer.toString(numDetBelow));
            fw.write("\n");
            fw.write(String.valueOf(objLen));
            fw.write("\n");
            fw.write(String.valueOf(objWid));
            fw.write("\n");
            fw.write(String.valueOf(objHt));
            fw.write("\n");
            fw.write(String.valueOf(htObjLowDet));
            fw.write("\n");
            fw.write (String.valueOf (detGap0));
            fw.write("\n");
            fw.write (String.valueOf (detGap1));
            fw.write("\n");
            fw.write(String.valueOf(TDCNum));
            fw.write("\n");
            fw.write(String.valueOf(activeTDCNum));
            fw.write("\n");
            fw.write(dataFName);
            fw.write("\n");            
            isSaved = 1;
            fw.close();
        } catch (IOException ex) {
            Logger.getLogger(SetParameterController.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    @FXML
    private void doLoadOld(ActionEvent event) {
        resetIt();
        FileChooser filechooser = new FileChooser();

        //File recordsDir = new File(System.getProperty("user.home"), "data");
        File recordsDir = new File("data");
        if (!recordsDir.exists()) {
            recordsDir.mkdirs();
        }

        filechooser.setInitialDirectory(recordsDir);

// Set extension filter
        FileChooser.ExtensionFilter extFilter
                = new FileChooser.ExtensionFilter("Tomography (CONFIG) files (*.tom)", "*.tom");
        filechooser.getExtensionFilters().add(extFilter);

        filechooser.setTitle("Save the Configuration for the Muon Tomography");
        File file = filechooser.showOpenDialog(myStage);
        configFName = file.getPath();
        try (BufferedReader reader = new BufferedReader(new FileReader(configFName))) {
            detShape = reader.readLine ();
            if (detShape.contains("rectDET") == true) {
                shapeRect.setSelected(true);
            } else if (detShape.contains("trapezeDET")) {
                shapeTrapez.setSelected(true);
            }

            lenUnit = reader.readLine();                        
            setParamLenUnit.setValue(lenUnit);
            enUnit = reader.readLine ();
            setParamEnergyUnit.setValue(enUnit);
            detSide1 = Double.parseDouble (reader.readLine ());
            setParamdetSideA.setText(String.valueOf(detSide1));
            detSide2 = Double.parseDouble (reader.readLine ());
            setParamdetSideB.setText(String.valueOf(detSide1));
            detSide3 = Double.parseDouble (reader.readLine ());
            setParamdetSideC.setText(String.valueOf(detSide3));
            detSide4 = Double.parseDouble (reader.readLine ());
            setParamdetSideD.setText(String.valueOf(detSide4));
            segTrapezeNum = Integer.parseInt (reader.readLine ());
            setParamdetsegNum.setText(String.valueOf(segTrapezeNum));
            gapSegment = Double.parseDouble (reader.readLine ());
            setParamdetsegGap.setText(String.valueOf(gapSegment));
            numStripsPerSeg = Integer.parseInt (reader.readLine ());
            setParamdetstripNum.setText(String.valueOf(gapSegment));
            gapStrips = Double.parseDouble (reader.readLine ());
            setParamdetstripGap.setText(String.valueOf(numStripsPerSeg));
            numDetAbove = Integer.parseInt (reader.readLine ());
            setParamdetstripNumUP.setText(String.valueOf(numDetAbove));
            numDetBelow = Integer.parseInt (reader.readLine ());
            setParamdetstripNumDN.setText(String.valueOf(numDetBelow));
            objLen = Double.parseDouble (reader.readLine ());
            setParamObjLen.setText(String.valueOf(objLen));
            objWid = Double.parseDouble (reader.readLine ());
            setParamObjwid.setText(String.valueOf(objHt));
            objHt = Double.parseDouble (reader.readLine ());
            setParamObjHt.setText(String.valueOf(objHt));
            htObjLowDet = Double.parseDouble (reader.readLine ());
            setParamObjLowDet.setText(String.valueOf(htObjLowDet));
            detGap0 = Double.parseDouble (reader.readLine ());
            setParamdetGap0.setText (String.valueOf (detGap0));
            detGap1 = Double.parseDouble (reader.readLine ());
            setParamdetGap1.setText (String.valueOf (detGap1));    
            TDCNum = Integer.parseInt(reader.readLine());
            setParamTDCNum.setText(String.valueOf(TDCNum));
            activeTDCNum = Integer.parseInt(reader.readLine());
            setParamTDCActiveNum.setText(String.valueOf(activeTDCNum));
            dataFName = reader.readLine ();
            dataFileName.setText(dataFName);     
            reader.close ();
        } catch (Exception e) {
            System.out.println("There was an error to read ");
        }
    }

    @FXML
    private void getDataFileName(MouseEvent event) {
        String fnames;

        FileChooser filechooser = new FileChooser();
        //File recordsDir = new File(System.getProperty("user.home"), "data");
        File recordsDir = new File("data");
        if (!recordsDir.exists()) {
            recordsDir.mkdirs();
        }
        filechooser.setInitialDirectory(recordsDir);
// Set extension filter
        FileChooser.ExtensionFilter extFilter
                = new FileChooser.ExtensionFilter("Tomography (CONFIG) files (*.root)", "*.root");
        filechooser.getExtensionFilters().add(extFilter);
        filechooser.setTitle("Select the ROOT file");
        fnames = filechooser.showOpenDialog(myStage).getPath();
        dataFileName.setText(fnames);
        dataFName = fnames;
    }

    /*  check for the injection method Google Guice etc..
    void initData(String dFName, String cFName) {
        dFName = this.dataFName;
        cFName = this.configFName;
    }
     */
    @FXML
    private void doAccept(ActionEvent event) {
        if (isSaved == 0) {
            return;
        }
        String setFileDetails = "myConf.tmp";
        File file = new File(setFileDetails);
        try (FileWriter fw = new FileWriter(file)) {
            fw.write(configFName);
            fw.write("\n");
            fw.write(dataFName);
            fw.write("\n");
            fw.close();

        } catch (IOException ex) {
            Logger.getLogger(SetParameterController.class
                    .getName()).log(Level.SEVERE, null, ex);
        }
    }

}
