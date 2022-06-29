package application;

import java.io.IOException;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.stage.Stage;

public class Controller {
	
	// **Declare static Stage**  
	private static Stage secondaryStage = new Stage(); 
	private void setSecondaryStage(Stage stage) {Controller.secondaryStage = stage;}
	static public Stage getPrimaryStage() {return Controller.secondaryStage;}
	
	@FXML
	public Button Gen_EM_Btn;

	public void initialize() throws IOException {
		Parent root = FXMLLoader.load(getClass().getResource("Execution.fxml")); 
		Scene scene = new Scene(root);
		secondaryStage.setScene(scene);
		//scene.getStylesheets().add(getClass().getResource("application.css").toExternalForm());
		secondaryStage.setTitle("Execution Manifest Generator");
		secondaryStage.setScene(scene);
	}
	public void Gen_EM(ActionEvent e) {
		secondaryStage.show();
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
                "ExecutionDependencies": [
                    {
                        "Process_name": "Proc_2",
                        "Mode": [
                            {"Mode":"Running"},
                            {"Mode":"on"}

                        ]
                    }
                ],
                "FunctionGroupDependencies": [
                    {
                        "Function_group": "FG_1",
                        "Mode": "on"
                    }
                ]
            }
        ]
        
    }
]
}
}*/