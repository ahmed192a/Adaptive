package application;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
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
			    ArrayList<Node> r = new ArrayList<>();
				r.add(JSONTree);
				Dialog<String> dialog = new Dialog<>();
				dialog.getDialogPane().getButtonTypes().addAll(ButtonType.CLOSE);
				dialog.getDialogPane().setContent(new TextArea(Node.TreeToJSON("",r, 0)));
				dialog.setResizable(true);
				dialog.setTitle("JSON");
				dialog.showAndWait();
			    //transform the file and show it with generate
			}
		}
	}
}
/*{
	"Execution_manifest": {
		"Execution_manifest_id": "exec_id",
		"Process": [
		    {
		        "Process_name": "process1",
		        "Mode_dependent_startup_configs": [
		            {
		                "Startup_options": [
		                    {
		                        "Option_kind": "commandLineShortForm",
		                        "Option_name": "EM_test_process",
		                        "Option_arg": "inputfile_1"
		                    }
		                ],
		                "FunctionGroupDependencies": [
		                    {
		                        "Function_group": "FG_1",
		                         "Modes": "Running,On"
		                    }
		                ]
		            }
		        ]
		        
		    }
		]
	}
}*/
