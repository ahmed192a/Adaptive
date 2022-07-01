package application;

import java.io.IOException;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.BorderPane;
import javafx.stage.Stage;

public class Controller {
	
	// **Declare static Stage**  
	private static Stage secondaryStage = new Stage(); 
	static public Stage getSecondaryStage() {return Controller.secondaryStage;}
	
	@FXML
	public Button Gen_EM_Btn;
	public BorderPane img;
	public ImageView iv = new ImageView(new Image("bg.png"));

	public void initialize() {
    	img.setCenter(iv);
	}
	public void Gen_EM(ActionEvent e) throws IOException  {
		Image icon = new Image("icon.png");
		secondaryStage.getIcons().add(icon);
		secondaryStage.setResizable(false);
		Parent root = FXMLLoader.load(getClass().getResource("Execution.fxml")); 
		Scene scene = new Scene(root);
		secondaryStage.setScene(scene);
		//scene.getStylesheets().add(getClass().getResource("application.css").toExternalForm());
		secondaryStage.setTitle("Execution Manifest Generator");
		secondaryStage.setScene(scene);
		Main.getPrimaryStage().close();
		secondaryStage.showAndWait();
		Main.getPrimaryStage().show();
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
