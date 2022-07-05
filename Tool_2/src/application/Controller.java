package application;

import java.io.File;
import java.io.IOException;
import java.util.Scanner;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.BorderPane;
import javafx.stage.FileChooser;
import javafx.stage.Stage;

public class Controller {
	
	// **Declare static Stage**  
	private static Stage secondaryStage = new Stage(); 
	static public Stage getSecondaryStage() {return Controller.secondaryStage;}
	
	@FXML
	public Button EM_Btn;
	public BorderPane img;
	public ImageView iv = new ImageView(new Image("bg.png"));
	public FileChooser FC = new FileChooser();
	
	
	public void initialize() {
    	img.setCenter(iv);
	}
	public void EM(ActionEvent e) throws IOException  {
		ChoiceDialog<String> choice = new ChoiceDialog<String>("Generate Manifest","Generate Manifest","Modify Manifest");
		choice.setTitle("Execution Manifest");
		choice.setContentText("Operation: ");
		choice.setHeaderText("Select Operation");
		choice.showAndWait();
		if(choice.resultProperty().getValue()==null)return;
		if(choice.resultProperty().getValue().equals("Generate Manifest")) {
			Image icon = new Image("icon.png");
			secondaryStage.getIcons().add(icon);
			secondaryStage.setResizable(false);
			ExecutionCTR.mode=0;
			Parent root = FXMLLoader.load(getClass().getResource("Execution.fxml")); 
			Scene scene = new Scene(root);
			secondaryStage.setScene(scene);
			secondaryStage.setTitle("Execution Manifest Generator");
			secondaryStage.setScene(scene);
			Main.getPrimaryStage().close();
			secondaryStage.showAndWait();
			Main.getPrimaryStage().show();
		}
		else if (choice.resultProperty().getValue().equals("Modify Manifest")) {
			Node JSONTree;
			String Data = new String();
			FC.setTitle("Load JSON File");
			FC.getExtensionFilters().clear();
			FC.getExtensionFilters().add(new FileChooser.ExtensionFilter("JSON File","*.JSON"));	
			File myObj = FC.showOpenDialog(Main.getPrimaryStage());
			if(myObj!=null) {
			    Scanner myReader = new Scanner(myObj);
			    while (myReader.hasNextLine()) Data += myReader.nextLine()+'\n';
			    myReader.close();
		    	JSONTree = Node.JSONToTree(Data);
			    if(JSONTree==null) {
					Alert alert = new Alert(AlertType.ERROR,"Please Load Consistent JSON File",ButtonType.CLOSE);
					alert.setHeaderText("JSON FILE INCONSISTENT!");
					alert.showAndWait();
					return;
				}
			    Image icon = new Image("icon.png");
				secondaryStage.getIcons().add(icon);
				secondaryStage.setResizable(false);
				ExecutionCTR.mode=1;
				ExecutionCTR.path=myObj.getPath();
				GUI res = Node.TreeToGUI(JSONTree);
				if(res==null) {
					Alert alert = new Alert(AlertType.ERROR,"JSON Loaded Is Not Execution Manifest!",ButtonType.CLOSE);
					alert.setHeaderText("FILE NOT EXECUTION MANIFEST!");
					alert.showAndWait();
					return;
				}
				ExecutionCTR.process_list=res.process_list;
				ExecutionCTR.process_name=res.process_name;
				ExecutionCTR.manifest_id = res.manifest_id;
				
				Parent root = FXMLLoader.load(getClass().getResource("Execution.fxml")); 
				Scene scene = new Scene(root);
				secondaryStage.setScene(scene);
				secondaryStage.setTitle("Execution Manifest Modify");
				secondaryStage.setScene(scene);
				Main.getPrimaryStage().close();
				secondaryStage.showAndWait();
				Main.getPrimaryStage().show();
			}
		}
	}
	public void MM(ActionEvent e) throws IOException  {
		ChoiceDialog<String> choice = new ChoiceDialog<String>("Generate Manifest","Generate Manifest","Modify Manifest");
		choice.setTitle("Machine Manifest");
		choice.setContentText("Operation: ");
		choice.setHeaderText("Select Operation");
		choice.showAndWait();
		if(choice.resultProperty().getValue()==null)return;
		if(choice.resultProperty().getValue().equals("Generate Manifest")) {
			Image icon = new Image("icon.png");
			secondaryStage.getIcons().add(icon);
			secondaryStage.setResizable(false);
			MachineCTR.mode=0;
			Parent root = FXMLLoader.load(getClass().getResource("Machine.fxml")); 
			Scene scene = new Scene(root);
			secondaryStage.setScene(scene);
			secondaryStage.setTitle("Machine Manifest Generator");
			secondaryStage.setScene(scene);
			Main.getPrimaryStage().close();
			secondaryStage.showAndWait();
			Main.getPrimaryStage().show();
		}
		else if (choice.resultProperty().getValue().equals("Modify Manifest")) {
			/*Node JSONTree;
			String Data = new String();
			FC.setTitle("Load JSON File");
			FC.getExtensionFilters().clear();
			FC.getExtensionFilters().add(new FileChooser.ExtensionFilter("JSON File","*.JSON"));	
			File myObj = FC.showOpenDialog(Main.getPrimaryStage());
			if(myObj!=null) {
			    Scanner myReader = new Scanner(myObj);
			    while (myReader.hasNextLine()) Data += myReader.nextLine()+'\n';
			    myReader.close();
		    	JSONTree = Node.JSONToTree(Data);
			    if(JSONTree==null) {
					Alert alert = new Alert(AlertType.ERROR,"Please Load Consistent JSON File",ButtonType.CLOSE);
					alert.setHeaderText("JSON FILE INCONSISTENT!");
					alert.showAndWait();
					return;
				}
			    Image icon = new Image("icon.png");
				secondaryStage.getIcons().add(icon);
				secondaryStage.setResizable(false);
				ExecutionCTR.mode=1;
				ExecutionCTR.path=myObj.getPath();
				GUI res = Node.TreeToGUI(JSONTree);
				ExecutionCTR.process_list=res.process_list;
				ExecutionCTR.process_name=res.process_name;
				ExecutionCTR.manifest_id = res.manifest_id;
				
				Parent root = FXMLLoader.load(getClass().getResource("Execution.fxml")); 
				Scene scene = new Scene(root);
				secondaryStage.setScene(scene);
				secondaryStage.setTitle("Execution Manifest Modify");
				secondaryStage.setScene(scene);
				Main.getPrimaryStage().close();
				secondaryStage.showAndWait();
				Main.getPrimaryStage().show();
			}*/
		}
	}

}

