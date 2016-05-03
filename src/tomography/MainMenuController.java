/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package tomography;

import java.io.*;
import java.lang.*;
import java.net.*;
import java.util.*;
import javafx.event.*;
import javafx.fxml.*;
import javafx.scene.control.*;
import javafx.scene.layout.*;

/**
 * FXML Controller class
 *
 * @author vega
 */
public class MainMenuController implements Initializable {

    @FXML
    private BorderPane rootPane;
    @FXML
    private Button rootsetParam;
    @FXML
    private Button rootVisualData;
    @FXML
    private Button rootTomography;
    @FXML
    private Button rootQuit;
    
    private Tomography myGUI;
    public void setMainApp(Tomography myGUI) {
        this.myGUI = myGUI;
    }
    
    
    

    /**
     * Initializes the controller class.
     */
    @Override
    public void initialize(URL url, ResourceBundle rb) {
        // TODO
    }    

    @FXML
    private void exit2System(ActionEvent event) {
        System.exit(0);
    }

    @FXML
    private void setParam(ActionEvent event)  throws IOException{
        myGUI.callSetup();
    }

    @FXML
    private void dataVis(ActionEvent event) {
        myGUI.VisData();
    }

    @FXML
    private void runTomo(ActionEvent event) {           
        myGUI.callRunTomo();
    }
    
}
