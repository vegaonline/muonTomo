/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package tomography;

import java.io.*;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.application.*;
import javafx.fxml.*;
import javafx.scene.*;
import javafx.scene.layout.*;
import javafx.stage.*;

/**
 *
 * @author vega
 */
public class Tomography extends Application {
    private Stage primaryStage;
    private BorderPane rootLayout;
    private Scene rootScene;
    private String rootDataFileName = null;
    private String tomoExecFileName = null;
    
    @Override
    public void start(Stage primaryStage) throws Exception {
        primaryStage.setTitle("MUON TOMOGRAPHY :: Abhijit Bhattacharyya");
        FXMLLoader loader = new FXMLLoader(Tomography.class.getResource("mainMenu.fxml"));
        rootLayout = (BorderPane) loader.load();
        rootLayout.autosize();
        rootScene = new Scene(rootLayout);        
        primaryStage.setScene(rootScene);
        MainMenuController controller = loader.getController();
        controller.setMainApp(this);
        primaryStage.show();
    }

    public void callSetup() {
        try {
            //FXMLLoader loader = new FXMLLoader(getClass().getResource("setParameter.fxml"));
            FXMLLoader loader = new FXMLLoader(Tomography.class.getResource("setParameter.fxml"));
            AnchorPane setupPage = (AnchorPane) loader.load();
            rootLayout.setCenter(setupPage);
            rootLayout.autosize();
            //SetParameterController controller = loader.<SetParameterController>getController();
            SetParameterController controller = loader.getController();
            controller.setMainApp(this);
            controller.setMyStage(primaryStage);
            //controller.initData(tomoExecFileName, rootDataFileName);
            //System.out.println("rootdata "+rootDataFileName);
        } catch (IOException ex) {
            System.out.println(" Problem in loading Setup Page...");
            Logger.getLogger(Tomography.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    public void VisData() {
         try {
            FXMLLoader loader = new FXMLLoader(Tomography.class.getResource("dataVis.fxml"));
            AnchorPane dataVisPage = (AnchorPane) loader.load();
            rootLayout.setCenter(dataVisPage);
            rootLayout.autosize();
        } catch (IOException ex) {
            System.out.println(" Problem in loading Data Visualization  Page...");
            Logger.getLogger(Tomography.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    
    public void callRunTomo() {
        try {
            //FXMLLoader loader = new FXMLLoader(getClass().getResource("setParameter.fxml"));
            FXMLLoader loader = new FXMLLoader(Tomography.class.getResource("runTOMO.fxml"));
            AnchorPane runTOMOPage = (AnchorPane) loader.load();
            rootLayout.setCenter(runTOMOPage);
            rootLayout.autosize();
            //SetParameterController controller = loader.<SetParameterController>getController();
            RunTOMOController controller = loader.getController();
            controller.setMainApp(this);
            controller.setMyStage(primaryStage);
            //controller.initData(tomoExecFileName, rootDataFileName);
            //System.out.println("rootdata "+rootDataFileName);
            System.out.println("Run TOMO ");
        } catch (IOException ex) {
            System.out.println(" Problem in loading Setup Page...");
            Logger.getLogger(Tomography.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        launch(args);
    }
    
}
