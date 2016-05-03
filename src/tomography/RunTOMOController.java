/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package tomography;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.net.*;
import java.util.*;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.fxml.*;
import javafx.scene.control.*;
import javafx.scene.input.*;
import javafx.scene.layout.*;
import javafx.stage.*;

/**
 * FXML Controller class
 *
 * @author vega
 */
public class RunTOMOController implements Initializable {
    
    String nameConfig = null;
    String nameData = null;
    
    @FXML
    private AnchorPane runTomoBase;
    @FXML
    private TextField tomoExecFile;
    @FXML
    private TextField execDataFile;
    @FXML
    private AnchorPane TomoImage;
    
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
        // TODO
    }
    
    void doRun() {
        try {
            Process p = null;
            String myCom = "CC/muonTomography.e";
            String arg1 =nameConfig;
            String arg2 = nameData;
            ProcessBuilder pb = new ProcessBuilder(myCom, arg1, arg2);
            File log = new File("log");
            pb.redirectErrorStream(true);
            pb.redirectOutput(ProcessBuilder.Redirect.appendTo(log));
            pb.start();
            assert pb.redirectOutput().file() == log;
        } catch (IOException ex) {
            Logger.getLogger(MainMenuController.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    @FXML
    private void selTomoExecFile(MouseEvent event) throws ClassNotFoundException {
        String setFileDetails = "myConf.tmp";
        File file = new File(setFileDetails);
        ObjectInputStream configStream = null;
        try {
            configStream = new ObjectInputStream(new FileInputStream(file));
        } catch (IOException e) {
            System.out.println("Could not open the file");
            System.exit(0);
        }
        try {
            try {
                nameConfig = (String) configStream.readObject();
            } catch (ClassNotFoundException ex) {
                Logger.getLogger(RunTOMOController.class.getName()).log(Level.SEVERE, null, ex);
            }
            tomoExecFile.setText(nameConfig);
            nameData = (String) configStream.readObject();
            execDataFile.setText(nameData);
            configStream.close();
            
        } catch (IOException e){
            System.out.println("Writing error: " + e);
            System.exit(0);
        }
        doRun();
    }
}
